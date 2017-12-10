#include "xc_configuration_bits.h"
#include "delays.h"

unsigned char read_switches_S1(void);
void switch_on_U1();
void switch_off_U1();
void display_on_U1(unsigned int display_val);

void main (void)
{   
    int patterns[4] = {0x84, 0xF5, 0x4C, 0x64}; 
    int switch_bank = read_switches_S1();
    
    switch(switch_bank){
        case 1: 
            switch_on_U1();
            display_on_U1(patterns[0]); 
            break;
        case 2:
            switch_on_U1();
            display_on_U1(patterns[1]);
            break;
        case 4: 
            switch_on_U1();
            display_on_U1(patterns[2]); 
            break;
        case 8:
            switch_on_U1();
            display_on_U1(patterns[3]); 
            break;
        default:
            switch_off_U1();
            
    }
  
}

unsigned char read_switches_S1(void)
{
    int x =  PORTC;
    
    x >> 2;
    
    if (PORTC == 0)
    {
        return 0;
    }
    else
    {   
    
        if (x > 15 && x <= 31)
            x = x-16;
        else if (x > 31 && x <= 63)
            x = x-32;
        else if (x > 63)
            x = x-48;
    }
    
    return x;
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

void switch_off_U1()
{
    TRISH = 0xFE;
    LATH = 0x01;
}

