#pragma once

#include "ReferenceCount.h"
#include "Action.h"

#include <type_traits>

namespace e1
{
    /**
     * A pointer to a value.
     */
    template <typename T>
    class Pointer
    {
    public:
        /**
         * Create a new empty Pointer object that points to null.
         */
        Pointer()
            : Pointer(nullptr, nullptr)
        {
        }

        /**
         * Create a new Pointer object that points to the provided value, but won't perform any type
         * of cleanup when the Pointer is destroyed.
         */
        Pointer(T* value)
            : Pointer(value, nullptr)
        {
        }

        /**
         * Create a new Pointer object that points to the provided value and uses the provided
         * ReferenceCount object to manage the value.
         */
        Pointer(T* value, ReferenceCount* referenceCount)
            : value(nullptr), referenceCount(nullptr)
        {
            this->set(value, referenceCount);
        }

        template <typename U>
        Pointer(const Pointer<U>& toCopy) requires std::is_base_of_v<T,U>
            : Pointer()
        {
            this->set(toCopy.template as<T>());
        }

        Pointer(const Pointer<T>& toCopy)
            : Pointer()
        {
            this->set(toCopy);
        }

        virtual ~Pointer()
        {
            this->clear();
        }

        /**
         * Set this Pointer to point to the provided raw pointer. This function assumes that the raw
         * pointer is being managed somewhere else, so when this pointer is destructed it will do
         * nothing to cleanup the provided raw pointer.
         * @param value The raw pointer to set.
         */
        void set(T* value)
        {
            this->set(value, nullptr);
        }
        /**
         * Set this Pointer to point to the provided value.
         * @param value The pointer to set.
         */
        void operator=(T* value)
        {
            this->set(value);
        }
        
        /**
         * Set this Pointer to point to the same value as the provided Pointer.
         * @param toCopy The Pointer to copy.
         */
        void set(const Pointer<T>& toCopy)
        {
            if (this->getValuePointer() != toCopy.getValuePointer())
            {
                this->set(toCopy.getValuePointer(), toCopy.getReferenceCount());
            }
        }
        /**
         * Set this Pointer to point to the same value as the provided Pointer.
         * @param toCopy The Pointer to copy.
         */
        void operator=(const Pointer<T>& toCopy)
        {
            this->set(toCopy);
        }

        /**
         * Set this Pointer to point to the same value as the provided Pointer.
         * @param toCopy The Pointer to copy.
         */
        template <typename U>
        void set(const Pointer<U>& toCopy) requires std::is_base_of_v<T,U>
        {
            this->set(toCopy.template as<T>());
        }
        /**
         * Set this Pointer to point to the same value as the provided Pointer.
         * @param toCopy The Pointer to copy.
         */
        template <typename U>
        void operator=(const Pointer<U>& toCopy) requires std::is_base_of_v<T,U>
        {
            this->set(toCopy);
        }

        /**
         * Set this Pointer to not point to a value.
         */
        void clear()
        {
            this->set(nullptr, nullptr);
        }

        /**
         * Get whether this Pointer has a value.
         */
        bool hasValue() const
        {
            return this->getValuePointer() != nullptr;
        }

        /**
         * Get the value that this Pointer points to.
         */
        template <typename U = T, typename std::enable_if<!std::is_void<U>::value, int>::type = 0>
        U& getValue() const
        {
            return *this->getValuePointer();
        }

        /**
         * Get the value that this Pointer points to.
         */
        template <typename U = T, typename std::enable_if<!std::is_void<U>::value, int>::type = 0>
        U& operator*() const
        {
            return this->getValue();
        }

        /**
         * Get a pointer to the value that this Pointer points to.
         */
        T* getValuePointer() const
        {
            return this->value;
        }

        /**
         * Get a pointer to the value that this Pointer points to.
         */
        T* operator->() const
        {
            return this->getValuePointer();
        }

        /**
         * Get a new pointer with the provided type U from this Pointer.
         */
        template <typename U>
        const Pointer<U> as() const
        {
            U* uValue = reinterpret_cast<U*>(this->getValuePointer());
            return Pointer<U>(uValue, this->getReferenceCount());
        }

        /**
         * Get whether this Pointer points at the same address as the provided raw pointer.
         * @param right The raw pointer to compare against this Pointer.
         */
        bool equals(const void* right) const
        {
            return this->getValuePointer() == right;
        }

        /**
         * Get whether this Pointer points at the same address as the provided raw pointer.
         * @param right The raw pointer to compare against this Pointer.
         */
        bool operator==(const void* right) const
        {
            return this->equals(right);
        }

        /**
         * Get whether this Pointer points at the same address as the provided Pointer.
         * @param right The Pointer to compare against this Pointer.
         */
        template <typename U>
        bool equals(const Pointer<U>& right) const
        {
            return this->getValuePointer() == right.getValuePointer();
        }

        /**
         * Get whether this Pointer points at the same address as the provided Pointer.
         * @param right The Pointer to compare against this Pointer.
         */
        template <typename U>
        bool operator==(const Pointer<U>& right) const
        {
            return this->equals(right);
        }

    private:
        void set(T* value, ReferenceCount* referenceCount)
        {
            if (this->value != value)
            {
                if (this->referenceCount != referenceCount)
                {
                    if (this->referenceCount != nullptr)
                    {
                        this->referenceCount->decrement();
                    }

                    this->referenceCount = referenceCount;

                    if (this->referenceCount != nullptr)
                    {
                        this->referenceCount->increment();
                    }
                }
                this->value = value;
            }
        }

        ReferenceCount* getReferenceCount() const
        {
            return this->referenceCount;
        }

        mutable T* value;
        ReferenceCount* referenceCount;
    };

    /**
     * A reference-counted pointer to a value.
     */
    template <typename T>
    using P = Pointer<T>;
}