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

class Timer2Tests : public NextagTest::Test
{
public:
    void setUp() override
    {
        cli();
        TCCR2A = 0;
        TCCR2B = 0;
        OCR2A = 0;
        OCR2B = 0;
        TIMSK2 = 0;
        TCNT2 = 0;
    }
};

TEST_F(Timer2Tests, SetModeToNormal_SetsCorrectRegisters)
{
    Timer2::setMode(Timer2::TimerMode::NORMAL);
    TEST_ASSERT_EQUAL(0, Timer2::Descriptor::controlAB);
}

TEST_F(Timer2Tests, SetModeToPwmPhaseCorrect_SetsCorrectRegisters)
{
    Timer2::setMode(Timer2::TimerMode::PWM_PHASE_CORRECT);
    TEST_ASSERT_EQUAL(_BV(WGM20), Timer2::Descriptor::controlAB);
}

TEST_F(Timer2Tests, SetModeToCTC_SetsCorrectRegisters)
{
    Timer2::setMode(Timer2::TimerMode::CTC);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM21), 0), Timer2::Descriptor::controlAB);
}

TEST_F(Timer2Tests, SetModeToFastPwm_SetsCorrectRegisters)
{
    Timer2::setMode(Timer2::TimerMode::FAST_PWM);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM20) | _BV(WGM21), 0), Timer2::Descriptor::controlAB);
}

TEST_F(Timer2Tests, SetModeToPwmPhaseCorrectCompareA_SetsCorrectRegisters)
{
    Timer2::setMode(Timer2::TimerMode::PWM_PHASE_CORRECT_COMPARE_A_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM20), _BV(WGM22)),
                      Timer2::Descriptor::controlAB);
}

TEST_F(Timer2Tests, SetModeToFastPwmCompareA_SetsCorrectRegisters)
{
    Timer2::setMode(Timer2::TimerMode::FAST_PWM_COMPARE_A_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM20) | _BV(WGM21), _BV(WGM22)),
                      Timer2::Descriptor::controlAB);
}

TEST_F(Timer2Tests, SetModeToNormal_AfterSetToFastPwmCompareATop_SetsCorrectRegisters)
{
    Timer2::setMode(Timer2::TimerMode::FAST_PWM_COMPARE_A_TOP);
    Timer2::setMode(Timer2::TimerMode::NORMAL);

    TEST_ASSERT_EQUAL(0, Timer2::Descriptor::controlAB);
}

TEST_F(Timer2Tests, SetClockSource_SetsCorrectRegisterValue)
{
    Timer2::setClockSource(Timer2::ClockSelect::PRESCALER_1);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS20), TCCR2B, "Prescaler 1 was not set correctly");

    Timer2::setClockSource(Timer2::ClockSelect::PRESCALER_8);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS21), TCCR2B, "Prescaler 8 was not set correctly");

    Timer2::setClockSource(Timer2::ClockSelect::PRESCALER_32);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS21) | _BV(CS20), TCCR2B, "Prescaler 32 was not set correctly");

    Timer2::setClockSource(Timer2::ClockSelect::PRESCALER_64);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS22), TCCR2B, "Prescaler 64 was not set correctly");

    Timer2::setClockSource(Timer2::ClockSelect::PRESCALER_128);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS22) | _BV(CS20), TCCR2B, "Prescaler 128 was not set correctly");

    Timer2::setClockSource(Timer2::ClockSelect::PRESCALER_256);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS22) | _BV(CS21), TCCR2B, "Prescaler 256 was not set correctly");

    Timer2::setClockSource(Timer2::ClockSelect::PRESCALER_1024);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS22) | _BV(CS21) | _BV(CS20), TCCR2B, "Prescaler 1024 was not set correctly");
}

TEST_F(Timer2Tests, Stop_ClearsPrescalerBitsInRegister)
{
    TCCR2B = 0xFF;
    Timer2::stop();

    TEST_ASSERT_EQUAL(0xFF & ~((_BV(CS22) | _BV(CS21) | _BV(CS20))), TCCR2B);
}

