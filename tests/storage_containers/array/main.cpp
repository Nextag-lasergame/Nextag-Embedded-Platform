/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include <test_utils/serial.h>

#include <NextagEmbeddedPlatform/storage_containers/array.h>

#include <avr/sleep.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::StorageContainers;

void setUp()
{
}

void tearDown()
{
}

void arrayWithSize10ReturnsSize10()
{
    Array<int, 10> array{};
    TEST_ASSERT_EQUAL(10, array.size());
}

int main()
{
    NextagEmbeddedPlatform::TestUtils::initTestSerial();

    UNITY_BEGIN();
    RUN_TEST(arrayWithSize10ReturnsSize10);
    UNITY_END();

    sleep_cpu();
}