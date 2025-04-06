#include "ArrayListTests.h"

#include "ArrayList.h"
#include "HeapAllocator.h"

namespace e1
{
    class TypeCounter
    {
    public:
        TypeCounter()
        {
            TypeCounter::DefaultConstructorCalls++;
        }
        TypeCounter([[maybe_unused]] const TypeCounter& toCopy)
        {
            TypeCounter::CopyConstructorCalls++;
        }
        ~TypeCounter()
        {
            TypeCounter::DestructorCalls++;
        }

        NotCopyable& operator=(const NotCopyable&) = delete;

        static void reset()
        {
            TypeCounter::DefaultConstructorCalls = 0;
            TypeCounter::CopyConstructorCalls = 0;
            TypeCounter::DestructorCalls = 0;
        }

        static inline int DefaultConstructorCalls = 0;
        static inline int CopyConstructorCalls = 0;
        static inline int DestructorCalls = 0;
    };

    void ArrayListTests(const P<TestRunner>& runner)
    {
        runner->testType("ArrayList<T>", [&]
        {
            runner->testMethod("constructor()", [&]
            {
                runner->test("on the stack with no allocator", [](Test test)
                {
                    ArrayList<int> list;
                    test.assertEqual(static_cast<std::size_t>(0), list.getCount());
                    test.assertEqual(nullptr, list.getAllocator());
                    test.assertEqual(&list, list.getThisPointer());
                });

                runner->test("on the stack with an allocator", [](Test test)
                {
                    HeapAllocator allocator;
                    ArrayList<int> list(&allocator);
                    test.assertEqual(static_cast<std::size_t>(0), list.getCount());
                    test.assertEqual(&allocator, list.getAllocator());
                    test.assertEqual(&list, list.getThisPointer());
                });

                runner->test("on the heap with no allocator", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>();
                    test.assertEqual(static_cast<std::size_t>(0), list->getCount());
                    test.assertEqual(&allocator, list->getAllocator());
                    test.assertEqual(list, list->getThisPointer());
                });

                runner->test("on the heap with an allocator", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator);
                    test.assertEqual(static_cast<std::size_t>(0), list->getCount());
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
                    test.assertEqual(static_cast<std::size_t>(1), list->getCount());
                    test.assertEqual(5, list->get(0));
                });

                runner->test("when ArrayList has one value and index is 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0);

                    const P<ArrayList<int>> result = list->insert(0, 1);

                    test.assertEqual(result, list);
                    test.assertEqual(static_cast<std::size_t>(2), list->getCount());
                    test.assertEqual(1, list->get(0));
                    test.assertEqual(0, list->get(1));
                });

                runner->test("when ArrayList has one value and index is 1", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0);

                    const P<ArrayList<int>> result = list->insert(1, 1);

                    test.assertEqual(result, list);
                    test.assertEqual(static_cast<std::size_t>(2), list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                });

