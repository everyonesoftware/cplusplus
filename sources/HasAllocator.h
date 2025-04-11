#pragma once

#include "Pointer.h"

namespace e1
{
    /**
     * Forward declaration for Allocator type.
     */
    class Allocator;

    /**
     * An interface that specifies that an implementing type can set and get an Allocator.
     */
    class HasAllocator
    {
    public:
        virtual ~HasAllocator() = default;

        /**
         * Set the Allocator for this object. This should only be called once.
         */
        virtual void setAllocator(const P<Allocator>& allocator) = 0;

        /**
         * Get this object's Allocator.
         */
        virtual const P<Allocator>& getAllocator() const = 0;
    };
}