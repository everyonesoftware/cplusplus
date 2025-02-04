#include "TestTests.h"

namespace e1
{
    void TestTests(const P<TestRunner>& runner)
    {
        runner->testType("Test", [&]
        {
            runner->test("fail()", [](Test test)
            {
                test.assertThrows([&]
                {
                    test.fail("fake-error-message");
                });
            });

            runner->testMethod("assertEqual()", [&]
            {
                auto assertEqualErrorTest = [&](const char* testName, auto left, auto right)
                {
                    runner->test(testName, [&](Test test)
                    {
                        test.assertThrows([&]
                        {
                            test.assertEqual(left, right);
                        });
                    });
                };
                assertEqualErrorTest("with 22 and 24", 22, 24);
                assertEqualErrorTest("with 2 and true", 2, true);
                assertEqualErrorTest("with true and 2", true, 2);

                auto assertEqualTest = [&](const char* testName, auto left, auto right)
                {
                    runner->test(testName, [&](Test test)
                    {
                        test.assertEqual(left, right);
                    });
                };
                assertEqualTest("with 22 and 22", 22, 22);
                assertEqualTest("with 0 and false", 0, false);
                assertEqualTest("with false and 0", false, 0);
                assertEqualTest("with 1 and true", 1, true);
                assertEqualTest("with true and 1", true, 1);
            });

            runner->testMethod("assertThrows()", [&]
            {
                runner->test("with nothing thrown", [](Test test)
                {
                    test.assertThrows([]
                    {
                        Test fakeTest;
                        fakeTest.assertThrows([]{});
                    });
                });

                runner->test("with a TestAssertionFailure thrown", [](Test test)
                {
                    test.assertThrows([]
                    {
                        throw TestAssertionFailure("fake error message");
                    });
                });

                runner->test("with an int thrown", [](Test test)
                {
                    test.assertThrows([]
                    {
                        throw 50;
                    });
                });
            });
        });
    }
}