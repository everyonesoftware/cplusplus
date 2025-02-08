#pragma once

#include "Action.h"
#include "NotCopyable.h"

namespace e1
{
    /**
     * A reference counter for a resource.
     */
    class ReferenceCount : NotCopyable
    {
    public:
        /**
         * Create a new ReferenceCount object with the provided cleanupAction.
         */
        ReferenceCount(Action<> cleanupAction);

        /**
         * Get the number of references.
         */
        int getCount() const;

        /**
         * Increment the count of references to the value.
         */
        void increment();

        /**
         * Decrement the count of references to the value. The value's cleanupAction will be invoked
         * if the reference count is decremented to zero.
         */
        void decrement();

    private:
        int referenceCount;
        Action<> cleanupAction;
    };
}