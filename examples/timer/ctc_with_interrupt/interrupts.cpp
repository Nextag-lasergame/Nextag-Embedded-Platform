/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

/*
 * At the moment this weird way of registering the interrupts is required. The
 */

#include "NextagEmbeddedPlatform/interrupt/interrupt_registry.h"

void onTimer0CompareMatchA();

static constexpr auto interruptRegistry = NextagEmbeddedPlatform::Interrupt::InterruptRegistry<
    {NextagEmbeddedPlatform::Interrupt::Interrupt::TIMER0_COMPARE_A, onTimer0CompareMatchA}
>{};

#include "NextagEmbeddedPlatform/interrupt/interrupt_handlers.h"