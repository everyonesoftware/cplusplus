#include "AllocatorDecorator.h"

namespace e1
{
    AllocatorDecorator::AllocatorDecorator(const P<Allocator>& inner)
        : inner(inner)
    {
    }

    AllocatorDecorator::~AllocatorDecorator()
    {
    }

    void* AllocatorDecorator::allocate(int byteCount)
    {
        return this->inner->allocate(byteCount);
    }

    void AllocatorDecorator::free(void* bytes, int byteCount)
    {
        this->inner->free(bytes, byteCount);
    }
}