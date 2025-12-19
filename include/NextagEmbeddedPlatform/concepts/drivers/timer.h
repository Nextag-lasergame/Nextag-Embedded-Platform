/*
 * Copyright © 2022-2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

namespace NextagEmbeddedPlatform
{

template <typename T>
concept HasTimerDataType = requires(T t) {
    typename T::DataType;
};

template <typename T>
concept HasTimerControlA = requires(T t) {
    T::controlA;
};

template <typename T>
concept HasTimerControlB = requires(T t) {
    T::controlB;
};

template <typename T>
concept HasTimerControlAB = requires(T t) {
    T::controlAB;
};

template <typename T>
concept HasTimerCompareA = requires(T t) {
    T::compareA;
};

template <typename T>
concept HasTimerCompareB = requires(T t) {
    T::compareB;
};

template <typename T>
concept HasTimerCounter = requires(T t) {
    T::counter;
};

template <typename T>
concept HasTimerInterrupt = requires(T t) {
    T::interrupt;
    typename T::Interrupt;
};

template <typename T>
concept HasTimerMode = requires(T t) {
    typename T::TimerMode;
    T::timerModeMask;
};

template <typename T>
concept HasCombinedTimerMode = HasTimerControlAB<T> && HasTimerMode<T>;

template <typename T>
concept HasClockSelect = requires(T t) {
    typename T::ClockSelect;
    T::clockSelectMask;
};

template <typename T>
concept HasClockSelectNoClockSource = HasClockSelect<T> && requires(T t) {
    T::ClockSelect::NO_CLOCK_SOURCE;
};

} // namespace NextagEmbeddedPlatform