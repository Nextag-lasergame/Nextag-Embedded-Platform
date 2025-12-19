/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "nextag_test/nextag_test.h"

#include "NextagEmbeddedPlatform/peripherals.h"

#include <avr/io.h>

#include <unity.h>

using namespace NextagEmbeddedPlatform::Peripherals;
using namespace NextagEmbeddedPlatform::Drivers;

class Timer0Tests : public NextagTest::Test
{
public:
    void setUp() override
    {
        cli();
        TCCR0A = 0;
        TCCR0B = 0;
        OCR0A = 0;
        OCR0B = 0;
        TIMSK0 = 0;
        TCNT0 = 0;
    }
};


TEST_F(Timer0Tests, SetModeToNormal_SetsCorrectRegisters)
{
    Timer0::setMode(Timer0::TimerMode::NORMAL);
    TEST_ASSERT_EQUAL(0, Timer0::Descriptor::controlAB);
}

TEST_F(Timer0Tests, SetModeToPwmPhaseCorrect_SetsCorrectRegisters)
{
    Timer0::setMode(Timer0::TimerMode::PWM_PHASE_CORRECT);
    TEST_ASSERT_EQUAL(_BV(WGM00), Timer0::Descriptor::controlAB);
}

TEST_F(Timer0Tests, SetModeToCTC_SetsCorrectRegisters)
{
    Timer0::setMode(Timer0::TimerMode::CTC);
    TEST_ASSERT_EQUAL(_BV(WGM01), Timer0::Descriptor::controlAB);
}

TEST_F(Timer0Tests, SetModeToFastPwm_SetsCorrectRegisters)
{
    Timer0::setMode(Timer0::TimerMode::FAST_PWM);
    TEST_ASSERT_EQUAL(_BV(WGM01) | _BV(WGM00), Timer0::Descriptor::controlAB);
}

TEST_F(Timer0Tests, SetModeToPwmPhaseCorrectComparaATop_SetsCorrectRegisters)
{
    Timer0::setMode(Timer0::TimerMode::PWM_PHASE_CORRECT_COMPARE_A_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM00), _BV(WGM02)),
                      Timer0::Descriptor::controlAB);
}

TEST_F(Timer0Tests, SetModeToFastPwmComparaATop_SetsCorrectRegisters)
{
    Timer0::setMode(Timer0::TimerMode::FAST_PWM_COMPARE_A_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM01) | _BV(WGM00), _BV(WGM02)),
                      Timer0::Descriptor::controlAB);
}

TEST_F(Timer0Tests, SetModeToNormal_AfterSetToCTC_SetsCorrectRegisters)
{
    Timer0::setMode(Timer0::TimerMode::CTC);
    Timer0::setMode(Timer0::TimerMode::NORMAL);

    TEST_ASSERT_EQUAL(0, Timer0::Descriptor::controlAB);
}

TEST_F(Timer0Tests, SetClockSource_SetsCorrectRegisterValue)
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

TEST_F(Timer0Tests, Stop_ClearsPrescalerBitsInRegister)
{
    TCCR0B = 0xFF;
    Timer0::stop();

    TEST_ASSERT_EQUAL(0xFF & ~((_BV(CS02) | _BV(CS01) | _BV(CS00))), TCCR0B);
}

TEST_F(Timer0Tests, SetCompareA_SetsCorrectRegisters)
{
    Timer0::setCompareA(200);
    TEST_ASSERT_EQUAL(200, OCR0A);

    Timer0::setCompareA(100);
    TEST_ASSERT_EQUAL(100, OCR0A);
}

TEST_F(Timer0Tests, SetCompareB_SetsCorrectRegisters)
{
    Timer0::setCompareB(200);
    TEST_ASSERT_EQUAL(200, OCR0B);

    Timer0::setCompareB(100);
    TEST_ASSERT_EQUAL(100, OCR0B);
}

TEST_F(Timer0Tests, ResetCounter_SetsCounterBackToZero)
{
    TCNT0 = 100;
    Timer0::resetCounter();
    TEST_ASSERT_EQUAL(0, TCNT0);
}

TEST_F(Timer0Tests, SetInterruptWithCompareAEnabled_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A);
    TEST_ASSERT_EQUAL(_BV(OCIE0A), TIMSK0);
}

TEST_F(Timer0Tests, SetInterruptWithCompareBEnabled_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_B);
    TEST_ASSERT_EQUAL(_BV(OCIE0B), TIMSK0);
}

TEST_F(Timer0Tests, SetInterruptWithOverflowEnabled_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(_BV(TOIE0), TIMSK0);
}

TEST_F(Timer0Tests, SetInterruptWithAllEnabled_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(_BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0), TIMSK0);
}

TEST_F(Timer0Tests, SetInterrupt_EnablesInterruptsInStatusRegister)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
}

TEST_F(Timer0Tests, ResetInterruptWithCompareA_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A);
    TEST_ASSERT_EQUAL(0, TIMSK0);
}

TEST_F(Timer0Tests, ResetInterruptWithCompareB_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_B);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_B);
    TEST_ASSERT_EQUAL(0, TIMSK0);
}

TEST_F(Timer0Tests, ResetInterruptWithOverflow_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::OVERFLOW);
    Timer0::resetInterrupt(Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(0, TIMSK0);
}

TEST_F(Timer0Tests, ResetInterruptWithAll_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(0, TIMSK0);
}

TEST_F(Timer0Tests, ResetInterruptWithAllEnabled_SetsCorrectRegisters)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_B);
    TEST_ASSERT_BITS_LOW(_BV(OCIE0B), TIMSK0);
    TEST_ASSERT_BITS_HIGH(_BV(OCIE0A) | _BV(TOIE0), TIMSK0);
}

TEST_F(Timer0Tests, ResetInterrupt_EnablesInterruptsInStatusRegister)
{
    Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
}

TEST_F(Timer0Tests, ControlA_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCCR0A, &Timer0::controlA());
}

TEST_F(Timer0Tests, ControlB_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCCR0B, &Timer0::controlB());
}

TEST_F(Timer0Tests, CompareA_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&OCR0A, &Timer0::compareA());
}

TEST_F(Timer0Tests, CompareB_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&OCR0B, &Timer0::compareB());
}

TEST_F(Timer0Tests, Counter_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCNT0, &Timer0::counter());
}

TEST_F(Timer0Tests, Interrupt_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TIMSK0, &Timer0::interrupt());
}
