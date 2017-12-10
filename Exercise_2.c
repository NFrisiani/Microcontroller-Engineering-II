    #include "xc_configuration_bits.h"
    #include "delays.h"
    #include "pconfig.h"
    #include "adc.h"                                                            
    #include "stdint.h"
    #include "timers.h"

    #define time_const 0.2 //how many seconds?

    void configure_PB2_interrupt(void);
    void enable_global_interrupts(void);
    unsigned char PB2_pressed(void);
    unsigned char PB1_pressed(void);
    void interrupt isr(void);
    void switch_on_U1(void);
    void switch_off_U1(void);
    void display_on_U1(unsigned char val);
    void TMR0_isr(void);
    void ADC_isr(void);
    int counter = 0;
    int PB_counter = 0;
    int ssd_symbols[] = {0x84, 0xF5, 0x4C, 0x64, 0x35, 0x26, 0x06, 0xF4, 0x04, 0x24, 0x14, 0x07, 0x8E, 0x45, 0x0E, 0x1E};

    void main(void) 
    {
        ADCON1 = 0x0F; 
        TRISF = 0x00; 
        
        LATH = 0xFF; 
        TRISC = 0xFF; 
        
        
        OpenADC(ADC_FOSC_16 & ADC_0_TAD, ADC_CH0 & ADC_INT_ON & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, 0x0E);
        OpenTimer0 (TIMER_INT_ON & T0_SOURCE_INT & T0_16BIT & T0_PS_1_64);

        WriteTimer0(64755); //20ms 

        
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
    
    void interrupt isr (void) 
    {
        if(PB2_pressed()) 
           PB_counter++;
        
       if (PB1_pressed())
           PB_counter = 0;
        
       if (PB_counter != 0)
       {
            if (T0IF) 
            { 
                T0IF = 0;
                TMR0_isr();
            }
            else if (PIR1bits.ADIF) 
            { 
                PIR1bits.ADIF = 0;
                ADC_isr();
            }
       }
       else
           switch_off_U1();
    }
    
    void ADC_isr()
    {
        switch_on_U1();
        display_on_U1(ssd_symbols[(counter)]);
        counter++;
        
        if(counter == 16)
        {
            counter = 0;
        }
    }
    
    void TMR0_isr(void)
    {
        static unsigned char timer_counter = 0;
        WriteTimer0(64755);
        timer_counter++;
        if (timer_counter >= 50*time_const) 
        {
            timer_counter = 0;
            ConvertADC(); 
        }
    }
    
    void display_on_U1(unsigned char value)
    {
        LATF = value;
    }
    
    void switch_on_U1(void)
    {
        TRISA = 0xFF;
        TRISH = 0xFE;  //0xFD for U2
        LATH = 0xFE;   //0xFD for U2
    }
    
    void switch_off_U1(void)
    {
        TRISH = 0xFF;
    }
  
    unsigned char PB2_pressed(void) 
    {
        return (!PORTBbits.RB0);
    }
    
    unsigned char PB1_pressed(void) 
    {
        return (!PORTJbits.RJ5);
    }

