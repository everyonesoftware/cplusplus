#ifndef E1_ACTION_H
#define E1_ACTION_H

#include <functional>

namespace e1
{
    /**
     * A function that doesn't return anything.
     */
    template<typename ...TArgs>
    using Action = std::function<void(TArgs...)>;
}

#endif