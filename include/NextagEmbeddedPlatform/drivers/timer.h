/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/concepts/concepts.h"
#include "NextagEmbeddedPlatform/concepts/drivers/timer.h"

#include <avr/interrupt.h>

namespace NextagEmbeddedPlatform::Drivers
{

template <typename TimerDescriptor>
class Timer
{
public:
    using TimerMode = typename TimerDescriptor::TimerMode;
    using ClockSelect = typename TimerDescriptor::ClockSelect;
    using Interrupt = typename TimerDescriptor::Interrupt;
    using DataType = typename TimerDescriptor::DataType;

    Timer() = delete;

    static void setMode(TimerMode timerMode)
        requires HasCombinedTimerMode<TimerDescriptor>
    {
        TimerDescriptor::controlAB |= static_cast<uint16_t>(timerMode);
    }

    static void setClockSource(ClockSelect clockSelect)
        requires HasClockSelect<TimerDescriptor> && HasTimerControlB<TimerDescriptor>
    {
        TimerDescriptor::controlB &= ~TimerDescriptor::clockSelectMask;
        TimerDescriptor::controlB |= static_cast<uint8_t>(clockSelect);
    }

    static void stop()
        requires HasClockSelectNoClockSource<TimerDescriptor> && HasTimerControlB<TimerDescriptor>
    {
        setClockSource(ClockSelect::NO_CLOCK_SOURCE);
    }

    static void setCompareA(DataType value)
        requires HasTimerCompareA<TimerDescriptor>
    {
        TimerDescriptor::compareA = value;
    }

    static void setCompareB(DataType value)
        requires HasTimerCompareB<TimerDescriptor>
    {
        TimerDescriptor::compareB = value;
    }

    static void resetCounter()
        requires HasTimerCounter<TimerDescriptor>
    {
        TimerDescriptor::counter = 0;
    }

    template <typename... T>
    static void setInterrupt(T... interrupts)
        requires Concepts::all_same_as<Interrupt, T...> && HasTimerInterrupt<TimerDescriptor>
    {
        const auto interruptMask = (static_cast<uint8_t>(interrupts) | ...);

        cli();
        TimerDescriptor::interrupt |= interruptMask;
        // TODO: Do we want to enable interrupts implicitly here?
        sei();
    }

    template <typename... T>
    static void resetInterrupt(T... interrupts)
        requires Concepts::all_same_as<Interrupt, T...> && HasTimerInterrupt<TimerDescriptor>
    {
        const auto interruptMask = (static_cast<uint8_t>(interrupts) | ...);

        cli();
        TimerDescriptor::interrupt &= ~interruptMask;
        sei();
    }

    static auto controlA() -> volatile uint8_t &
        requires HasTimerControlA<TimerDescriptor>
    {
        return TimerDescriptor::controlA;
    }

    static auto controlB() -> volatile uint8_t &
        requires HasTimerControlB<TimerDescriptor>
    {
        return TimerDescriptor::controlB;
    }

    static auto compareA() -> volatile uint8_t &
        requires HasTimerCompareA<TimerDescriptor>
    {
        return TimerDescriptor::compareA;
    }

    static auto compareB() -> volatile uint8_t &
        requires HasTimerCompareB<TimerDescriptor>
    {
        return TimerDescriptor::compareB;
    }

    static auto counter() -> volatile uint8_t &
        requires HasTimerCounter<TimerDescriptor>
    {
        return TimerDescriptor::counter;
    }

    static auto interrupt() -> volatile uint8_t &
        requires HasTimerInterrupt<TimerDescriptor>
    {
        return TimerDescriptor::interrupt;
    }
};

} // namespace NextagEmbeddedPlatform::Drivers
