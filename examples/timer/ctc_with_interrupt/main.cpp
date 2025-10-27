/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/digital_io.h"
#include "NextagEmbeddedPlatform/interrupt/interrupt_manager.h"
#include "NextagEmbeddedPlatform/peripherals.h"

using namespace NextagEmbeddedPlatform;

Drivers::DigitalIO led{Drivers::Pins::B5};
Drivers::DigitalIO led2{Drivers::Pins::B4};

int main()
{
    using namespace NextagEmbeddedPlatform::Peripherals;

    // DDRB |= _BV(DDB5);
    // DDRB |= _BV(DDB4);
    led.setPinMode(Drivers::Mode::OUTPUT);
    led2.setPinMode(Drivers::Mode::OUTPUT);

    // PORTB |= _BV(PORTB5);
    // PORTB |= _BV(PORTB4);
    led.setState(Drivers::State::HIGH);
    led2.setState(Drivers::State::HIGH);

    Timer0::setMode(Timer0::TimerMode::CTC);
    Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_1024);
    Timer0::setCompareA(200);
    Timer0::setCompareB(100);

    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B);

    while (true);
}

struct Timer0CompareAHandler
{
    static void operator()()
    {
        // PORTB ^= _BV(PORTB5);
        led.setState(led.getState() == Drivers::State::HIGH ? Drivers::State::LOW : Drivers::State::HIGH);
    }
};

struct Timer0CompareBHandler
{
    static void operator()()
    {
        // PORTB ^= _BV(PORTB4);
        led2.setState(led2.getState() == Drivers::State::HIGH ? Drivers::State::LOW : Drivers::State::HIGH);
    }
};

template <>
inline auto Interrupt::interrupts<> =
    InterruptManager<
        InterruptDescriptor<InterruptIdentifier::TIMER0_COMPARE_A, Timer0CompareAHandler>,
        InterruptDescriptor<InterruptIdentifier::TIMER0_COMPARE_B, Timer0CompareBHandler>>{};

INTERRUPT_HANDLERS;