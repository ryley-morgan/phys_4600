#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t keep_going = 1;

/*
void loop()
{
    //PORTD |= 2; // Bitwise OR operation to change pin PD1 to high without affecting the rest of PORTD
    PORTD |= (1 << PD1);    // Bitwise OR operation using bit-shifting via macros specified in the header files
    _delay_ms(50);
    PORTD &= ~(1 << PD1);  // Bitwise OR operation to unset this pin
    _delay_ms(50);
}

void setup()
{

}

int main()
{
    setup();
    while(keep_going) loop();
 
    return 0;
}
*/

//Adding interupt functions - Called everytime Timer0 overflows
ISR(TIMER0_OVF_vect)
{
    PORTD ^= (1<<PD1);   //Bitwise xor
}

void setup()
{
    // PortD-Pin1 setup
    DDRD |= (1<<PD1);   //set DATADIRECTIOND to say pin d is an output pin
    PORTD &= ~(1<<PD1); // start pin as 0


}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}