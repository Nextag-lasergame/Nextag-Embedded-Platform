/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "timer0_tests.h"

#include "NextagEmbeddedPlatform/chips/peripherals.h"

#include <avr/io.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::Peripherals;
using namespace NextagEmbeddedPlatform::Drivers;

namespace Timer0Tests
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
    // TODO: Add tests that verify behaviour when you set the value of a register multiple times
    // TODO: Add tests for interrupts
    RUN_TEST(SetModeToCTC_SetsCorrectRegisters);
    RUN_TEST(SetCompareA_SetsCorrectRegisters);
    RUN_TEST(SetCompareB_SetsCorrectRegisters);
    RUN_TEST(SetTimerClock_SetsCorrectRegisterValue);
    RUN_TEST(Stop_ClearsPrescalerBitsInRegister);
}

void SetModeToCTC_SetsCorrectRegisters()
{
    Timer0::setMode(Timer0::TimerMode::CTC);
    TEST_ASSERT_BITS_HIGH(_BV(WGM01), TCCR0A);
}

void SetCompareA_SetsCorrectRegisters()
{
    Timer0::setCompareA(200);
    TEST_ASSERT_EQUAL(200, OCR0A);
}

void SetCompareB_SetsCorrectRegisters()
{
    Timer0::setCompareB(100);
    TEST_ASSERT_EQUAL(100, OCR0B);
}

void SetTimerClock_SetsCorrectRegisterValue()
{
    Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_1);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS00), TCCR0B, "Prescaler 1 was not set correctly");

    Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_8);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS01), TCCR0B, "Prescaler 8 was not set correctly");

    Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_64);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS01) | _BV(CS00), TCCR0B, "Prescaler 64 was not set correctly");

    Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_256);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS02), TCCR0B, "Prescaler 256 was not set correctly");

    Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_1024);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS02) | _BV(CS00), TCCR0B, "Prescaler 1024 was not set correctly");

    Timer0::setClockSource(Timer0::ClockSelect::EXTERNAL_SOURCE_FALLING_EDGE);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS02) | _BV(CS01), TCCR0B, "Prescaler falling edge was not set correctly");

    Timer0::setClockSource(Timer0::ClockSelect::EXTERNAL_SOURCE_RISING_EDGE);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS02) | _BV(CS01) | _BV(CS00), TCCR0B, "Prescaler rising edge was not set correctly");
}

void Stop_ClearsPrescalerBitsInRegister()
{
    TCCR0B = 0xFF;
    Timer0::stop();

    TEST_ASSERT_BITS(0xFF, ~(_BV(CS02) | _BV(CS01) | _BV(CS00)), TCCR0B);
}

} // namespace Timer0Tests