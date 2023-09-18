/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/timer.h"

#include "timer_registers.h"

#include <avr/io.h>

namespace NextagEmbeddedPlatform::Drivers
{

class Timer8Bit : public Timer
{
public:
    explicit Timer8Bit(TimerRegister<uint8_t> * registers) : m_registers(registers)
    {

    }

    void setMode(TimerMode /*mode*/) override
    {
        m_registers->controlB = m_registers->controlB | _BV(WGM01);
    }

private:
    TimerRegister<uint8_t> * m_registers;
};

static Timer8Bit timer0Definition{reinterpret_cast<TimerRegister<uint8_t>*>(0x44)};
Timer & Timer::timer0 = timer0Definition;

} // namespace NextagEmbeddedPlatform::Drivers
