/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "nextag_test/test.h"
#include "nextag_test/test_collection.h"

#define TEST(TestName)                                                                                        \
    class Test_##TestName : public NextagTest::Test                                                           \
    {                                                                                                         \
    public:                                                                                                   \
        Test_##TestName()                                                                                     \
        {                                                                                                     \
            NextagTest::TestCollection::addTest(this);                                                        \
        }                                                                                                     \
        void operator()() override;                                                                           \
    };                                                                                                        \
    Test_##TestName test_##TestName = NextagTest::createTest<Test_##TestName>(#TestName, __FILE__, __LINE__); \
    void Test_##TestName::operator()()

#define TEST_F(TestSuite, TestName)                                                                           \
    class Test_##TestName : public TestSuite                                                                  \
    {                                                                                                         \
    public:                                                                                                   \
        Test_##TestName()                                                                                     \
        {                                                                                                     \
            NextagTest::TestCollection::addTest(this);                                                        \
        }                                                                                                     \
        void operator()() override;                                                                           \
    };                                                                                                        \
    Test_##TestName test_##TestName = NextagTest::createTest<Test_##TestName>(#TestName, __FILE__, __LINE__); \
    void Test_##TestName::operator()()
