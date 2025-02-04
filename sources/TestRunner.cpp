#include "TestRunner.h"

#include "TestAssertionFailure.h"

namespace e1
{
    TestRunner::TestRunner(const P<CharacterWriteStream>& writeStream)
        : writeStream(writeStream),
          currentTestGroup(),
          passedTestCount(),
          failedTestCount(),
          errorCount()
    {
    }

    void TestRunner::testFile(const char* fileName, const Action<>& testFileAction)
    {
        this->testGroup(fileName, testFileAction);
    }

    void TestRunner::testType(const char* typeName, const Action<>& testFileAction)
    {
        this->testGroup(typeName, testFileAction);
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
            this->incrementErrorCount();
            this->writeStream->writeString("Unexpected exception: ");
            this->writeStream->writeLine(e.what());
        }
        catch(...)
        {
            this->incrementErrorCount();
            this->writeStream->writeString("Unexpected non-exception thrown.");
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
            this->incrementPassedTestCount();
            this->writeStream->writeLine("PASS");
        }
        catch(const TestAssertionFailure& e)
        {
            this->incrementFailedTestCount();
            this->writeStream->writeLine("FAIL");
            this->writeStream->writeString("  ");
            this->writeStream->writeLine(e.getMessage());
        }
        catch(...)
        {
            this->incrementErrorCount();
            this->writeStream->writeString("Unexpected non-exception thrown.");
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

    int TestRunner::getPassedTestCount() const
    {
        return this->passedTestCount;
    }

    void TestRunner::incrementPassedTestCount()
    {
        this->passedTestCount++;
    }

    int TestRunner::getFailedTestCount() const
    {
        return this->failedTestCount;
    }

    void TestRunner::incrementFailedTestCount()
    {
        this->failedTestCount++;
    }

    int TestRunner::getErrorCount() const
    {
        return this->errorCount;
    }

    void TestRunner::incrementErrorCount()
    {
        this->errorCount++;
    }

    void TestRunner::writeSummary()
    {
        this->writeStream->writeLine();

        this->writeSummaryCount("Passed", this->getPassedTestCount());
        this->writeSummaryCount("Failed", this->getFailedTestCount());
        this->writeSummaryCount("Errors", this->getErrorCount());
    }

    void TestRunner::writeSummaryCount(const char* countName, int count)
    {
        if (count > 0)
        {
            this->writeStream->writeString(countName);
            this->writeStream->writeString(": ");
            this->writeStream->writeInt(count);
            this->writeStream->writeLine();
        }
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