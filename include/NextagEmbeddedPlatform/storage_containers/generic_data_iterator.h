/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

namespace NextagEmbeddedPlatform::StorageContainers
{

/**
 * Template class for a data operator. The iterator assumes the collection has the
 * [] operator overloaded to read data from the collection.
 */
template <typename T, typename Collection>
class CollectionIterator
{
public:
    CollectionIterator(Collection & collection, const size_t index) :
        m_collection(collection), m_index(index)
    {
    }

    bool operator!=(const CollectionIterator & other) const
    {
        return m_index != other.m_index;
    }

    const T & operator*() const
    {
        return m_collection[m_index];
    }

    const CollectionIterator & operator++()
    {
        ++m_index;
        return *this;
    }

private:
    Collection & m_collection;
    size_t m_index;
};

} // namespace NextagEmbeddedPlatform::StorageContainers
