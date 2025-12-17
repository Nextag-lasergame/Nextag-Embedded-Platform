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

TEST_F(Timer1Tests, SetModeToFastPWM8Bits_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_8_BIT);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM10), _BV(WGM12)), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToFastPWM9Bits_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_9_BIT);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM11), _BV(WGM12)), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToFastPWM10Bits_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::FAST_PWM_10_BIT);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM10) | _BV(WGM11), _BV(WGM12)), Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPWMPhaseAndFrequencyCorrectInputCaptureTop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_AND_FREQUENCY_CORRECT_INPUT_CAPTURE_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(0, _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPWMPhaseAndFrequencyCorrectComparaATop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_AND_FREQUENCY_CORRECT_COMPARE_A_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM10), _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPWMPhaseCorrectInputCaptureTop_SetsCorrectRegisters)
{
    Timer1::setMode(Timer1::TimerMode::PWM_PHASE_CORRECT_INPUT_CAPTURE_TOP);
    TEST_ASSERT_EQUAL(NextagEmbeddedPlatform::createCombinedRegisterValue(_BV(WGM11), _BV(WGM13)),
                      Timer1::Descriptor::controlAB);
}

TEST_F(Timer1Tests, SetModeToPWMPhaseCorrectComparaATop_SetsCorrectRegisters)
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

// TEST_F(Timer1Tests, SetClockSource_SetsCorrectRegisterValue)
// {
//     Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_1);
//     TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS00), TCCR0B, "Prescaler 1 was not set correctly");
//
//     Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_8);
//     TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS01), TCCR0B, "Prescaler 8 was not set correctly");
//
//     Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_64);
//     TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS01) | _BV(CS00), TCCR0B, "Prescaler 64 was not set correctly");
//
//     Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_256);
//     TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS02), TCCR0B, "Prescaler 256 was not set correctly");
//
//     Timer0::setClockSource(Timer0::ClockSelect::PRESCALER_1024);
//     TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS02) | _BV(CS00), TCCR0B, "Prescaler 1024 was not set correctly");
//
//     Timer0::setClockSource(Timer0::ClockSelect::EXTERNAL_SOURCE_FALLING_EDGE);
//     TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS02) | _BV(CS01), TCCR0B, "Prescaler falling edge was not set correctly");
//
//     Timer0::setClockSource(Timer0::ClockSelect::EXTERNAL_SOURCE_RISING_EDGE);
//     TEST_ASSERT_BITS_MESSAGE(0xFF, _BV(CS02) | _BV(CS01) | _BV(CS00), TCCR0B, "Prescaler rising edge was not set correctly");
// }
//
// TEST_F(Timer1Tests, Stop_ClearsPrescalerBitsInRegister)
// {
//     TCCR0B = 0xFF;
//     Timer0::stop();
//
//     TEST_ASSERT_EQUAL(0xFF & ~((_BV(CS02) | _BV(CS01) | _BV(CS00))), TCCR0B);
// }
//
// TEST_F(Timer1Tests, SetCompareA_SetsCorrectRegisters)
// {
//     Timer0::setCompareA(200);
//     TEST_ASSERT_EQUAL(200, OCR0A);
//
//     Timer0::setCompareA(100);
//     TEST_ASSERT_EQUAL(100, OCR0A);
// }
//
// TEST_F(Timer1Tests, SetCompareB_SetsCorrectRegisters)
// {
//     Timer0::setCompareB(200);
//     TEST_ASSERT_EQUAL(200, OCR0B);
//
//     Timer0::setCompareB(100);
//     TEST_ASSERT_EQUAL(100, OCR0B);
// }
//
// TEST_F(Timer1Tests, ResetCounter_SetsCounterBackToZero)
// {
//     TCNT0 = 100;
//     Timer0::resetCounter();
//     TEST_ASSERT_EQUAL(0, TCNT0);
// }
//
// TEST_F(Timer1Tests, SetInterruptWithCompareAEnabled_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A);
//     TEST_ASSERT_EQUAL(_BV(OCIE0A), TIMSK0);
// }
//
// TEST_F(Timer1Tests, SetInterruptWithCompareBEnabled_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_B);
//     TEST_ASSERT_EQUAL(_BV(OCIE0B), TIMSK0);
// }
//
// TEST_F(Timer1Tests, SetInterruptWithOverflowEnabled_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::OVERFLOW);
//     TEST_ASSERT_EQUAL(_BV(TOIE0), TIMSK0);
// }
//
// TEST_F(Timer1Tests, SetInterruptWithAllEnabled_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
//     TEST_ASSERT_EQUAL(_BV(OCIE0A) | _BV(OCIE0B) | _BV(TOIE0), TIMSK0);
// }
//
// TEST_F(Timer1Tests, SetInterrupt_EnablesInterruptsInStatusRegister)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
//     TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
// }
//
// TEST_F(Timer1Tests, ResetInterruptWithCompareA_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A);
//     Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A);
//     TEST_ASSERT_EQUAL(0, TIMSK0);
// }
//
// TEST_F(Timer1Tests, ResetInterruptWithCompareB_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_B);
//     Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_B);
//     TEST_ASSERT_EQUAL(0, TIMSK0);
// }
//
// TEST_F(Timer1Tests, ResetInterruptWithOverflow_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::OVERFLOW);
//     Timer0::resetInterrupt(Timer0::Interrupt::OVERFLOW);
//     TEST_ASSERT_EQUAL(0, TIMSK0);
// }
//
// TEST_F(Timer1Tests, ResetInterruptWithAll_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
//     Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
//     TEST_ASSERT_EQUAL(0, TIMSK0);
// }
//
// TEST_F(Timer1Tests, ResetInterruptWithAllEnabled_SetsCorrectRegisters)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
//     Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_B);
//     TEST_ASSERT_BITS_LOW(_BV(OCIE0B), TIMSK0);
//     TEST_ASSERT_BITS_HIGH(_BV(OCIE0A) | _BV(TOIE0), TIMSK0);
// }
//
// TEST_F(Timer1Tests, ResetInterrupt_EnablesInterruptsInStatusRegister)
// {
//     Timer0::setInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
//     Timer0::resetInterrupt(Timer0::Interrupt::COMPARE_A, Timer0::Interrupt::COMPARE_B, Timer0::Interrupt::OVERFLOW);
//     TEST_ASSERT_BITS_HIGH(_BV(SREG_I), SREG);
// }
//
// TEST_F(Timer1Tests, ControlA_ReturnsReferenceToCorrectRegister)
// {
//     TEST_ASSERT_EQUAL(&TCCR0A, &Timer0::controlA());
// }
//
// TEST_F(Timer1Tests, ControlB_ReturnsReferenceToCorrectRegister)
// {
//     TEST_ASSERT_EQUAL(&TCCR0B, &Timer0::controlB());
// }
//
// TEST_F(Timer1Tests, CompareA_ReturnsReferenceToCorrectRegister)
// {
//     TEST_ASSERT_EQUAL(&OCR0A, &Timer0::compareA());
// }
//
// TEST_F(Timer1Tests, CompareB_ReturnsReferenceToCorrectRegister)
// {
//     TEST_ASSERT_EQUAL(&OCR0B, &Timer0::compareB());
// }
//
// TEST_F(Timer1Tests, Counter_ReturnsReferenceToCorrectRegister)
// {
//     TEST_ASSERT_EQUAL(&TCNT0, &Timer0::counter());
// }
//
// TEST_F(Timer1Tests, Interrupt_ReturnsReferenceToCorrectRegister)
// {
//     TEST_ASSERT_EQUAL(&TIMSK0, &Timer0::interrupt());
// }