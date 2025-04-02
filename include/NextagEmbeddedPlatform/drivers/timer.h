/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/concepts/drivers/timer.h"

#include <avr/io.h>

namespace NextagEmbeddedPlatform::Drivers
{

// TODO: Add impl class to differentiate between different timer implementations (registers, supported prescalers, etc)
template<Concepts::Drivers::timer_datatype TimerDataType, Concepts::Drivers::timerChipSpecialization TimerSpecialization>
class Timer
{
public:
    template<TimerMode timerMode>
    void setMode()
    {
        TCCR0A |= TimerSpecialization::template getModeMaskControlA<timerMode>();
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
        TCCR0B &= ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
        TCCR0B |= TimerSpecialization::template getClockSourceMask<clockSource>();
    }

    void stop()
    {
        TCCR0B &= ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
    }
};

} // namespace NextagEmbeddedPlatform::Drivers
