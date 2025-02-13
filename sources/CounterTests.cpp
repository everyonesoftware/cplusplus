#include "CounterTests.h"

#include "Counter.h"

namespace e1
{
    void CounterTests(const P<TestRunner>& runner)
    {
        runner->testType("Counter", [&]
        {
            runner->testMethod("constructor()", [&]
            {
                runner->test("with no parenthesis", [](Test test)
                {
                    Counter c;
                    test.assertEqual(0, c.get());
                });

                runner->test("with curly brackets", [](Test test)
                {
                    Counter c{};
                    test.assertEqual(0, c.get());
                });
            });

            runner->testMethod("constructor(int)", [&]
            {
                runner->test("with parenthesis", [](Test test)
                {
                    Counter c(1);
                    test.assertEqual(1, c.get());
                });

                runner->test("with curly brackets", [](Test test)
                {
                    Counter c{2};
                    test.assertEqual(2, c.get());
                });
            });

            runner->test("operator=(int)", [](Test test)
            {
                Counter c;

                c = 20;

                test.assertEqual(20, c.get());
            });

            runner->test("set(int)", [](Test test)
            {
                Counter c;

                c.set(21);

                test.assertEqual(21, c.get());
            });

            runner->test("operator=(const Counter&)", [](Test test)
            {
                Counter c1;
                Counter c2(11);

                c1 = c2;

                test.assertEqual(11, c1.get());
                test.assertEqual(11, c2.get());
            });

            runner->test("set(const Counter&)", [](Test test)
            {
                Counter c1;
                Counter c2(11);

                c1.set(c2);

                test.assertEqual(11, c1.get());
                test.assertEqual(11, c2.get());
            });

            runner->test("operator int()", [](Test test)
            {
                Counter c(3);

                test.assertEqual(3, (int)c);
                test.assertEqual(3, static_cast<int>(c));
            });

            runner->test("increment()", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    c.increment();
                    test.assertEqual(i + 1, c.get());
                }
            });

            runner->test("incrementAndGet()", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    int value = c.incrementAndGet();
                    test.assertEqual(i + 1, value);
                    test.assertEqual(value, c.get());
                }
            });

            runner->test("operator++()", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    int value = ++c;
                    test.assertEqual(i + 1, value);
                    test.assertEqual(value, c.get());
                }
            });

            runner->test("getAndIncrement()", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    int value = c.getAndIncrement();
                    test.assertEqual(i, value);
                    test.assertEqual(i + 1, c.get());
                }
            });

            runner->test("operator++(int)", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    int value = c++;
                    test.assertEqual(i, value);
                    test.assertEqual(i + 1, c.get());
                }
            });

            runner->test("decrement()", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    c.decrement();
                    test.assertEqual(-(i + 1), c.get());
                }
            });

            runner->test("decrementAndGet()", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    int value = c.decrementAndGet();
                    test.assertEqual(-(i + 1), value);
                    test.assertEqual(value, c.get());
                }
            });

            runner->test("operator--()", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    int value = --c;
                    test.assertEqual(-(i + 1), value);
                    test.assertEqual(value, c.get());
                }
            });

            runner->test("getAndDecrement()", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    int value = c.getAndDecrement();
                    test.assertEqual(-i, value);
                    test.assertEqual(-(i + 1), c.get());
                }
            });

            runner->test("operator--(int)", [](Test test)
            {
                Counter c;
                for (int i = 0; i < 10; i++)
                {
                    int value = c--;
                    test.assertEqual(-i, value);
                    test.assertEqual(-(i + 1), c.get());
                }
            });
        });
    }
}