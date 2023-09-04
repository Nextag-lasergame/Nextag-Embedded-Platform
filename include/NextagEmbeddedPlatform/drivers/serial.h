/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/storage_containers/circular_buffer.h"

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Drivers
{

struct SerialRegisters;

class Serial
{
public:
    ~Serial() = default;
    Serial(Serial &) = delete;
    Serial(Serial &&) = delete;
    Serial & operator=(Serial&) = delete;
    Serial & operator=(Serial&&) = delete;

    void begin(uint32_t baudrate);

    void sendByte(uint8_t byte);

    void print(const char * msg);
    void print(const uint8_t * bytes, size_t count);

    void println(const char * msg);
    void println(const uint8_t * bytes, size_t count);

    [[nodiscard]] size_t available();
    [[nodiscard]] uint8_t read();
    [[nodiscard]] uint8_t peek();

    static Serial serial;

protected:
    Serial();

private:
    SerialRegisters * m_registers;

    StorageContainers::CircularBuffer<uint8_t, 32> m_txBuffer{};
    StorageContainers::CircularBuffer<uint8_t, 32> m_rxBuffer{};
};

} // namespace NextagEmbeddedPlatform::Drivers
