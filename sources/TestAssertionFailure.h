#pragma once

#include <stdexcept>

namespace e1
{
    /**
     * An exception that is thrown when a test assertion fails.
     */
    class TestAssertionFailure : public std::exception
    {
    public:
        /**
         * Create a new TestAssertionFailure.
         * @param message An explanation of why the assertion failed.
         */
        TestAssertionFailure(const char* message);
        virtual ~TestAssertionFailure();

        /**
         * Get the message that explains why the assertion failed.
         */
        const char* getMessage() const;

        virtual const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW;

    private:
        const char* message;
    };
}