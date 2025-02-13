#pragma once

#include "HasThisPointer.h"
#include "HasAllocator.h"
#include "NotCopyable.h"
#include "Array.h"
#include "Allocator.h"

namespace e1
{
    /**
     * A dynamic list data structure that stores its values in an array.
     */
    template <typename T>
    class ArrayList : public HasThisPointer, public HasAllocator, public NotCopyable
    {
    public:
        /**
         * Create a new empty ArrayList object with no allocator. An allocator must be assigned
         * before any values can be added to this ArrayList.
         */
        ArrayList()
            : HasThisPointer(this), HasAllocator(), count(0), array()
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
        int getCount() const
        {
            return this->count;
        }

        /**
         * Add the provided value onto the end of this ArrayList.
         * @param value The value to add.
         */
        const P<ArrayList<T>> add(const T& value)
        {
            const int currentCount = this->getCount();
            if (!this->array.hasValue() ||
                this->array->getCount() == currentCount)
            {
                const P<Array<T>> newArray = this->getAllocator()->template createArray<T>((2 * currentCount) + 1);
                for (int i = 0; i < currentCount; i++)
                {
                    newArray->set(i, this->get(i));
                }
                this->array.set(newArray);
            }
            this->array->set(currentCount, value);
            this->count++;

            return this->getThisPointer();
        }

        /**
         * Get the value at the provided index.
         * @param index The index of the value to return.
         */
        T& get(int index) const
        {
            return this->array->get(index);
        }

        const P<ArrayList<T>> getThisPointer() const
        {
            return this->HasThisPointer::getThisPointer<ArrayList<T>>();
        }

    private:
        int count;
        P<Array<T>> array;
    };
}