/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/chips/atmega328p/timers.h"
#include "NextagEmbeddedPlatform/concepts/drivers/timer.h"
#include "NextagEmbeddedPlatform/drivers/timer.h"

namespace NextagEmbeddedPlatform::Peripherals
{

inline Concepts::Drivers::timerNew auto timer0 = Drivers::Timer<uint8_t, Chips::Atmega328p::Timer0Specialization>{};

static_assert(Concepts::Drivers::timerNew<Drivers::Timer<uint8_t, Chips::Atmega328p::Timer0Specialization>>);

} // namespace NextagEmbeddedPlatform::Peripherals
