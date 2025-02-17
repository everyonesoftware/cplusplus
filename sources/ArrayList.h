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
         * Insert the provided value into this ArrayList at the provided index. All values at and
         * after the provided index will be shifted to the right one index position.
         * @param index The index to insert the value at.
         * @param value The value to insert.
         */
        const P<ArrayList<T>> insert(int index, const T& value)
        {
            const int currentCount = this->getCount();
            if (!this->array.hasValue() ||
                this->array->getCount() == currentCount)
            {
                const P<Array<T>> newArray = this->getAllocator()->template createArray<T>((2 * currentCount) + 1);
                for (int i = 0; i < index; i++)
                {
                    newArray->set(i, this->get(i));
                }
                for (int i = index; i < currentCount; i++)
                {
                    newArray->set(i + 1, this->get(i));
                }
                this->array.set(newArray);
            }
            else
            {
                for (int i = currentCount; index < i; i--)
                {
                    this->set(i, this->get(i - 1));
                }
            }
            this->set(index, value);
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
        const P<ArrayList<T>> set(int index, const T& value)
        {
            this->array->set(index, value);

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

        /**
         * Remove and return the value at the provided index. All values after the provided index
         * will be shifted to the left one index position.
         * @param index The index at which to remove a value.
         */
        const T removeAt(int index)
        {
            const T result = this->get(index);

            const int currentCount = this->getCount();
            for (int i = index; i < currentCount - 1; i++)
            {
                this->set(i, this->get(i + 1));
            }
            this->count--;

            return result;
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