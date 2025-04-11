#pragma once

#include "HasAllocator.h"

namespace e1
{
    /**
     * A mix-in type that specifies that the derived type contains an Allocator. This is
     * particularly useful for data structures that need to dynamically allocate memory.
     */
    class HasAllocatorBase : public HasAllocator
    {
    public:
        virtual ~HasAllocatorBase() = default;

        /**
         * Set the Allocator for this object.
         */
        virtual void setAllocator(const P<Allocator>& allocator);

        /**
         * Get this object's Allocator.
         */
        virtual const P<Allocator>& getAllocator() const;

    protected:
        HasAllocatorBase() = default;

    private:
        P<Allocator> allocator;
    };
}