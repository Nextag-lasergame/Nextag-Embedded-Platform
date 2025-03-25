/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "timer0_tests.h"

#include "NextagEmbeddedPlatform/peripherals.h"

#include <avr/io.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::Peripherals;
using namespace NextagEmbeddedPlatform::Drivers;

namespace Timer0Tests
{

static void SetModeToCTC_SetsCorrectRegisters();
static void SetClockSource_SetsCorrectRegisterValue();
static void Stop_ClearsPrescalerBitsInRegister();
static void SetCompareA_SetsCorrectRegisters();
static void SetCompareB_SetsCorrectRegisters();
static void ResetCounter_SetsCounterBackToZero();

static void SetInterruptWithCompareAEnabled_SetsCorrectRegisters();
static void SetInterruptWithCompareBEnabled_SetsCorrectRegisters();
static void SetInterruptWithOverflowEnabled_SetsCorrectRegisters();
static void SetInterruptWithAllEnabled_SetsCorrectRegisters();
static void SetInterrupt_EnablesInterruptsInStatusRegister();

static void ResetInterruptWithCompareA_SetsCorrectRegisters();
static void ResetInterruptWithCompareB_SetsCorrectRegisters();
static void ResetInterruptWithOverflow_SetsCorrectRegisters();
static void ResetInterruptWithAll_SetsCorrectRegisters();
static void ResetInterruptWithAllEnabled_SetsCorrectRegisters();
static void ResetInterrupt_EnablesInterruptsInStatusRegister();

static void ControlA_ReturnsReferenceToCorrectRegister();
static void ControlB_ReturnsReferenceToCorrectRegister();
static void CompareA_ReturnsReferenceToCorrectRegister();
static void CompareB_ReturnsReferenceToCorrectRegister();
static void Counter_ReturnsReferenceToCorrectRegister();
static void Interrupt_ReturnsReferenceToCorrectRegister();


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
    RUN_TEST(SetClockSource_SetsCorrectRegisterValue);
    RUN_TEST(Stop_ClearsPrescalerBitsInRegister);
    RUN_TEST(SetCompareA_SetsCorrectRegisters);
    RUN_TEST(SetCompareB_SetsCorrectRegisters);
    RUN_TEST(ResetCounter_SetsCounterBackToZero);

    RUN_TEST(SetInterruptWithCompareAEnabled_SetsCorrectRegisters);
    RUN_TEST(SetInterruptWithCompareBEnabled_SetsCorrectRegisters);
    RUN_TEST(SetInterruptWithOverflowEnabled_SetsCorrectRegisters);
    RUN_TEST(SetInterruptWithAllEnabled_SetsCorrectRegisters);
    RUN_TEST(SetInterrupt_EnablesInterruptsInStatusRegister);

    RUN_TEST(ResetInterruptWithCompareA_SetsCorrectRegisters);
    RUN_TEST(ResetInterruptWithCompareB_SetsCorrectRegisters);
    RUN_TEST(ResetInterruptWithOverflow_SetsCorrectRegisters);
    RUN_TEST(ResetInterruptWithAll_SetsCorrectRegisters);
    RUN_TEST(ResetInterruptWithAllEnabled_SetsCorrectRegisters);
    RUN_TEST(ResetInterrupt_EnablesInterruptsInStatusRegister);

    RUN_TEST(ControlA_ReturnsReferenceToCorrectRegister);
    RUN_TEST(ControlB_ReturnsReferenceToCorrectRegister);
    RUN_TEST(CompareA_ReturnsReferenceToCorrectRegister);
    RUN_TEST(CompareB_ReturnsReferenceToCorrectRegister);
    RUN_TEST(Counter_ReturnsReferenceToCorrectRegister);
    RUN_TEST(Interrupt_ReturnsReferenceToCorrectRegister);
}

void SetModeToCTC_SetsCorrectRegisters()
{
    Timer0::setMode(Timer0::TimerMode::CTC);
    TEST_ASSERT_BITS_HIGH(_BV(WGM01), TCCR0A);
}

void SetClockSource_SetsCorrectRegisterValue()
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

static void Stop_ClearsPrescalerBitsInRegister()
{
    TCCR0B = 0xFF;
    Timer0::stop();

    TEST_ASSERT_BITS_LOW((_BV(CS02) | _BV(CS01) | _BV(CS00)), TCCR0B);
}

static void SetCompareA_SetsCorrectRegisters()
{
    Timer0::setCompareA(200);
    TEST_ASSERT_EQUAL(200, OCR0A);

    Timer0::setCompareA(100);
    TEST_ASSERT_EQUAL(100, OCR0A);
}

static void SetCompareB_SetsCorrectRegisters()
{
    Timer0::setCompareB(200);
    TEST_ASSERT_EQUAL(200, OCR0B);

    Timer0::setCompareB(100);
    TEST_ASSERT_EQUAL(100, OCR0B);
}

static void ResetCounter_SetsCounterBackToZero()
{
    TCNT0 = 100;
    Timer0::resetCounter();
    TEST_ASSERT_EQUAL(0, TCNT0);
}

static void SetInterruptWithCompareAEnabled_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A);
    TEST_ASSERT_BITS_HIGH(_BV(OCIE0A), TIMSK0);
}

static void SetInterruptWithCompareBEnabled_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_B);
    TEST_ASSERT_BITS_HIGH(_BV(OCIE0B), TIMSK0);
}

static void SetInterruptWithOverflowEnabled_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_HIGH(_BV(TOIE0), TIMSK0);
}

static void SetInterruptWithAllEnabled_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_HIGH(_BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0), TIMSK0);
}

static void SetInterrupt_EnablesInterruptsInStatusRegister()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
}

static void ResetInterruptWithCompareA_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A);
    TEST_ASSERT_BIT_LOW(_BV(OCIE0A), TIMSK0);
}

static void ResetInterruptWithCompareB_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_B);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_B);
    TEST_ASSERT_BIT_LOW(_BV(OCIE0B), TIMSK0);
}

static void ResetInterruptWithOverflow_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::OVERFLOW);
    Timer0::resetInterrupt(Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_BIT_LOW(_BV(TOIE0), TIMSK0);
}

static void ResetInterruptWithAll_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_LOW(_BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0), TIMSK0);
}

static void ResetInterruptWithAllEnabled_SetsCorrectRegisters()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_B);
    TEST_ASSERT_BITS_LOW(_BV(OCIE0B), TIMSK0);
    TEST_ASSERT_BITS_HIGH(_BV(OCIE0A) | _BV(TOIE0), TIMSK0);
}

static void ResetInterrupt_EnablesInterruptsInStatusRegister()
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
}

static void ControlA_ReturnsReferenceToCorrectRegister()
{
    TEST_ASSERT_EQUAL(&TCCR0A, &Timer0::controlA());
}

static void ControlB_ReturnsReferenceToCorrectRegister()
{
    TEST_ASSERT_EQUAL(&TCCR0B, &Timer0::controlB());
}

static void CompareA_ReturnsReferenceToCorrectRegister()
{
    TEST_ASSERT_EQUAL(&OCR0A, &Timer0::compareA());
}

static void CompareB_ReturnsReferenceToCorrectRegister()
{
    TEST_ASSERT_EQUAL(&OCR0B, &Timer0::compareB());
}

static void Counter_ReturnsReferenceToCorrectRegister()
{
    TEST_ASSERT_EQUAL(&TCNT0, &Timer0::counter());
}

static void Interrupt_ReturnsReferenceToCorrectRegister()
{
    TEST_ASSERT_EQUAL(&TIMSK0, &Timer0::interrupt());
}

} // namespace Timer0Tests