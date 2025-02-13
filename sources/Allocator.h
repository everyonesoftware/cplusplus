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

    protected:
        /**
         * Get a Pointer to this object.
         */
        const Pointer<Allocator> getThisPointer() const;
    };
}

#include "HasAllocator.h"
#include "Counter.h"

namespace e1
{
    template <typename T, typename ...TArgs>
    Pointer<T> Allocator::create(TArgs... args)
    {
        const int valueByteCount = sizeof(T);
        const int counterByteCount = sizeof(Counter);
        const int byteCount = valueByteCount + counterByteCount;
        void* bytes = this->allocate(byteCount);

        T* valuePointer = reinterpret_cast<T*>(bytes);
        new(valuePointer) T(args...);

        Counter* counterPointer = reinterpret_cast<Counter*>(valuePointer + 1);
        new(counterPointer) Counter();

        const Action<> cleanupAction = [=, this]
        {
            valuePointer->~T();
            counterPointer->~Counter();
            this->free(bytes, byteCount);
        };

        Pointer<T> result(valuePointer, counterPointer, cleanupAction);

        if constexpr (std::is_base_of_v<HasAllocator,T>)
        {
            if (result->getAllocator() == nullptr)
            {
                result->setAllocator(this->getThisPointer());
            }
        }

        if constexpr (std::is_base_of_v<HasThisPointer,T>)
        {
            // Decrement the reference count so that the ThisPointer won't keep it from being
            // cleaned up.
            counterPointer->decrement();
            result->setThisPointer(result);
        }

        return result;
    }

    template <typename T>
    Pointer<Array<T>> Allocator::createArray(int count)
    {
        const int valuesByteCount = sizeof(T) * count;
        const int arrayByteCount = sizeof(Array<T>);
        const int counterByteCount = sizeof(Counter);
        const int byteCount = valuesByteCount + arrayByteCount + counterByteCount;
        void* bytes = this->allocate(byteCount);

        T* valuesPointer = reinterpret_cast<T*>(bytes);
        new(valuesPointer) T[count];

        Array<T>* arrayPointer = reinterpret_cast<Array<T>*>(valuesPointer + count);
        new(arrayPointer) Array<T>(count, valuesPointer);

        Counter* counterPointer = reinterpret_cast<Counter*>(arrayPointer + 1);
        new(counterPointer) Counter();

        const Action<> cleanupAction = [=, this]
        {
            for (int i = 0; i < count; i++)
            {
                valuesPointer[i].~T();
            }
            arrayPointer->~Array();
            counterPointer->~Counter();
            this->free(bytes, byteCount);
        };

        Pointer<Array<T>> result(arrayPointer, counterPointer, cleanupAction);

        const P<Allocator> thisPointer = this->getThisPointer();
        result->setAllocator(thisPointer);

        // Decrement the reference count so that the ThisPointer won't keep it from being cleaned
        // up.
        counterPointer->decrement();
        result->setThisPointer(result);

        return result;
    }
}