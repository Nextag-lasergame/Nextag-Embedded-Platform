/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "array.h"

#include <inttypes.h>

namespace NextagEmbeddedPlatform::StorageContainers
{

//template<typename T>
//concept is_default_constructable = requires(T t)
//{
//    T{};
//};

/**
 *
 * \brief FIFO fixed size circular buffer
 *
 * The CircularBuffer is a fixed-size data structure where the front and end of the buffer are connected, eliminating the need for data to be moved around
 * when written or read from. The buffer interface follows the FIFO (first in, first out) principle, meaning that the data can only be added to the back, and read from the front.
 * Since the CircularBuffer is allocated on the stack and utilizes an array it can't be resized during runtime. The CircularBuffer is also only able to store a single datatype. Both
 * can be configured using the template arguments.
 *
 * @tparam DataType The datatype stored within the buffer
 * @tparam Size The size of the buffer
 */
template<typename DataType, size_t Size>
class CircularBuffer
{
public:
    /**
     * \brief Returns the amount of data (of type DataType) that's currently stored in the buffer.
     *
     * Returns the amount of data (of type DataType) that's currently stored in the buffer.
     *
     * @return The amount of data in the buffer
     */
    [[nodiscard]] size_t count() const noexcept
    {
        return m_head - m_tail;
    }

    /**
     * \brief Adds data to the end of the buffer
     *
     * Adds data to the end of the buffer. This is done by making a copy of the passed in data. The function will return true if
     * successful, and false if unsuccessful (a.k.a. buffer is full).
     *
     * @param data The data to add to the buffer
     * @return whether the operation is successful
     */
    bool push_back(const DataType & data) noexcept
    {
        if(count() >= Size)
        {
            return false;
        }

        m_array[m_head % Size] = data;
        m_head ++;
        return true;
    }

    /**
     * \brief Returns the data that is in the front of te buffer and removes this data from the buffer.
     *
     * Returns the data that is in the front of te buffer and removes this data from the buffer.
     * Even the buffer is empty it will return a default constructed object. Since
     * it gives no warning that the object is default constructed, and thus was not in the buffer, \ref count should be checked
     * before popping to see if there is any data in the buffer.
     *
     * @return The data
     */
    [[nodiscard]] DataType pop() noexcept
    {
        if(count() <= 0)
            return {};

        return m_array[m_tail++ % Size];
    }

    [[nodiscard]] DataType peek() noexcept
    {
        if(count() <= 0)
            return {};

        return m_array[m_tail % Size];
    }

private:
    Array<DataType, Size> m_array;
    uint16_t m_head{};
    uint16_t m_tail{};
};

} // namespace NextagEmbeddedPlatform::StorageContainers