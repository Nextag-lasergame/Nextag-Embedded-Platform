/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#include "NextagEmbeddedPlatform/chips/atmega328p/descriptor.h"
#else
#error Unsupported chip
#endif