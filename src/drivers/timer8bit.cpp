/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/timer8bit.h"

#include "timer_registers.h"

#include <avr/io.h>

namespace NextagEmbeddedPlatform::Drivers
{

Timer8Bit::Timer8Bit(TimerRegister<uint8_t> * registers) : m_registers(registers)
{
}

void Timer8Bit::setMode(TimerMode /*mode*/)
{
    m_registers->controlA = m_registers->controlA | _BV(WGM01);
}

void Timer8Bit::setCompareA(uint16_t value)
{
    m_registers->compareA = value & 0xFF;
}

void Timer8Bit::setCompareB(uint16_t value)
{
    m_registers->compareB = value & 0xFF;
}

void Timer8Bit::setClockSource(TimerClock clock)
{
    const auto convertClockToBitMask = [clock](){
        if (clock == TimerClock::SYSTEM_PRESCALER_1024)
            return 0x01;
        return 0xFF;
    };

    const auto bitMask = convertClockToBitMask();
    stop();
    m_registers->controlB = m_registers->controlB | bitMask;
}

void Timer8Bit::stop()
{
//    m_registers->controlB = m_registers->controlB & ~(_BV(CS00) | _BV(CS01) | _BV(CS02))
}

Timer8Bit Timer8Bit::timer0{reinterpret_cast<TimerRegister<uint8_t>*>(0x44)};

} // namespace NextagEmbeddedPlatform::Drivers
