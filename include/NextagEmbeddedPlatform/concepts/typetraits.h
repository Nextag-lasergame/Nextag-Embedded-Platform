/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

namespace NextagEmbeddedPlatform::Concepts
{

template<class T, class U>
struct is_same
{
    static constexpr bool value = false;
};

template<class T>
struct is_same<T, T>
{
    static constexpr bool value = true;
};

} // namespace NextagEmbeddedPlatform::Concepts