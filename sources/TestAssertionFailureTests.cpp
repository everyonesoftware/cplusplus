#include "TestAssertionFailureTests.h"

namespace e1
{
    void TestAssertionFailureTests(const P<TestRunner>& runner)
    {
        runner->testType("TestAssertionFailure", [&]
        {
            runner->test("getMessage()", [](Test test)
            {
                TestAssertionFailure failure("fake error message");
                test.assertEqual("fake error message", failure.getMessage());
            });

            runner->test("what()", [](Test test)
            {
                TestAssertionFailure failure("fake error message");
                test.assertEqual("fake error message", failure.what());
            });
        });
    }
}