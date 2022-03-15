
#include <string>
#define CRZ_INFO    0x21B
// BO_ 539 CRZ_INFO: 8 XXX
//  SQ_ ERROR : 0|8@0+ (1,0) [0|255] "" XXX
//  SG_ NEW_SIGNAL_1 : 15|11@0+ (1,0) [0|16383] "" XXX
//  SG_ BRAKE_ALLOWED : 16|1@1+ (1,0) [0|3] "" XXX
//  SG_ GAS_ALLOWED : 17|1@0+ (1,0) [0|63] "" XXX
//  SG_ ACCEL_CMD : 31|11@0- (1,1) [0|1] "" XXX
//  SG_ ACC_ACTIVE : 33|1@0+ (1,0) [0|1] "" XXX
//  SG_ ACC_SET_ALLOWED : 34|1@0+ (1,0) [0|1] "" XXX
//  SG_ CRZ_ENDED : 36|1@0+ (1,0) [0|255] "" XXX
//  SG_ NEW_SIGNAL_7 : 47|8@0+ (1,0) [0|255] "" XXX
//  SG_ CTR1 : 55|8@0+ (1,0) [0|255] "" XXX
//  SG_ CHKSUM : 63|8@0+ (1,0) [0|255] "" XXX
#define CRZ_EVENTS  0x21F
// BO_ 543 CRZ_EVENTS: 8 XXXsignalData_t crz_info_obj;
//  SG_ CRZ_SPEED : 7|16@0+ (0.005,-0.5) [0|328] "kph" XXX
//  SG_ CRUISE_ACTIVE_CAR_MOVING : 16|1@0+ (1,0) [0|1] "" XXX
//  SG_ PLUS_ONE_CRZ : 17|1@0+ (1,0) [0|255] "" XXX
//  SG_ GAS_MAYBE : 22|1@0+ (1,0) [0|1] "" XXX
//  SG_ NEW_SIGNAL_21 : 23|1@0+ (1,0) [0|15] "" XXX
//  SG_ ACCEL_CMD_LOW_RES : 29|8@0- (1,0) [0|255] "" XXX
//  SG_ ACCEL_CMD : 47|11@0- (1,0) [0|15] "" XXX
//  SG_ CTR : 51|4@0+ (1,0) [0|15] "" XXX
//  SG_ CHKSUM : 63|8@0+ (1,0) [0|15] "" XXX
#define CRZ_BTN     0x9D
// BO_ 157 CRZ_BTNS: 8 XXX
//  SG_ BIT1 : 16|1@0+ (1,0) [0|1] "" XXX
//  SG_ BIT2 : 18|1@0+ (1,0) [0|1] "" XXX
//  SG_ BIT3 : 20|1@0+ (1,0) [0|1] "" XXX
//  SG_ SET_P_INV : 21|1@0+ (1,0) [0|1] "" XXX
//  SG_ CAN_OFF_INV : 17|1@0+ (1,0) [0|1] "" XXX
//  SG_ CAN_OFF : 0|1@0+ (1,0) [0|1] "" XXX
//  SG_ SET_M_INV : 22|1@0+ (1,0) [0|1] "" XXX
//  SG_ SET_M : 5|1@0+ (1,0) [0|1] "" XXX
//  SG_ SET_P : 4|1@0+ (1,0) [0|1] "" XXX
//  SG_ RES_INV : 19|1@0+ (1,0) [0|1] "" XXX
//  SG_ RES : 2|1@0+ (1,0) [0|1] "" XXX
//  SG_ DISTANCE_LESS : 7|1@0+ (1,0) [0|1] "" XXX
//  SG_ DISTANCE_LESS_INV : 8|1@0+ (1,0) [0|1] "" XXX
//  SG_ DISTANCE_MORE : 6|1@0+ (1,0) [0|1] "" XXX
//  SG_ DISTANCE_MORE_INV : 23|1@0+ (1,0) [0|1] "" XXX
//  SG_ MODE_Y : 13|1@0+ (1,0) [0|1] "" XXX
//  SG_ MODE_X : 14|1@0+ (1,0) [0|1] "" XXX
//  SG_ MODE_Y_INV : 30|1@0+ (1,0) [0|1] "" XXX
//  SG_ MODE_X_INV : 31|1@0+ (1,0) [0|1] "" XXX
//  SG_ CTR : 29|4@0+ (1,0) [0|15] "" XXX
#define CRZ_CTRL    0x21C
// BO_ 540 CRZ_CTRL: 8 XXX
//  SG_ NEW_SIGNAL_6 : 10|1@0+ (1,0) [0|1] "" XXX
//  SG_ NEW_SIGNAL_9 : 31|1@0+ (1,0) [0|255] "" XXX
//  SG_ ACC_GAS_MAYBE2 : 29|1@0+ (1,0) [0|1] "" XXX
//  SG_ HANDS_OFF_STEERING : 48|1@0+ (1,0) [0|1] "" XXX
//  SG_ HANDS_ON_STEER_WARN : 59|4@0+ (1,0) [0|255] "" XXX
//  SG_ CRZ_ACTIVE : 3|1@0+ (1,0) [0|1] "" XXX
//  SG_ CRZ_AVAILABLE : 17|1@0+ (1,0) [0|255] "" XXX
//  SG_ DISTANCE_SETTING : 20|3@0+ (1,0) [0|7] "" XXX
//  SG_ MSG_1_INV : 1|1@0+ (1,0) [0|1] "" XXX
//  SG_ MSG_1 : 0|1@0+ (1,0) [0|3] "" XXX
//  SG_ MSG_1_COPY : 9|1@0+ (1,0) [0|1] "" XXX
//  SG_ MSG_1_INV_COPY : 8|1@0+ (1,0) [0|7] "" XXX
//  SG_ ACC_GAS_MAYBE : 23|1@0+ (1,0) [0|31] "" XXX
//  SG_ ACC_ACTIVE : 52|1@0+ (1,0) [0|1] "" XXX
//  SG_ 5_SECOND_TIMER : 45|3@0+ (1,0) [0|7] "" XXX
////////////////////////////////////////////////////////////////////////////////
#define OP_CMD      0x2FF
typedef struct SignalData_t{
    uint64_t* values;
    uint64_t* masks;
    std::string* signals;
    uint8_t size;
    uint64_t mask_all;
}SignalData_t;

