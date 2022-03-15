/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>

using namespace std;

uint64_t value;
uint64_t data;
uint64_t size = 11U; // size of the signal from dbc
uint64_t msb = 31;  // most sig bit of signal from dbc
uint8_t shift;

void doo(uint64_t data)
{
    // data = 0xF00000FFE000000F
    // mask =   000000FFE0000000
    cout << "  doo data  ";
    value = data & (0xFFEULL << shift);
    // value = FFE0000000
    value = value >> shift;
    // value = FFE
    cout << value;
    cout << "  ";
}

int main()
{
    uint8_t helper = 70;
    data = 0xF00000FFE000000F; 
    msb = helper-msb;
    shift = msb - size;
    doo(data);
    return(0);
}