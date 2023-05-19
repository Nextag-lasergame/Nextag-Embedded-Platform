/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/pin_definitions/pin_definitions.h"

namespace NextagEmbeddedBase::Drivers
{

enum class PinMode
{
    INPUT,
    OUTPUT
};

struct DigitalIORegisters
{
    volatile uint8_t pin;
    volatile uint8_t direction;
    volatile uint8_t port;
};

class DigitalIO
{
public:
    DigitalIO(Pins pin);

    void setPinMode(PinMode mode);
private:
    uint8_t m_bit;
    DigitalIORegisters * m_registers;
};

} // namespace NextagEmbeddedBase