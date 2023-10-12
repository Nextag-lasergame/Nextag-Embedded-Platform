/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "timer_clock.h"
#include "timer_mode.h"
#include "timer_result.h"

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Drivers
{

template <typename T>
struct TimerRegister;

class Timer8Bit
{
public:
    void setMode(TimerMode mode);
    void setCompareA(uint16_t value);
    void setCompareB(uint16_t value);

    [[nodiscard]] auto setClockSource(TimerClock clock) -> TimerResult;
    void stop();

    static Timer8Bit timer0;

protected:
    explicit Timer8Bit(TimerRegister<uint8_t> * registers);

private:
    TimerRegister<uint8_t> * m_registers;
};

} // namespace NextagEmbeddedPlatform::Drivers