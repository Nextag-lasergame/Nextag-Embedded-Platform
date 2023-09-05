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

void setUp()
{
}

void tearDown()
{
}

void setModeSetsTimer0ModeCorrectly()
{
    auto & timer0 = Timer::timer0;

    timer0.setMode(TimerMode::CTC);

    TEST_ASSERT_BITS_HIGH(_BV(WGM01), TCCR0B);
}

int main()
{
   NextagEmbeddedPlatform::TestUtils::initTestSerial();

   UNITY_BEGIN();
   RUN_TEST(setModeSetsTimer0ModeCorrectly);
   UNITY_END();

   sleep_cpu();
}