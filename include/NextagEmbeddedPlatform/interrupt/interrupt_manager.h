/*
 * Copyright © 2025 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "interrupts.h"

#include <inttypes.h>
#include <avr/interrupt.h>

namespace NextagEmbeddedPlatform::Interrupt
{

template<typename T>
concept Invokable = requires(T t)
{
    T::operator();
};

template<InterruptIdentifier Num, typename InterruptHandler>
struct is_handler_for_interrupt
{
    static constexpr bool value = InterruptHandler::interruptNum() == Num;
};

template<InterruptIdentifier Num, typename ... InterruptHandlers>
struct has_handler_for_interrupt
{
    static constexpr bool value = (is_handler_for_interrupt<Num, InterruptHandlers>::value || ...);
};

template<InterruptIdentifier Num, Invokable Fun>
struct InterruptDescriptor
{
    [[nodiscard]] static consteval auto interruptNum()
    {
        return Num;
    }

    static constexpr void operator()()
    {
        Fun{}();
    }
};

template<typename... Interrupts>
struct InterruptManager
{
    template<InterruptIdentifier Num>
    static consteval auto run()
    {
        return []__attribute__((noreturn))()
        {
            asm("jmp __bad_interrupt");
            while(true);
        };
    }

    template<InterruptIdentifier Num>
    static consteval auto run() requires has_handler_for_interrupt<Num, Interrupts...>::value
    {
        return [](){(([](auto interrupt){
            if constexpr (decltype(interrupt)::interruptNum() == Num)
            {
                interrupt();
            }
        }(Interrupts{})), ...);};
    }
};

template <typename...> inline auto interrupts = InterruptManager<>{};

template<typename Manager>
struct InterruptWrapper2
{
    template<InterruptIdentifier Num>
    static consteval auto operator()()
    {
        return Manager::template run<Num>();
    }
};

struct InterruptWrapper
{
    template<typename... S> requires(sizeof...(S) == 0)
    static consteval auto getWrapper()
    {
        return InterruptWrapper2<decltype(interrupts<S...>)>{};
    }
};

inline constexpr uint8_t TIMER0_COMPARE_A = TIMER0_COMPA_vect_num;
inline constexpr uint8_t TIMER0_COMPARE_B = TIMER0_COMPB_vect_num;

} // namespace NextagEmbeddedPlatform::Interrupt

#define INTERRUPT_HANDLER_IMPLEMENTATION(InterruptVect, InterruptId)                                                            \
ISR(InterruptVect)                                                                                                              \
{                                                                                                                               \
    decltype(Interrupt::InterruptWrapper::getWrapper<>())::operator()<InterruptId>()();                                         \
}

#define INTERRUPT_HANDLERS                                                                                                      \
INTERRUPT_HANDLER_IMPLEMENTATION(TIMER0_COMPA_vect, NextagEmbeddedPlatform::Interrupt::InterruptIdentifier::TIMER0_COMPARE_A);  \
INTERRUPT_HANDLER_IMPLEMENTATION(TIMER0_COMPB_vect, NextagEmbeddedPlatform::Interrupt::InterruptIdentifier::TIMER0_COMPARE_B);
