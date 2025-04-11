#pragma once

#include "HasThisPointer.h"
#include "HasAllocatorBase.h"
#include "NotCopyable.h"
#include "Array.h"
#include "Allocator.h"
#include "Byte.h"

namespace e1
{
    /**
     * A dynamic list data structure that stores its values in an array.
     */
    template <typename T>
    class ArrayList : public HasThisPointer, public HasAllocatorBase, public NotCopyable
    {
    public:
        /**
         * Create a new empty ArrayList object with no allocator. An allocator must be assigned
         * before any values can be added to this ArrayList.
         */
        ArrayList()
            : HasThisPointer(this), HasAllocatorBase(), count(0), byteArray()
        {
        }

        /**
         * Create a new empty ArrayList object with the provided Allocator.
         */
        ArrayList(const P<Allocator>& allocator)
            : ArrayList()
        {
            this->setAllocator(allocator);
        }
        virtual ~ArrayList() = default;

        /**
         * Get the number of values in this ArrayList.
         */
        std::size_t getCount() const
        {
            return this->count;
        }

        /**
         * Insert the provided value into this ArrayList at the provided index. All values at and
         * after the provided index will be shifted to the right one index position.
         * @param index The index to insert the value at.
         * @param value The value to insert.
         */
        const P<ArrayList<T>> insert(std::size_t index, const T& value)
        {
            const std::size_t currentCount = this->getCount();
            const std::size_t currentCountBytes = currentCount * sizeof(T);
            if (!this->byteArray.hasValue() ||
                this->byteArray->getCount() == currentCountBytes)
            {
                const P<Array<T>> oldValueArray = this->getValueArray();

                const std::size_t newCountBytes = sizeof(T) * ((2 * currentCount) + 1);
                this->byteArray = this->getAllocator()->template createArray<byte>(newCountBytes);
                T* valueArrayPtr = this->getValueArrayPointer();

                for (std::size_t i = 0; i < index; i++)
                {
                    T& valueRef = oldValueArray->get(i);
                    new(valueArrayPtr + i) T(valueRef);
                    valueRef.~T();
                }

                new(valueArrayPtr + index) T(value);

                for (std::size_t i = index; i < currentCount; i++)
                {
                    T& valueRef = oldValueArray->get(i);
                    new(valueArrayPtr + i + 1) T(valueRef);
                    valueRef.~T();
                }
            }
            else
            {
                T* valueArrayPtr = this->getValueArrayPointer();
                for (std::size_t i = currentCount - 1; index <= i; i--)
                {
                    T* valuePtr = valueArrayPtr + i;
                    new(valuePtr + 1) T(*valuePtr);
                    valuePtr->~T();

                    if (index == i)
                    {
                        break;
                    }
                }
                new (valueArrayPtr + index) T(value);
            }
            this->count++;

            return this->getThisPointer();
        }

        /**
         * Add the provided value onto the end of this ArrayList.
         * @param value The value to add.
         */
        const P<ArrayList<T>> add(const T& value)
        {
            return this->insert(this->getCount(), value);
        }

        /**
         * Set the value at the provided index.
         * @param index The index to set.
         * @param value The value to set.
         */
        const P<ArrayList<T>> set(std::size_t index, const T& value)
        {
            T* valuePtr = this->getValueArrayPointer() + index;
            valuePtr->~T();
            new (valuePtr) T(value);

            return this->getThisPointer();
        }

        /**
         * Get the value at the provided index.
         * @param index The index of the value to return.
         */
        T& get(std::size_t index) const
        {
            return this->getValueArray()->get(index);
        }

        /**
         * Remove and return the value at the provided index. All values after the provided index
         * will be shifted to the left one index position.
         * @param index The index at which to remove a value.
         */
        const T removeAt(std::size_t index)
        {
            const T result = this->get(index);

            const std::size_t currentCount = this->getCount();
            T* valueArrayPtr = this->getValueArrayPointer();
            for (std::size_t i = index; i < currentCount - 1; i++)
            {
                T* valuePtr = valueArrayPtr + i;
                valuePtr->~T();
                new (valuePtr) T(*(valuePtr + 1));
            }
            (valueArrayPtr + currentCount - 1)->~T();
            this->count--;

            return result;
        }

        const P<ArrayList<T>> getThisPointer() const
        {
            return this->HasThisPointer::getThisPointer<ArrayList<T>>();
        }

    private:
        const P<Array<T>> getValueArray() const
        {
            return this->byteArray.reinterpretAs<Array<T>>();
        }

        T* getValueArrayPointer() const
        {
            return this->getValueArray()->getValuesPointer();
        }

        std::size_t count;
        P<Array<byte>> byteArray;
    };
}