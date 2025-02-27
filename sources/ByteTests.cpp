#include "ByteTests.h"

#include "Byte.h"

namespace e1
{
    void ByteTests(const P<TestRunner>& runner)
    {
        runner->testType("byte", [&]
        {
            runner->test("sizeof", [](Test test)
            {
                test.assertEqual(1, sizeof(byte));
            });
        });
    }
}