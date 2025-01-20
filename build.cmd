mkdir outputs

set COMPILE=g++ -std=c++20 -x c++ -g -c --coverage
set LINK=g++ --coverage

del outputs\*.gcno

%COMPILE% -o outputs\AllocatorDecorator.o sources\AllocatorDecorator.cpp || exit /b
%COMPILE% -o outputs\ByteCountingAllocator.o sources\ByteCountingAllocator.cpp || exit /b
%COMPILE% -o outputs\CharacterWriteStream.o sources\CharacterWriteStream.cpp || exit /b
%COMPILE% -o outputs\CurrentProcess.o sources\CurrentProcess.cpp || exit /b
%COMPILE% -o outputs\HeapAllocator.o sources\HeapAllocator.cpp || exit /b
%COMPILE% -o outputs\Main.o sources\Main.cpp || exit /b
%COMPILE% -o outputs\StdCoutCharacterWriteStream.o sources\StdCoutCharacterWriteStream.cpp || exit /b
%COMPILE% -o outputs\Test.o sources\Test.cpp || exit /b
%COMPILE% -o outputs\TestGroup.o sources\TestGroup.cpp || exit /b
%COMPILE% -o outputs\TestAssertionFailure.o sources\TestAssertionFailure.cpp || exit /b
%COMPILE% -o outputs\TestRunner.o sources\TestRunner.cpp || exit /b

%LINK% -o outputs\Main.exe outputs\CurrentProcess.o outputs\HeapAllocator.o outputs\Main.o outputs\StdCoutCharacterWriteStream.o || exit /b

%COMPILE% -o outputs\ByteCountingAllocatorTests.o sources\ByteCountingAllocatorTests.cpp || exit /b
%COMPILE% -o outputs\TestMain.o sources\TestMain.cpp || exit /b
%COMPILE% -o outputs\TestTests.o sources\TestTests.cpp || exit /b

%LINK% -o outputs\TestMain.exe outputs\AllocatorDecorator.o outputs\ByteCountingAllocator.o outputs\ByteCountingAllocatorTests.o outputs\CurrentProcess.o outputs\HeapAllocator.o outputs\StdCoutCharacterWriteStream.o outputs\Test.o outputs\TestAssertionFailure.o outputs\TestGroup.o outputs\TestRunner.o outputs\TestMain.o outputs\TestTests.o || exit /b