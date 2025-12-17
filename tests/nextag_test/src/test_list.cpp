/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "nextag_test/test_list.h"

#include <stdio.h>

namespace NextagTest
{

auto TestList::size() const noexcept -> size_t
{
    return m_size;
}

auto TestList::at(size_t index) const noexcept -> Test *
{
    if (index >= m_size)
    {
        return nullptr;
    }

    return m_tests[index];
}

void TestList::add(Test * test)
{
    if (m_size + 1 == MAX_TESTS)
    {
        asm("jmp __bad_interrupt");
    }

    m_tests[m_size++] = test;
}

} // namespace NextagTest