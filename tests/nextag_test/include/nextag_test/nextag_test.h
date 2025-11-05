/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "nextag_test/test.h"
#include "nextag_test/test_collection.h"

#define CONCAT(a, b)              a##b
#define CONCAT_TEST_NAME(a, b, c) CONCAT(a##b, c)

#define TEST_IMPL(TestSuite, TestName, DisplayName)                              \
    class TestName : public TestSuite                                            \
    {                                                                            \
    public:                                                                      \
        TestName()                                                               \
        {                                                                        \
            NextagTest::TestCollection::addTest(this);                           \
        }                                                                        \
        void operator()() override;                                              \
    };                                                                           \
    static TestName CONCAT(test_, TestName);                                     \
    static const auto CONCAT(initializedTest_, TestName) = [](TestName & test) { \
        test.setMetaData(#TestSuite "\\" #DisplayName, __FILE__, __LINE__);      \
        return true;                                                             \
    }(CONCAT(test_, TestName));                                                  \
    void TestName::operator()()

#define TEST_F(TestSuite, TestName) TEST_IMPL(TestSuite, CONCAT_TEST_NAME(Test_, TestName, __COUNTER__), TestName)

#define TEST(TestName)              TEST_F(NextagTest::Test, TestName)
