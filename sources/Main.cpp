#include "CurrentProcess.h"

using namespace e1;

int main(int argc, const char** argv)
{
    return CurrentProcess::run(argc, argv, [](const P<CurrentProcess>& process)
    {
        process->getOutputWriteStream()->writeLine("Hello world!");

        return 0;
    });
}
