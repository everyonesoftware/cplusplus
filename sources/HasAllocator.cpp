#include "HasAllocator.h"

#include "Allocator.h"

namespace e1
{
    void HasAllocator::setAllocator(const P<Allocator>& allocator)
    {
        this->allocator.set(allocator);
    }

    const P<Allocator>& HasAllocator::getAllocator() const
    {
        return this->allocator;
    }
}