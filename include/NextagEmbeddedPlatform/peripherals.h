/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/concepts/drivers/timer.h"
#include "NextagEmbeddedPlatform/drivers/timer8bit.h"

namespace NextagEmbeddedPlatform::Peripherals
{

Concepts::Drivers::timer auto & timer0 = Drivers::Timer8Bit::timer0;

} // namespace NextagEmbeddedPlatform::Peripherals