// Generated from dbc discriptions

//CRZ_INFO
uint64_t ERROR = 0;
uint64_t CTR1 = 0;
uint64_t ACC_ACTIVE = 0;
uint64_t CHKSUM = 0; 
uint64_t NEW_SIGNAL_1 = 0; 
uint64_t BRAKE_ALLOWED =0; 
uint64_t GAS_ALLOWED = 0; 
uint64_t NEW_SIGNAL_7 = 0; 
uint64_t CRZ_ENDED = 0; 
uint64_t ACC_SET_ALLOWED = 0; 
uint64_t ACCEL_CMD = 0;
//CRZ_EVENTS
uint64_t MSG_1 = 0;
uint64_t MSG_1_INV = 0;
uint64_t CRZ_ACTIVE = 0;
uint64_t MSG_1_INV_COPY = 0;
uint64_t MSG_1_COPY = 0;
uint64_t NEW_SIGNAL_6 = 0;
uint64_t NEW_SIGNAL_3 = 0;
uint64_t CRZ_AVAILABLE = 0;
uint64_t DISTANCE_SETTING = 0;
uint64_t ACC_GAS_MAYBE = 0;
uint64_t ACC_GAS_MAYBE2 = 0;
uint64_t NEW_SIGNAL_10 = 0;
uint64_t NEW_SIGNAL_9 = 0;
uint64_t TIMER_5_SECONDS = 0;
uint64_t HANDS_OFF_STEERING = 0;
uint64_t ACC_ACTIVE_2 = 0;
uint64_t HANDS_ON_STEER_WARN = 0;

std::string crz_info_signals[] = 
  {"ERROR",
   "NEW_SIGNAL_1", 
   "BRAKE_ALLOWED", 
   "GAS_ALLOWED", 
   "ACCEL_CMD", 
   "ACC_ACTIVE", 
   "ACC_SET_ALLOWED", 
   "CRZ_ENDED", 
   "NEW_SIGNAL_7", 
   "CTR1", 
   "CHKSUM"};

