/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/concepts/concepts.h"
#include "NextagEmbeddedPlatform/concepts/drivers/timer.h"

#include <avr/io.h>

namespace NextagEmbeddedPlatform::Drivers
{

// TODO: Add impl class to differentiate between different timer implementations (registers, supported prescalers, etc)
template<Concepts::Drivers::timer_datatype TimerDataType>
class Timer
{
public:
    template<TimerMode timerMode>
    void setMode()
    {
        TCCR0A |= getModeMaskControlA(timerMode);
    }

    template<TimerDataType value>
    void setCompareA()
    {
        OCR0A = value;
    }

    template<TimerDataType value>
    void setCompareB()
    {
        OCR0B = value;
    }

    template<TimerClock clockSource>
    void setClockSource()
    {
        TCCR0B |= getClockSourceMask(clockSource);
    }

    void stop()
    {
        TCCR0B &= ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
    }

private:
    [[nodiscard]] static constexpr auto getModeMaskControlA(TimerMode /*mode*/)
    {
        return _BV(WGM01);
    }

    [[nodiscard]] constexpr auto getClockSourceMask(TimerClock clock) const -> uint8_t
    {
        // TODO: Check whether prescaler is valid?
        switch (clock)
        {
        case TimerClock::SYSTEM_PRESCALER_1:
            return _BV(CS00);
        case TimerClock::SYSTEM_PRESCALER_8:
            return _BV(CS01);
        case TimerClock::SYSTEM_PRESCALER_64:
            return _BV(CS01) | _BV(CS00);
        case TimerClock::SYSTEM_PRESCALER_256:
            return _BV(CS02);
        case TimerClock::SYSTEM_PRESCALER_1024:
            return _BV(CS02) | _BV(CS00);
        case TimerClock::EXTERNAL_CLOCK_FALLING_EDGE:
            return _BV(CS02) | _BV(CS01);
        case TimerClock::EXTERNAL_CLOCK_RISING_EDGE:
            return _BV(CS02) | _BV(CS01) | _BV(CS00);
        case TimerClock::SYSTEM_PRESCALER_32:
        case TimerClock::SYSTEM_PRESCALER_128:
            return 0;
        }
        return 0;
    }
};

static_assert(Concepts::Drivers::timerNew<Timer<uint8_t>>);

} // namespace NextagEmbeddedPlatform::Drivers
