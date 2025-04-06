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

    void* AllocatorDecorator::allocate(std::size_t byteCount)
    {
        return this->inner->allocate(byteCount);
    }

    void AllocatorDecorator::free(void* bytes, std::size_t byteCount)
    {
        this->inner->free(bytes, byteCount);
    }
}