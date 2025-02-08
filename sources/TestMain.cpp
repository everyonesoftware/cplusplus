#include "CurrentProcess.h"
#include "Pointer.h"
#include "TestRunner.h"

#include "ByteTests.h"
#include "ByteCountingAllocatorTests.h"
#include "HeapAllocatorTests.h"
#include "PointerTests.h"
#include "TestAssertionFailureTests.h"
#include "TestRunnerTests.h"
#include "TestTests.h"

using namespace e1;

int main(int argc, char** argv)
{
    return CurrentProcess::run([](const P<CurrentProcess>& process)
    {
        TestRunner runner(process->getOutputWriteStream());

        ByteTests(&runner);
        ByteCountingAllocatorTests(&runner);
        HeapAllocatorTests(&runner);
        PointerTests(&runner);
        TestAssertionFailureTests(&runner);
        TestRunnerTests(&runner);
        TestTests(&runner);

        runner.writeSummary();

        return 0;
    });
}
