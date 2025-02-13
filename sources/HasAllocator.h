#pragma once

#include "Pointer.h"

namespace e1
{
    /**
     * Forward declaration for Allocator type.
     */
    class Allocator;

    /**
     * A mix-in type that specifies that the derived type contains an Allocator. This is
     * particularly useful for data structures that need to dynamically allocate memory.
     */
    class HasAllocator
    {
    public:
        /**
         * Set the Allocator for this object.
         */
        void setAllocator(const P<Allocator>& allocator);

        /**
         * Get this object's Allocator.
         */
        const P<Allocator>& getAllocator() const;

    protected:
        HasAllocator() = default;

        HasAllocator(const P<Allocator>& allocator)
            : allocator(allocator)
        {
        }

    private:
        Pointer<Allocator> allocator;
    };
}