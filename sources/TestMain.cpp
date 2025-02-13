#include "CurrentProcess.h"
#include "Pointer.h"
#include "TestRunner.h"

#include "ArrayListTests.h"
#include "ByteTests.h"
#include "ByteCountingAllocatorTests.h"
#include "CounterTests.h"
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
        const P<Allocator> allocator = process->getAllocator();
        const P<CharacterWriteStream> outputWriteStream = process->getOutputWriteStream();
        const P<TestRunner> runner = allocator->create<TestRunner>(outputWriteStream);

        ArrayListTests(runner);
        ByteTests(runner);
        ByteCountingAllocatorTests(runner);
        CounterTests(runner);
        HeapAllocatorTests(runner);
        PointerTests(runner);
        TestAssertionFailureTests(runner);
        TestRunnerTests(runner);
        TestTests(runner);

        runner->writeSummary();

        return 0;
    });
}
