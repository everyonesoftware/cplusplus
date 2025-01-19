#include "HeapAllocator.h"

namespace e1
{
    void* HeapAllocator::allocate(int byteCount)
    {
        return operator new(byteCount);
    }

    void HeapAllocator::free(void* bytes, int byteCount)
    {
        operator delete(bytes);
    }
}