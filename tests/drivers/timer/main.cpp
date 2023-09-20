/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#include <test_utils/serial.h>

#include <NextagEmbeddedPlatform/peripherals.h>

#include <avr/sleep.h>
#include <avr/io.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform;
using namespace NextagEmbeddedPlatform::Drivers;

void setUp()
{
    TCCR0A = 0;
    TCCR0B = 0;
    OCR0A = 0;
    OCR0B = 0;
    TIMSK0 = 0;
    TCNT0 = 0;
}

void tearDown()
{
}

void Timer0_SetModeToCTC_SetsCorrectRegisters()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setMode(TimerMode::CTC);

    TEST_ASSERT_BITS_HIGH(_BV(WGM01), TCCR0A);
}

void Timer0_SetCompareA_SetsCorrectRegisters()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setCompareA(200);
    TEST_ASSERT_EQUAL(200, OCR0A);
}

void Timer0_SetCompareAToHigh_ClipsValueInRegister()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setCompareA(500);
    // 244 is 500 & 0xFF
    TEST_ASSERT_EQUAL(244, OCR0A);
}

void Timer0_SetCompareB_SetsCorrectRegisters()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setCompareB(100);
    TEST_ASSERT_EQUAL(100, OCR0B);
}

void Timer0_SetCompareBToHigh_ClipsValueInRegister()
{
    auto & timer0 = Peripherals::timer0;

    timer0.setCompareB(600);
    // 88 is 600 & 0xFF
    TEST_ASSERT_EQUAL(88, OCR0B);
}

void Timer0_SetTimerClock_SetsCorrectRegisterValue()
{
    auto & timer0 = Peripherals::timer0;

    TEST_ASSERT_EQUAL(TimerResult::OK, timer0.setClockSource(TimerClock::SYSTEM_PRESCALER_1));
    TEST_ASSERT_BITS(0xFF, _BV(CS00), TCCR0B);

    TEST_ASSERT_EQUAL(TimerResult::OK, timer0.setClockSource(TimerClock::SYSTEM_PRESCALER_8));
    TEST_ASSERT_BITS(0xFF, _BV(CS01), TCCR0B);

    TEST_ASSERT_EQUAL(TimerResult::INVALID_CLOCK_SOURCE, timer0.setClockSource(TimerClock::SYSTEM_PRESCALER_32));

    TEST_ASSERT_EQUAL(TimerResult::OK, timer0.setClockSource(TimerClock::SYSTEM_PRESCALER_64));
    TEST_ASSERT_BITS(0xFF, _BV(CS01) | _BV(CS00), TCCR0B);

    TEST_ASSERT_EQUAL(TimerResult::INVALID_CLOCK_SOURCE, timer0.setClockSource(TimerClock::SYSTEM_PRESCALER_128));

    TEST_ASSERT_EQUAL(TimerResult::OK, timer0.setClockSource(TimerClock::SYSTEM_PRESCALER_256));
    TEST_ASSERT_BITS(0xFF, _BV(CS02), TCCR0B);

    TEST_ASSERT_EQUAL(TimerResult::OK, timer0.setClockSource(TimerClock::SYSTEM_PRESCALER_1024));
    TEST_ASSERT_BITS(0xFF, _BV(CS02) | _BV(CS00), TCCR0B);

    TEST_ASSERT_EQUAL(TimerResult::OK, timer0.setClockSource(TimerClock::EXTERNAL_CLOCK_FALLING_EDGE));
    TEST_ASSERT_BITS(0xFF, _BV(CS02) | _BV(CS01), TCCR0B);

    TEST_ASSERT_EQUAL(TimerResult::OK, timer0.setClockSource(TimerClock::EXTERNAL_CLOCK_RISING_EDGE));
    TEST_ASSERT_BITS(0xFF, _BV(CS02) | _BV(CS01) | _BV(CS00), TCCR0B);
}

void Timer0_Stop_ClearsPrescalerBitsInRegister()
{
    Concepts::Drivers::timer auto & timer0 = Peripherals::timer0;

    TCCR0B = 0xFF;
    timer0.stop();

    TEST_ASSERT_BITS(0xFF, ~(_BV(CS02) | _BV(CS01) | _BV(CS00)), TCCR0B);
}

int main()
{
    NextagEmbeddedPlatform::TestUtils::initTestSerial();

    UNITY_BEGIN();
    RUN_TEST(Timer0_SetModeToCTC_SetsCorrectRegisters);
    RUN_TEST(Timer0_SetCompareA_SetsCorrectRegisters);
    RUN_TEST(Timer0_SetCompareAToHigh_ClipsValueInRegister);
    RUN_TEST(Timer0_SetCompareB_SetsCorrectRegisters);
    RUN_TEST(Timer0_SetCompareBToHigh_ClipsValueInRegister);
    RUN_TEST(Timer0_SetTimerClock_SetsCorrectRegisterValue);
    RUN_TEST(Timer0_Stop_ClearsPrescalerBitsInRegister);
    UNITY_END();

    sleep_cpu();
}