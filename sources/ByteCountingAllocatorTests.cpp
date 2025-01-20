#include "ByteCountingAllocatorTests.h"

#include "ByteCountingAllocator.h"
#include "HeapAllocator.h"

namespace e1
{
    void ByteCountingAllocatorTests(const P<TestRunner>& runner)
    {
        runner->testType("ByteCountingAllocator", [&]
        {
            runner->test("getAllocatedByteCount", [](Test test)
            {
                HeapAllocator ha;
                ByteCountingAllocator bca(&ha);

                test.assertEqual(0, bca.getAllocatedByteCount());

                P<int> p1 = bca.create<int>(1);
                test.assertEqual(sizeof(RefCountedValue<int>), bca.getAllocatedByteCount());

                P<int> p2 = bca.create<int>(2);
                test.assertEqual(2 * sizeof(RefCountedValue<int>), bca.getAllocatedByteCount());

                p1.clear();
                test.assertEqual(sizeof(RefCountedValue<int>), bca.getAllocatedByteCount());

                p2.clear();
                test.assertEqual(0, bca.getAllocatedByteCount());
            });
        });
    }
}