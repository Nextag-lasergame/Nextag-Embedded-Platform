/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/concepts/drivers/timer.h"
#include "NextagEmbeddedPlatform/drivers/timer.h"

namespace NextagEmbeddedPlatform::Peripherals
{

inline Concepts::Drivers::timerNew auto timer0 = Drivers::Timer<uint8_t>{};

} // namespace NextagEmbeddedPlatform::Peripherals
