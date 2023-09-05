/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

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

    static Timer timer0;

    void setMode(TimerMode mode);

protected:
    Timer() = default;
};

} // namespace NextagEmbeddedPlatform::Drivers
