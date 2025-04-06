#include "CurrentProcess.h"

using namespace e1;

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    return CurrentProcess::run([](const P<CurrentProcess>& process)
    {
        process->getOutputWriteStream()->writeLine("Hello world!");

        return 0;
    });
}
