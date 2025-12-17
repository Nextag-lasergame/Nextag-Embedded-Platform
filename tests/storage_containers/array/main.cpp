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

void setUp()
{
}

void tearDown()
{
}

class ArrayTest : public NextagTest::Test
{
protected:
    Array<uint32_t, 10> m_array{};
};

TEST_F(ArrayTest, arrayWithSize10ReturnsSize10)
{
    TEST_ASSERT_EQUAL_INT32(10, m_array.size());
}

TEST_F(ArrayTest, addingToArrayAddToArrayCorrectly)
{
    m_array[0] = 100;
    TEST_ASSERT_EQUAL_INT32(100, m_array[0]);
}

TEST_F(ArrayTest, addingTwoItemsToArrayAddToArrayCorrectly)
{
    m_array[1] = 200;
    m_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(200, m_array[1]);
    TEST_ASSERT_EQUAL_INT32(1000000, m_array[2]);
}

TEST_F(ArrayTest, accessingItemUsingAtWorksCorrectly)
{
    m_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(m_array[2], m_array.at(2));
}

TEST_F(ArrayTest, accessingFirstElementUsingDataFunctionWorksCorrectly)
{
    m_array[2] = 1000000;
    TEST_ASSERT_EQUAL_INT32(m_array[2], *((m_array.data()) + 2));
}

TEST_F(ArrayTest, arraySupportsRangeBasedForLoop)
{
    for (const auto & _ : m_array)
    {
        (void)_;
    }
}

TEST_F(ArrayTest, constArraySupportsRangeBasedForLoop)
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