#include "TestGroup.h"

namespace e1
{
    /**
     * Create a new TestGroup.
     * @param testGroupName The name of this test group.
     * @param parent The parent TestGroup that contains this TestGroup.
     */
    TestGroup::TestGroup(const char* testGroupName, const P<TestGroup>& parent)
        : testGroupName(testGroupName), parent(parent)
    {
    }

    const char* TestGroup::getName() const
    {
        return this->testGroupName;
    }

    const P<TestGroup>& TestGroup::getParent() const
    {
        return this->parent;
    }
}