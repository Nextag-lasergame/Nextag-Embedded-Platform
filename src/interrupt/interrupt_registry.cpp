/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/interrupt/interrupt_registry.h"

#include <avr/interrupt.h>
#include <avr/io.h>

namespace NextagEmbeddedPlatform::Interrupt
{

void InterruptRegistry::enableInterrupt(Interrupt interrupt)
{
    cli();

    switch (interrupt)
    {
    case Interrupt::TIMER0_COMPARE_A:
        TIMSK0 = TIMSK0 | _BV(OCIE0A);
        break;
    case Interrupt::TIMER0_COMPARE_B:
        TIMSK0 = TIMSK0 | _BV(OCIE0B);
        break;
    }

    sei();
}

} // namespace NextagEmbeddedPlatform::Interrupt

void onTimer0CompareMatchA() __attribute__((weak));
void onTimer0CompareMatchB() __attribute__((weak));

void onTimer0CompareMatchA()
{
}

void onTimer0CompareMatchB()
{
}

ISR(TIMER0_COMPA_vect)
{
    onTimer0CompareMatchA();
}

ISR(TIMER0_COMPB_vect)
{
    onTimer0CompareMatchB();
}