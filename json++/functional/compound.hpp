#pragma once

#include <type_traits>
#include <functional>

namespace fun
{
    template<typename Callable>
    struct function;

    template<typename Ret, typename ...Args>
    struct function<Ret(Args...)>
    {
        Ret(*fn_ptr)(Args...);

        Ret operator()(Args ... args) {
            return std::invoke(fn_ptr, args...);
        }
    };

    template<typename Ret, typename ...Args>
    function(Ret(*)(Args...)) -> function<Ret(Args...)>;

    template<class... Ts> struct compound : Ts... { 
        compound(Ts && ... t) : Ts{t}... {}

        using Ts::operator()...; 
    };

    template<class... Ts> compound(Ts...) -> compound<std::decay_t<Ts>...>;
}

