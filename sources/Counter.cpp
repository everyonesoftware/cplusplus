#include "Counter.h"

namespace e1
{
    Counter::Counter()
        : value(0)
    {
    }
    Counter::Counter(int initialValue)
        : value(initialValue)
    {
    }

    void Counter::operator=(int value)
    {
        this->set(value);
    }
    void Counter::set(int value)
    {
        this->value = value;
    }

    void Counter::operator=(const Counter& toCopy)
    {
        this->set(toCopy);
    }
    void Counter::set(const Counter& toCopy)
    {
        this->set(toCopy.get());
    }

    int Counter::get() const
    {
        return this->value;
    }

    Counter::operator int() const
    {
        return this->get();
    }

    void Counter::increment()
    {
        this->incrementAndGet();
    }

    int Counter::incrementAndGet()
    {
        return ++(this->value);
    }
    int Counter::operator++()
    {
        return this->incrementAndGet();
    }

    int Counter::getAndIncrement()
    {
        return (this->value)++;
    }
    int Counter::operator++(int)
    {
        return this->getAndIncrement();
    }

    void Counter::decrement()
    {
        this->decrementAndGet();
    }

    int Counter::decrementAndGet()
    {
        return --(this->value);
    }
    int Counter::operator--()
    {
        return this->decrementAndGet();
    }

    int Counter::getAndDecrement()
    {
        return (this->value)--;
    }
    int Counter::operator--(int)
    {
        return this->getAndDecrement();
    }
}