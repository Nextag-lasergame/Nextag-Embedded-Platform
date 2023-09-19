/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#include "timer8bit.h"

#include <avr/io.h>

namespace NextagEmbeddedPlatform::Drivers
{

Timer8Bit::Timer8Bit(TimerRegister<uint8_t> * registers) : m_registers(registers)
{
}

void Timer8Bit::setMode(TimerMode /*mode*/)
{
    m_registers->controlB = m_registers->controlB | _BV(WGM01);
}

void Timer8Bit::setCompareA(uint16_t value)
{
}

void Timer8Bit::setCompareB(uint16_t value)
{
}

} // namespace NextagEmbeddedPlatform::Drivers
