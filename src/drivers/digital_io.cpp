/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/digital_io.h"

#include "digital_io_registers.h"

namespace NextagEmbeddedPlatform::Drivers
{

DigitalIO::DigitalIO(Pins pin) :
    m_bit(static_cast<uint16_t>(pin) & 0xFF),
    m_registers(reinterpret_cast<DigitalIORegisters *>(static_cast<uint16_t>(pin) >> 8 & 0xFF))
{
}

void DigitalIO::setPinMode(Mode mode) noexcept
{
    m_registers->direction = mode == Mode::INPUT ?
                                 m_registers->direction & ~(1 << m_bit):
                                 m_registers->direction | (1 << m_bit);
}

void DigitalIO::setState(State state) noexcept
{
    m_registers->port = state == State::LOW ?
                                 m_registers->port & ~(1 << m_bit):
                                 m_registers->port | (1 << m_bit);
}

[[nodiscard]] State DigitalIO::getState() noexcept
{
    const auto registerBitMask = m_registers->pin & (1 << m_bit);
    return registerBitMask > 0 ? State::HIGH : State::LOW;
}

}
