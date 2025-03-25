/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

namespace NextagEmbeddedPlatform::Interrupt
{

enum class InterruptIdentifier
{
    TIMER0_COMPARE_A,
    TIMER0_COMPARE_B,
    TIMER0_OVERFLOW
};

} // namespace NextagEmbeddedPlatform::Interrupt