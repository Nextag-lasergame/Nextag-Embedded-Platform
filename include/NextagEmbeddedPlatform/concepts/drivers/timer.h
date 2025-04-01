/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "NextagEmbeddedPlatform/concepts/concepts.h"
#include "NextagEmbeddedPlatform/drivers/timer_clock.h"
#include "NextagEmbeddedPlatform/drivers/timer_mode.h"
#include "NextagEmbeddedPlatform/drivers/timer_result.h"

#include <inttypes.h>

namespace NextagEmbeddedPlatform::Concepts::Drivers
{

template<typename T>
concept timer_datatype = is_same<T, uint8_t>::value || is_same<T, uint16_t>::value;

template <typename T>
concept timer = requires(T t, NextagEmbeddedPlatform::Drivers::TimerMode mode, uint16_t value, NextagEmbeddedPlatform::Drivers::TimerClock clock) {
    { t.setMode(mode) } -> returns_void;
    { t.setCompareA(value) } -> returns_void;
    { t.setCompareB(value) } -> returns_void;
    { t.setClockSource(clock) } -> returns_type<NextagEmbeddedPlatform::Drivers::TimerResult>;
    { t.stop() } -> returns_void;
};

template <typename T, typename DataType>
concept timerSpecialized = timer_datatype<DataType> && requires(T t) {
    { t.template setMode<NextagEmbeddedPlatform::Drivers::TimerMode::CTC>() } -> returns_void;
    { t.template setCompareA<DataType{0}>() } -> returns_void;
    { t.template setCompareB<DataType{0}>() } -> returns_void;
    { t.template setClockSource<NextagEmbeddedPlatform::Drivers::TimerClock::SYSTEM_PRESCALER_1>() } -> returns_void;
    { t.stop() } -> returns_void;
};

template <typename T>
concept timerNew = timerSpecialized<T, uint8_t> || timerSpecialized<T, uint16_t>;

} // namespace NextagEmbeddedPlatform::Concepts::Drivers