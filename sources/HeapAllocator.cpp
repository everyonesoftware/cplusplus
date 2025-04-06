#include "HeapAllocator.h"

namespace e1
{
    void* HeapAllocator::allocate(std::size_t byteCount)
    {
        return operator new(byteCount);
    }

    void HeapAllocator::free(void* bytes, [[maybe_unused]] std::size_t byteCount)
    {
        operator delete(bytes);
    }
}