TEST_F(Timer2Tests, SetCompareA_SetsCorrectRegisters)
{
    Timer2::setCompareA(200);
    TEST_ASSERT_EQUAL(200, OCR2A);

    Timer2::setCompareA(100);
    TEST_ASSERT_EQUAL(100, OCR2A);
}

TEST_F(Timer2Tests, SetCompareB_SetsCorrectRegisters)
{
    Timer2::setCompareB(200);
    TEST_ASSERT_EQUAL(200, OCR2B);

    Timer2::setCompareB(100);
    TEST_ASSERT_EQUAL(10'0, OCR2B);
}

TEST_F(Timer2Tests, ResetCounter_SetsCounterBackToZero)
{
    TCNT2 = 200;
    Timer2::resetCounter();
    TEST_ASSERT_EQUAL(0, TCNT2);
}

TEST_F(Timer2Tests, SetInterruptWithCompareAEnabled_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_A);
    TEST_ASSERT_EQUAL(_BV(OCIE2A), TIMSK2);
}

TEST_F(Timer2Tests, SetInterruptWithCompareBEnabled_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_B);
    TEST_ASSERT_EQUAL(_BV(OCIE2B), TIMSK2);
}

TEST_F(Timer2Tests, SetInterruptWithOverflowEnabled_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(_BV(TOIE2), TIMSK2);
}

TEST_F(Timer2Tests, SetInterruptWithAllEnabled_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_A, Timer2::Interrupt::COMPARE_B, Timer2::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(_BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0), TIMSK2);
}

TEST_F(Timer2Tests, SetInterrupt_EnablesInterruptsInStatusRegister)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_A, Timer2::Interrupt::COMPARE_B, Timer2::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
}

TEST_F(Timer2Tests, ResetInterruptWithCompareA_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_A);
    Timer2::resetInterrupt(Timer2::Interrupt::COMPARE_A);
    TEST_ASSERT_EQUAL(0, TIMSK2);
}

TEST_F(Timer2Tests, ResetInterruptWithCompareB_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_B);
    Timer2::resetInterrupt(Timer2::Interrupt::COMPARE_B);
    TEST_ASSERT_EQUAL(0, TIMSK2);
}

TEST_F(Timer2Tests, ResetInterruptWithOverflow_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::OVERFLOW);
    Timer2::resetInterrupt(Timer2::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(0, TIMSK2);
}

TEST_F(Timer2Tests, ResetInterruptWithAll_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_A, Timer2::Interrupt::COMPARE_B, Timer2::Interrupt::OVERFLOW);
    Timer2::resetInterrupt(Timer2::Interrupt::COMPARE_A, Timer2::Interrupt::COMPARE_B, Timer2::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(0, TIMSK2);
}

TEST_F(Timer2Tests, ResetInterruptWithAllEnabled_SetsCorrectRegisters)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_A, Timer2::Interrupt::COMPARE_B, Timer2::Interrupt::OVERFLOW);
    Timer2::resetInterrupt(Timer2::Interrupt::COMPARE_B);
    TEST_ASSERT_EQUAL(_BV(OCIE2A) | _BV(TOIE2), TIMSK2);
}

TEST_F(Timer2Tests, ResetInterrupt_EnablesInterruptsInStatusRegister)
{
    Timer2::setInterrupt(Timer2::Interrupt::COMPARE_A, Timer2::Interrupt::COMPARE_B, Timer2::Interrupt::OVERFLOW);
    Timer2::resetInterrupt(Timer2::Interrupt::COMPARE_A, Timer2::Interrupt::COMPARE_B, Timer2::Interrupt::OVERFLOW);
    TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
}

TEST_F(Timer2Tests, ControlA_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCCR2A, &Timer2::controlA());
}

TEST_F(Timer2Tests, ControlB_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCCR2B, &Timer2::controlB());
}

TEST_F(Timer2Tests, CompareA_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&OCR2A, &Timer2::compareA());
}

TEST_F(Timer2Tests, CompareB_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&OCR2B, &Timer2::compareB());
}

TEST_F(Timer2Tests, Counter_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCNT2, &Timer2::counter());
}

TEST_F(Timer2Tests, Interrupt_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TIMSK2, &Timer2::interrupt());
}