/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "NextagEmbeddedPlatform/storage_containers/array.h"
#include "NextagEmbeddedPlatform/interrupt/interrupts.h"

namespace NextagEmbeddedPlatform::Interrupt
{
    using InterruptFunction = void(*)();

    struct InterruptPair
    {
        constexpr InterruptPair(Interrupt _interrupt, InterruptFunction _function) : interrupt(_interrupt), function(_function)
        {

        }

        Interrupt interrupt;
        InterruptFunction function;
    };

    template<InterruptPair... Values>
    constexpr bool contains(Interrupt interrupt)
    {
        return ((interrupt == Values.interrupt) || ...);
    }

    template<InterruptPair... interruptFunctions>
    class InterruptRegistry
    {
    public:
//        static constexpr InterruptRegistry& getInstance()
//        {
//            static InterruptRegistry instance{};
//            return instance;
//
//        }

        constexpr void timer0CompareMatchA() const
        {
            executeCallbackForInterrupt<Interrupt::TIMER0_COMPARE_A>();
        }

        constexpr void timer0CompareMatchB() const
        {
            executeCallbackForInterrupt<Interrupt::TIMER0_COMPARE_B>();
        }

    private:
//        InterruptRegistry() = default;

        template<Interrupt InterruptNumber>
        constexpr void executeCallbackForInterrupt() const
        {
            const auto findInterrupt = [](StorageContainers::Array<InterruptPair, sizeof...(interruptFunctions)> pairs, Interrupt interrupt)
            {
                for(size_t i = 0; i < sizeof...(interruptFunctions); i++)
                {
                    if (pairs[i].interrupt == interrupt)
                    {
                        return pairs[i].function;
                    }
                }
                return static_cast<InterruptFunction>([](){});
            };

            constexpr StorageContainers::Array<InterruptPair, sizeof...(interruptFunctions)> pairs = { { interruptFunctions... } };
            constexpr auto function = findInterrupt(pairs, InterruptNumber);

            if constexpr (contains<interruptFunctions...>(InterruptNumber))
            {
                function();
            }
            else
            {
                __asm("jmp __bad_interrupt");
            }
        }
    };
}
