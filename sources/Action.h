#pragma once

#include <functional>

namespace e1
{
    /**
     * A function that doesn't return anything.
     */
    template<typename ...TArgs>
    using Action = std::function<void(TArgs...)>;
}