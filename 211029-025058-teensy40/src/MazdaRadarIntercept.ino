#include <FlexCAN_T4.h>
#include "signal_defs.h"
#include "Arduino.h"
#include <iostream>
#include <map>
#include <iterator>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> radar;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> mazda;

CAN_message_t msg;
CAN_message_t crz_info_frame;
CAN_message_t crz_btn_frame;
CAN_message_t crz_ctrl_frame;
CAN_message_t crz_events_frame;

SignalData_t crzInfo;
SignalData_t crzEvents;
SignalData_t crzBtn;
SignalData_t crzCtrl;

std::map<std::string, std::pair<uint64_t, uint64_t> > Signal2MaskValueMap;

// Tester function.
// Put the test_frame array into the msg.buf and return the msg.
CAN_message_t test_frame_to_msg(uint8_t *test_frame)
{
  CAN_message_t msg;
  memcpy(msg.buf, test_frame, 8);
  return msg;
}

// Teester function. Might not be useful
// Turns the msg.buf from an array to an ULL.
// Now we don't have to iterate through the msg.buf array.
uint64_t get_data(CAN_message_t msg)
{
  uint64_t result = 0;
  memcpy(&result, msg.buf, sizeof(result));
  return result;
}

// Helper fuction.
// This function is used to get the signal value from the signal name using the Signal2MaskValueMap.
uint64_t get_val(const char *key)
{
  return(Signal2MaskValueMap.find(key)->second.second);
}
// Helper fuction.
// This function is used to set the signal value from the signal name using the Signal2MaskValueMap.

void set_val(const char *key, uint64_t val)
{
  Signal2MaskValueMap.find(key)->second.second = val;
}

/* Create a map of signal names to (masks, value) pairs.
 This will be used to map the signals to their corresponding mask and value.
 This function should be called in setup()
*/
void MakeSignalMap(SignalData_t *signal_dbc)
{
  Serial.println("Creating Signal Map");
  for (uint8_t i = 0; i < signal_dbc->size ; i++)
  {
    Signal2MaskValueMap[signal_dbc->signals[i]] = std::pair<uint64_t,uint64_t>(signal_dbc->masks[i], signal_dbc->values[i]);
  }
  //iterate through the map and print out the key and value pairs
  std::map<std::string, std::pair<uint64_t,uint64_t> >::iterator it = Signal2MaskValueMap.begin();
  while(it != Signal2MaskValueMap.end())
  {
    // Print the key
    Serial.print("SIGNAL: ");
    Serial.print(it->first.c_str());
    // Print the value pair
    Serial.print("  MASK = ");
    Serial.print(it->second.first, HEX);
    Serial.print("  VALUE = ");
    Serial.println(it->second.second, HEX);
    it++;
  }
  // use the find function to find the value pair for the key "ACCEL_CMD"
  //Serial.print("ACCEL_CMD MASK = ");
  //Serial.println(Uint2UintMap.find("ACCEL_CMD")->second.first, HEX);
  

  // OUTPUT: SIGNAL: ACCEL_CMD
  //         MASK = E0FF000000
  //         VALUE = 0
  //         SIGNAL: ERROR
  //         MASK = FF
  //         VALUE = 0
  //         SIGNAL: NEW_SIGNAL_1
  //         MASK = E0FF00
  //         VALUE = 0
  //         SIGNAL: BRAKE_ALLOWED
  //         MASK = 10000
  //         VALUE = 0
  //         SIGNAL: GAS_ALLOWED
  //         MASK = 20000
  //         VALUE = 0
  //         SIGNAL: ACC_ACTIVE
  //         MASK = 200000000
  //         VALUE = 0
  //         SIGNAL: ACC_SET_ALLOWED
  //         MASK = 400000000
  //         VALUE = 0
  //         SIGNAL: CRZ_ENDED
  //         MASK = 1000000000
  //         VALUE = 0
  //         SIGNAL: NEW_SIGNAL_7
  //         MASK = FF0000000000
  //         VALUE = 0
  //         SIGNAL: CTR1
  //         MASK = FF000000000000
  //         VALUE = 0
  //         SIGNAL: CHKSUM
  //         MASK = FF00000000000000
  //         VALUE = 0
  //         ACCEL_CMD MASK = E0FF000000
}


