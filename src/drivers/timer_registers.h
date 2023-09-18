/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <inttypes.h>

template<typename T>
struct TimerRegister;

template<>
struct TimerRegister<uint8_t>
{
    volatile uint8_t controlA;
    volatile uint8_t controlB;
    volatile uint8_t counter;
    volatile uint8_t compareA;
    volatile uint8_t compareB;
};

template<>
struct TimerRegister<uint16_t>
{
    volatile uint8_t controlA;
    volatile uint8_t controlB;
    volatile uint8_t controlC;
    volatile uint8_t reserved;
    volatile uint16_t counter;
    volatile uint16_t compareA;
    volatile uint16_t compareB;
};