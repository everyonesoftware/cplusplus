#ifndef E1_POINTERVALUE_H
#define E1_POINTERVALUE_H

namespace e1
{
    /**
     * A ref-counted value.
     */
    template <typename T>
    class RefCountedValue
    {
    public:
        template <typename ...TArgs>
        RefCountedValue(TArgs... args);

        RefCountedValue(const RefCountedValue<T>&) = delete;
        RefCountedValue<T>& operator=(const RefCountedValue<T>&) = delete;

        int* getRefCountPointer();

        T* getValuePointer();

    private:
        int refCount;
        T value;
    };
}

namespace e1
{
    template <typename T>
    template <typename ...TArgs>
    RefCountedValue<T>::RefCountedValue(TArgs... args)
        : refCount(0), value(args...)
    {
    }

    template <typename T>
    int* RefCountedValue<T>::getRefCountPointer()
    {
        return &this->refCount;
    }

    template <typename T>
    T* RefCountedValue<T>::getValuePointer()
    {
        return &this->value;
    }
}

#endif