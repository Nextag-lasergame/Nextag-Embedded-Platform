/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/drivers/timer_clock.h"
#include "NextagEmbeddedPlatform/drivers/timer_mode.h"

#include <avr/io.h>

namespace NextagEmbeddedPlatform::Chips::Atmega328p
{

struct Timer0Specialization
{
    template<Drivers::TimerMode mode>
    [[nodiscard]] static constexpr auto getModeMaskControlA() -> uint8_t
    {
        static_assert(mode == Drivers::TimerMode::CTC);
        return _BV(WGM01);
    }

    template<Drivers::TimerClock clock>
    [[nodiscard]] static constexpr auto getClockSourceMask() -> uint8_t
    {
        static_assert(clock != Drivers::TimerClock::SYSTEM_PRESCALER_32 && "Timer 0 does not support prescaler 32");
        static_assert(clock != Drivers::TimerClock::SYSTEM_PRESCALER_128 && "Timer 0 does not support prescaler 128");

        switch (clock)
        {
        case Drivers::TimerClock::SYSTEM_PRESCALER_1:
            return _BV(CS00);
        case Drivers::TimerClock::SYSTEM_PRESCALER_8:
            return _BV(CS01);
        case Drivers::TimerClock::SYSTEM_PRESCALER_64:
            return _BV(CS01) | _BV(CS00);
        case Drivers::TimerClock::SYSTEM_PRESCALER_256:
            return _BV(CS02);
        case Drivers::TimerClock::SYSTEM_PRESCALER_1024:
            return _BV(CS02) | _BV(CS00);
        case Drivers::TimerClock::EXTERNAL_CLOCK_FALLING_EDGE:
            return _BV(CS02) | _BV(CS01);
        case Drivers::TimerClock::EXTERNAL_CLOCK_RISING_EDGE:
            return _BV(CS02) | _BV(CS01) | _BV(CS00);
        case Drivers::TimerClock::SYSTEM_PRESCALER_32:
        case Drivers::TimerClock::SYSTEM_PRESCALER_128:
            return 0;
        }
        return 0;
    }

    static auto timerControlA() -> volatile uint8_t&
    {
        return TCCR0A;
    }

    static auto timerControlB() -> volatile uint8_t&
    {
        return TCCR0B;
    }

    static auto outputCompareA() -> volatile uint8_t&
    {
        return OCR0A;
    }

    static auto outputCompareB() -> volatile uint8_t&
    {
        return OCR0B;
    }
};

static_assert(Concepts::Drivers::timerChipSpecialization<Timer0Specialization>);

} // namespace NextagEmbeddedPlatform::Chips::Atmega328p
