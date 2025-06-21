/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/digital_io.h"
#include "NextagEmbeddedPlatform/interrupt/interrupt_manager.h"
#include "NextagEmbeddedPlatform/peripherals.h"

using namespace NextagEmbeddedPlatform;

Drivers::DigitalIO led{Drivers::Pins::B5};

int main()
{
    using namespace NextagEmbeddedPlatform;

    led.setPinMode(Drivers::Mode::OUTPUT);
    led.setState(Drivers::State::HIGH);

    auto & timer = Peripherals::timer0;

    timer.setMode<Drivers::TimerMode::CTC>();
    timer.setCompareA<250>();
    timer.setClockSource<Drivers::TimerClock::SYSTEM_PRESCALER_1024>();

    // TODO: Add function on the timer class
    cli();
    TIMSK0 = TIMSK0 | _BV(OCIE0A);
    sei();

    while (true);
}

struct Timer0CompareAHandler
{
    static void operator()()
    {
        led.setState(led.getState() == Drivers::State::HIGH ? Drivers::State::LOW : Drivers::State::HIGH);
    }
};

template <>
inline auto Interrupt::interrupts<> =
    InterruptManager<InterruptDescriptor<InterruptIdentifier::TIMER0_COMPARE_A, Timer0CompareAHandler>>{};

INTERRUPT_HANDLERS;