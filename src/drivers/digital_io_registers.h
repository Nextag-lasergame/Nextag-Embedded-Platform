/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Drivers
{

struct DigitalIORegisters
{
    volatile uint8_t pin;
    volatile uint8_t direction;
    volatile uint8_t port;
};

}