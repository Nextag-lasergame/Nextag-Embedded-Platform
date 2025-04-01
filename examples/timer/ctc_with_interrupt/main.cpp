// /*
//  * Copyright © 2022 Tim Herreijgers
//  * Licensed using the MIT license
//  */
//
// #include "NextagEmbeddedPlatform/drivers/digital_io.h"
// #include "NextagEmbeddedPlatform/interrupt/interrupt_manager.h"
// #include "NextagEmbeddedPlatform/peripherals.h"
//
// using namespace NextagEmbeddedPlatform;
//
// Drivers::DigitalIO led{Drivers::Pins::B5};
//
// int main()
// {
//     using namespace NextagEmbeddedPlatform;
//
//     led.setPinMode(Drivers::Mode::OUTPUT);
//     led.setState(NextagEmbeddedPlatform::Drivers::State::HIGH);
//
//     auto & timer = Peripherals::timer0;
//
//     timer.setMode(NextagEmbeddedPlatform::Drivers::TimerMode::CTC);
//     timer.setCompareA(100);
//
//     if (timer.setClockSource(Drivers::TimerClock::SYSTEM_PRESCALER_1) != Drivers::TimerResult::OK)
//     {
//         // Something went wrong, handle here
//     }
//
//     TIMSK0 = TIMSK0 | _BV(OCIE0A);
//
//     while (true);
// }
//
// struct Timer0CompareAHandler
// {
//     static void operator()()
//     {
//         led.setState(Drivers::State::HIGH);
//     }
// };
//
// template <>
// inline auto Interrupt::interrupts<> =
//     InterruptManager<InterruptDescriptor<InterruptIdentifier::TIMER0_COMPARE_A, Timer0CompareAHandler>>{};
//
// INTERRUPT_HANDLERS;

int main()
{

}
