#include "ByteCountingAllocator.h"

namespace e1
{
    ByteCountingAllocator::ByteCountingAllocator(const P<Allocator>& inner)
        : AllocatorDecorator(inner), allocatedByteCount(0)
    {
    }

    ByteCountingAllocator::~ByteCountingAllocator()
    {
    }

    void* ByteCountingAllocator::allocate(int byteCount)
    {
        void* result = AllocatorDecorator::allocate(byteCount);
        this->allocatedByteCount += byteCount;

        return result;
    }

    void ByteCountingAllocator::free(void* bytes, int byteCount)
    {
        AllocatorDecorator::free(bytes, byteCount);

        this->allocatedByteCount -= byteCount;
    }

    int ByteCountingAllocator::getAllocatedByteCount() const
    {
        return this->allocatedByteCount;
    }
}