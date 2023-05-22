/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/pin_definitions/pin_definitions.h"

namespace NextagEmbeddedPlatform::Drivers
{

enum class Mode
{
    INPUT,
    OUTPUT
};

enum class State
{
    HIGH,
    LOW
};

struct DigitalIORegisters;

class DigitalIO
{
public:
    explicit DigitalIO(Pins pin);

    void setPinMode(Mode mode) noexcept;
    void setState(State state) noexcept;
    [[nodiscard]] State getState() noexcept;

private:
    uint8_t m_bit;
    DigitalIORegisters * m_registers;
};

} // namespace NextagEmbeddedPlatform::Drivers