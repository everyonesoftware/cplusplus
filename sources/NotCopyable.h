#ifndef E1_NOTCOPYABLE_H
#define E1_NOTCOPYABLE_H

namespace e1
{
    /**
     * A type that makes any derived type not able to be copied.
     */
    class NotCopyable
    {
    public:
        NotCopyable() = default;
        ~NotCopyable() = default;

    private:
        NotCopyable(const NotCopyable&) = delete;
        NotCopyable& operator=(const NotCopyable&) = delete;
    };
}

#endif