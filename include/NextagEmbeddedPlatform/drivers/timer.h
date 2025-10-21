/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/concepts/drivers/timer.h"

namespace NextagEmbeddedPlatform::Drivers
{

// TODO: Add impl class to differentiate between different timer implementations (registers, supported prescalers, etc)
template <Concepts::Drivers::timer_datatype TimerDataType, Concepts::Drivers::timerChipSpecialization TimerSpecialization>
class Timer
{
public:
    template <TimerMode timerMode>
    void setMode()
    {
        TimerSpecialization::timerControlA() |= TimerSpecialization::template getModeMaskControlA<timerMode>();
        TimerSpecialization::timerControlB() |= TimerSpecialization::template getModeMaskControlB<timerMode>();
    }

    template <TimerDataType value>
    void setCompareA()
    {
        TimerSpecialization::outputCompareA() = value;
    }

    template <TimerDataType value>
    void setCompareB()
    {
        TimerSpecialization::outputCompareB() = value;
    }

    template <TimerClock clockSource>
    void setClockSource()
    {
        TimerSpecialization::timerControlB() &= TimerSpecialization::getClockSourceBitMask();
        TimerSpecialization::timerControlB() |= TimerSpecialization::template getClockSourceMask<clockSource>();
    }

    void stop()
    {
        TimerSpecialization::timerControlB() &= TimerSpecialization::getClockSourceBitMask();
    }
};

} // namespace NextagEmbeddedPlatform::Drivers
