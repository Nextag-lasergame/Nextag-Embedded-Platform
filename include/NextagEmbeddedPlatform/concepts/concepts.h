/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

namespace NextagEmbeddedPlatform::Concepts
{

template <typename T>
concept is_default_constructable = requires(T t) {
    T{};
};

} // namespace NextagEmbeddedPlatform::Concepts