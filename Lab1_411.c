#include "xc_configuration_bits.h"
#include "delays.h"

unsigned char read_switches_S1(void);
void illuminate_LEDs_L1(unsigned char pattern);
void illuminate_U1();

void main (void)
{    
    int y = read_switches_S1();
    illuminate_LEDs_L1(y); 
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

void illuminate_LEDs_L1(unsigned char pattern)
{
    TRISA = 0xEF;
    PORTA = 0xFF;
    
    TRISF = 0x00;
    
    LATF = pattern;
}