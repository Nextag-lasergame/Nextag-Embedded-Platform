/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "array.h"

#include <inttypes.h>

namespace NextagEmbeddedPlatform::StorageContainers
{

template<typename T, size_t N>
class CircularBuffer
{
public:
    [[nodiscard]] size_t available() const
    {
        return m_head - m_tail;
    }

    bool push_back(const T & data)
    {
        if(available() >= N)
        {
            return false;
        }

        m_array[m_head % N] = data;
        m_head ++;
        return true;
    }

    [[nodiscard]] T pop()
    {
        if(available() <= 0)
            return {};

        return m_array[m_tail++ % N];
    }

    [[nodiscard]] T peek()
    {
        if(available() <= 0)
            return {};

        return m_array[m_tail % N];
    }

private:
    Array<T, N> m_array;
    uint16_t m_head{};
    uint16_t m_tail{};
};

} // namespace NextagEmbeddedPlatform::StorageContainers