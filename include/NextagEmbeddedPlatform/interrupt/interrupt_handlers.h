/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>

ISR(TIMER0_COMPA_vect)
{
    interruptRegistry.timer0CompareMatchA();
}

ISR(TIMER0_COMPB_vect)
{
    interruptRegistry.timer0CompareMatchB();
}
