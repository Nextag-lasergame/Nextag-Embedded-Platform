/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

namespace NextagEmbeddedPlatform::Drivers
{

enum class TimerClock
{
    SYSTEM_PRESCALER_1,
    SYSTEM_PRESCALER_8,
    SYSTEM_PRESCALER_32, // Not supported on timer0
    SYSTEM_PRESCALER_64,
    SYSTEM_PRESCALER_128, // Not supported on timer0
    SYSTEM_PRESCALER_256,
    SYSTEM_PRESCALER_1024
};

} // namespace NextagEmbeddedPlatform::Drivers
