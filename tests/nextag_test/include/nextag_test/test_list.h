/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "test.h"

namespace NextagTest
{

static constexpr size_t MAX_TESTS = 128;

class TestList
{
public:
    TestList() = default;
    ~TestList() = default;
    TestList(const TestList &) = delete;
    TestList(TestList &&) = delete;
    TestList & operator=(const TestList &) = delete;
    TestList & operator=(TestList &&) = delete;

    [[nodiscard]] auto size() const noexcept -> size_t;
    [[nodiscard]] auto at(size_t index) const noexcept -> Test *;
    void add(Test * test);

private:
    Test * m_tests[MAX_TESTS];
    size_t m_size{0};
};

} // namespace NextagTest