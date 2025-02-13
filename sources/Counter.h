#pragma once

namespace e1
{
    class Counter
    {
    public:
        Counter();
        explicit Counter(int initialValue);

        void operator=(int value);
        void set(int value);

        void operator=(const Counter& toCopy);
        void set(const Counter& toCopy);

        int get() const;
        explicit operator int() const;

        void increment();

        int incrementAndGet();
        int operator++();

        int getAndIncrement();
        int operator++(int);

        void decrement();

        int decrementAndGet();
        int operator--();

        int getAndDecrement();
        int operator--(int);

    private:
        int value;
    };
}