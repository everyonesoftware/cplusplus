#include "TestRunner.h"

#include "TestAssertionFailure.h"

namespace e1
{
    TestRunner::TestRunner(const P<CharacterWriteStream>& writeStream)
        : writeStream(writeStream)
    {
    }

    void TestRunner::testFile(const char* testFileName, const Action<>& testFileAction)
    {
        this->testGroup(testFileName, testFileAction);
    }

    void TestRunner::testType(const char* fileName, const Action<>& testFileAction)
    {
        this->testGroup(fileName, testFileAction);
    }

    void TestRunner::testMethod(const char* methodName, const Action<>& testMethodAction)
    {
        this->testGroup(methodName, testMethodAction);
    }

    void TestRunner::testGroup(const char* testGroupName, const Action<>& testGroupAction)
    {
        TestGroup testGroup(testGroupName, this->getCurrentTestGroup());
        this->setCurrentTestGroup(&testGroup);

        try
        {
            testGroupAction();
        }
        catch(const std::exception& e)
        {
            this->writeStream->writeString("Unexpected exception: ");
            this->writeStream->writeLine(e.what());
        }
        
        this->setCurrentTestGroup(testGroup.getParent());
    }

    void TestRunner::test(const char* testName, const Action<Test>& testAction)
    {
        this->writeTestFullName(testName);
        this->writeStream->writeString(" - ");
        Test test;
        try
        {
            testAction(test);
            this->writeStream->writeLine("PASS");
        }
        catch(const TestAssertionFailure& e)
        {
            this->writeStream->writeLine("FAIL");
            this->writeStream->writeString("  ");
            this->writeStream->writeLine(e.getMessage());
        }
    }

    const P<TestGroup>& TestRunner::getCurrentTestGroup() const
    {
        return this->currentTestGroup;
    }

    void TestRunner::setCurrentTestGroup(const P<TestGroup>& currentTestGroup)
    {
        this->currentTestGroup.set(currentTestGroup);
    }

    void TestRunner::writeTestGroupFullName(const P<TestGroup>& testGroup)
    {
        if (testGroup.hasValue())
        {
            this->writeTestGroupFullName(testGroup->getParent());
            this->writeStream->writeString(" ");
            this->writeStream->writeString(testGroup->getName());
        }
    }

    void TestRunner::writeTestFullName(const char* testName)
    {
        const P<TestGroup>& currentTestGroup = this->getCurrentTestGroup();
        if (currentTestGroup.hasValue())
        {
            this->writeTestGroupFullName(currentTestGroup);
            this->writeStream->writeString(" ");
        }
        this->writeStream->writeString(testName);
    }
}