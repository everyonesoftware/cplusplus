#ifndef E1_HasThisPointer_H
#define E1_HasThisPointer_H

#include "Pointer.h"

namespace e1
{
    class HasThisPointer
    {
    public:
        virtual ~HasThisPointer() = default;

        /**
         * Get a Pointer to this object.
         */
        template <typename T>
        const P<T> getThisPointer() const requires std::is_base_of_v<HasThisPointer,T>
        {
            return this->thisPointer.as<T>();
        }

        /**
         * Set the Pointer for this object.
         */
        template <typename T>
        void setThisPointer(const P<T>& thisPointer) requires std::is_base_of_v<HasThisPointer,T>
        {
            this->thisPointer.set(thisPointer.template as<void>());
        }

    protected:
        template <typename T>
        HasThisPointer(T* thisPointer) requires std::is_base_of_v<HasThisPointer,T>
            : thisPointer(thisPointer)
        {
        }

    private:
        Pointer<void> thisPointer;
    };
}

#endif