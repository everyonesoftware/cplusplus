#include "HasAllocatorBase.h"

#include "Allocator.h"

namespace e1
{
    void HasAllocatorBase::setAllocator(const P<Allocator>& allocator)
    {
        this->allocator.set(allocator);
    }

    const P<Allocator>& HasAllocatorBase::getAllocator() const
    {
        return this->allocator;
    }
}