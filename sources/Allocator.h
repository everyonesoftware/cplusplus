#ifndef E1_ALLOCATOR_H
#define E1_ALLOCATOR_H

#include "HasThisPointer.h"
#include "NotCopyable.h"
#include "Pointer.h"

namespace e1
{
    /**
     * An object that can allocate bytes/memory that other objects can be created in.
     */
    class Allocator
        : public HasThisPointer,
          public NotCopyable
    {
    public:
        explicit Allocator()
            : HasThisPointer(this)
        {
        };
        virtual ~Allocator() {};

        /**
         * Create a new object of type T. Any arguments provided will be passed to T's constructor.
         */
        template <typename T, typename ...TArgs>
        Pointer<T> create(TArgs... args);

        /**
         * Allocate a block of memory that contains the provided amount of bytes.
         * @param byteCount The number of bytes to allocate and return.
         */
        virtual void* allocate(int byteCount) = 0;
        /**
         * Free a block of memory that was previously allocated.
         * @param bytes The block of memory to free.
         * @param byteCount The number of bytes contained by the memory block.
         */
        virtual void free(void* bytes, int byteCount) = 0;
    };
}

#include "HasAllocator.h"
#include "HasThisPointer.h"
#include "RefCountedValue.h"

namespace e1
{
    template <typename T, typename ...TArgs>
    Pointer<T> Allocator::create(TArgs... args)
    {
        const int refCountedValueByteCount = sizeof(RefCountedValue<T>);
        void* bytes = this->allocate(refCountedValueByteCount);

        RefCountedValue<T>* refCountedValue = new(bytes) RefCountedValue<T>(args...);
        
        T* valuePointer = refCountedValue->getValuePointer();
        
        int* refCountPointer = refCountedValue->getRefCountPointer();

        const Action<> releaseAction = [=, this]
        {
            refCountedValue->~RefCountedValue();
            this->free(refCountedValue, refCountedValueByteCount);
        };

        Pointer<T> result(valuePointer, refCountPointer, releaseAction);

        // if constexpr (std::is_base_of_v<HasAllocator,T>)
        // {
        //     result.template as<HasAllocator>()->setAllocator(this->getThisPointer());
        // }

        if constexpr (std::is_base_of_v<HasThisPointer,T>)
        {
            result.template as<HasThisPointer>()->setThisPointer(result);
        }

        return result;
    }
}

#endif