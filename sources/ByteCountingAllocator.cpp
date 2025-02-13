#include "ByteCountingAllocator.h"

namespace e1
{
    ByteCountingAllocator::ByteCountingAllocator(const P<Allocator>& inner)
        : AllocatorDecorator(inner), allocatedByteCount(0)
    {
    }

    void* ByteCountingAllocator::allocate(int byteCount)
    {
        void* result = this->AllocatorDecorator::allocate(byteCount);
        this->allocatedByteCount += byteCount;

        return result;
    }

    void ByteCountingAllocator::free(void* bytes, int byteCount)
    {
        this->AllocatorDecorator::free(bytes, byteCount);

        this->allocatedByteCount -= byteCount;
    }

    int ByteCountingAllocator::getAllocatedByteCount() const
    {
        return this->allocatedByteCount;
    }
}