/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Drivers
{

struct SerialRegisters
{
    volatile uint8_t controlA;
    volatile uint8_t controlB;
    volatile uint8_t controlC;
    volatile uint8_t _reserved_;
    union {
        struct
        {
            volatile uint8_t baudRateLow;
            volatile uint8_t baudRateHigh;
        };
        volatile uint16_t baudRate;
    };
    volatile uint8_t data;
};

} // namespace NextagEmbeddedPlatform::Drivers