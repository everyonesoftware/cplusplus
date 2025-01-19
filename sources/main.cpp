#include "ByteCountingAllocator.h"
#include "CurrentProcess.h"
#include "Pointer.h"

using namespace e1;

int main(int argc, char** argv)
{
    return CurrentProcess::run([](const P<CurrentProcess>& process)
    {
        CharacterWriteStream& output = process->getOutputWriteStream();

        output.writeLine("Hello world!");

        P<Allocator> allocator = process->getAllocator();
        P<ByteCountingAllocator> bcAllocator = allocator->create<ByteCountingAllocator>(allocator);
        
        Action<> writeAllocatorStats = [&]
        {
            output.writeString("Allocated bytes: ");
            output.writeInt(bcAllocator->getAllocatedByteCount());
            output.writeLine(" bytes");
        };
        writeAllocatorStats();

        P<Allocator> p;

        p.set(allocator);
        p.set(bcAllocator);

        writeAllocatorStats();

        p.clear();

        writeAllocatorStats();

        return 0;
    });
}
