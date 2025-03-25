/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "timer0_tests.h"

#include "test_utils/serial.h"

#include <avr/sleep.h>
#include <unity.h>

void setUp()
{
    Timer0::setUp();
}

void tearDown()
{
}

int main()
{
    NextagEmbeddedPlatform::TestUtils::initTestSerial();

    UNITY_BEGIN();
    Timer0::runTests();
    UNITY_END();

    sleep_cpu();
}