/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Drivers
{

enum class Pins : uint16_t
{
    B0 = 0x2300,
    B1 = 0x2301,
    B2 = 0x2302,
    B3 = 0x2303,
    B4 = 0x2304,
    B5 = 0x2305,
    B6 = 0x2306,
    B7 = 0x2307,

    C0 = 0x2600,
    C1 = 0x2601,
    C2 = 0x2602,
    C3 = 0x2603,
    C4 = 0x2604,
    C5 = 0x2605,
    C6 = 0x2606,

    D0 = 0x2900,
    D1 = 0x2901,
    D2 = 0x2902,
    D3 = 0x2903,
    D4 = 0x2904,
    D5 = 0x2905,
    D6 = 0x2906,
    D7 = 0x2907,
};

} // namespace NextagEmbeddedPlatform::Drivers