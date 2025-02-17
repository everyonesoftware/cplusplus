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

            runner->testMethod("insert()", [&]
            {
                runner->test("when ArrayList is empty", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator);

                    const P<ArrayList<int>> result = list->insert(0, 5);

                    test.assertEqual(result, list);
                    test.assertEqual(1, list->getCount());
                    test.assertEqual(5, list->get(0));
                });

                runner->test("when ArrayList has one value and index is 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0);

                    const P<ArrayList<int>> result = list->insert(0, 1);

                    test.assertEqual(result, list);
                    test.assertEqual(2, list->getCount());
                    test.assertEqual(1, list->get(0));
                    test.assertEqual(0, list->get(1));
                });

                runner->test("when ArrayList has one value and index is 1", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0);

                    const P<ArrayList<int>> result = list->insert(1, 1);

                    test.assertEqual(result, list);
                    test.assertEqual(2, list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                });

                runner->test("when ArrayList has two values and index is 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0)->add(1);

                    const P<ArrayList<int>> result = list->insert(0, 2);

                    test.assertEqual(result, list);
                    test.assertEqual(3, list->getCount());
                    test.assertEqual(2, list->get(0));
                    test.assertEqual(0, list->get(1));
                    test.assertEqual(1, list->get(2));
                });

                runner->test("when ArrayList has two values and index is 1", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0)->add(1);

                    const P<ArrayList<int>> result = list->insert(1, 2);

                    test.assertEqual(result, list);
                    test.assertEqual(3, list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(2, list->get(1));
                    test.assertEqual(1, list->get(2));
                });

                runner->test("when ArrayList has two values and index is 2", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0)->add(1);

                    const P<ArrayList<int>> result = list->insert(2, 2);

                    test.assertEqual(result, list);
                    test.assertEqual(3, list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                    test.assertEqual(2, list->get(2));
                });
            });

            runner->testMethod("add()", [&]
            {
                runner->test("when ArrayList is empty", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator);

                    const P<ArrayList<int>> result = list->add(5);

                    test.assertEqual(result, list);
                    test.assertEqual(1, list->getCount());
                    test.assertEqual(5, list->get(0));
                });

                runner->test("when ArrayList has one value", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0);

                    const P<ArrayList<int>> result = list->add(1);

                    test.assertEqual(result, list);
                    test.assertEqual(2, list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                });

                runner->test("when ArrayList has more than one value", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>()
                        ->add(0)
                        ->add(1);

                    const P<ArrayList<int>> result = list->add(2);

                    test.assertEqual(result, list);
                    test.assertEqual(3, list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                    test.assertEqual(2, list->get(2));
                });
            });

            runner->testMethod("removeAt()", [&]
            {
                runner->test("with one value and index 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>()
                        ->add(1);

                    const int result = list->removeAt(0);

                    test.assertEqual(1, result);
                    test.assertEqual(0, list->getCount());
                });

                runner->test("with two values and index 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>()
                        ->add(0)
                        ->add(1);

                    const int result = list->removeAt(0);

                    test.assertEqual(0, result);
                    test.assertEqual(1, list->getCount());
                    test.assertEqual(1, list->get(0));
                });

                runner->test("with two values and index 1", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>()
                        ->add(0)
                        ->add(1);

                    const int result = list->removeAt(1);

                    test.assertEqual(1, result);
                    test.assertEqual(1, list->getCount());
                    test.assertEqual(0, list->get(0));
                });

                runner->test("with three values and index 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>()
                        ->add(0)
                        ->add(1)
                        ->add(2);

                    const int result = list->removeAt(0);

                    test.assertEqual(0, result);
                    test.assertEqual(2, list->getCount());
                    test.assertEqual(1, list->get(0));
                    test.assertEqual(2, list->get(1));
                });

                runner->test("with three values and index 1", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>()
                        ->add(0)
                        ->add(1)
                        ->add(2);

                    const int result = list->removeAt(1);

                    test.assertEqual(1, result);
                    test.assertEqual(2, list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(2, list->get(1));
                });

                runner->test("with three values and index 2", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>()
                        ->add(0)
                        ->add(1)
                        ->add(2);

                    const int result = list->removeAt(2);

                    test.assertEqual(2, result);
                    test.assertEqual(2, list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                });
            });
        });
    }
}