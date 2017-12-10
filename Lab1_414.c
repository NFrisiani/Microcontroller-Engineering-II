#include "xc_configuration_bits.h"
#include "delays.h"

int which_display = 0;
unsigned char read_switches_S1(void);
unsigned char PB1_pressed(void);
void switch_on_U1();
void switch_off_U1();
void display_on_U1(unsigned int display_val);
void switch_on_U2();
void switch_off_U2();
void display_on_U2(unsigned int display_val);

void main (void)
{   
    int patterns[4] = {0x84, 0xF5, 0x4C, 0x64}; 
    int switch_bank = read_switches_S1();
    
    if (PB1_pressed() == 1)
        if (which_display == 0)
            which_display = 1;
        else
            which_display = 0;
    
    switch(switch_bank){
        case 1: 
            if (which_display == 0)
            {
                switch_off_U2();
                switch_on_U1();
                display_on_U1(patterns[0]); 
            }
            else 
            {
                switch_off_U1();
                switch_on_U2();
                display_on_U2(patterns[0]);
            }
            break;
            
        case 2:
            if (which_display == 0)
            {
                switch_off_U2();
                switch_on_U1();
                display_on_U1(patterns[1]); 
            }
            else 
            {
                switch_off_U1();
                switch_on_U2();
                display_on_U2(patterns[1]); 
            }
            break;
            
        case 4: 
            if (which_display == 0)
            {
                switch_off_U2();               
                switch_on_U1();
                display_on_U1(patterns[2]);
            }
            else 
            {
                switch_off_U1();
                switch_on_U2();
                display_on_U2(patterns[2]); 
            }
            break;
            
        case 8:
            if (which_display == 0)
            {
                switch_off_U2();                
                switch_on_U1();
                display_on_U1(patterns[3]); 
            }
            else 
            {
                switch_off_U1();               
                switch_on_U2();
                display_on_U2(patterns[3]); 
            }
            break;
        default:
            switch_off_U1();
            display_on_U2(0xFF);
    }
 
}

unsigned char read_switches_S1(void)
{
    TRISC = 0xFF;
    int x =  PORTC;
    
    x /= 4;
    
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
    LATH = 0xFE;
}

void switch_off_U1()
{
    TRISH = 0xFF;
}

void display_on_U2(unsigned int display_val)
{
    TRISF = 0x00;
    LATF = display_val;
}

void switch_on_U2()
{
    TRISH = 0xFD;
    LATH = 0xFD;
}

void switch_off_U2()
{
    TRISH = 0xFF;
}

unsigned char PB1_pressed(void)
{
   return (!PORTJbits.RJ5); 
}
