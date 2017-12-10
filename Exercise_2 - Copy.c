#include "xc_configuration_bits.h"
#include "delays.h"
#include "adc.h"
#define F_high 100.0


void configure_ADC(void);
unsigned int get_ADC_value(void);
char U1_on(void);
char U2_on(void);
unsigned char bin2hex(unsigned int val);
void display_U1(int low_value);
void display_U2(int high_value);
int minimum_delay;
int ssd_symbols[] = {0x84, 0xF5, 0x4C, 0x64, 0x35, 0x26, 0x06, 0xF4, 0x04, 0x24, 0x14, 0x07, 0x8E, 0x45, 0x0E, 0x1E};


void main (void)
{
    TRISF = 0x00;
    unsigned char vpot;
    unsigned char vpot_high;
    unsigned char vpot_low;
    configure_ADC(); 
    
    minimum_delay = 1/F_high/0.0000004/1000;
    
    while(1)
    {   
        vpot = get_ADC_value()/4;
        
        vpot_high = (vpot & 0xF0) >> 4;
        vpot_low = (vpot & 0x0F);
        
        
        display_U1(bin2hex(vpot_low)); 
        
        Delay1KTCYx(minimum_delay);
        for (int i = 255; i >= vpot; i--)
            Delay10TCYx(40);
        
        display_U2(bin2hex(vpot_high)); 
        
        Delay1KTCYx(minimum_delay);
        for (int i = 255; i >= vpot; i--)
            Delay10TCYx(40);
        
    }
}

void configure_ADC(void)
{
     OpenADC(ADC_FOSC_16 & ADC_RIGHT_JUST & ADC_0_TAD, ADC_CH0 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, 0x0E);
}

unsigned int get_ADC_value(void)
{
     ConvertADC();
        
     while(BusyADC())
     {;}
        
     return ReadADC();
}

unsigned char bin2hex(unsigned int val)
{
    return ssd_symbols[val];
}

void display_U1(int low_value)
{
    TRISH = 0xFE;
    LATH = 0xFE;
    LATF = low_value;
}

void display_U2(int high_value)
{
    TRISH = 0xFD;
    LATH = 0xFD;
    LATF = high_value;
}