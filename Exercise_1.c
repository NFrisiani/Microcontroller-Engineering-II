    #include "xc_configuration_bits.h"
    #include "delays.h"
    #include "pconfig.h"
    #include "adc.h"                                                            
    #include "stdint.h"

    void configure_PB2_interrupt(void);
    void enable_global_interrupts(void);
    unsigned char PB2_pressed(void);
    void interrupt isr(void);
    unsigned char read_switches_S1(void);
    void illuminate_LEDs_L1(unsigned char val);

    void main(void) 
    {
        ADCON1 = 0x0F; 
        TRISF = 0x00; 
        
        LATH = 0xFF; 
        TRISC = 0xFF; 
        
        LATA = 0x10; 
        TRISA = 0xEF;
        
        
        OpenADC(ADC_FOSC_16 & ADC_0_TAD, ADC_CH0 & ADC_INT_ON & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, 0x0E);
        
        enable_global_interrupts();
        configure_PB2_interrupt();
        
        while(1)
            ;
    }

    void configure_PB2_interrupt(void) 
    {
        OpenRB0INT(PORTB_CHANGE_INT_ON & FALLING_EDGE_INT & PORTB_PULLUPS_OFF); 
    }
    
    void enable_global_interrupts(void) 
    {
        INTCON = 0xC0; 
    }

    unsigned char PB2_pressed(void) 
    {
        return (!PORTBbits.RB0);
    }
    
    void interrupt isr (void) 
    {
        unsigned char val = read_switches_S1();
        
        while (PB2_pressed()) 
        {
            illuminate_LEDs_L1(val);
        }
        
        LATF = 0x00; 
        INTCON = INTCON & 0xFE; 
    }

    unsigned char read_switches_S1() 
    {
        int x =  PORTC; 
        x = x >> 2;
        x = x&0x0F;
        return x;
    }
    
    void illuminate_LEDs_L1(unsigned char pattern)
    {
        TRISF = 0x00;
        LATF = pattern;
    }

