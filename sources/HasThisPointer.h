#pragma once

#include "Pointer.h"

namespace e1
{
    class HasThisPointer
    {
    public:
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

        /**
         * Get a Pointer to this object.
         */
        template <typename T>
        const P<T> getThisPointer() const requires std::is_base_of_v<HasThisPointer,T>
        {
            return this->thisPointer.as<T>();
        }

    private:
        Pointer<void> thisPointer;
    };
}