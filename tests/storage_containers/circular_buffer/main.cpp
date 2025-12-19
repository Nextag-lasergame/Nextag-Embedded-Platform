/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include <nextag_test/nextag_test.h>
#include <nextag_test/serial.h>

#include <NextagEmbeddedPlatform/storage_containers/circular_buffer.h>

#include <avr/sleep.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::StorageContainers;

void setUp()
{
}

void tearDown()
{
}

class CircularBufferTest : public NextagTest::Test
{
protected:
    CircularBuffer<uint8_t, 10> s_buffer{};
};

TEST_F(CircularBufferTest, emptyBufferReturnsBufferAvailableBytesOf0)
{
    TEST_ASSERT_EQUAL(0, s_buffer.count());
}

TEST_F(CircularBufferTest, addingToBufferReturnsCorrectAvailability)
{
    s_buffer.push_back(10);
    s_buffer.push_back(20);
    TEST_ASSERT_EQUAL(2, s_buffer.count());
}

TEST_F(CircularBufferTest, addingToBufferReturnsTrueOnSuccess)
{
    TEST_ASSERT_TRUE(s_buffer.push_back(0));
}

TEST_F(CircularBufferTest, addingToBufferWhenBufferIsFullReturnFalse)
{
    for (auto i = 0; i < 10; i++)
    {
        TEST_ASSERT_TRUE_MESSAGE(s_buffer.push_back(0), "Something went wrong when filling up the buffer");
    }

    TEST_ASSERT_FALSE(s_buffer.push_back(0));
}

TEST_F(CircularBufferTest, poppingFromBufferChangesAvailability)
{
    s_buffer.push_back(0);
    s_buffer.push_back(0);
    [[maybe_unused]] const auto _ = s_buffer.pop();

    TEST_ASSERT_EQUAL(1, s_buffer.count());
}

TEST_F(CircularBufferTest, poppingFromBufferReturnsCorrectData)
{
    s_buffer.push_back(10);
    s_buffer.push_back(20);

    TEST_ASSERT_EQUAL(10, s_buffer.pop());
    TEST_ASSERT_EQUAL(20, s_buffer.pop());
}

TEST_F(CircularBufferTest, poppingFromBufferSizeOverflowReturnsCorrectData)
{
    for (auto i = 0; i < 10; i++)
    {
        s_buffer.push_back(0);
        [[maybe_unused]] const auto _ = s_buffer.pop();
    }

    s_buffer.push_back(10);
    TEST_ASSERT_EQUAL(10, s_buffer.pop());
}

TEST_F(CircularBufferTest, checkingAvailabilityOnCounterOverflowStillWorks)
{
    for (uint32_t i = 0; i < 65534; i++)
    {
        s_buffer.push_back(0);
        [[maybe_unused]] const auto _ = s_buffer.pop();
    }

    TEST_ASSERT_EQUAL_MESSAGE(0, s_buffer.count(), "The buffer availability is not zero before overflowing");

    s_buffer.push_back(0);
    s_buffer.push_back(0);
    s_buffer.push_back(0);
    s_buffer.push_back(0);
    s_buffer.push_back(0);

    TEST_ASSERT_EQUAL(5, s_buffer.count());
}

TEST_F(CircularBufferTest, poppingOnEmptyBufferReturnsDefaultConstructedObject)
{
    s_buffer.push_back(10);
    TEST_ASSERT_EQUAL(10, s_buffer.pop());
    TEST_ASSERT_EQUAL(uint16_t{}, s_buffer.pop());
}

TEST_F(CircularBufferTest, peekDoesntChangeAvailability)
{
    s_buffer.push_back(10);
    s_buffer.push_back(20);
    [[maybe_unused]] const auto _ = s_buffer.peek();

    TEST_ASSERT_EQUAL(2, s_buffer.count());
}

TEST_F(CircularBufferTest, peekReturnCorrectValue)
{
    s_buffer.push_back(10);
    s_buffer.push_back(20);

    TEST_ASSERT_EQUAL(10, s_buffer.peek());
    [[maybe_unused]] const auto _ = s_buffer.pop();
    TEST_ASSERT_EQUAL(20, s_buffer.peek());
}

int main()
{
    NextagTest::initTestSerial();
    NextagTest::TestCollection::runAllTests();

    sleep_cpu();
}