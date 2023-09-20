/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include <test_utils/serial.h>

#include <NextagEmbeddedPlatform/storage_containers/array.h>

#include <avr/sleep.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::StorageContainers;

static Array<uint32_t, 10> s_array;

void setUp()
{
    s_array = Array<uint32_t, 10>{};
}

void tearDown()
{
}

void arrayWithSize10ReturnsSize10()
{
    TEST_ASSERT_EQUAL_INT32(10, s_array.size());
}

void addingToArrayAddToArrayCorrectly()
{
    s_array[0] = 100;
    TEST_ASSERT_EQUAL_INT32(100, s_array[0]);
}

void addingTwoItemsToArrayAddToArrayCorrectly()
{
    s_array[1] = 200;
    s_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(200, s_array[1]);
    TEST_ASSERT_EQUAL_INT32(1000000, s_array[2]);
}

void accessingItemUsingAtWorksCorrectly()
{
    s_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(s_array[2], s_array.at(2));
}

void accessingFirstElementUsingDataFunctionWorksCorrectly()
{
    s_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(s_array[2], *((s_array.data()) + 2));
}

void arraySupportsRangeBasedForLoop()
{
    for (const auto & _ : s_array)
    {
        (void) _;
    }
}

void constArraySupportsRangeBasedForLoop()
{
    const Array<uint32_t, 5> array{};

    for (const auto & _ : array)
    {
        (void) _;
    }
}

int main()
{
    NextagEmbeddedPlatform::TestUtils::initTestSerial();

    UNITY_BEGIN();
    RUN_TEST(arrayWithSize10ReturnsSize10);
    RUN_TEST(addingToArrayAddToArrayCorrectly);
    RUN_TEST(addingTwoItemsToArrayAddToArrayCorrectly);
    RUN_TEST(accessingItemUsingAtWorksCorrectly);
    RUN_TEST(accessingFirstElementUsingDataFunctionWorksCorrectly);
    RUN_TEST(arraySupportsRangeBasedForLoop);
    RUN_TEST(constArraySupportsRangeBasedForLoop);
    UNITY_END();

    sleep_cpu();
}