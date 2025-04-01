/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "timer0_tests.h"

#include "NextagEmbeddedPlatform/peripherals.h"

#include <avr/io.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform;
using namespace NextagEmbeddedPlatform::Drivers;

namespace Timer0
{

void setUp()
{
    TCCR0A = 0;
    TCCR0B = 0;
    OCR0A = 0;
    OCR0B = 0;
    TIMSK0 = 0;
    TCNT0 = 0;
}

void runTests()
{
    RUN_TEST(SetModeToCTC_SetsCorrectRegisters);
    RUN_TEST(SetCompareA_SetsCorrectRegisters);
    RUN_TEST(SetCompareB_SetsCorrectRegisters);
    RUN_TEST(SetTimerClock_SetsCorrectRegisterValue);
    // RUN_TEST(Stop_ClearsPrescalerBitsInRegister);
}

void SetModeToCTC_SetsCorrectRegisters()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setMode<TimerMode::CTC>();

    TEST_ASSERT_BITS_HIGH(_BV(WGM01), TCCR0A);
}

void SetCompareA_SetsCorrectRegisters()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setCompareA<200>();
    TEST_ASSERT_EQUAL(200, OCR0A);
}

void SetCompareB_SetsCorrectRegisters()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setCompareB<100>();
    TEST_ASSERT_EQUAL(100, OCR0B);
}

void SetTimerClock_SetsCorrectRegisterValue()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setClockSource<TimerClock::SYSTEM_PRESCALER_1>();
    TEST_ASSERT_BITS(0xFF, _BV(CS00), TCCR0B);

    timer0.setClockSource<TimerClock::SYSTEM_PRESCALER_8>();
    TEST_ASSERT_BITS(0xFF, _BV(CS01), TCCR0B);

    timer0.setClockSource<TimerClock::SYSTEM_PRESCALER_64>();
    TEST_ASSERT_BITS(0xFF, _BV(CS01) | _BV(CS00), TCCR0B);

    timer0.setClockSource<TimerClock::SYSTEM_PRESCALER_256>();
    TEST_ASSERT_BITS(0xFF, _BV(CS02), TCCR0B);

    timer0.setClockSource<TimerClock::SYSTEM_PRESCALER_1024>();
    TEST_ASSERT_BITS(0xFF, _BV(CS02) | _BV(CS00), TCCR0B);

    timer0.setClockSource<TimerClock::EXTERNAL_CLOCK_FALLING_EDGE>();
    TEST_ASSERT_BITS(0xFF, _BV(CS02) | _BV(CS01), TCCR0B);

    timer0.setClockSource<TimerClock::EXTERNAL_CLOCK_RISING_EDGE>();
    TEST_ASSERT_BITS(0xFF, _BV(CS02) | _BV(CS01) | _BV(CS00), TCCR0B);
}

void Stop_ClearsPrescalerBitsInRegister()
{
    auto & timer0 = Peripherals::timer0;

    TCCR0B = 0xFF;
    timer0.stop();

    TEST_ASSERT_BITS(0xFF, ~(_BV(CS02) | _BV(CS01) | _BV(CS00)), TCCR0B);
}

} // namespace Timer0