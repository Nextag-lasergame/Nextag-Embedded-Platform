/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/digital_io.h"

namespace NextagEmbeddedBase::Drivers
{

DigitalIO::DigitalIO(NextagEmbeddedBase::Pins pin) :
    m_bit(static_cast<uint16_t>(pin) & 0xFF),
    m_registers(reinterpret_cast<DigitalIORegisters *>(static_cast<uint16_t>(pin) >> 8 & 0xFF))
{
}

void DigitalIO::setPinMode(PinMode mode)
{
    m_registers->direction |= mode == PinMode::INPUT ? 0 << m_bit : 1 << m_bit;
}

}
