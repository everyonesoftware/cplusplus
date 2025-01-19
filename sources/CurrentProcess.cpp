#include "CurrentProcess.h"

#include "HeapAllocator.h"

namespace e1
{
    int CurrentProcess::run(const Action<P<CurrentProcess>> action)
    {
        CurrentProcess process;

        HeapAllocator allocator;
        process.setAllocator(&allocator);

        action(&process);

        return process.getExitCode();
    }

    CurrentProcess::CurrentProcess()
        : HasThisPointer(this),
          allocator(),
          exitCode(),
          fileSystem(),
          stdout()
    {
    }

    const P<CurrentProcess> CurrentProcess::setAllocator(const P<Allocator>& allocator)
    {
        this->allocator = allocator;
        return this->getThisPointer();
    }

    const P<Allocator>& CurrentProcess::getAllocator()
    {
        return this->allocator;
    }

    const P<CurrentProcess> CurrentProcess::setExitCode(int exitCode)
    {
        this->exitCode = exitCode;
        return this->getThisPointer();
    }

    int CurrentProcess::getExitCode() const
    {
        return this->exitCode;
    }

    FileSystem& CurrentProcess::getFileSystem()
    {
        return this->fileSystem;
    }

    CharacterWriteStream& CurrentProcess::getOutputWriteStream()
    {
        return this->stdout;
    }

    const P<CurrentProcess> CurrentProcess::getThisPointer() const
    {
        return HasThisPointer::getThisPointer<CurrentProcess>();
    }
}