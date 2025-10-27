/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

namespace NextagEmbeddedPlatform::Concepts
{

template <class T, class U>
struct is_same
{
    static constexpr bool value = false;
};

template <class T>
struct is_same<T, T>
{
    static constexpr bool value = true;
};

template <bool B, class T, class F>
struct conditional
{
    using type = T;
};

template <class T, class F>
struct conditional<false, T, F>
{
    using type = F;
};

} // namespace NextagEmbeddedPlatform::Concepts