/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/timer.h"

#include "timer8bit.h"

namespace NextagEmbeddedPlatform::Drivers
{

static timer auto timer0Definition = Timer8Bit{reinterpret_cast<TimerRegister<uint8_t>*>(0x44)};
Timer & Timer::timer0 = timer0Definition;

} // namespace NextagEmbeddedPlatform::Drivers
