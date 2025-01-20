#include "CurrentProcess.h"

using namespace e1;

int main(int argc, char** argv)
{
    return CurrentProcess::run([](const P<CurrentProcess>& process)
    {
        process->getOutputWriteStream()->writeLine("Hello world!");

        return 0;
    });
}
