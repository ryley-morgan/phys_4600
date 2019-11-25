#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//uint8_t keep_going = 1;

// ADC bit-shift 
uint16_t lowbyte;
uint16_t highbyte;
uint16_t finalvalue;

//Adding interupt functions - Called everytime Timer0 overflows
ISR(TIMER0_OVF_vect)
{
    //PORTD ^= (1<<PD1);   // Bitwise XOR (flip state)
    //PORTD &= ~(1 << PD6);
}

ISR(TIMER0_COMPA_vect)
{
    //PORTD |= (1 << PD6);
}

void loop()
{
    
}

void setup()
{
    /*
    // PortD-Pin1 setup
    //DDRD |= (1<<PD1);   //set DATADIRECTIOND to say pin d is an output pin
    //PORTD &= ~(1<<PD1); // start pin as 0

    //TCCR0B = 0x01;   //TimerControlRegister0 set to operate in normal counting mode with no scaling (see data sheet)

// PortD-Pin6 setup (COM0)
    DDRD |= (1<<PD6) | (1<<PD5);   //set DATADIRECTIOND to say pin d is an output pin
    
    PORTD &= ~(1<<PD6); // start pin as 0

    //TCCR0B = 0x01;   //TimerControlRegister0 set to operate in normal counting mode with no scaling (see data sheet)

    // Timer setup
    TCCR0A |= (1<<COM0A0) | (1<<COM0A1) | (1<<COM0B0) | (1<<COM0B1);
    TCCR0A |= (1<<WGM01) | (1<<WGM00);
    TCCR0B |= (1<<CS00);
    
    //TIMSK0 = 1;
    //TIMSK0 |= (1<<OCIE0A)|(1<<TOIE0);

    OCR0A = 100; // Number to compare
    OCR0B = 50;

    sei();  // Start looking for timer interupts
    */
}

int main(int argc, char const *argv[])
{
    //setup();
    //while(keep_going) loop();
    ADMUX |= (1 << REFS0) | (1<< MUX0); //Chosing ref source & input ch
    ADCSRA |= (1<<ADEN);         // Start Data aquisition

    while(! ADCSRA & (1<<ADIF)); // Loop until ADC complete

    // 10 1110 1101
    lowbyte = ADCL;    // 0000 0000 1110 1101
    highbyte = ADCH;   // 0000 0000 0000 0010

    finalvalue = (highbyte << 8) | lowbyte;
 
    return 0;
}