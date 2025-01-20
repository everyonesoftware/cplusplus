#ifndef E1_POINTER_H
#define E1_POINTER_H

#include "RefCountedValue.h"
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
        Pointer()
            : Pointer(nullptr, nullptr, []{})
        {
        }

        Pointer(T* value)
            : Pointer(value, nullptr, []{})
        {
        }

        Pointer(T* value, int* refCount, const Action<>& releaseAction)
            : value(value), refCount(refCount), releaseAction(releaseAction)
        {
            this->incrementRefCount();
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
            if (this->value != value)
            {
                this->clear();

                this->value = value;
            }
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
            if (this->value != toCopy.value)
            {
                this->clear();

                this->refCount = toCopy.refCount;
                this->incrementRefCount();

                this->value = toCopy.value;
                this->releaseAction = toCopy.releaseAction;
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
            if (this->refCount != nullptr)
            {
                *this->refCount -= 1;
                if (*this->refCount == 0)
                {
                    this->releaseAction();
                }
                this->refCount = nullptr;
            }
            this->value = nullptr;
            this->releaseAction = []{};
        }

        /**
         * Get whether this Pointer has a value.
         */
        bool hasValue() const
        {
            return this->value != nullptr;
        }

        /**
         * Get the value that this Pointer points to.
         */
        template <typename U = T, typename std::enable_if<!std::is_void<U>::value, int>::type = 0>
        U& getValue() const
        {
            return *this->value;
        }

        /**
         * Get the value that this Pointer points to.
         */
        template <typename U = T, typename std::enable_if<!std::is_void<U>::value, int>::type = 0>
        U& operator*() const
        {
            return *this->value;
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
            return this->value;
        }

        /**
         * Get a new pointer with the provided type U from this Pointer.
         */
        template <typename U>
        const Pointer<U> as() const
        {
            U* uValue = reinterpret_cast<U*>(this->value);
            return Pointer<U>(uValue, this->refCount, this->releaseAction);
        }

    private:
        /**
         * Increment this Pointer's refCount value.
         */
        void incrementRefCount()
        {
            if (this->refCount != nullptr)
            {
                *this->refCount += 1;
            }
        }

        mutable T* value;
        int* refCount;
        Action<> releaseAction;
    };

    /**
     * A reference-counted pointer to a value.
     */
    template <typename T>
    using P = Pointer<T>;
}

#endif