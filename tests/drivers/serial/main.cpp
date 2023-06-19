/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include <test_utils/serial.h>

#include <NextagEmbeddedPlatform/drivers/serial.h>

#include <avr/sleep.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::Drivers;

void setUp()
{
    UBRR0H = 0;
    UBRR0L = 0;
    UCSR0A = 0;
    UCSR0B = 0;
    UCSR0C = 0;
}

void tearDown()
{
}

void callingBeginWithBaudRate9600SetsCorrectBaudRate()
{
    Serial serial{};
    serial.begin(9600);

    const auto baudRate = UBRR0;

    NextagEmbeddedPlatform::TestUtils::initTestSerial();
    TEST_ASSERT_EQUAL(103, baudRate);
}

void callingBeginWithBaudRate115200SetsCorrectBaudRate()
{
    Serial serial{};
    serial.begin(115200);

    const auto baudRate = UBRR0;

    NextagEmbeddedPlatform::TestUtils::initTestSerial();
    TEST_ASSERT_EQUAL(8, baudRate);
}

void callingBeginEnablesTransmitter()
{
    Serial serial{};
    serial.begin(9600);

    const auto registerBValues = UCSR0B;

    NextagEmbeddedPlatform::TestUtils::initTestSerial();
    TEST_ASSERT_BITS_HIGH(_BV(TXEN0), registerBValues);
}

void callingBeginSetsMessageFormatToEightBits()
{
    Serial serial{};
    serial.begin(9600);

    const auto registerCValues = UCSR0C;

    NextagEmbeddedPlatform::TestUtils::initTestSerial();
    TEST_ASSERT_BITS_HIGH(_BV(UCSZ00) | _BV(UCSZ01), registerCValues);
}

void callingBeginSetsMessageFormatToOneStopBit()
{
    Serial serial{};
    serial.begin(9600);

    const auto registerCValues = UCSR0C;

    NextagEmbeddedPlatform::TestUtils::initTestSerial();
    TEST_ASSERT_BITS_LOW(_BV(USBS0), registerCValues);
}

void callingBeginSetsMessageFormatToNoParity()
{
    Serial serial{};
    serial.begin(9600);

    const auto registerCValues = UCSR0C;

    NextagEmbeddedPlatform::TestUtils::initTestSerial();
    TEST_ASSERT_BITS_LOW(_BV(UPM00) | _BV(UPM01), registerCValues);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(callingBeginWithBaudRate9600SetsCorrectBaudRate);
    RUN_TEST(callingBeginWithBaudRate115200SetsCorrectBaudRate);
    RUN_TEST(callingBeginEnablesTransmitter);
    RUN_TEST(callingBeginSetsMessageFormatToEightBits);
    RUN_TEST(callingBeginSetsMessageFormatToOneStopBit);
    RUN_TEST(callingBeginSetsMessageFormatToNoParity);
    UNITY_END();

    sleep_cpu();
}