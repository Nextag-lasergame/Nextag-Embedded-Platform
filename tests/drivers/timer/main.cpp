/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#include <test_utils/serial.h>

#include <NextagEmbeddedPlatform/drivers/timer.h>

#include <avr/sleep.h>
#include <avr/io.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::Drivers;

//void setUp()
//{
//}
//
//void tearDown()
//{
//}
//
//void Timer0_SetModeToCTC_SetsCorrectRegisters()
//{
//    auto & timer0 = Timer::timer0;
//
//    timer0.setMode(TimerMode::CTC);
//
//    TEST_ASSERT_BITS_HIGH(_BV(WGM01), TCCR0A);
//}
//
//void Timer0_SetCompareA_SetsCorrectRegisters()
//{
//    auto & timer0 = Timer::timer0;
//
//    timer0.setCompareA(200);
//    TEST_ASSERT_EQUAL(200, OCR0A);
//}
//
//void Timer0_SetCompareAToHigh_ClipsValueInRegister()
//{
//    auto & timer0 = Timer::timer0;
//
//    timer0.setCompareA(500);
//    // 244 is 500 & 0xFF
//    TEST_ASSERT_EQUAL(244, OCR0A);
//}
//
//void Timer0_SetCompareB_SetsCorrectRegisters()
//{
//    auto & timer0 = Timer::timer0;
//
//    timer0.setCompareB(100);
//    TEST_ASSERT_EQUAL(100, OCR0B);
//}
//
//void Timer0_SetCompareBToHigh_ClipsValueInRegister()
//{
//    auto & timer0 = Timer::timer0;
//
//    timer0.setCompareB(600);
//    // 88 is 600 & 0xFF
//    TEST_ASSERT_EQUAL(88, OCR0B);
//}

int main()
{
//   NextagEmbeddedPlatform::TestUtils::initTestSerial();
//
//   UNITY_BEGIN();
//   RUN_TEST(Timer0_SetModeToCTC_SetsCorrectRegisters);
//   RUN_TEST(Timer0_SetCompareA_SetsCorrectRegisters);
//   RUN_TEST(Timer0_SetCompareAToHigh_ClipsValueInRegister);
//   RUN_TEST(Timer0_SetCompareB_SetsCorrectRegisters);
//   RUN_TEST(Timer0_SetCompareBToHigh_ClipsValueInRegister);
//   UNITY_END();

    auto & timer = Timer::timer0;
    timer.setMode(TimerMode::CTC);
    timer.setCompareA(200);
    timer.setClockSource(TimerClock::SYSTEM_PRESCALER_1);

    sleep_cpu();
}