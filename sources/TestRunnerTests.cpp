#include "TestRunnerTests.h"

#include "StdCoutCharacterWriteStream.h"

namespace e1
{
    void TestRunnerTests(const P<TestRunner>& runner)
    {
        runner->testType("TestRunner", [&]
        {
            runner->test("constructor", [](Test test)
            {
                StdCoutCharacterWriteStream writeStream;
                TestRunner fakeRunner(&writeStream);

                test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                test.assertEqual(0, fakeRunner.getPassedTestCount());
                test.assertEqual(0, fakeRunner.getFailedTestCount());
                test.assertEqual(0, fakeRunner.getErrorCount());
            });

            runner->testMethod("getCurrentTestGroup()", [&]()
            {
                runner->test("with no current TestGroup", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                });
            });

            runner->testMethod("testFile()", [&]
            {
                runner->test("with empty file name", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testFile("", [&]
                    {
                        const P<TestGroup>& testGroup = fakeRunner.getCurrentTestGroup();
                        test.assertEqual("", testGroup->getName());
                        test.assertEqual(nullptr, testGroup->getParent());
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });

                runner->test("with non-empty file name", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testFile("fake file", [&]
                    {
                        const P<TestGroup>& testGroup = fakeRunner.getCurrentTestGroup();
                        test.assertEqual("fake file", testGroup->getName());
                        test.assertEqual(nullptr, testGroup->getParent());
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });
            });

            runner->testMethod("testType()", [&]
            {
                runner->test("with empty file name", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testType("", [&]
                    {
                        const P<TestGroup>& testGroup = fakeRunner.getCurrentTestGroup();
                        test.assertEqual("", testGroup->getName());
                        test.assertEqual(nullptr, testGroup->getParent());
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });

                runner->test("with non-empty type name", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testType("fake type", [&]
                    {
                        const P<TestGroup>& testGroup = fakeRunner.getCurrentTestGroup();
                        test.assertEqual("fake type", testGroup->getName());
                        test.assertEqual(nullptr, testGroup->getParent());
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });
            });

            runner->testMethod("testMethod()", [&]
            {
                runner->test("with empty method name", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testMethod("", [&]
                    {
                        const P<TestGroup>& testGroup = fakeRunner.getCurrentTestGroup();
                        test.assertEqual("", testGroup->getName());
                        test.assertEqual(nullptr, testGroup->getParent());
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });

                runner->test("with non-empty type name", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testMethod("fake method", [&]
                    {
                        const P<TestGroup>& testGroup = fakeRunner.getCurrentTestGroup();
                        test.assertEqual("fake method", testGroup->getName());
                        test.assertEqual(nullptr, testGroup->getParent());
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });
            });

            runner->testMethod("testGroup()", [&]
            {
                runner->test("with empty group name", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testGroup("", [&]
                    {
                        const P<TestGroup>& testGroup = fakeRunner.getCurrentTestGroup();
                        test.assertEqual("", testGroup->getName());
                        test.assertEqual(nullptr, testGroup->getParent());
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });

                runner->test("with non-empty group name", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testGroup("fake group", [&]
                    {
                        const P<TestGroup>& testGroup = fakeRunner.getCurrentTestGroup();
                        test.assertEqual("fake group", testGroup->getName());
                        test.assertEqual(nullptr, testGroup->getParent());
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });

                runner->test("with lambda that throws a TestAssertionFailure", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testGroup("fake group", [&]
                    {
                        throw TestAssertionFailure("hello");
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(1, fakeRunner.getErrorCount());
                });

                runner->test("with lambda that throws an int", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());
                    fakeRunner.testGroup("fake group", [&]
                    {
                        throw 30;
                    });
                    test.assertEqual(nullptr, fakeRunner.getCurrentTestGroup());

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(1, fakeRunner.getErrorCount());
                });
            });

            runner->testMethod("test()", [&]
            {
                runner->test("with function that doesn't throw", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    fakeRunner.test("fake test name", [](Test fakeTest)
                    {
                        fakeTest.assertEqual(3, 3);
                    });

                    test.assertEqual(1, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });

                runner->test("with function that throws a TestAssertionFailure", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    fakeRunner.test("fake test name", [](Test fakeTest)
                    {
                        fakeTest.assertEqual(3, 3);
                        throw TestAssertionFailure("fake error message");
                    });

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(1, fakeRunner.getFailedTestCount());
                    test.assertEqual(0, fakeRunner.getErrorCount());
                });

                runner->test("with function that throws an int", [](Test test)
                {
                    StdCoutCharacterWriteStream writeStream;
                    TestRunner fakeRunner(&writeStream);

                    fakeRunner.test("fake test name", [](Test fakeTest)
                    {
                        fakeTest.assertEqual(3, 3);
                        throw 13;
                    });

                    test.assertEqual(0, fakeRunner.getPassedTestCount());
                    test.assertEqual(0, fakeRunner.getFailedTestCount());
                    test.assertEqual(1, fakeRunner.getErrorCount());
                });
            });
        });
    }
}