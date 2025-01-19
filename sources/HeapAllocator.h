#ifndef E1_HEAPALLOCATOR_H
#define E1_HEAPALLOCATOR_H

#include "Allocator.h"

namespace e1
{
    class HeapAllocator : public Allocator
    {
    public:
        explicit HeapAllocator() = default;
        virtual ~HeapAllocator() = default;

        /**
         * Allocate a block of memory that contains the provided amount of bytes.
         * @param byteCount The number of bytes to allocate and return.
         */
        virtual void* allocate(int byteCount);

        /**
         * Free a block of memory that was previously allocated.
         * @param bytes The block of memory to free.
         * @param byteCount The number of bytes contained by the memory block.
         */
        virtual void free(void* bytes, int byteCount);
    };
}

#endif