/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/digital_io.h"
#include "NextagEmbeddedPlatform/interrupt/interrupt_registry.h"
#include "NextagEmbeddedPlatform/peripherals.h"

NextagEmbeddedPlatform::Drivers::DigitalIO led{NextagEmbeddedPlatform::Drivers::Pins::B5};

int main()
{
    using namespace NextagEmbeddedPlatform;

    led.setPinMode(Drivers::Mode::OUTPUT);

    auto & timer = Peripherals::timer0;

    timer.setMode(NextagEmbeddedPlatform::Drivers::TimerMode::CTC);
    timer.setCompareA(100);

    if (timer.setClockSource(Drivers::TimerClock::SYSTEM_PRESCALER_1) != Drivers::TimerResult::OK)
    {
        // Something went wrong, handle here
    }

    Interrupt::InterruptRegistry::enableInterrupt(Interrupt::Interrupt::TIMER0_COMPARE_A);
}

void onTimer0CompareMatchA()
{
    led.setState(NextagEmbeddedPlatform::Drivers::State::HIGH);
}