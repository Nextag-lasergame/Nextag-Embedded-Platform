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
void onTimer1CompareMatchA() __attribute__((weak));


void onTimer0CompareMatchA()
{
    // We need this load intermediate to prevent compiler "optimization" where vectors call each other while pushing and popping every register.
    // In the end this results in a smaller binary
    __asm("push r31");
    __asm("ldi r31, 0xE");
    __asm("jmp __bad_interrupt");
    __asm("pop r31");
}

void onTimer0CompareMatchB()
{
    // We need this load intermediate to prevent vectors from calling eachother
    __asm("push r31");
    __asm("ldi r31, 0xF");
    __asm("jmp __bad_interrupt");
    __asm("pop r31");
}

void onTimer1CompareMatchA()
{
    // We need this load intermediate to prevent vectors from calling eachother
    __asm("push r31");
    __asm("ldi r31, 0xB");
    __asm("jmp __bad_interrupt");
    __asm("pop r31");
}

ISR(TIMER0_COMPA_vect)
{
    onTimer0CompareMatchA();
}

ISR(TIMER0_COMPB_vect)
{
    onTimer0CompareMatchB();
}

ISR(TIMER1_COMPA_vect)
{
    onTimer1CompareMatchA();
}