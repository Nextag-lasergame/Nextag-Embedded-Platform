/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "nextag_test/test.h"

namespace NextagTest
{

const char * Test::name() const noexcept
{
    return m_name;
}

const char * Test::file() const noexcept
{
    return m_file;
}

int Test::line() const noexcept
{
    return m_line;
}
void Test::setMetaData(const char * name, const char * file, int line)
{
    m_name = name;
    m_file = file;
    m_line = line;
}

} // namespace NextagTest