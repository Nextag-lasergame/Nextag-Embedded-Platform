/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/chips/chip_descriptor.h"
#include "NextagEmbeddedPlatform/concepts/typetraits.h"
#include "NextagEmbeddedPlatform/drivers/timer.h"

namespace NextagEmbeddedPlatform
{

template <typename T>
concept HasTimer0 = requires(T t) {
    typename T::Timer0;
};

template <typename T>
concept HasTimer1 = requires(T t) {
    typename T::Timer1;
};

template <typename T>
concept HasTimer2 = requires(T t) {
    typename T::Timer2;
};

struct NotExisting;

struct EmptyDef
{
    using Timer0 = NotExisting;
    using Timer1 = NotExisting;
    using Timer2 = NotExisting;
};

namespace Peripherals
{

using Timer0 = Drivers::Timer<Concepts::conditional<HasTimer0<ChipDescriptor>, ChipDescriptor, EmptyDef>::type::Timer0>;
using Timer1 = Drivers::Timer<Concepts::conditional<HasTimer1<ChipDescriptor>, ChipDescriptor, EmptyDef>::type::Timer1>;
using Timer2 = Drivers::Timer<Concepts::conditional<HasTimer2<ChipDescriptor>, ChipDescriptor, EmptyDef>::type::Timer2>;

} // namespace Peripherals

} // namespace NextagEmbeddedPlatform