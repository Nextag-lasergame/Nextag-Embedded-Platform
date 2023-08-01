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
    uint8_t controlA;
    uint8_t controlB;
    uint8_t controlC;
    uint8_t _reserved_;
    union
    {
        struct
        {
            uint8_t baudRateLow;
            uint8_t baudRateHigh;
        };
        uint16_t baudRate;
    };
    volatile uint8_t data;
};

} // namespace NextagEmbeddedPlatform::Drivers