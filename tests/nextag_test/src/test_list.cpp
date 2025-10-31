/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "nextag_test/test_list.h"

#include <stdio.h>

namespace NextagTest
{

TestList::~TestList()
{
    auto head = m_head;
    while (head != nullptr)
    {
        auto next = head->next;
        delete head;
        head = next;
    }
}

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

    auto head = m_head;
    for (size_t i = 0; i < index; i++)
    {
        head = head->next;
    }

    return head->test;
}

void TestList::add(Test * test)
{
    auto node = new TestListNode{test, nullptr};
    m_size++;

    if (m_head == nullptr)
    {
        m_head = node;
        return;
    }

    auto head = m_head;
    while (head->next != nullptr)
    {
        head = head->next;
    }
    head->next = node;
}

} // namespace NextagTest