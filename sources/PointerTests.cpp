#include "PointerTests.h"

namespace e1
{
    void PointerTests(const P<TestRunner>& runner)
    {
        runner->testType("Pointer", [&]
        {
            runner->test("constructor()", [](Test test)
            {
                Pointer<int> p;

                test.assertEqual(nullptr, p.getValuePointer());
                test.assertEqual(false, p.hasValue());
            });

            runner->testMethod("constructor(T*)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<int> p(nullptr);

                    test.assertEqual(nullptr, p.getValuePointer());
                    test.assertEqual(false, p.hasValue());
                });

                runner->test("with local variable", [](Test test)
                {
                    int value = 50;
                    Pointer<int> p(&value);

                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(true, p.hasValue());
                    test.assertEqual(value, p.getValue());
                    test.assertEqual(value, *p);
                });
            });

            runner->testMethod("constructor(T*,int*,Action)", [&]
            {
                runner->test("with local variables", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });

                    Pointer<bool> p(&value, &refCount);
                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                    test.assertEqual(false, *p);
                });
            });

            runner->testMethod("constructor(const Pointer<U>&)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<TestAssertionFailure> p1(nullptr);

                    Pointer<std::exception> p2(p1);

                    test.assertEqual(nullptr, p2.getValuePointer());
                    test.assertEqual(false, p2.hasValue());
                });

                runner->test("with non-null", [](Test test)
                {
                    TestAssertionFailure value("fake error");
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    Pointer<TestAssertionFailure> p1(&value, &refCount);

                    Pointer<std::exception> p2(p1);

                    test.assertEqual(&value, p2.getValuePointer());
                    test.assertEqual(true, p2.hasValue());
                    test.assertEqual(2, refCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    p2.set(nullptr);

                    test.assertEqual(nullptr, p2.getValuePointer());
                    test.assertEqual(false, p2.hasValue());
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });
            });

            runner->testMethod("constructor(const Pointer<T>&)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<bool> p1(nullptr);

                    Pointer<bool> p2(p1);

                    test.assertEqual(nullptr, p2.getValuePointer());
                    test.assertEqual(false, p2.hasValue());
                });

                runner->test("with non-null", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    Pointer<bool> p1(&value, &refCount);

                    Pointer<bool> p2(p1);

                    test.assertEqual(&value, p2.getValuePointer());
                    test.assertEqual(true, p2.hasValue());
                    test.assertEqual(false, value);
                    test.assertEqual(2, refCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    p2.set(nullptr);

                    test.assertEqual(nullptr, p2.getValuePointer());
                    test.assertEqual(false, p2.hasValue());
                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });
            });

            runner->testMethod("destructor", [&]
            {
                runner->test("with one pointer", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });

                    {
                        Pointer<bool> p(&value, &refCount);
                        test.assertEqual(false, value);
                        test.assertEqual(1, refCount.getCount());
                        test.assertEqual(0, cleanupCount);
                        test.assertEqual(false, *p);
                    }

                    test.assertEqual(false, value);
                    test.assertEqual(0, refCount.getCount());
                    test.assertEqual(1, cleanupCount);
                });

                runner->test("with two pointers", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });

                    Pointer<bool> p1(&value, &refCount);
                    {
                        Pointer<bool> p2(&value, &refCount);
                        test.assertEqual(false, value);
                        test.assertEqual(2, refCount.getCount());
                        test.assertEqual(0, cleanupCount);
                        test.assertEqual(false, *p2);
                    }

                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });
            });

            runner->testMethod("set(T*)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<int> p;

                    p.set(nullptr);

                    test.assertEqual(nullptr, p.getValuePointer());
                    test.assertEqual(false, p.hasValue());
                });

                runner->test("with non-null but same as current value", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });

                    Pointer<bool> p(&value, &refCount);
                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    p.set(&value);
                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });

                runner->test("with non-null but different from current value", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    bool value2 = true;

                    Pointer<bool> p(&value, &refCount);
                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    p.set(&value2);
                    test.assertEqual(&value2, p.getValuePointer());
                    test.assertEqual(true, *p);
                    test.assertEqual(0, refCount.getCount());
                    test.assertEqual(1, cleanupCount);
                });
            });

            runner->testMethod("operator=(T*)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<int> p;

                    p = nullptr;

                    test.assertEqual(nullptr, p.getValuePointer());
                    test.assertEqual(false, p.hasValue());
                });

                runner->test("with non-null but same as current value", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });

                    Pointer<bool> p(&value, &refCount);
                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    p = &value;
                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });

                runner->test("with non-null but different from current value", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    bool value2 = true;

                    Pointer<bool> p(&value, &refCount);
                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(false, value);
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    p = &value2;
                    test.assertEqual(&value2, p.getValuePointer());
                    test.assertEqual(true, *p);
                    test.assertEqual(0, refCount.getCount());
                    test.assertEqual(1, cleanupCount);
                });
            });

            runner->testMethod("set(const Pointer<T>&)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<int> p1;
                    Pointer<int> p2;

                    p1.set(p2);

                    test.assertEqual(nullptr, p1.getValuePointer());
                    test.assertEqual(false, p1.hasValue());
                });

                runner->test("with non-null but same as current value", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    Pointer<bool> p1(&value, &refCount);
                    Pointer<bool> p2(p1);

                    p1.set(p2);
                    test.assertEqual(&value, p1.getValuePointer());
                    test.assertEqual(2, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });

                runner->test("with non-null but different from current value", [](Test test)
                {
                    bool value1 = false;
                    int cleanupCount1 = 0;
                    ReferenceCount refCount1([&]{ cleanupCount1++; });
                    Pointer<bool> p1(&value1, &refCount1);

                    bool value2 = true;
                    int cleanupCount2 = 0;
                    ReferenceCount refCount2([&]{ cleanupCount2++; });
                    Pointer<bool> p2(&value2, &refCount2);

                    p1.set(p2);
                    test.assertEqual(&value2, p1.getValuePointer());
                    test.assertEqual(0, refCount1.getCount());
                    test.assertEqual(2, refCount2.getCount());
                    test.assertEqual(1, cleanupCount1);
                    test.assertEqual(0, cleanupCount2);
                });
            });

            runner->testMethod("operator=(const Pointer<T>&)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<int> p1;
                    Pointer<int> p2;

                    p1 = p2;

                    test.assertEqual(nullptr, p1.getValuePointer());
                    test.assertEqual(false, p1.hasValue());
                });

                runner->test("with non-null but same as current value", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    Pointer<bool> p1(&value, &refCount);
                    Pointer<bool> p2(p1);

                    p1 = p2;
                    test.assertEqual(&value, p1.getValuePointer());
                    test.assertEqual(2, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });

                runner->test("with non-null but different from current value", [](Test test)
                {
                    bool value1 = false;
                    int cleanupCount1 = 0;
                    ReferenceCount refCount1([&]{ cleanupCount1++; });
                    Pointer<bool> p1(&value1, &refCount1);

                    bool value2 = true;
                    int cleanupCount2 = 0;
                    ReferenceCount refCount2([&]{ cleanupCount2++; });
                    Pointer<bool> p2(&value2, &refCount2);

                    p1 = p2;
                    test.assertEqual(&value2, p1.getValuePointer());
                    test.assertEqual(0, refCount1.getCount());
                    test.assertEqual(2, refCount2.getCount());
                    test.assertEqual(1, cleanupCount1);
                    test.assertEqual(0, cleanupCount2);
                });
            });

            runner->testMethod("set(U*)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    TestAssertionFailure* value = nullptr;
                    Pointer<std::exception> p;

                    p.set(value);

                    test.assertEqual(nullptr, p.getValuePointer());
                    test.assertEqual(false, p.hasValue());
                });

                runner->test("with non-null but same as current value", [](Test test)
                {
                    TestAssertionFailure value("fake error");
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });

                    Pointer<std::exception> p(&value, &refCount);
                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    p.set(&value);
                    test.assertEqual(&value, p.getValuePointer());
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });

                runner->test("with non-null but different from current value", [](Test test)
                {
                    TestAssertionFailure value1("fake error 1");
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    TestAssertionFailure value2("fake error 2");

                    Pointer<std::exception> p(&value1, &refCount);
                    test.assertEqual(&value1, p.getValuePointer());
                    test.assertEqual(1, refCount.getCount());
                    test.assertEqual(0, cleanupCount);

                    p.set(&value2);
                    test.assertEqual(&value2, p.getValuePointer());
                    test.assertEqual(0, refCount.getCount());
                    test.assertEqual(1, cleanupCount);
                });
            });

            runner->testMethod("set(const Pointer<U>&)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<std::exception> p1;
                    Pointer<TestAssertionFailure> p2;

                    p1.set(p2);

                    test.assertEqual(nullptr, p1.getValuePointer());
                    test.assertEqual(false, p1.hasValue());
                });

                runner->test("with non-null but same as current value", [](Test test)
                {
                    TestAssertionFailure value("fake error");
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    Pointer<TestAssertionFailure> p1(&value, &refCount);
                    Pointer<std::exception> p2(p1);

                    p2.set(p1);
                    test.assertEqual(&value, p2.getValuePointer());
                    test.assertEqual(2, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });

                runner->test("with non-null but different from current value", [](Test test)
                {
                    TestAssertionFailure value1("fake error 1");
                    int cleanupCount1 = 0;
                    ReferenceCount refCount1([&]{ cleanupCount1++; });
                    Pointer<TestAssertionFailure> p1(&value1, &refCount1);

                    TestAssertionFailure value2("fake error 2");
                    int cleanupCount2 = 0;
                    ReferenceCount refCount2([&]{ cleanupCount2++; });
                    Pointer<std::exception> p2(&value2, &refCount2);

                    p2.set(p1);
                    test.assertEqual(&value1, p2.getValuePointer());
                    test.assertEqual(2, refCount1.getCount());
                    test.assertEqual(0, refCount2.getCount());
                    test.assertEqual(0, cleanupCount1);
                    test.assertEqual(1, cleanupCount2);
                });
            });

            runner->testMethod("operator=(const Pointer<U>&)", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<std::exception> p1;
                    Pointer<TestAssertionFailure> p2;

                    p1 = p2;

                    test.assertEqual(nullptr, p1.getValuePointer());
                    test.assertEqual(false, p1.hasValue());
                });

                runner->test("with non-null but same as current value", [](Test test)
                {
                    TestAssertionFailure value("fake error");
                    int cleanupCount = 0;
                    ReferenceCount refCount([&]{ cleanupCount++; });
                    Pointer<TestAssertionFailure> p1(&value, &refCount);
                    Pointer<std::exception> p2(p1);

                    p2 = p1;
                    test.assertEqual(&value, p2.getValuePointer());
                    test.assertEqual(2, refCount.getCount());
                    test.assertEqual(0, cleanupCount);
                });

                runner->test("with non-null but different from current value", [](Test test)
                {
                    TestAssertionFailure value1("fake error 1");
                    int cleanupCount1 = 0;
                    ReferenceCount refCount1([&]{ cleanupCount1++; });
                    Pointer<TestAssertionFailure> p1(&value1, &refCount1);

                    TestAssertionFailure value2("fake error 2");
                    int cleanupCount2 = 0;
                    ReferenceCount refCount2([&]{ cleanupCount2++; });
                    Pointer<std::exception> p2(&value2, &refCount2);

                    p2 = p1;
                    test.assertEqual(&value1, p2.getValuePointer());
                    test.assertEqual(2, refCount1.getCount());
                    test.assertEqual(0, refCount2.getCount());
                    test.assertEqual(0, cleanupCount1);
                    test.assertEqual(1, cleanupCount2);
                });
            });

            runner->testMethod("clear()", [&]
            {
                runner->test("with no value", [](Test test)
                {
                    Pointer<int> p;

                    p.clear();

                    test.assertEqual(nullptr, p.getValuePointer());
                    test.assertEqual(false, p.hasValue());
                });

                runner->test("with value", [](Test test)
                {
                    bool value = false;
                    int cleanupCount = 0;
                    ReferenceCount referenceCount([&]{ cleanupCount++; });
                    Pointer<bool> p(&value, &referenceCount);

                    for (int i = 0; i < 3; i++)
                    {
                        p.clear();
                        test.assertEqual(0, referenceCount.getCount());
                        test.assertEqual(1, cleanupCount);
                        test.assertEqual(nullptr, p.getValuePointer());
                        test.assertEqual(false, p.hasValue());
                    }
                });
            });

            runner->testMethod("operator*()", [&]
            {
                runner->test("with value", [](Test test)
                {
                    int value = 20;
                    Pointer<int> p(&value);

                    test.assertEqual(20, value);
                    test.assertEqual(20, *p);

                    *p = 30;

                    test.assertEqual(30, value);
                    test.assertEqual(30, *p);
                });
            });

            runner->testMethod("getValue()", [&]
            {
                runner->test("with value", [](Test test)
                {
                    int value = 20;
                    Pointer<int> p(&value);

                    test.assertEqual(20, value);
                    test.assertEqual(20, p.getValue());

                    p.getValue() = 30;

                    test.assertEqual(30, value);
                    test.assertEqual(30, p.getValue());
                });
            });

            runner->testMethod("getValuePointer()", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<int> p(nullptr);

                    test.assertEqual(nullptr, p.getValuePointer());
                });

                runner->test("with value", [](Test test)
                {
                    int value = 20;
                    Pointer<int> p(&value);

                    test.assertEqual(&value, p.getValuePointer());
                });
            });

            runner->testMethod("as<U>()", [&]
            {
                runner->test("with null", [](Test test)
                {
                    Pointer<int> p1;

                    Pointer<bool> p2 = p1.as<bool>();

                    test.assertEqual(nullptr, p2.getValuePointer());
                });

                runner->test("with non-null and same type", [](Test test)
                {
                    int value = 15;
                    Pointer<int> p1(&value);

                    Pointer<int> p2 = p1.as<int>();

                    test.assertEqual(&value, p2.getValuePointer());
                    int p2Value = *p2;
                    test.assertEqual(15, p2Value);
                });

                runner->test("with non-null and base type", [](Test test)
                {
                    TestAssertionFailure value("fake error");
                    Pointer<TestAssertionFailure> p1(&value);

                    Pointer<std::exception> p2 = p1.as<std::exception>();

                    test.assertEqual(&value, p2.getValuePointer());
                    test.assertEqual("fake error", p2->what());
                });

                runner->test("with non-null and derived type", [](Test test)
                {
                    TestAssertionFailure value("fake error");
                    Pointer<std::exception> p1(&value);

                    Pointer<TestAssertionFailure> p2 = p1.as<TestAssertionFailure>();

                    test.assertEqual(&value, p2.getValuePointer());
                    test.assertEqual("fake error", p2->getMessage());
                });
            });

            runner->testMethod("equals(const void*)", [&]
            {
                runner->test("with null and null", [](Test test)
                {
                    Pointer<int> left(nullptr);
                    const void* right = nullptr;

                    test.assertEqual(true, left.equals(right));
                });

                runner->test("with null and non-null", [](Test test)
                {
                    Pointer<int> left;
                    int value = 20;
                    const void* right = &value;

                    test.assertEqual(false, left.equals(right));
                });

                runner->test("with non-null and null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    const void* right = nullptr;

                    test.assertEqual(false, left.equals(right));
                });

                runner->test("with non-null and different non-null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    int value2 = 19;
                    const void* right = &value2;

                    test.assertEqual(false, left.equals(right));
                });

                runner->test("with non-null and same non-null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    const void* right = &value;

                    test.assertEqual(true, left.equals(right));
                });
            });

            runner->testMethod("operator==(const void*)", [&]
            {
                runner->test("with null and null", [](Test test)
                {
                    Pointer<int> left(nullptr);
                    const void* right = nullptr;

                    test.assertEqual(true, left == right);
                });

                runner->test("with null and non-null", [](Test test)
                {
                    Pointer<int> left;
                    int value = 20;
                    const void* right = &value;

                    test.assertEqual(false, left == right);
                });

                runner->test("with non-null and null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    const void* right = nullptr;

                    test.assertEqual(false, left == right);
                });

                runner->test("with non-null and different non-null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    int value2 = 19;
                    const void* right = &value2;

                    test.assertEqual(false, left == right);
                });

                runner->test("with non-null and same non-null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    const void* right = &value;

                    test.assertEqual(true, left == right);
                });
            });

            runner->testMethod("equals(const Pointer<U>&)", [&]
            {
                runner->test("with null and null", [](Test test)
                {
                    Pointer<int> left(nullptr);
                    Pointer<int> right;

                    test.assertEqual(true, left.equals(right));
                });

                runner->test("with null and non-null", [](Test test)
                {
                    Pointer<int> left;
                    int value = 20;
                    Pointer<int> right(&value);

                    test.assertEqual(false, left.equals(right));
                });

                runner->test("with non-null and null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    Pointer<int> right;

                    test.assertEqual(false, left.equals(right));
                });

                runner->test("with non-null and different non-null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    int value2 = 19;
                    Pointer<int> right(&value2);

                    test.assertEqual(false, left.equals(right));
                });

                runner->test("with non-null and same non-null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    Pointer<int> right(&value);

                    test.assertEqual(true, left.equals(right));
                });
            });

            runner->testMethod("operator==(const Pointer<U>&)", [&]
            {
                runner->test("with null and null", [](Test test)
                {
                    Pointer<int> left(nullptr);
                    Pointer<int> right;

                    test.assertEqual(true, left == right);
                });

                runner->test("with null and non-null", [](Test test)
                {
                    Pointer<int> left;
                    int value = 20;
                    Pointer<int> right(&value);

                    test.assertEqual(false, left == right);
                });

                runner->test("with non-null and null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    Pointer<int> right;

                    test.assertEqual(false, left == right);
                });

                runner->test("with non-null and different non-null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    int value2 = 19;
                    Pointer<int> right(&value2);

                    test.assertEqual(false, left == right);
                });

                runner->test("with non-null and same non-null", [](Test test)
                {
                    int value = 18;
                    Pointer<int> left(&value);
                    Pointer<int> right(&value);

                    test.assertEqual(true, left == right);
                });
            });
        });
    }
}