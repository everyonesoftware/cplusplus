#include "ByteCountingAllocatorTests.h"

#include "ByteCountingAllocator.h"
#include "HeapAllocator.h"

namespace e1
{
    void ByteCountingAllocatorTests(const P<TestRunner>& runner)
    {
        runner->testType("ByteCountingAllocator", [&]
        {
            runner->test("getAllocatedByteCount", [&](Test test)
            {
                const P<Allocator> allocator = runner->getAllocator();
                ByteCountingAllocator bca(allocator);
                const std::size_t allocationByteCount = sizeof(int) + sizeof(Counter);

                test.assertEqual(static_cast<std::size_t>(0), bca.getAllocatedByteCount());

                P<int> p1 = bca.create<int>(1);
                test.assertEqual(allocationByteCount, bca.getAllocatedByteCount());

                P<int> p2 = bca.create<int>(2);
                test.assertEqual(2 * allocationByteCount, bca.getAllocatedByteCount());

                p1.clear();
                test.assertEqual(allocationByteCount, bca.getAllocatedByteCount());

                p2.clear();
                test.assertEqual(static_cast<std::size_t>(0), bca.getAllocatedByteCount());
            });
        });
    }
}