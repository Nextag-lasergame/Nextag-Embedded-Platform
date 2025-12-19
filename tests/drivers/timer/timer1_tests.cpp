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

class Timer1Tests : public NextagTest::Test
{
public:
    void setUp() override
    {
        cli();
        TCCR1A = 0;
        TCCR1B = 0;
        OCR1A = 0;
        OCR1B = 0;
        TIMSK1 = 0;
        TCNT1 = 0;
    }
};


TEST_F(Timer1Tests, SetModeToNormal_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::NORMAL);
    TEST_ASSERT_EQUAL(0, Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPwmPhaseCorrect8Bit_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_CORRECT_8_BIT);
    TEST_ASSERT_EQUAL(_BV(WGM10), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPwmPhaseCorrect9Bit_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_CORRECT_9_BIT);
    TEST_ASSERT_EQUAL(_BV(WGM11), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPwmPhaseCorrect10Bit_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_CORRECT_10_BIT);
    TEST_ASSERT_EQUAL(_BV(WGM10) | _BV(WGM11), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToCTC_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::CTC);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(0, _BV(WGM12)), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToFastPwm8Bits_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_8_BIT);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM10), _BV(WGM12)), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToFastPwm9Bits_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_9_BIT);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM11), _BV(WGM12)), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToFastPwm10Bits_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_10_BIT);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM10) | _BV(WGM11), _BV(WGM12)), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPwmPhaseAndFrequencyCorrectInputCaptureTop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_AND_FREQUENCY_CORRECT_INPUT_CAPTURE_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(0, _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPwmPhaseAndFrequencyCorrectComparaATop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_AND_FREQUENCY_CORRECT_COMPARE_A_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM10), _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPwmPhaseCorrectInputCaptureTop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_CORRECT_INPUT_CAPTURE_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM11), _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPwmPhaseCorrectComparaATop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_CORRECT_COMPARE_A_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM10) | _BV(WGM11), _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToCtcInputCaptureTop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::CTC_INPUT_CAPTURE_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(0, _BV(WGM12) | _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToFastPwmInputCaptureTop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_INPUT_CAPTURE_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM11), _BV(WGM12) | _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToFastPwmCompareATop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_COMPARE_A_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM10) | _BV(WGM11), _BV(WGM12) | _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}
TEST_F(Timer1Tests, SetModeToNormal_AfterSetToFastPwmCompareATop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_COMPARE_A_TOP);
    Timer1::setMode(Timer1::TimerMode::NORMAL);

    TEST_ASSERT_EQUAL(0, Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetClockSource_SetsCorrectRegisterValue)
{
    Timer1::setClockSource(Timer1::ClockSelect::PRESCALER_1);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS10), TCCR1B, "Prescaler 1 was not set correctly");

    Timer1::setClockSource(Timer1::ClockSelect::PRESCALER_8);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS11), TCCR1B, "Prescaler 8 was not set correctly");

    Timer1::setClockSource(Timer1::ClockSelect::PRESCALER_64);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS11) | _BV(CS10), TCCR1B, "Prescaler 64 was not set correctly");

    Timer1::setClockSource(Timer1::ClockSelect::PRESCALER_256);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS12), TCCR1B, "Prescaler 256 was not set correctly");

    Timer1::setClockSource(Timer1::ClockSelect::PRESCALER_1024);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS12) | _BV(CS10), TCCR1B, "Prescaler 1024 was not set correctly");

    Timer1::setClockSource(Timer1::ClockSelect::EXTERNAL_SOURCE_FALLING_EDGE);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS12) | _BV(CS11), TCCR1B, "Prescaler falling edge was not set correctly");

    Timer1::setClockSource(Timer1::ClockSelect::EXTERNAL_SOURCE_RISING_EDGE);
    TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS12) | _BV(CS11) | _BV(CS10), TCCR1B, "Prescaler rising edge was not set correctly");
}

TEST_F(Timer1Tests, Stop_ClearsPrescalerBitsInRegister)
{
    TCCR1B = 0xFF;
    Timer1::stop();

    TEST_ASSERT_EQUAL(0xFF & ~((_BV(CS12) | _BV(CS11) | _BV(CS10))), TCCR1B);
}

