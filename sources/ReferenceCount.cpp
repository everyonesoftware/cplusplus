#include "ReferenceCount.h"

namespace e1
{
    ReferenceCount::ReferenceCount(Action<> cleanupAction)
        : referenceCount(0), cleanupAction(cleanupAction)
    {
    }

    int ReferenceCount::getCount() const
    {
        return this->referenceCount;
    }

    void ReferenceCount::increment()
    {
        ++this->referenceCount;
    }

    void ReferenceCount::decrement()
    {
        if (0 == --this->referenceCount)
        {
            this->cleanupAction();
        }
    }
}