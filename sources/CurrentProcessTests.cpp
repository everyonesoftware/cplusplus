#include "CurrentProcessTests.h"

#include "CurrentProcess.h"

namespace e1
{
    void CurrentProcessTests(const P<TestRunner>& runner)
    {
        runner->testType("CurrentProcess", [&]
        {
            runner->test("constructor", [](Test test)
            {
                CurrentProcess process;
                test.assertEqual(0, process.getCommandLineArgumentCount());
                test.assertEqual(nullptr, process.getCommandLineArguments());
                test.assertEqual(nullptr, process.getAllocator());
                test.assertEqual(0, process.getExitCode());
                test.assertEqual(nullptr, process.getFileSystem());
                test.assertEqual(nullptr, process.getOutputWriteStream());
            });

            runner->test("setCommandLineArguments()", [](Test test)
            {
                CurrentProcess process;
                const int argc = 2;
                const char argvCharacters[argc][5] = {
                    "ab",
                    "cd",
                };
                const char* argv[argc] = {
                    argvCharacters[0],
                    argvCharacters[1],
                };

                const P<CurrentProcess> result = process.setCommandLineArguments(argc, argv);

                test.assertEqual(&process, result);
                test.assertEqual(argc, process.getCommandLineArgumentCount());
                test.assertEqual(argv, process.getCommandLineArguments());
            });

            runner->test("setExitCode()", [](Test test)
            {
                CurrentProcess process;

                const P<CurrentProcess> result = process.setExitCode(20);

                test.assertEqual(&process, result);
                test.assertEqual(20, process.getExitCode());
            });
        });
    }
}