TEST_F(Timer1Tests, SetCompareA_SetsCorrectRegisters)
{
    Timer1::setCompareA(200);
    TEST_ASSERT_EQUAL(200, OCR1A);

    Timer1::setCompareA(10'000);
    TEST_ASSERT_EQUAL(10'000, OCR1A);
}

TEST_F(Timer1Tests, SetCompareB_SetsCorrectRegisters)
{
    Timer1::setCompareB(200);
    TEST_ASSERT_EQUAL(200, OCR1B);

    Timer1::setCompareB(10'000);
    TEST_ASSERT_EQUAL(10'000, OCR1B);
}

TEST_F(Timer1Tests, ResetCounter_SetsCounterBackToZero)
{
    TCNT1 = 10'000;
    Timer1::resetCounter();
    TEST_ASSERT_EQUAL(0, TCNT1);
}

TEST_F(Timer1Tests, SetInterruptWithCompareAEnabled_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_A);
    TEST_ASSERT_EQUAL(_BV(OCIE1A), TIMSK1);
}

TEST_F(Timer1Tests, SetInterruptWithCompareBEnabled_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_B);
    TEST_ASSERT_EQUAL(_BV(OCIE1B), TIMSK1);
}

TEST_F(Timer1Tests, SetInterruptWithOverflowEnabled_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(_BV(TOIE1), TIMSK1);
}

TEST_F(Timer1Tests, SetInterruptWithInputCaptureEnabled_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::INPUT_CAPTURE);
    TEST_ASSERT_EQUAL(_BV(ICIE1), TIMSK1);
}

TEST_F(Timer1Tests, SetInterruptWithAllEnabled_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_A, Timer1::Interrupt::COMPARE_B, Timer1::Interrupt::OVERFLOW, Timer1::Interrupt::INPUT_CAPTURE);
    TEST_ASSERT_EQUAL(_BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0) | _BV(ICIE1), TIMSK1);
}

TEST_F(Timer1Tests, SetInterrupt_EnablesInterruptsInStatusRegister)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_A, Timer1::Interrupt::COMPARE_B, Timer1::Interrupt::OVERFLOW, Timer1::Interrupt::INPUT_CAPTURE);
    TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
}

TEST_F(Timer1Tests, ResetInterruptWithCompareA_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_A);
    Timer1::resetInterrupt(Timer1::Interrupt::COMPARE_A);
    TEST_ASSERT_EQUAL(0, TIMSK1);
}

TEST_F(Timer1Tests, ResetInterruptWithCompareB_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_B);
    Timer1::resetInterrupt(Timer1::Interrupt::COMPARE_B);
    TEST_ASSERT_EQUAL(0, TIMSK1);
}

TEST_F(Timer1Tests, ResetInterruptWithOverflow_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::OVERFLOW);
    Timer1::resetInterrupt(Timer1::Interrupt::OVERFLOW);
    TEST_ASSERT_EQUAL(0, TIMSK1);
}

TEST_F(Timer1Tests, ResetInterruptWithInputCaptureEnabled_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::INPUT_CAPTURE);
    Timer1::resetInterrupt(Timer1::Interrupt::INPUT_CAPTURE);
    TEST_ASSERT_EQUAL(0, TIMSK1);
}

TEST_F(Timer1Tests, ResetInterruptWithAll_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_A, Timer1::Interrupt::COMPARE_B, Timer1::Interrupt::OVERFLOW, Timer1::Interrupt::INPUT_CAPTURE);
    Timer1::resetInterrupt(Timer1::Interrupt::COMPARE_A, Timer1::Interrupt::COMPARE_B, Timer1::Interrupt::OVERFLOW, Timer1::Interrupt::INPUT_CAPTURE);
    TEST_ASSERT_EQUAL(0, TIMSK1);
}

TEST_F(Timer1Tests, ResetInterruptWithAllEnabled_SetsCorrectRegisters)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_A, Timer1::Interrupt::COMPARE_B, Timer1::Interrupt::OVERFLOW, Timer1::Interrupt::INPUT_CAPTURE);
    Timer1::resetInterrupt(Timer1::Interrupt::COMPARE_B);
    TEST_ASSERT_EQUAL(_BV(OCIE1A) | _BV(TOIE1) | _BV(ICIE1), TIMSK1);
}

TEST_F(Timer1Tests, ResetInterrupt_EnablesInterruptsInStatusRegister)
{
    Timer1::setInterrupt(Timer1::Interrupt::COMPARE_A, Timer1::Interrupt::COMPARE_B, Timer1::Interrupt::OVERFLOW, Timer1::Interrupt::INPUT_CAPTURE);
    Timer1::resetInterrupt(Timer1::Interrupt::COMPARE_A, Timer1::Interrupt::COMPARE_B, Timer1::Interrupt::OVERFLOW, Timer1::Interrupt::INPUT_CAPTURE);
    TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
}

TEST_F(Timer1Tests, ControlA_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCCR1A, &Timer1::controlA());
}

TEST_F(Timer1Tests, ControlB_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCCR1B, &Timer1::controlB());
}

TEST_F(Timer1Tests, CompareA_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&OCR1A, &Timer1::compareA());
}

TEST_F(Timer1Tests, CompareB_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&OCR1B, &Timer1::compareB());
}

TEST_F(Timer1Tests, Counter_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TCNT1, &Timer1::counter());
}

TEST_F(Timer1Tests, Interrupt_ReturnsReferenceToCorrectRegister)
{
    TEST_ASSERT_EQUAL(&TIMSK1, &Timer1::interrupt());
}