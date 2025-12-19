/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <avr/io.h>
#include <avr/pgmspace.h>

#define UNITY_OUTPUT_FLUSH()    // optional, flush UART
#define UNITY_OUTPUT_START()    // optional
#define UNITY_OUTPUT_COMPLETE() // optional

#define UNITY_PROGMEM           PROGMEM
