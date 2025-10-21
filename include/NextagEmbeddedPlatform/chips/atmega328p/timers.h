/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/concepts/drivers/timer.h"
#include "NextagEmbeddedPlatform/drivers/timer_clock.h"
#include "NextagEmbeddedPlatform/drivers/timer_mode.h"

#include <avr/io.h>

namespace NextagEmbeddedPlatform::Chips::Atmega328p
{

template <Drivers::TimerClock clock>
concept Timer0SupportedClock = clock == Drivers::TimerClock::SYSTEM_PRESCALER_1 || clock == Drivers::TimerClock::SYSTEM_PRESCALER_8 || clock == Drivers::TimerClock::SYSTEM_PRESCALER_64 || clock == Drivers::TimerClock::SYSTEM_PRESCALER_256 || clock == Drivers::TimerClock::SYSTEM_PRESCALER_1024 || clock == Drivers::TimerClock::EXTERNAL_CLOCK_FALLING_EDGE || clock == Drivers::TimerClock::EXTERNAL_CLOCK_RISING_EDGE;

struct Timer0Specialization
{
    template <Drivers::TimerMode mode>
    [[nodiscard]] static consteval auto getModeMaskControlA() -> uint8_t
    {
        static_assert(mode == Drivers::TimerMode::CTC);
        return _BV(WGM01);
    }

    template <Drivers::TimerMode mode>
    [[nodiscard]] static consteval auto getModeMaskControlB() -> uint8_t
    {
        static_assert(mode == Drivers::TimerMode::CTC);
        return 0;
    }

    template <Drivers::TimerClock clock>
        requires Timer0SupportedClock<clock>
    [[nodiscard]] static consteval auto getClockSourceMask() -> uint8_t
    {
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
            [[fallthrough]];
        case Drivers::TimerClock::SYSTEM_PRESCALER_128:
            [[fallthrough]];
        }
        return 0;
    }

    static auto getClockSourceBitMask() -> uint8_t
    {
        return _BV(CS02) | _BV(CS01) | _BV(CS00);
    }

    static auto timerControlA() -> volatile uint8_t &
    {
        return TCCR0A;
    }

    static auto timerControlB() -> volatile uint8_t &
    {
        return TCCR0B;
    }

    static auto outputCompareA() -> volatile uint8_t &
    {
        return OCR0A;
    }

    static auto outputCompareB() -> volatile uint8_t &
    {
        return OCR0B;
    }
};

static_assert(Concepts::Drivers::timerChipSpecialization<Timer0Specialization>);

} // namespace NextagEmbeddedPlatform::Chips::Atmega328p
