#include "xc_configuration_bits.h"
#include "delays.h"

void switch_on_U1();
void display_on_U1(unsigned int display_val);

void main (void)
{    
    switch_on_U1();
    display_on_U1(0x64);
    
}
void display_on_U1(unsigned int display_val)
{
    TRISF = 0x00;
    LATF = display_val;
}

void switch_on_U1()
{
    TRISH = 0xFE;
    LATH = 0x00;
}

