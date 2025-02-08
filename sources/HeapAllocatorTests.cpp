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

                void* bytes = allocator.allocate(50);
                test.assertNotEqual(nullptr, bytes);

                allocator.free(bytes, 50);
            });

            runner->testMethod("create()", [&]
            {
                runner->test("with bool", [](Test test)
                {
                    HeapAllocator allocator;

                    P<bool> pValue = allocator.create<bool>(true);
                    test.assertNotEqual(nullptr, pValue);
                    test.assertEqual(true, pValue.getValue());
                });

                runner->test("with P<int>", [](Test test)
                {
                    int value = 5;
                    int cleanupCount = 0;
                    ReferenceCount referenceCount([&]{ cleanupCount++; });
                    P<int> pValue(&value, &referenceCount);

                    HeapAllocator allocator;

                    P<P<int>> ppValue = allocator.create<P<int>>(pValue);
                    test.assertEqual(2, referenceCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    ppValue.clear();
                    test.assertEqual(1, referenceCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    pValue.clear();
                    test.assertEqual(0, referenceCount.getCount());
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
                    test.assertEqual(5, pArray->getCount());
                });

                runner->test("with P<int>", [](Test test)
                {
                    int value = 5;
                    int cleanupCount = 0;
                    ReferenceCount referenceCount([&]{ cleanupCount++; });
                    P<int> pValue(&value, &referenceCount);

                    HeapAllocator allocator;

                    P<Array<P<int>>> pArray = allocator.createArray<P<int>>(3);
                    test.assertNotEqual(nullptr, pArray);
                    test.assertEqual(3, pArray->getCount());
                    for (int i = 0; i < pArray->getCount(); i++)
                    {
                        pArray->get(i).set(pValue);
                    }
                    test.assertEqual(4, referenceCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    pArray.clear();
                    test.assertEqual(1, referenceCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    pValue.clear();
                    test.assertEqual(0, referenceCount.getCount());
                    test.assertEqual(1, cleanupCount);
                });
            });
        });
    }
}