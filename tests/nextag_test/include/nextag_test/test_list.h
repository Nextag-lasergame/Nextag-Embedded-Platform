/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once
#include "test.h"

#include <stdio.h>

namespace NextagTest
{

struct TestListNode
{
    Test * test{nullptr};
    TestListNode * next{nullptr};

    void * operator new(size_t size)
    {
        return malloc(size);
    }

    void operator delete(void * ptr)
    {
        free(ptr);
    }
};

class TestList
{
public:
    TestList() = default;
    ~TestList();
    TestList(const TestList &) = delete;
    TestList(TestList &&) = delete;
    TestList & operator=(const TestList &) = delete;
    TestList & operator=(TestList &&) = delete;

    [[nodiscard]] auto size() const noexcept -> size_t;
    [[nodiscard]] auto at(size_t index) const noexcept -> Test *;
    void add(Test * test);

private:
    TestListNode * m_head{nullptr};
    size_t m_size{0};
};

} // namespace NextagTest