uint64_t crz_info_values[] = 
   {ERROR,
    NEW_SIGNAL_1, 
    BRAKE_ALLOWED, 
    GAS_ALLOWED,
    ACCEL_CMD,
    ACC_ACTIVE,
    ACC_SET_ALLOWED,
    CRZ_ENDED,
    NEW_SIGNAL_7,
    CTR1,
    CHKSUM};

uint64_t crz_info_masks[sizeof(crz_info_signals) / sizeof(crz_info_signals[0])] = 
  {0xFFULL,         // ERROR
   0xE0FF00ULL,     // NEW_SIGNAL_1
   0x1ULL << 16,    // BRAKE_ALLOWED
   0x1ULL << 17,    // GAS_ALLOWED
   0xE0FFULL << 24, // ACCEL_CMD
   0x1ULL << 33,    // ACC_ACTIVE
   0x1ULL << 34,    // ACC_SET_ALLOWED
   0x1ULL << 36,    // CRZ_ENDED
   0xFFULL << 40,   // NEW_SIGNAL_7
   0xFFULL << 48,   // CTR1
   0xFFULL << 56};  // CHKSUM

uint64_t crz_info_masks_2d[2)][sizeof(crz_info_signals) / sizeof(crz_info_signals[0]] = 
  {{0xFFULL, 0},         // ERROR
   {0xE0FF00ULL, 0},     // NEW_SIGNAL_1
   {0x1ULL, 16},    // BRAKE_ALLOWED
   {0x1ULL, 17},    // GAS_ALLOWED
   {0xE0FFULL,  24}, // ACCEL_CMD
   {0x1ULL, 33},    // ACC_ACTIVE
   {0x1ULL, 34},    // ACC_SET_ALLOWED
   {0x1ULL, 36},    // CRZ_ENDED
   {0xFFULL, 40},   // NEW_SIGNAL_7
   {0xFFULL, 48},   // CTR1
   {0xFFULL, 56}};  // CHKSUM
if Map bit 31 is  = 63-31+7 = 39
int sizeInBits = sizeof(mask) * BITS_PER_BYTE; // BITS_PER_BYTE = 8;
mask = (param >= sizeInBits ? -1 : (1 <<  param) - 1);

std::string crz_events_signals[] = 
  {"ERROR",
   "NEW_SIGNAL_1", 
   "BRAKE_ALLOWED", 
   "GAS_ALLOWED", 
   "ACCEL_CMD", 
   "ACC_ACTIVE", 
   "ACC_SET_ALLOWED", 
   "CRZ_ENDED", 
   "NEW_SIGNAL_7", 
   "CTR1", 
   "CHKSUM"};

uint64_t crz_events_values[] = 
   {ERROR,
    NEW_SIGNAL_1, 
    BRAKE_ALLOWED, 
    GAS_ALLOWED,
    ACCEL_CMD,
    ACC_ACTIVE,
    ACC_SET_ALLOWED,
    CRZ_ENDED,
    NEW_SIGNAL_7,
    CTR1,
    CHKSUM};

uint64_t crz_events_masks[sizeof(crz_events_signals) / sizeof(crz_events_signals[0])] = 
  {0xFFULL,         // ERROR
   0xE0FF00ULL,     // NEW_SIGNAL_1
   0x1ULL << 16,    // BRAKE_ALLOWED
   0x1ULL << 17,    // GAS_ALLOWED
   0xE0FFULL << 24, // ACCEL_CMD
   0x1ULL << 33,    // ACC_ACTIVE
   0x1ULL << 34,    // ACC_SET_ALLOWED
   0x1ULL << 36,    // CRZ_ENDED
   0xFFULL << 40,   // NEW_SIGNAL_7
   0xFFULL << 48,   // CTR1
   0xFFULL << 56};  // CHKSUM

std::string crz_btn_signals[] = 
  {"ERROR",
   "NEW_SIGNAL_1", 
   "BRAKE_ALLOWED", 
   "GAS_ALLOWED", 
   "ACCEL_CMD", 
   "ACC_ACTIVE", 
   "ACC_SET_ALLOWED", 
   "CRZ_ENDED", 
   "NEW_SIGNAL_7", 
   "CTR1", 
   "CHKSUM"};

uint64_t crz_btn_values[] = 
   {ERROR,
    NEW_SIGNAL_1, 
    BRAKE_ALLOWED, 
    GAS_ALLOWED,
    ACCEL_CMD,
    ACC_ACTIVE,
    ACC_SET_ALLOWED,
    CRZ_ENDED,
    NEW_SIGNAL_7,
    CTR1,
    CHKSUM};

uint64_t crz_btn_masks[sizeof(crz_btn_signals) / sizeof(crz_btn_signals[0])] = 
  {0xFFULL,         // ERROR
   0xE0FF00ULL,     // NEW_SIGNAL_1
   0x1ULL << 16,    // BRAKE_ALLOWED
   0x1ULL << 17,    // GAS_ALLOWED
   0xE0FFULL << 24, // ACCEL_CMD
   0x1ULL << 33,    // ACC_ACTIVE
   0x1ULL << 34,    // ACC_SET_ALLOWED
   0x1ULL << 36,    // CRZ_ENDED
   0xFFULL << 40,   // NEW_SIGNAL_7
   0xFFULL << 48,   // CTR1
   0xFFULL << 56};  // CHKSUM

std::string crz_ctrl_signals[] = 
  {"MSG_1",
   "MSG_1_INV", 
   "CRZ_ACTIVE", 
   "MSG_1_INV_COPY", 
   "MSG_1_COPY",
   "NEW_SIGNAL_6", 
   "NEW_SIGNAL_3", 
   "CRZ_AVAILABLE", 
   "DISTANCE_SETTING", 
   "ACC_GAS_MAYBE", 
   "ACC_GAS_MAYBE2", 
   "NEW_SIGNAL_10",
   "NEW_SIGNAL_9",
   "TIMER_5_SECONDS",
   "HANDS_OFF_STEERING",
   "ACC_ACTIVE_2",
   "HANDS_ON_STEER_WARN"};

uint64_t crz_ctrl_values[] = 
    {MSG_1,
     MSG_1_INV, 
     CRZ_ACTIVE, 
     MSG_1_INV_COPY, 
     MSG_1_COPY,
     NEW_SIGNAL_6, 
     NEW_SIGNAL_3, 
     CRZ_AVAILABLE, 
     DISTANCE_SETTING, 
     ACC_GAS_MAYBE, 
     ACC_GAS_MAYBE2, 
     NEW_SIGNAL_10,
     NEW_SIGNAL_9,
     TIMER_5_SECONDS,
     HANDS_OFF_STEERING,
     ACC_ACTIVE_2,
     HANDS_ON_STEER_WARN};

uint64_t crz_ctrl_masks[sizeof(crz_ctrl_signals) / sizeof(crz_ctrl_signals[0])] = 
  {0x01ULL,              // MSG_1
   0x01ULL << 1,         // MSG_1_INV
   0x01ULL << 3,         // CRZ_ACTIVE
   0x01ULL << 8,         // MSG_1_INV_COPY
   0x01ULL << 9,         // MSG_1_COPY
   0x01ULL << 10,        // NEW_SIGNAL_6
   0x03ULL << 14,        // NEW_SIGNAL_3
   0x01ULL << 17,        // CRZ_AVAILABLE
   0x07ULL << 20,        // DISTANCE_SETTING
   0x01ULL << 23,        // ACC_GAS_MAYBE
   0x01ULL << 29,        // ACC_GAS_MAYBE2
   0x01ULL << 30,        // NEW_SIGNAL_10
   0x01ULL << 31,        // NEW_SIGNAL_9
   0x07ULL << 45,        // TIMER_5_SECONDS
   0x01ULL << 48,        // HANDS_OFF_STEERING
   0x01ULL << 52,        // ACC_ACTIVE_2
   0x0FULL << 49};       // HANDS_ON_STEER_WARN








