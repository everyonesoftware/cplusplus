#pragma once

#include "Pointer.h"

namespace e1
{
    /**
     * A group of tests.
     */
    class TestGroup
    {
    public:
        /**
         * Create a new TestGroup.
         * @param testGroupName The name of this test group.
         * @param parent The parent TestGroup that contains this TestGroup.
         */
        explicit TestGroup(const char* testGroupName, const P<TestGroup>& parent);

        /**
         * Get the name of this TestGroup.
         */
        const char* getName() const;

        /**
         * Get the TestGroup that contains this TestGroup. This may be null if this TestGroup is not
         * contained by any other TestGroup.
         */
        const P<TestGroup>& getParent() const;

    private:
        const char* testGroupName;
        const P<TestGroup> parent;
    };
}