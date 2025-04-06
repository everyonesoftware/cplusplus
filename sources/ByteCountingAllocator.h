#pragma once

#include "AllocatorDecorator.h"

namespace e1
{
    class ByteCountingAllocator : public AllocatorDecorator
    {
    public:
        ByteCountingAllocator(const P<Allocator>& inner);
        virtual ~ByteCountingAllocator() = default;

        virtual void* allocate(std::size_t byteCount);
        virtual void free(void* bytes, std::size_t byteCount);

        std::size_t getAllocatedByteCount() const;

    private:
        std::size_t allocatedByteCount;
    };
}