/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include <test_utils/serial.h>

#include <avr/sleep.h>
#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

void testFunction()
{
    TEST_ASSERT_EQUAL_INT(1, 1);
}

int main(void)
{
    NextagEmbeddedBase::TestUtils::initTestSerial();

    UNITY_BEGIN();
    RUN_TEST(testFunction);
    UNITY_END();

    sleep_cpu();
}