/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "NextagEmbeddedPlatform/concepts/concepts.h"
#include "NextagEmbeddedPlatform/drivers/timer_mode.h"
#include "NextagEmbeddedPlatform/drivers/timer_clock.h"

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Concepts::Drivers
{

template <typename T>
concept timer = requires(T t, NextagEmbeddedPlatform::Drivers::TimerMode mode, uint16_t value, NextagEmbeddedPlatform::Drivers::TimerClock clock)
{
    {t.setMode(mode)} -> returns_void;
    t.setCompareA(value);
    t.setCompareB(value);
    t.setClockSource(clock);
    t.stop();
};

} // namespace NextagEmbeddedPlatform::Concepts