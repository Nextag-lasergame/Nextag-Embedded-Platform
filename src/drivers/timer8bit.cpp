/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/timer8bit.h"

#include "timer_registers.h"

#include <avr/io.h>

namespace NextagEmbeddedPlatform::Drivers
{

class TimerClockConverter
{
public:
    [[nodiscard]] constexpr auto convertToMask(TimerClock clock) const -> uint8_t
    {
        switch (clock)
        {
            case TimerClock::SYSTEM_PRESCALER_1:
                return _BV(CS00);
            case TimerClock::SYSTEM_PRESCALER_8:
                return _BV(CS01);
            case TimerClock::SYSTEM_PRESCALER_64:
                return _BV(CS01) | _BV(CS00);
            case TimerClock::SYSTEM_PRESCALER_256:
                return _BV(CS02);
            case TimerClock::SYSTEM_PRESCALER_1024:
                return _BV(CS02) | _BV(CS00);
            case TimerClock::EXTERNAL_CLOCK_FALLING_EDGE:
                return _BV(CS02) | _BV(CS01);
            case TimerClock::EXTERNAL_CLOCK_RISING_EDGE:
                return _BV(CS02) | _BV(CS01) | _BV(CS00);
            case TimerClock::SYSTEM_PRESCALER_32:
            case TimerClock::SYSTEM_PRESCALER_128:
                return 0;
            }
        return 0;
    }

    [[nodiscard]] constexpr auto clockIsSupportedByTimer(TimerClock clock) const -> bool
    {
        switch (clock)
        {
            case TimerClock::SYSTEM_PRESCALER_1:
            case TimerClock::SYSTEM_PRESCALER_8:
            case TimerClock::SYSTEM_PRESCALER_64:
            case TimerClock::SYSTEM_PRESCALER_256:
            case TimerClock::SYSTEM_PRESCALER_1024:
            case TimerClock::EXTERNAL_CLOCK_FALLING_EDGE:
            case TimerClock::EXTERNAL_CLOCK_RISING_EDGE:
                return true;

            case TimerClock::SYSTEM_PRESCALER_32:
            case TimerClock::SYSTEM_PRESCALER_128:
                return false;
        }

        return false;
    }
};

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

auto Timer8Bit::setClockSource(TimerClock clock) -> TimerResult
{
    static constexpr TimerClockConverter converter;

    if(!converter.clockIsSupportedByTimer(clock))
        return TimerResult::INVALID_CLOCK_SOURCE;

    auto bitMask = converter.convertToMask(clock);
    stop();
    m_registers->controlB = m_registers->controlB | bitMask;
    return TimerResult::OK;
}

void Timer8Bit::stop()
{
    m_registers->controlB = m_registers->controlB & ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
}

Timer8Bit Timer8Bit::timer0{reinterpret_cast<TimerRegister<uint8_t>*>(0x44)};

} // namespace NextagEmbeddedPlatform::Drivers
