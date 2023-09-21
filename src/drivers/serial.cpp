/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/serial.h"

#include "serial_registers.h"

#include <avr/interrupt.h>
#include <avr/io.h>

#include <math.h>
#include <string.h>

namespace NextagEmbeddedPlatform::Drivers
{

Serial Serial::serial{};

[[nodiscard]] static uint16_t calculateBaudRateRegisterValue(int32_t baudRate);

struct SerialCallback
{
    void (*txInterruptFunction)(void);
    void (*rxInterruptFunction)(uint8_t);
};

static SerialCallback serialCallbacks{};

NextagEmbeddedPlatform::Drivers::Serial::Serial()
{
    m_registers = reinterpret_cast<SerialRegisters *>(0xC0);
}

void Serial::begin(uint32_t baudrate)
{
    const auto baud = calculateBaudRateRegisterValue(baudrate);
    m_registers->baudRate = baud;

    cli();
    m_registers->controlB = _BV(RXCIE0) | _BV(TXCIE0) | _BV(TXEN0) | _BV(RXEN0);
    m_registers->controlC = _BV(UCSZ01) | _BV(UCSZ00);
    sei();

    serialCallbacks.txInterruptFunction = []() {
        auto & serial = Serial::serial;

        if (serial.m_txBuffer.count() > 0)
        {
            serial.m_registers->data = serial.m_txBuffer.pop();
        }
    };

    serialCallbacks.rxInterruptFunction = [](uint8_t byte) {
        auto & serial = Serial::serial;

        serial.m_rxBuffer.push_back(byte);
    };
}

void Serial::sendByte(uint8_t byte)
{
    while (!(m_registers->controlA & _BV(UDRE0))) {}

    m_registers->data = byte;
}

void Serial::print(const uint8_t * bytes, uint16_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        m_txBuffer.push_back(bytes[i]);
    }

    m_registers->data = m_txBuffer.pop();
}

void Serial::print(const char * msg)
{
    const auto messageLength = strlen(msg);
    print(reinterpret_cast<const uint8_t *>(msg), messageLength);
}

void Serial::println(const char * msg)
{
    const auto messageLength = strlen(msg);
    println(reinterpret_cast<const uint8_t *>(msg), messageLength);
}

void Serial::println(const uint8_t * bytes, uint16_t count)
{
    static const uint8_t newlineCharacter = '\n';

    print(bytes, count);
    print(&newlineCharacter, 1);
}

size_t Serial::available()
{
    return m_rxBuffer.count();
}

uint8_t Serial::read()
{
    return m_rxBuffer.count() > 0 ? m_rxBuffer.pop() : 0;
}

uint8_t Serial::peek()
{
    return m_rxBuffer.peek();
}

static uint16_t calculateBaudRateRegisterValue(int32_t baudRate)
{
    return static_cast<uint16_t>(round(F_CPU / 16.0 / baudRate - 1.));
}

ISR(USART_RX_vect)
{
    if (serialCallbacks.rxInterruptFunction != nullptr)
    {
        serialCallbacks.rxInterruptFunction(UDR0);
    }
}

ISR(USART_TX_vect)
{
    if (serialCallbacks.txInterruptFunction != nullptr)
    {
        serialCallbacks.txInterruptFunction();
    }
}

} // namespace NextagEmbeddedPlatform::Drivers