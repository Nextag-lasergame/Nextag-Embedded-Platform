/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#include "NextagEmbeddedPlatform/peripherals.h"

int main()
{
   using namespace NextagEmbeddedPlatform;

    [[maybe_unused]] auto & timer = Peripherals::timer0;

    timer.setMode(NextagEmbeddedPlatform::Drivers::TimerMode::CTC);
    timer.setCompareA(100);

    if(timer.setClockSource(Drivers::TimerClock::SYSTEM_PRESCALER_1) != Drivers::TimerResult::OK)
    {
        // Something went wrong, handle here
    }
}

// This function is registered as an interrupt handler in interrupts.cpp
void onTimer0CompareMatchA()
{

}