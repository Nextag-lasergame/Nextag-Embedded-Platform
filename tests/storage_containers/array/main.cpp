/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include <nextag_test/nextag_test.h>
#include <nextag_test/serial.h>

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

TEST(arrayWithSize10ReturnsSize10)
{
    TEST_ASSERT_EQUAL_INT32(10, s_array.size());
}

TEST(addingToArrayAddToArrayCorrectly)
{
    s_array[0] = 100;
    TEST_ASSERT_EQUAL_INT32(100, s_array[0]);
}

TEST(addingTwoItemsToArrayAddToArrayCorrectly)
{
    s_array[1] = 200;
    s_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(200, s_array[1]);
    TEST_ASSERT_EQUAL_INT32(1000000, s_array[2]);
}

TEST(accessingItemUsingAtWorksCorrectly)
{
    s_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(s_array[2], s_array.at(2));
}

TEST(accessingFirstElementUsingDataFunctionWorksCorrectly)
{
    s_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(s_array[2], *((s_array.data()) + 2));
}

TEST(arraySupportsRangeBasedForLoop)
{
    for (const auto & _ : s_array)
    {
        (void)_;
    }
}

TEST(constArraySupportsRangeBasedForLoop)
{
    const Array<uint32_t, 5> array{};

    for (const auto & _ : array)
    {
        (void)_;
    }
}

int main()
{
    NextagTest::initTestSerial();
    NextagTest::TestCollection::runAllTests();

    sleep_cpu();
}