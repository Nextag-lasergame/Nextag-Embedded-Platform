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
    explicit Serial();

    void begin(int32_t baudRate);

    void print(const uint8_t * buffer, uint8_t size);
    void print(const char * msg);

    void println(const uint8_t * buffer, uint8_t size);
    void println(const char * msg);

    [[nodiscard]] uint8_t available();
    [[nodiscard]] uint8_t peek();

    [[nodiscard]] uint8_t readByte();
    [[nodiscard]] char readChar();

private:
    SerialRegisters * m_registers;
};

} // namespace NextagEmbeddedPlatform::Drivers