/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/drivers/timer.h"

namespace NextagEmbeddedPlatform::Drivers
{

Timer Timer::timer0{};

void Timer::setMode(TimerMode mode)
{
}

} // namespace NextagEmbeddedPlatform::Drivers
