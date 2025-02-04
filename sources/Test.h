#ifndef E1_TEST_H
#define E1_TEST_H

#include "Action.h"
#include "TestAssertionFailure.h"

namespace e1
{
    /**
     * A collection of assertions that are used to write tests.
     */
    class Test
    {
    public:
        /**
         * Throw a TestAssertionFailure exception with the provided message.
         * @param message An explanation of why the Test failed.
         */
        void fail(const char* message);

        /**
         * Assert that the provided values are equal.
         * @param left The left value in the comparison.
         * @param right The right value in the comparison.
         */
        template <typename T, typename U>
        void assertEqual(T left, U right)
        {
            if (!(left == right))
            {
                this->fail("Expected the values to be equal, but they weren't.");
            }
        }

        /**
         * Assert that the provided Action throws an exception.
         */
        void assertThrows(const Action<>& action);
    };
}

#endif