#pragma once

#include <type_traits>
#include <functional>

namespace fun
{
    template<class... Ts> struct compound : Ts... { 
        constexpr compound(Ts && ... t) : Ts{t}... {}

        using Ts::operator()...; 
    };

    template<class... Ts> compound(Ts...) -> compound<std::decay_t<Ts>...>;
}

