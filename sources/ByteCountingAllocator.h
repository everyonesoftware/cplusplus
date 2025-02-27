#pragma once

#include "AllocatorDecorator.h"

namespace e1
{
    class ByteCountingAllocator : public AllocatorDecorator
    {
    public:
        ByteCountingAllocator(const P<Allocator>& inner);
        virtual ~ByteCountingAllocator() = default;

        virtual void* allocate(int byteCount);
        virtual void free(void* bytes, int byteCount);

        int getAllocatedByteCount() const;

    private:
        int allocatedByteCount;
    };
}