                runner->test("when ArrayList has two values and index is 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0)->add(1);
                    int value = list->get(0);
                    test.assertEqual(0, value);
                    value = list->get(1);
                    test.assertEqual(1, value);

                    const P<ArrayList<int>> result = list->insert(0, 2);

                    // test.assertEqual(result, list);
                    // test.assertEqual(static_cast<std::size_t>(3), list->getCount());
                    // value = list->get(0);
                    // test.assertEqual(2, value);
                    // value = list->get(1);
                    // test.assertEqual(0, value);
                    // value = list->get(2);
                    // test.assertEqual(1, value);
                });

                runner->test("when ArrayList has two values and index is 1", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0)->add(1);

                    const P<ArrayList<int>> result = list->insert(1, 2);

                    test.assertEqual(result, list);
                    test.assertEqual(static_cast<std::size_t>(3), list->getCount());
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
                    test.assertEqual(static_cast<std::size_t>(3), list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                    test.assertEqual(2, list->get(2));
                });

                runner->test("invoked 100 times and index 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>();

                    for (std::size_t i = 0; i < 100; i++)
                    {
                        const P<ArrayList<int>> result = list->insert(0, 50);
                        test.assertEqual(result, list);
                        test.assertEqual(i + 1, list->getCount());

                        for (std::size_t j = 0; j <= i; j++)
                        {
                            test.assertEqual(50, list->get(j));
                        }
                    }
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
                    test.assertEqual(static_cast<std::size_t>(1), list->getCount());
                    test.assertEqual(5, list->get(0));
                });

                runner->test("when ArrayList has one value", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator)->add(0);

                    const P<ArrayList<int>> result = list->add(1);

                    test.assertEqual(result, list);
                    test.assertEqual(static_cast<std::size_t>(2), list->getCount());
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
                    test.assertEqual(static_cast<std::size_t>(3), list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                    test.assertEqual(2, list->get(2));
                });

                runner->test("with TypeCounter", [](Test test)
                {
                    TypeCounter::reset();

                    HeapAllocator allocator;
                    const P<ArrayList<TypeCounter>> list = allocator.create<ArrayList<TypeCounter>>();

                    test.assertEqual(0, TypeCounter::DefaultConstructorCalls);
                    test.assertEqual(0, TypeCounter::CopyConstructorCalls);
                    test.assertEqual(0, TypeCounter::DestructorCalls);

                    list->add(TypeCounter());
                    test.assertEqual(1, TypeCounter::DefaultConstructorCalls);
                    test.assertEqual(1, TypeCounter::CopyConstructorCalls);
                    test.assertEqual(1, TypeCounter::DestructorCalls);

                    list->add(TypeCounter());
                    test.assertEqual(2, TypeCounter::DefaultConstructorCalls);
                    test.assertEqual(3, TypeCounter::CopyConstructorCalls);
                    test.assertEqual(3, TypeCounter::DestructorCalls);

                    list->add(TypeCounter());
                    test.assertEqual(3, TypeCounter::DefaultConstructorCalls);
                    test.assertEqual(4, TypeCounter::CopyConstructorCalls);
                    test.assertEqual(4, TypeCounter::DestructorCalls);

                    list->add(TypeCounter());
                    test.assertEqual(4, TypeCounter::DefaultConstructorCalls);
                    test.assertEqual(8, TypeCounter::CopyConstructorCalls);
                    test.assertEqual(8, TypeCounter::DestructorCalls);

                    for (int i = 1; i <= 4; i++)
                    {
                        list->removeAt(list->getCount() - 1);
                        test.assertEqual(4, TypeCounter::DefaultConstructorCalls);
                        test.assertEqual(8 + i, TypeCounter::CopyConstructorCalls);
                        test.assertEqual(8 + (i * 2), TypeCounter::DestructorCalls);
                    }
                });
            });

            runner->test("set()", [](Test test)
            {
                HeapAllocator allocator;
                const P<ArrayList<int>> list = allocator.create<ArrayList<int>>(&allocator);
                for (int i = 0; i < 10; i++)
                {
                    list->add(i);
                }

                for (std::size_t i = 0; i < list->getCount(); i++)
                {
                    list->set(i, list->get(i) + 1);
                }

                for (std::size_t i = 0; i < list->getCount(); i++)
                {
                    const int value = list->get(i);
                    test.assertEqual(static_cast<int>(i + 1), value);
                }
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
                    test.assertEqual(static_cast<std::size_t>(0), list->getCount());
                });

                runner->test("with two values and index 0", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>()
                        ->add(0)
                        ->add(1);

                    const int result = list->removeAt(0);

                    test.assertEqual(0, result);
                    test.assertEqual(static_cast<std::size_t>(1), list->getCount());
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
                    test.assertEqual(static_cast<std::size_t>(1), list->getCount());
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
                    test.assertEqual(static_cast<std::size_t>(2), list->getCount());
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
                    test.assertEqual(static_cast<std::size_t>(2), list->getCount());
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
                    test.assertEqual(static_cast<std::size_t>(2), list->getCount());
                    test.assertEqual(0, list->get(0));
                    test.assertEqual(1, list->get(1));
                });

                runner->test("with 100 values", [](Test test)
                {
                    HeapAllocator allocator;
                    const P<ArrayList<int>> list = allocator.create<ArrayList<int>>();
                    for (int i = 0; i < 100; i++)
                    {
                        list->add(i);
                    }
                    test.assertEqual(static_cast<std::size_t>(100), list->getCount());

                    for (int i = 0; i < 100; i++)
                    {
                        const int value = list->removeAt(0);
                        test.assertEqual(i, value);
                    }
                    test.assertEqual(static_cast<std::size_t>(0), list->getCount());
                });
            });
        });
    }
}