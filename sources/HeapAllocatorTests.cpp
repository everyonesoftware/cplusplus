#include "HeapAllocatorTests.h"

#include "HeapAllocator.h"
#include "Array.h"
#include "Pointer.h"

namespace e1
{
    void HeapAllocatorTests(const P<TestRunner>& runner)
    {
        runner->testType("HeapAllocator", [&]
        {
            runner->test("allocate() and free()", [](Test test)
            {
                HeapAllocator allocator;

                const int byteCount = 50;
                void* bytes = allocator.allocate(byteCount);
                test.assertNotEqual(nullptr, bytes);

                allocator.free(bytes, byteCount);
            });

            runner->testMethod("create()", [&]
            {
                runner->test("with bool", [](Test test)
                {
                    HeapAllocator allocator;

                    P<bool> pValue = allocator.create<bool>(true);
                    test.assertNotEqual(nullptr, pValue);
                    test.assertEqual(true, pValue.getValue());

                    pValue.clear();
                    test.assertEqual(nullptr, pValue);
                });

                runner->test("with P<int>", [](Test test)
                {
                    int value = 5;
                    int cleanupCount = 0;
                    Counter counter;
                    P<int> pValue(&value, &counter, [&]{ cleanupCount++; });

                    HeapAllocator allocator;

                    P<P<int>> ppValue = allocator.create<P<int>>(pValue);
                    test.assertEqual(2, counter.get());
                    test.assertEqual(0, cleanupCount);

                    ppValue.clear();
                    test.assertEqual(1, counter.get());
                    test.assertEqual(0, cleanupCount);

                    pValue.clear();
                    test.assertEqual(0, counter.get());
                    test.assertEqual(1, cleanupCount);
                });
            });

            runner->testMethod("createArray()", [&]
            {
                runner->test("with bool", [](Test test)
                {
                    HeapAllocator allocator;

                    P<Array<bool>> pArray = allocator.createArray<bool>(5);
                    test.assertNotEqual(nullptr, pArray);
                    test.assertEqual(static_cast<std::size_t>(5), pArray->getCount());

                    pArray.clear();
                    test.assertEqual(nullptr, pArray);
                });

                runner->test("with P<int>", [](Test test)
                {
                    int value = 5;
                    Counter counter;
                    int cleanupCount = 0;
                    P<int> pValue(&value, &counter, [&]{ cleanupCount++; });

                    HeapAllocator allocator;

                    P<Array<P<int>>> pArray = allocator.createArray<P<int>>(3);
                    test.assertNotEqual(nullptr, pArray);
                    test.assertEqual(static_cast<std::size_t>(3), pArray->getCount());
                    for (std::size_t i = 0; i < pArray->getCount(); i++)
                    {
                        pArray->get(i).set(pValue);
                    }
                    test.assertEqual(4, counter.get());
                    test.assertEqual(0, cleanupCount);

                    pArray.clear();
                    test.assertEqual(1, counter.get());
                    test.assertEqual(0, cleanupCount);

                    pValue.clear();
                    test.assertEqual(0, counter.get());
                    test.assertEqual(1, cleanupCount);
                });
            });
        });
    }
}