#include "xc_configuration_bits.h"
#include "delays.h"

unsigned char read_witches_S1(void);
void illuminate_LEDs_L1(unsigned char pattern);
void switch_off_U1(void);
void switch_on_U1(void);
void display_on_U1(unsigned int display_val);
void switch_off_U2(void);
void switch_on_U2(void);
void display_on_U2(unsigned int display_val);
unsigned char PB1_pressed(void);

void main (void){
    char data = 0;
                    //configuration of the I/o
    TRISF = 0x00;   //all bits of Port F as outputs
                    //main program loop
    
    TRISA = 0xEF;
    PORTA = 0xFF; //patch by other student
    
    while (1){
        for(int i = 0; i<5; i++)
        {
            LATF = data;
            Delay10KTCYx(25);
            LATF = 0x00;
            Delay10KTCYx(25);
        }
        data = data + 1;
    }
    
}

void switch_on_U1(void)
{
    LATH = 0x01;
}

void switch_on_U1(void)
{
    LATH = 0x02;
}

void switch_off_U2(void)
{
    LATH = 0x00;
}

void switch_off_U1(void)
{
    LATH = 0x00;
}


unsigned char PB1_pressed(void)
{
    if(PORTJ == 0x20)
        return 0;
    else 
        return 1;
}

