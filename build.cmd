call clean.cmd

mkdir outputs

set COMPILE=g++ -std=c++20 -x c++ -g -c --coverage -pedantic-errors
set LINK=g++ --coverage

del outputs\*.gcno

%COMPILE% -o outputs\Allocator.o sources\Allocator.cpp || exit /b
%COMPILE% -o outputs\AllocatorDecorator.o sources\AllocatorDecorator.cpp || exit /b
%COMPILE% -o outputs\ByteCountingAllocator.o sources\ByteCountingAllocator.cpp || exit /b
%COMPILE% -o outputs\CharacterWriteStream.o sources\CharacterWriteStream.cpp || exit /b
%COMPILE% -o outputs\Counter.o sources\Counter.cpp || exit /b
%COMPILE% -o outputs\CurrentProcess.o sources\CurrentProcess.cpp || exit /b
%COMPILE% -o outputs\HasAllocator.o sources\HasAllocator.cpp || exit /b
%COMPILE% -o outputs\HeapAllocator.o sources\HeapAllocator.cpp || exit /b
%COMPILE% -o outputs\Main.o sources\Main.cpp || exit /b
%COMPILE% -o outputs\StdCoutCharacterWriteStream.o sources\StdCoutCharacterWriteStream.cpp || exit /b
%COMPILE% -o outputs\Test.o sources\Test.cpp || exit /b
%COMPILE% -o outputs\TestAssertionFailure.o sources\TestAssertionFailure.cpp || exit /b
%COMPILE% -o outputs\TestGroup.o sources\TestGroup.cpp || exit /b
%COMPILE% -o outputs\TestRunner.o sources\TestRunner.cpp || exit /b

%LINK% -o outputs\Main.exe outputs\CurrentProcess.o outputs\HeapAllocator.o outputs\Main.o outputs\StdCoutCharacterWriteStream.o outputs\HasAllocator.o outputs\Allocator.o outputs\Counter.o || exit /b

%COMPILE% -o outputs\ArrayListTests.o sources\ArrayListTests.cpp || exit /b
%COMPILE% -o outputs\ByteTests.o sources\ByteTests.cpp || exit /b
%COMPILE% -o outputs\ByteCountingAllocatorTests.o sources\ByteCountingAllocatorTests.cpp || exit /b
%COMPILE% -o outputs\CounterTests.o sources\CounterTests.cpp || exit /b
%COMPILE% -o outputs\HeapAllocatorTests.o sources\HeapAllocatorTests.cpp || exit /b
%COMPILE% -o outputs\PointerTests.o sources\PointerTests.cpp || exit /b
%COMPILE% -o outputs\TestAssertionFailureTests.o sources\TestAssertionFailureTests.cpp || exit /b
%COMPILE% -o outputs\TestMain.o sources\TestMain.cpp || exit /b
%COMPILE% -o outputs\TestRunnerTests.o sources\TestRunnerTests.cpp || exit /b
%COMPILE% -o outputs\TestTests.o sources\TestTests.cpp || exit /b

%LINK% -o outputs\TestMain.exe outputs\AllocatorDecorator.o outputs\ByteCountingAllocator.o outputs\ByteCountingAllocatorTests.o outputs\CurrentProcess.o outputs\HeapAllocator.o outputs\StdCoutCharacterWriteStream.o outputs\Test.o outputs\TestAssertionFailure.o outputs\TestAssertionFailureTests.o outputs\TestGroup.o outputs\TestRunner.o outputs\TestMain.o outputs\TestTests.o outputs\TestRunnerTests.o outputs\PointerTests.o outputs\HeapAllocatorTests.o outputs\ByteTests.o outputs\ArrayListTests.o outputs\HasAllocator.o outputs\Allocator.o outputs\CounterTests.o outputs\Counter.o || exit /b