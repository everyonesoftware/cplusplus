mkdir outputs

set COMPILE=g++ -std=c++20 -x c++ -g -c
%COMPILE% -o outputs\AllocatorDecorator.o sources\AllocatorDecorator.cpp || exit /b
%COMPILE% -o outputs\ByteCountingAllocator.o sources\ByteCountingAllocator.cpp || exit /b
%COMPILE% -o outputs\CharacterWriteStream.o sources\CharacterWriteStream.cpp || exit /b
%COMPILE% -o outputs\CurrentProcess.o sources\CurrentProcess.cpp || exit /b
%COMPILE% -o outputs\HeapAllocator.o sources\HeapAllocator.cpp || exit /b
%COMPILE% -o outputs\Main.o sources\Main.cpp || exit /b
%COMPILE% -o outputs\StdCoutCharacterWriteStream.o sources\StdCoutCharacterWriteStream.cpp || exit /b

g++ -o outputs\Main.exe outputs\AllocatorDecorator.o outputs\ByteCountingAllocator.o outputs\CharacterWriteStream.o outputs\CurrentProcess.o outputs\HeapAllocator.o outputs\Main.o outputs\StdCoutCharacterWriteStream.o || exit /b
