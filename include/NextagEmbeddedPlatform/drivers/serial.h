/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Drivers
{

struct SerialRegisters;

class Serial
{
public:
    Serial();
    void begin(uint32_t baudrate);

    void sendByte(uint8_t byte);

private:
    SerialRegisters * m_registers;
};

} // namespace NextagEmbeddedPlatform::Drivers
