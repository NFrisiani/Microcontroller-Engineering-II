#include "xc_configuration_bits.h"
#include "delays.h"
#include "adc.h"

void enable_global_interrupts(void);
void isr (void);
void configure_PB2_interrupt(void);
void display_on_U1(unsigned char display_val);

void main (void) 
{
    unsigned int vpot;
    unsigned int maxval;
    TRISF = 0x00; // all bits of Port ?? as outputs
    LATF = 0xFF; // turn U1 and U2 off
    OpenADC(ADC_FOSC_16 & ADC_RIGHT_JUST & ADC_0_TAD, ADC_CH0 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, 0x0E);
    
    enable_global_interrupts();
    
    ConvertADC();

    while (1)
    {
        ;
    }
}

void enable_global_interrupts() 
{
    INTCONbits.PEIE = 1; // peripheral interrupt enable
    INTCONbits.GIE = 1; // global interrupt enable
}

void isr (void)
{
    PIR1bits.ADIF = 0; // clear ADC interrupt flag
    display_on_U1(); // read and display AD sample
    ConvertADC();
}

void configure_PB2_interrupt(void)
{
    
}
