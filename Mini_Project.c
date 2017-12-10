#include "xc_configuration_bits.h"
#include "delays.h"
#include "adc.h"


void setup_Time(); //used to setup the time at the beginning
void show_on_U1(int low_value);
void show_on_U2(int high_value);
void show_on_LED(int value);
unsigned char PB1_pressed();
void minimum_delay();
unsigned int get_ADC_value(void);
void configure_ADC(void);

int second;        //current seconds
int minute;        //current minutes
int hour;          //current hours
int day;           //current day
int month;         //current month
int year;          //current year

int ssd_symbols[] = {0x84, 0xF5, 0x4C, 0x64, 0x35, 0x26, 0x06, 0xF4, 0x04, 0x24, 0x14, 0x07, 0x8E, 0x45, 0x0E, 0x1E}; // all the hex symbols from the ssd



void main(void)
{
    configure_ADC();
    TRISF = 0x00;
    setup_Time();
}

//function used to setup the initial time when the program is started
void setup_Time()
{
    //Setting up the minutes
    while(!PB1_pressed())
    {    
        show_on_LED(2)
        minimum_delay();
        show_on_U2(0);
        minimum_delay();
        show_on_U1(0);
        minimum_delay();
        minute = get_ADC_value()*59/256;
    }
}

//function used to show a value on the LEDs and turn off U1 and U2
void show_on_LED(int value)
{
    TRISH = 0xFF;
    TRISA = 0xEF;
    PORTA = 0xFF;
    
    LATF = value;
}

//function used to show a value on U1 and turn off U2
void show_on_U1(int low_value)
{
    TRISH = 0xFE;  //set PORTH pin 1 as output
    LATH = 0xFE;   //Turn on transistor Q1
    LATF = ssd_symbols[low_value];   //Show symbol on display
}

//function used to show a value on U2 and turn off U1
void show_on_U2(int high_value)
{
    TRISH = 0xFD;
    LATH = 0xFD;
    LATF = ssd_symbols[high_value];
}


unsigned int get_ADC_value(void)
{
     ConvertADC();
        
     while(BusyADC())
     {;}
        
     return ReadADC()>>2;
}

unsigned char PB1_pressed(void)
{
   return (!PORTJbits.RJ5); 
}

unsigned char PB2_pressed(void)
{
   return (!PORTBbits.RB0); 
}

void minimum_delay()
{
    Delay10TCYx(2);
}

void configure_ADC(void)
{
     OpenADC(ADC_FOSC_16 & ADC_RIGHT_JUST & ADC_0_TAD, ADC_CH0 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, 0x0E);
}