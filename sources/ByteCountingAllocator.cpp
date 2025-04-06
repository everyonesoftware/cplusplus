#include "ByteCountingAllocator.h"

namespace e1
{
    ByteCountingAllocator::ByteCountingAllocator(const P<Allocator>& inner)
        : AllocatorDecorator(inner), allocatedByteCount(0)
    {
    }

    void* ByteCountingAllocator::allocate(std::size_t byteCount)
    {
        void* result = this->AllocatorDecorator::allocate(byteCount);
        this->allocatedByteCount += byteCount;

        return result;
    }

    void ByteCountingAllocator::free(void* bytes, std::size_t byteCount)
    {
        this->AllocatorDecorator::free(bytes, byteCount);

        this->allocatedByteCount -= byteCount;
    }

    std::size_t ByteCountingAllocator::getAllocatedByteCount() const
    {
        return this->allocatedByteCount;
    }
}