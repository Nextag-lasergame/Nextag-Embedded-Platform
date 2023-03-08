#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB = 0xFF;

    for (;;)
    {
        PORTB = ~PORTB;
        _delay_ms(1000);
    }
}