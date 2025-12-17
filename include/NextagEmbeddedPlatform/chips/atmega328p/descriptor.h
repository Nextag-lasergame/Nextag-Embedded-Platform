/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <avr/io.h>

namespace NextagEmbeddedPlatform
{

static auto consteval createCombinedRegisterValue(uint8_t lower, uint8_t higher) -> uint16_t
{
    uint16_t result = 0;
    result |= (static_cast<uint16_t>(higher) << 8) | lower;
    return result;
}

struct Atmega328pDescriptor
{
    struct Timer0
    {
        using DataType = uint8_t;

        static volatile uint8_t & controlA;
        static volatile uint8_t & controlB;
        static volatile uint16_t & controlAB;
        static volatile uint8_t & compareA;
        static volatile uint8_t & compareB;
        static volatile uint8_t & counter;
        static volatile uint8_t & interrupt;

        static constexpr uint16_t timerModeMask = createCombinedRegisterValue(_BV(WGM00) | _BV(WGM01), _BV(WGM02));
        enum class TimerMode
        {
            NORMAL = createCombinedRegisterValue(0, 0),
            PWM_PHASE_CORRECT = createCombinedRegisterValue(_BV(WGM00), 0),
            CTC = createCombinedRegisterValue(_BV(WGM01), 0),
            FAST_PWM = createCombinedRegisterValue(_BV(WGM01) | _BV(WGM00), 0),
            PWM_PHASE_CORRECT_COMPARE_A_TOP = createCombinedRegisterValue(_BV(WGM00), _BV(WGM02)),
            FAST_PWM_COMPARE_A_TOP = createCombinedRegisterValue(_BV(WGM00) | _BV(WGM01), _BV(WGM02)),
        };

        static constexpr uint8_t clockSelectMask = _BV(CS00) | _BV(CS01) | _BV(CS02);
        enum class ClockSelect
        {
            NO_CLOCK_SOURCE = 0,
            PRESCALER_1 = _BV(CS00),
            PRESCALER_8 = _BV(CS01),
            PRESCALER_64 = _BV(CS01) | _BV(CS00),
            PRESCALER_256 = _BV(CS02),
            PRESCALER_1024 = _BV(CS02) | _BV(CS00),
            EXTERNAL_SOURCE_FALLING_EDGE = _BV(CS02) | _BV(CS01),
            EXTERNAL_SOURCE_RISING_EDGE = _BV(CS02) | _BV(CS01) | _BV(CS00),
        };

        enum class Interrupt
        {
            COMPARE_A = _BV(OCIE0A),
            COMPARE_B = _BV(OCIE0B),
            OVERFLOW = _BV(TOIE0)
        };
    };
};

inline volatile uint8_t & Atmega328pDescriptor::Timer0::controlA = TCCR0A;
inline volatile uint8_t & Atmega328pDescriptor::Timer0::controlB = TCCR0B;
inline volatile uint16_t & Atmega328pDescriptor::Timer0::controlAB = reinterpret_cast<volatile uint16_t &>((TCCR0A));
inline volatile uint8_t & Atmega328pDescriptor::Timer0::compareA = OCR0A;
inline volatile uint8_t & Atmega328pDescriptor::Timer0::compareB = OCR0B;
inline volatile uint8_t & Atmega328pDescriptor::Timer0::counter = TCNT0;
inline volatile uint8_t & Atmega328pDescriptor::Timer0::interrupt = TIMSK0;

using ChipDescriptor = Atmega328pDescriptor;

} // namespace NextagEmbeddedPlatform