/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Drivers
{

enum class TimerMode
{
    CTC
};

enum class TimerClock
{
    SYSTEM_PRESCALER_1,
    SYSTEM_PRESCALER_8,
    SYSTEM_PRESCALER_32, // Not supported on timer0
    SYSTEM_PRESCALER_64,
    SYSTEM_PRESCALER_128, // Not supported on timer0
    SYSTEM_PRESCALER_256,
    SYSTEM_PRESCALER_1024
};

template <typename T>
concept timer = requires(T t, TimerMode mode, uint16_t value, TimerClock clock)
{
    {t.setMode(mode)};
    t.setCompareA(value);
    t.setCompareB(value);
    t.setClockSource(clock);
    t.stop();
};

class Timer
{
public:
    ~Timer() = default;
    Timer(Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&) = delete;
    Timer& operator=(Timer&&) = delete;

    static Timer & timer0;

    virtual void setMode(TimerMode mode) = 0;
    virtual void setCompareA(uint16_t value) = 0;
    virtual void setCompareB(uint16_t value) = 0;

    virtual void setClockSource(TimerClock clock) = 0;
    virtual void stop() = 0;

protected:
    Timer() = default;
};

} // namespace NextagEmbeddedPlatform::Drivers
