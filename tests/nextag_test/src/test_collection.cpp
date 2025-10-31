/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "nextag_test/test_collection.h"

#include <unity.h>

namespace NextagTest
{

TestList TestCollection::m_testList;

static Test * testToExecute = nullptr;

void TestCollection::runAllTests()
{
    UNITY_BEGIN();
    for (size_t i = 0; i < m_testList.size(); i++)
    {
        auto & test = *m_testList.at(i);
        UnitySetTestFile(test.file());
        testToExecute = &test;
        test.setUp();
        UnityDefaultTestRun([]() { testToExecute->operator()(); }, test.name(), test.line());
        test.tearDown();
    }
    UNITY_END();
}

void TestCollection::addTest(Test * test)
{
    m_testList.add(test);
}

} // namespace NextagTest