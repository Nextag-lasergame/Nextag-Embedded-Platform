/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "nextag_test/test.h"
#include "nextag_test/test_list.h"

namespace NextagTest
{

struct TestCollection
{
    static void runAllTests();
    static void addTest(Test * test);

private:
    static TestList m_testList;
};

} // namespace NextagTest