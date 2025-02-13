#pragma once

#include "NotCopyable.h"
#include "HasAllocator.h"
#include "HasThisPointer.h"

#include <type_traits>

namespace e1
{
    /**
     * An array of values.
     */
    template <typename T, typename std::enable_if<!std::is_void<T>::value, int>::type = 0>
    class Array : public NotCopyable, public HasThisPointer, public HasAllocator
    {
    public:
        Array(int count, T* values)
            : HasThisPointer(this), HasAllocator(), count(count), values(values)
        {
        }
        virtual ~Array() = default;

        /**
         * Set this Array to point to the same value as the provided Array.
         * @param toCopy The Array to copy.
         */
        void operator=(const Array<T>& toCopy) = delete;

        /**
         * Get the number of elements in this Array.
         */
        int getCount() const
        {
            return this->count;
        }

        /**
         * Set the value at the provided index to the provided value.
         */
        void set(int index, const T& value)
        {
            this->getValuesPointer()[index] = value;
        }

        /**
         * Get the value at the provided index in this Array.
         */
        T& get(int index) const
        {
            return this->getValuesPointer()[index];
        }

        /**
         * Get the value at the provided index in this Array.
         */
        T& operator[](int index) const
        {
            return this->get(index);
        }

        /**
         * Get a pointer to the values that this Array points to.
         */
        T* getValuesPointer() const
        {
            return this->values;
        }

    private:
        int count;
        mutable T* values;
    };
}