#include "ArrayListTests.h"

#include "ArrayList.h"
#include "HeapAllocator.h"

namespace e1
{
    void ArrayListTests(const P<TestRunner>& runner)
    {
        runner->testType("ArrayList<T>", [&]
        {
            runner->testMethod("constructor()", [&]
            {
                runner->test("on the stack with no allocator", [](Test test)
                {
                    ArrayList<int> list;
                    test.assertEqual(0, list.getCount());
                    test.assertEqual(nullptr, list.getAllocator());
                    test.assertEqual(&list, list.getThisPointer());
                });

                runner->test("on the stack with an allocator", [](Test test)
                {
                    HeapAllocator allocator;
                    ArrayList<int> list(&allocator);
                    test.assertEqual(0, list.getCount());
                    test.assertEqual(&allocator, list.getAllocator());
                    test.assertEqual(&list, list.getThisPointer());
                });

                runner->test("on the heap with no allocator", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>();
                    test.assertEqual(0, list->getCount());
                    test.assertEqual(&allocator, list->getAllocator());
                    test.assertEqual(list, list->getThisPointer());
                });

                runner->test("on the heap with an allocator", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator);
                    test.assertEqual(0, list->getCount());
                    test.assertEqual(&allocator, list->getAllocator());
                    test.assertEqual(list, list->getThisPointer());
                });
            });

            runner->testMethod("add()", [&]
            {
                runner->test("when ArrayList is empty", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator);

                    const P<ArrayList<int>> addResult = list->add(5);

                    test.assertEqual(addResult, list);
                    test.assertEqual(1, list->getCount());
                    test.assertEqual(5, list->get(0));
                });

                runner->test("when ArrayList has one value", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0);

                    const P<ArrayList<int>> addResult = list->add(1);

                    test.assertEqual(addResult, list);
                    test.assertEqual(2, list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                });
            });
        });
    }
}