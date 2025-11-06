/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "nextag_test/test_collection.h"

#include <avr/pgmspace.h>
#include <unity.h>

namespace NextagTest
{

TestList TestCollection::m_testList;

static Test * testToExecute = nullptr;

void TestCollection::runAllTests()
{
    UnityBegin("");
    for (size_t i = 0; i < m_testList.size(); i++)
    {
        auto & test = *m_testList.at(i);
        char testFileBuffer[128] = {0};
        char testNameBuffer[123] = {0};

        strcpy_P(testFileBuffer, test.file());
        strcpy_P(testNameBuffer, test.name());

        UnitySetTestFile(testFileBuffer);
        testToExecute = &test;
        test.setUp();
        UnityDefaultTestRun([]() {
            testToExecute->operator()();
        },
                            testNameBuffer, test.line());
        test.tearDown();
    }
    UnityEnd();
}

void TestCollection::addTest(Test * test)
{
    m_testList.add(test);
}

} // namespace NextagTest