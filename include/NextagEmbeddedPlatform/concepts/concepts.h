/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "typetraits.h"

namespace NextagEmbeddedPlatform::Concepts
{

template <typename T>
concept is_default_constructable = requires(T t) {
    T{};
};

template <typename T>
concept returns_void = is_same<void, T>::value;

template <typename T, typename ReturnType>
concept returns_type = is_same<ReturnType, T>::value;

template <typename T, typename U>
concept same_as = is_same<T, U>::value;

template <typename T, typename... Ts>
concept all_same_as = (same_as<T, Ts> && ...);

} // namespace NextagEmbeddedPlatform::Concepts