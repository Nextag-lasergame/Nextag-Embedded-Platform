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

protected:
    Timer() = default;
};

} // namespace NextagEmbeddedPlatform::Drivers
