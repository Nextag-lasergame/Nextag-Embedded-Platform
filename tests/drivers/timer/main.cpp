/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "nextag_test/nextag_test.h"
#include "nextag_test/serial.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <unity.h>

void setUp()
{
}

void tearDown()
{
}

int main()
{
    NextagTest::initTestSerial();
    NextagTest::TestCollection::runAllTests();

    cli();
    sleep_cpu();
}