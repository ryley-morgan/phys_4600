#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t keep_going = 1;

void loop()
{
    //PORTD |= 2; // Bitwise OR operation to change pin PD1 to high without affecting the rest of PORTD
    PORTD |= (1 << PD1);    // Bitwise OR operation using bit-shifting via macros specified in the header files
    _delay_ms(50);
    PORTD &= ~(1 << PD1);
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