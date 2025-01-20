#ifndef E1_TESTRUNNER_H
#define E1_TESTRUNNER_H

#include "Action.h"
#include "CharacterWriteStream.h"
#include "Pointer.h"
#include "Test.h"
#include "TestGroup.h"

namespace e1
{
    /**
     * A type that can be used to run tests.
     */
    class TestRunner
    {
    public:
        /**
         * Create a new TestRunner object with the provided CharacterWriteStream.
         * @param writeStream The CharacterWriteStream that this TestRunner will write to.
         */
        TestRunner(const P<CharacterWriteStream>& writeStream);

        /**
         * Create a test group that contains tests pertaining to a specific file.
         * @param fileName The name of the file to test.
         * @param testFileAction The Action that defines the test group.
         */
        void testFile(const char* fileName, const Action<>& testFileAction);

        /**
         * Create a test group that contains tests pertaining to a specific type.
         * @param typeName The name of the type to test.
         * @param testTypeAction The Action that defines the test group.
         */
        void testType(const char* typeName, const Action<>& testTypeAction);

        /**
         * Create a test group that contains tests pertaining to a specific method.
         * @param methodName The name of the method to test.
         * @param testMethodAction The Action that defines the test group.
         */
        void testMethod(const char* methodName, const Action<>& testMethodAction);

        /**
         * Create a test group that will contain other test groups and/or tests.
         * @param testGroupName The name of the test group.
         * @param testGroupAction The Action that defines the test group.
         */
        void testGroup(const char* testGroupName, const Action<>& testGroupAction);

        /**
         * Create a test that will run the provided Action.
         * @param testName The name of the test.
         * @param testAction The Action that defines the test.
         */
        void test(const char* testName, const Action<Test>& testAction);

    private:
        /**
         * Get the current TestGroup for this TestRunner. This may be null if there isn't a
         * TestGroup currently running.
         */
        const P<TestGroup>& getCurrentTestGroup() const;
        /**
         * Set the curently running TestGroup for this TestRunner.
         * @param currentTestGroup The currently running TestGroup. This may be null to indicate
         * that no TestGroup is currently running.
         */
        void setCurrentTestGroup(const P<TestGroup>& currentTestGroup);

        void writeTestGroupFullName(const P<TestGroup>& testGroup);
        void writeTestFullName(const char* testName);

        P<CharacterWriteStream> writeStream;
        P<TestGroup> currentTestGroup;
    };
}

#endif