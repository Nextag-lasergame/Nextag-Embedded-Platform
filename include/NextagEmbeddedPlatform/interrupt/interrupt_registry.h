/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "NextagEmbeddedPlatform/interrupt/interrupts.h"

namespace NextagEmbeddedPlatform::Interrupt
{
    class InterruptRegistry
    {
    public:
        InterruptRegistry() = delete;

        static void enableInterrupt(Interrupt interrupt);
    };
}
