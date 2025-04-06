#pragma once

#include "NotCopyable.h"
#include "HasAllocator.h"
#include "HasThisPointer.h"

#include <cstddef>
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
        Array(std::size_t count, T* values)
            : HasThisPointer(this), HasAllocator(), count(count), values(values)
        {
        }
        virtual ~Array() = default;

        /**
         * Get the number of elements in this Array.
         */
        std::size_t getCount() const
        {
            return this->count;
        }

        /**
         * Set the value at the provided index to the provided value.
         */
        void set(std::size_t index, const T& value)
        {
            this->getValuesPointer()[index] = value;
        }

        /**
         * Get the value at the provided index in this Array.
         */
        T& get(std::size_t index) const
        {
            return this->getValuesPointer()[index];
        }

        /**
         * Get the value at the provided index in this Array.
         */
        T& operator[](std::size_t index) const
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
        std::size_t count;
        mutable T* values;
    };
}