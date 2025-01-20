#include "Test.h"

#include "TestAssertionFailure.h"

namespace e1
{
    void Test::fail(const char* message)
    {
        throw TestAssertionFailure(message);
    }

    void Test::assertThrows(const Action<>& action)
    {
        bool threwException = false;
        try
        {
            action();
            threwException = false;
        }
        catch (...)
        {
            threwException = true;
        }
        
        if (!threwException)
        {
            this->fail("Expected an exception to be thrown.");
        }
    }
}