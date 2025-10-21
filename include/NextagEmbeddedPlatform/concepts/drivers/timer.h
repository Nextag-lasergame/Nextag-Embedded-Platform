/*
 * Copyright © 2022-2025 Tim Herreijgers
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

template <typename T>
concept timer_datatype = is_same<T, uint8_t>::value || is_same<T, uint16_t>::value;

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

template <typename T>
concept timerChipSpecialization = requires(T t) {
    { T::template getModeMaskControlA<NextagEmbeddedPlatform::Drivers::TimerMode::CTC>() } -> returns_type<uint8_t>;
    { T::template getModeMaskControlB<NextagEmbeddedPlatform::Drivers::TimerMode::CTC>() } -> returns_type<uint8_t>;
    { T::template getClockSourceMask<NextagEmbeddedPlatform::Drivers::TimerClock::SYSTEM_PRESCALER_1>() } -> returns_type<uint8_t>;
    { T::getClockSourceBitMask() } -> returns_type<uint8_t>;
    { T::timerControlA() } -> returns_type<volatile uint8_t &>;
    { T::timerControlB() } -> returns_type<volatile uint8_t &>;
    { T::outputCompareA() } -> returns_type<volatile uint8_t &>;
    { T::outputCompareB() } -> returns_type<volatile uint8_t &>;
};

} // namespace NextagEmbeddedPlatform::Concepts::Drivers