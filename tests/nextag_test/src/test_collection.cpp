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
    UnityBegin(PSTR("N/A"));
    for (size_t i = 0; i < m_testList.size(); i++)
    {
        auto & test = *m_testList.at(i);
        char testFileBuffer[64] = {0};
        char testNameBuffer[128] = {0};

        strncpy_P(testFileBuffer, test.file(), 63);
        strncpy_P(testNameBuffer, test.name(), 127);

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