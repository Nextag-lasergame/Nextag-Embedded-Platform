/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "timer_registers.h"

#include "NextagEmbeddedPlatform/drivers/timer.h"

namespace NextagEmbeddedPlatform::Drivers
{

class Timer8Bit : public Timer
{
public:
    Timer8Bit(TimerRegister<uint8_t> * registers);

    void setMode(TimerMode mode) final;
    void setCompareA(uint16_t value) final;
    void setCompareB(uint16_t value) final;

private:
    TimerRegister<uint8_t> * m_registers;
};

} // namespace NextagEmbeddedPlatform::Drivers