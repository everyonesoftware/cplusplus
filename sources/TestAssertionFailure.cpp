#include "TestAssertionFailure.h"

namespace e1
{
    TestAssertionFailure::TestAssertionFailure(const char* message)
        : message(message)
    {
    }

    TestAssertionFailure::~TestAssertionFailure()
    {
    }

    const char* TestAssertionFailure::getMessage() const
    {
        return this->message;
    }

    const char* TestAssertionFailure::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW
    {
        return this->getMessage();
    }
}