#include "CurrentProcess.h"
#include "Pointer.h"
#include "TestRunner.h"

#include "ByteCountingAllocatorTests.h"
#include "TestTests.h"

using namespace e1;

int main(int argc, char** argv)
{
    return CurrentProcess::run([](const P<CurrentProcess>& process)
    {
        TestRunner runner(process->getOutputWriteStream());

        ByteCountingAllocatorTests(&runner);
        TestTests(&runner);

        return 0;
    });
}
