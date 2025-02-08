#pragma once

#include "HasThisPointer.h"
#include "NotCopyable.h"
#include "Pointer.h"
#include "Array.h"

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
         * Create a new Array of type T.
         */
        template <typename T>
        Pointer<Array<T>> createArray(int count);

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
#include "ReferenceCount.h"

namespace e1
{
    template <typename T, typename ...TArgs>
    Pointer<T> Allocator::create(TArgs... args)
    {
        const int valueByteCount = sizeof(T);
        const int referenceCountByteCount = sizeof(ReferenceCount);
        const int byteCount = valueByteCount + referenceCountByteCount;
        void* bytes = this->allocate(byteCount);

        T* valuePointer = reinterpret_cast<T*>(bytes);
        new(valuePointer) T(args...);

        ReferenceCount* referenceCountPointer = reinterpret_cast<ReferenceCount*>(valuePointer + 1);
        const Action<> cleanupAction = [=, this]
        {
            referenceCountPointer->~ReferenceCount();
            valuePointer->~T();
            this->free(bytes, byteCount);
        };
        new(referenceCountPointer) ReferenceCount(cleanupAction);

        Pointer<T> result(valuePointer, referenceCountPointer);

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

    template <typename T>
    Pointer<Array<T>> Allocator::createArray(int count)
    {
        const int valuesByteCount = sizeof(T) * count;
        const int arrayByteCount = sizeof(Array<T>);
        const int referenceCountByteCount = sizeof(ReferenceCount);
        const int byteCount = referenceCountByteCount + valuesByteCount + arrayByteCount;
        void* bytes = this->allocate(byteCount);

        T* valuesPointer = reinterpret_cast<T*>(bytes);
        new(valuesPointer) T[count];

        Array<T>* arrayPointer = reinterpret_cast<Array<T>*>(valuesPointer + count);
        new(arrayPointer) Array<T>(count, valuesPointer);

        ReferenceCount* referenceCountPointer = reinterpret_cast<ReferenceCount*>(arrayPointer + 1);
        const Action<> cleanupAction = [=, this]
        {
            referenceCountPointer->~ReferenceCount();
            arrayPointer->~Array();
            for (int i = 0; i < count; i++)
            {
                valuesPointer[i].~T();
            }
            this->free(bytes, byteCount);
        };
        new(referenceCountPointer) ReferenceCount(cleanupAction);

        Pointer<Array<T>> result(arrayPointer, referenceCountPointer);

        // if constexpr (std::is_base_of_v<HasAllocator,T>)
        // {
        //     result.template as<HasAllocator>()->setAllocator(this->getThisPointer());
        // }

        result->setThisPointer(result);

        return result;
    }
}