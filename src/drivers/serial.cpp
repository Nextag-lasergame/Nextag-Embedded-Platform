/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/serial.h"

#include "serial_registers.h"

#include <avr/io.h>
#include <math.h>

namespace NextagEmbeddedPlatform::Drivers
{

static uint16_t calculateBaudRateRegisterValue(int32_t baudRate);

Serial::Serial()
{
    m_registers = reinterpret_cast<SerialRegisters *>(0xC0);
}

void Serial::begin(int32_t baudRate)
{
    const auto baud = calculateBaudRateRegisterValue(baudRate);
    m_registers->baudRate = baud;

    m_registers->controlB = _BV(TXEN0);
    m_registers->controlC = _BV(UCSZ01) | _BV(UCSZ00);
}

static uint16_t calculateBaudRateRegisterValue(int32_t baudRate)
{
    return static_cast<uint16_t>(round(F_CPU / 16.0 / baudRate - 1.));
}

} // namespace NextagEmbeddedPlatform::Drivers
