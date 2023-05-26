/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#include <test_utils/serial.h>

#include <NextagEmbeddedPlatform/storage_containers/circular_buffer.h>

#include <avr/sleep.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::StorageContainers;

static CircularBuffer<uint8_t , 10> s_buffer;

void setUp()
{
    s_buffer = CircularBuffer<uint8_t , 10>{};
}

void tearDown()
{
}

void emptyBufferReturnsBufferAvailableBytesOf0()
{
    TEST_ASSERT_EQUAL(0, s_buffer.count());
}

void addingToBufferReturnsCorrectAvailability()
{
    s_buffer.push_back(10);
    s_buffer.push_back(20);
    TEST_ASSERT_EQUAL(2, s_buffer.count());
}

void addingToBufferReturnsTrueOnSuccess()
{
    TEST_ASSERT_TRUE(s_buffer.push_back(0));
}

void addingToBufferWhenBufferIsFullReturnFalse()
{
    for(auto i = 0; i < 10; i++)
    {
        TEST_ASSERT_TRUE_MESSAGE(s_buffer.push_back(0), "Something went wrong when filling up the buffer");
    }

    TEST_ASSERT_FALSE(s_buffer.push_back(0));
}

void poppingFromBufferChangesAvailability()
{
    s_buffer.push_back(0);
    s_buffer.push_back(0);
    [[maybe_unused]] const auto _ = s_buffer.pop();

    TEST_ASSERT_EQUAL(1, s_buffer.count());
}

void poppingFromBufferReturnsCorrectData()
{
    s_buffer.push_back(10);
    s_buffer.push_back(20);

    TEST_ASSERT_EQUAL(10, s_buffer.pop());
    TEST_ASSERT_EQUAL(20, s_buffer.pop());
}

void poppingFromBufferSizeOverflowReturnsCorrectData()
{
    for(auto i = 0; i < 10; i++)
    {
        s_buffer.push_back(0);
        [[maybe_unused]] const auto _ = s_buffer.pop();
    }

    s_buffer.push_back(10);
    TEST_ASSERT_EQUAL(10, s_buffer.pop());
}

void checkingAvailabilityOnCounterOverflowStillWorks()
{
    for(uint32_t i = 0; i < 65534 ; i++)
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

void poppingOnEmptyBufferReturnsDefaultConstructedObject()
{
    s_buffer.push_back(10);
    TEST_ASSERT_EQUAL(10, s_buffer.pop());
    TEST_ASSERT_EQUAL(uint16_t{}, s_buffer.pop());
}

void peekDoesntChangeAvailability()
{
    s_buffer.push_back(10);
    s_buffer.push_back(20);
    [[maybe_unused]] const auto _ = s_buffer.peek();

    TEST_ASSERT_EQUAL(2, s_buffer.count());
}

void peekReturnCorrectValue()
{
    s_buffer.push_back(10);
    s_buffer.push_back(20);

    TEST_ASSERT_EQUAL(10, s_buffer.peek());
    [[maybe_unused]] const auto _ = s_buffer.pop();
    TEST_ASSERT_EQUAL(20, s_buffer.peek());
}

int main()
{
   NextagEmbeddedPlatform::TestUtils::initTestSerial();

   UNITY_BEGIN();
   RUN_TEST(emptyBufferReturnsBufferAvailableBytesOf0);
   RUN_TEST(addingToBufferReturnsCorrectAvailability);
   RUN_TEST(addingToBufferReturnsTrueOnSuccess);
   RUN_TEST(addingToBufferWhenBufferIsFullReturnFalse);
   RUN_TEST(poppingFromBufferChangesAvailability);
   RUN_TEST(poppingFromBufferReturnsCorrectData);
   RUN_TEST(poppingFromBufferSizeOverflowReturnsCorrectData);
   RUN_TEST(checkingAvailabilityOnCounterOverflowStillWorks);
   RUN_TEST(poppingOnEmptyBufferReturnsDefaultConstructedObject);
   RUN_TEST(peekDoesntChangeAvailability);
   RUN_TEST(peekReturnCorrectValue);
   UNITY_END();

   sleep_cpu();
}