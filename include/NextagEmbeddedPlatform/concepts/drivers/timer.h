/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "NextagEmbeddedPlatform/concepts/concepts.h"
#include "NextagEmbeddedPlatform/drivers/timer_mode.h"
#include "NextagEmbeddedPlatform/drivers/timer_clock.h"
#include "NextagEmbeddedPlatform/drivers/timer_result.h"

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Concepts::Drivers
{

template <typename T>
concept timer = requires(T t, NextagEmbeddedPlatform::Drivers::TimerMode mode, uint16_t value, NextagEmbeddedPlatform::Drivers::TimerClock clock)
{
    {t.setMode(mode)} -> returns_void;
    {t.setCompareA(value)} -> returns_void;
    {t.setCompareB(value)} -> returns_void;
    {t.setClockSource(clock)} -> returns_type<NextagEmbeddedPlatform::Drivers::TimerResult>;
    {t.stop()} -> returns_void;
};

} // namespace NextagEmbeddedPlatform::Concepts