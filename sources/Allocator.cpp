#include "Allocator.h"

namespace e1
{
    const Pointer<Allocator> Allocator::getThisPointer() const
    {
        return this->HasThisPointer::getThisPointer<Allocator>();
    }
}