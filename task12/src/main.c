/*
File: main.c
Author: Ryley Morgan <ryley-morgan@github.com>

Count up on 8 bit binary LED's
*/
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 10000000

uint8_t keep_going = 1;
uint8_t data = 0;

void loop()
{
    _delay_ms(200);             // Delay 200 ms to see changes
    PORTB &= ~(1<<PB6);         // Set chip select low
    data++;                     // Increment the counter by 1 (rolls over at 256)
    SPDR = data;                // Set data register to value in data
    while(!(SPSR & (1<<SPIF))); // Wait for completetion of data register transfer to sn595 chip
    PORTB |= (1<<PB6);          // Set chip select high
}

void setup()
{
    // Outputs
    // Set Chip Select (PB6 out), MOSI(PB3 out), SCK(PB5 out), SS (PB2)
    DDRB |= (1<<PB6) | (1<<PB3) | (1<<PB5) | (1<<PB2);

    // Inputs
    // Set MISO(PB4 in)
    DDRB &= ~(1<<PB4);

    // Set SPI Control Registry (18.5.1)
    SPCR |= (1<<SPE) | (1<<MSTR) | (1<<CPOL);
    SPCR &= ~(1<<SPIE) & ~(1<<DORD) & ~(1<<CPHA);
}

int main(int argc, char const *argv[])
{
    setup();
    while(keep_going) loop();
    return 0;
}