/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <stdlib.h>

namespace NextagTest
{

class Test
{
public:
    explicit Test() = default;

    virtual void operator()() = 0;

    virtual void setUp() {}
    virtual void tearDown() {}

    [[nodiscard]] const char * name() const noexcept;
    [[nodiscard]] const char * file() const noexcept;
    [[nodiscard]] int line() const noexcept;

    void setMetaData(const char * name, const char * file, int line);

protected:
    ~Test() = default;

private:
    const char * m_name = "";
    const char * m_file = "";
    int m_line = 0;
};

} // namespace NextagTest