#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t keep_going = 1;

// ADC bit-shift 
uint16_t lowbyte;
uint16_t highbyte;
uint16_t finalvalue;

void loop()
{

    _delay_ms(50);
    
    ADCSRA |= (1<<ADEN);         // Start Data aquisition

    while(!(ADCSRA & (1<<ADIF))); // Loop until ADC complete

    // 10 1110 1101
    lowbyte = ADCL;    // 0000 0000 1110 1101
    highbyte = ADCH;   // 0000 0000 0000 0010

    finalvalue = (highbyte << 8) | lowbyte;

    if (finalvalue < 85)
    {
        PORTD &= ~(1<<PD1) & ~(1<<PD2);
        PORTD |= (1<<PD0);
    }
    else if(finalvalue >= 170)
    {
        PORTD &= ~(1<<PD0) & ~(1<< PD1);
        PORTD |= (1<<PD2);
    }
    else
    {
        PORTD &= ~(1<<PD0) & ~(1<< PD2);
        PORTD |= (1<<PD1);
    }
}

void setup()
{
    
    // PortD-Pin1 setup
    DDRD |= (1<<PD0) | (1<<PD1) | (1<<PD2);   //set DATADIRECTIOND to say pin d is an output pin
    //PORTD &= ~(1<<PD0); // start pin as 0

    DDRC &= ~(1<<PC4); // Set PC4 (ADC4) to input direction

    ADMUX |= (1<<REFS0) | (1<<MUX2); //Chosing ref source & input ch

}

int main(int argc, char const *argv[])
{
    setup();
    while(keep_going) loop();
    return 0;
}