void setup() {
  Serial.begin(115200);
  Serial.println("Mazda Radar Interceptor");
  radar.begin();
  radar.setBaudRate(500000);
  radar.enableMBInterrupts();
  radar.onReceive(radarSniff);
  //radar.mailboxStatus();
  mazda.begin();
  mazda.setBaudRate(500000);
  mazda.enableMBInterrupts();
  mazda.onReceive(mazdaSniff);
  init();
  Serial.println("Setup complete");
  // Create a can message to test the code.
  uint8_t test_frame[8] = {0x01,0xFF,0xe3,0xFF,0xc0,0x80,0x0c,0xd1};
  crz_info_frame = test_frame_to_msg(test_frame);
  for (int i = 0; i < 8; i++){
    Serial.print(crz_info_frame.buf[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  // OUTPUT: 01 FF E3 FF C0 80 0C D1

  //Test the code one time to see if it works.

  // A list of all the signal objects that we are interested in.
  SignalData_t address_objects[] = {crzInfo, crzEvents, crzBtn, crzCtrl};

  // A list of all the signal frames that we are interested in.
  CAN_message_t address_frames[sizeof(address_objects)] = {crz_info_frame, crz_events_frame, crz_btn_frame, crz_ctrl_frame};
  for (uint16_t i = 0; i < sizeof(address_objects); i++)
  {
    GetValuesFromMsg(&address_objects[i],&address_frames[i]);
  }
  //CarState();
  ModifySignalValues();

  for (uint16_t i = 0; i < sizeof(address_objects); i++)
  {
    MergeSignalValues(&address_objects[i],&address_frames[i]);
  }

  //test_fcn();

}

void MergeSignalValues(SignalData_t *signal_dbc, CAN_message_t *msg)
{
  uint64_t frame = 0x0ULL;
  uint64_t data = 0x0ULL;
  memcpy(&data, msg->buf, sizeof(data));;
  for (int i = 0; i < signal_dbc->size; i++){
    frame |= Signal2MaskValueMap.find(signal_dbc->signals[i])->second.second;
  }
  // merge the modified frame with the original frame
  frame |= (~signal_dbc->mask_all & data);

  // once the signals are extracted and modified and merged, the message can be converted back to a CAN message.
  // convert the uint64_t frame to a an 8 byte array
  uint8_t* frame_array = (uint8_t*)&frame;
  memcpy(msg->buf, frame_array, sizeof(msg->buf));
}

/*
Given the SignalData_t object and the CAN_message_t message, 
put the values into the SignalData_t object according to the objects 
signals and masks using a map.
The map key is the signal name and the value is the mask and value pair.*/
void GetValuesFromMsg(SignalData_t *signal_dbc, CAN_message_t *msg)
{
  uint8_t size = signal_dbc->size;
  // make one mask for all the signals
  uint64_t mask_all = 0; // initialize to zero
  for (uint8_t i = 0; i < size; i++)
  {
    mask_all |= signal_dbc->masks[i];
  }
  // Get data from the crz_info message.
  uint64_t data = 0x0ULL;
  memcpy(&data, msg->buf, sizeof(data));
  // extract the signal from the data.
  // and put them into the map
  for (uint8_t i = 0; i < size; i++)
  {
    Signal2MaskValueMap.find(signal_dbc->signals[i])->second.second = data & (Signal2MaskValueMap.find(signal_dbc->signals[i])->second.first);
  }
}
// Given the SignalData_t object,
// modify the values in the SignalData_t object according to ...
void ModifySignalValues()
{
  if (get_val("ACCEL_CMD") == 0)
  {
    set_val("ACCEL_CMD",get_val("ACCEL_CMD"));
  }
}
void test_fcn()
{
  uint8_t size = sizeof(crz_info_signals)/sizeof(crz_info_signals[0]);
  // make one mask for all the signals
  uint64_t mask_all = 0; // initialize to zero
  for (uint8_t i = 0; i < size; i++)
  {
    mask_all |= crz_info_masks[i];
  }
  // Get data from the crz_info message.
  uint64_t data = get_data(crz_info_frame); // depricated
  // extract the signal from the data.
  
  for (uint8_t i = 0; i < size; i++)
  {
    Signal2MaskValueMap.find(crz_info_signals[i])->second.second = data & (Signal2MaskValueMap.find(crz_info_signals[i])->second.first);

  }
  // moddify the signals here
  // Example 1:
  Signal2MaskValueMap.find("ACCEL_CMD")->second.second = (0x8000ULL << 24);
  // Example 2:
  // The the value of a signalin an outgoing message to the value of an incomming message signal.
  // When we receive a acceleration command from openpilot we will just copy the value over because they will be the same format.
  // Signal2MaskValueMap.find("ACCEL_CMD")->second.second = Signal2MaskValueMap.find("OP_ACCEL_CMD")->second.second
  // merge all the signals together after they are modified
  // merge the original message with the modified message
  
  uint64_t frame = 0x0ULL;
  for (int i = 0; i < size; i++){
    frame |= Signal2MaskValueMap.find(crz_info_signals[i])->second.second;
  }
  // print the modifeid frame
  //Serial.print("frame: ");
  //Serial.println(frame, HEX);

  // OUTPUT: frame: D10C80C0FFE3FF01

  // print the mask all
  //Serial.print("mask_all: ");
  //Serial.println(mask_all, HEX);

  // OUTPUT: mask_all: FFFFFFF6FFE3FFFF
  
  // merge the modified frame with the original frame
  frame |= (~mask_all & data);
  // print the merged frame
  //Serial.print("frame: ");
  //Serial.println(frame, HEX);

  // OUTPUT: frame: D10C80C0FFE3FF01

  // once the signals are extracted and modified and merged, the message can be converted back to a CAN message.
  // convert the uint64_t frame to a an 8 byte array
  uint8_t* frame_array = (uint8_t*)&frame;
  
  
  memcpy(crz_info_frame.buf, frame_array, 8);
  // do a check sum on the message
  crz_info_frame.buf[7] = checksum(crz_info_frame.buf);
  //print crz_info.buf in hex with a for loop
  for (int i = 0; i < 8; i++)
  {
    Serial.print(crz_info_frame.buf[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // OUTPUT: 1 FF E3 FF C0 80 C D1
}

// not used for testing
void radarSniff(const CAN_message_t &msg)
{ //use the test_frame_to_msg function to convert the test_frame array to a CAN_message_t
  
  //use a for loop to print out the contents of the CAN_message_t msg.buf
  for (int i = 0; i < 8; i++)
  {
    Serial.print(msg.buf[i], HEX);
    Serial.print(" ");
  }
  //use a switch statement to select a struct to store the message data based on the msg  ID.
  switch(msg.id)
  {
    case CRZ_INFO:
      mazda.write(msg);
      break;
    case CRZ_EVENTS:
      mazda.write(msg);
      break;
    case CRZ_BTN:
      mazda.write(msg);
      break;
    case CRZ_CTRL:
      mazda.write(msg);
      break;
    default:
      mazda.write(msg);
      break;
  }
}
// not used for testing
void mazdaSniff(const CAN_message_t &msg)
{
  switch(msg.id)
  {
    case OP_CMD:
      //Serial.println("OP_CMD");
      break;
    default:
      radar.write(msg);
      break;
  }
}
// not used for testing
void loop() {
  // check for incoming messages
  radar.events();
  mazda.events();
  Serial.println("loop");
  //add a delay to allow the serial monitor to print out the messages
  delay(100);
}

void init(void) {
  
  // Create a map of the signal names and their corrisponding masks

  crzInfo.signals = crz_info_signals;
  crzInfo.masks = crz_info_masks;
  crzInfo.values = crz_info_values;
  crzInfo.size = sizeof(crz_info_signals) / sizeof(crz_info_signals[0]);
  for (uint8_t i = 0; i < crzInfo.size; i++)
  {
    crzInfo.mask_all |= crzInfo.masks[i];
  }  
  crzEvents.signals = crz_events_signals;
  crzEvents.masks = crz_events_masks;
  crzEvents.values = crz_events_values;
  crzEvents.size = sizeof(crz_events_signals) / sizeof(crz_events_signals[0]);
  for (uint8_t i = 0; i < crzEvents.size; i++)
  {
    crzEvents.mask_all |= crzEvents.masks[i];
  }
  crzBtn.signals = crz_btn_signals;
  crzBtn.masks = crz_btn_masks;
  crzBtn.values = crz_btn_values;
  crzBtn.size = sizeof(crz_btn_signals) / sizeof(crz_btn_signals[0]);
  for (uint8_t i = 0; i < crzBtn.size; i++)
  {
    crzBtn.mask_all |= crzBtn.masks[i];
  }
  crzCtrl.signals = crz_ctrl_signals;
  crzCtrl.masks = crz_ctrl_masks;
  crzCtrl.values = crz_ctrl_values;
  crzCtrl.size = sizeof(crz_ctrl_signals) / sizeof(crz_ctrl_signals[0]);
  for (uint8_t i = 0; i < crzCtrl.size; i++)
  {
    crzCtrl.mask_all |= crzCtrl.masks[i];
  }

  MakeSignalMap(&crzInfo);
  MakeSignalMap(&crzCtrl);
  MakeSignalMap(&crzEvents);
  MakeSignalMap(&crzBtn);
}

// Create a function that does a checksum on the message
// This function should take in a pointer to an array of bytes
// and a length of the array.
// The function should return the checksum of the message.
uint16_t checksum(uint8_t *data)
{
  uint16_t checksum = 0;
  for (int i = 0; i < 7; i++)
  {
    checksum += data[i];
  }
  checksum &= 0xFF;
  checksum = ~checksum;
  return checksum;
}
// given the most significant bit of the signal, and the size of the signal, return the (mask, shift) pair
uint64_t generate_shift_mask(uint8_t *msb uint8_t *lenth)
{
  uint8_t shift = 63-msb+7;
  int sizeInBits = sizeof(mask) * 8; // BITS_PER_BYTE = 8;
  mask = (lenth >= sizeInBits ? -1 : (1 <<  lenth) - 1);
  //make a pair of the mask and the shift and return it
  return (mask, shift);
