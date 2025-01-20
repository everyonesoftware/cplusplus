#include "CurrentProcess.h"

#include "HeapAllocator.h"

namespace e1
{
    int CurrentProcess::run(const Action<P<CurrentProcess>> action)
    {
        CurrentProcess process;

        HeapAllocator allocator;
        process.setAllocator(&allocator);

        StdCoutCharacterWriteStream outputWriteStream;
        process.setOutputWriteStream(&outputWriteStream);

        action(&process);

        return process.getExitCode();
    }

    CurrentProcess::CurrentProcess()
        : HasThisPointer(this),
          allocator(),
          exitCode(),
          fileSystem(),
          outputWriteStream()
    {
    }

    const P<CurrentProcess> CurrentProcess::setAllocator(const P<Allocator>& allocator)
    {
        this->allocator = allocator;
        return this->getThisPointer();
    }

    const P<Allocator>& CurrentProcess::getAllocator() const
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

    const P<CharacterWriteStream>& CurrentProcess::getOutputWriteStream() const
    {
        return this->outputWriteStream;
    }

    const P<CurrentProcess> CurrentProcess::setOutputWriteStream(const P<CharacterWriteStream>& outputWriteStream)
    {
        this->outputWriteStream = outputWriteStream;
        return this->getThisPointer();
    }

    const P<CurrentProcess> CurrentProcess::getThisPointer() const
    {
        return HasThisPointer::getThisPointer<CurrentProcess>();
    }
}