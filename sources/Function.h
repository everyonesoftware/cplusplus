#pragma once

#include <functional>

namespace e1
{
    /**
     * A function that returns a value.
     */
    template <typename TReturn, typename... TArgs>
    using Function = typename std::enable_if<
        !std::is_void<TReturn>::value,
        std::function<TReturn(TArgs...)>
    >::type;
}