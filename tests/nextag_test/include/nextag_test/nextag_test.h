/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "nextag_test/test.h"
#include "nextag_test/test_collection.h"

#define TEST_F(TestSuite, TestName)                                            \
    class Test_##TestName : public TestSuite                                   \
    {                                                                          \
    public:                                                                    \
        Test_##TestName()                                                      \
        {                                                                      \
            NextagTest::TestCollection::addTest(this);                         \
        }                                                                      \
        void operator()() override;                                            \
    };                                                                         \
    static Test_##TestName test_##TestName;                                    \
    static const auto intializedTest_##TestName = [](Test_##TestName & test) { \
        test.setMetaData(#TestName, __FILE__, __LINE__);                       \
        return true;                                                           \
    }(test_##TestName);                                                        \
    void Test_##TestName::operator()()

#define TEST(TestName) TEST_F(NextagTest::Test, TestName)
