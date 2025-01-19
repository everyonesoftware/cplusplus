#include "StdCoutCharacterWriteStream.h"

#include <iostream>

namespace e1
{
    StdCoutCharacterWriteStream::StdCoutCharacterWriteStream()
    {
    }

    void StdCoutCharacterWriteStream::writeString(const char* toWrite)
    {
        std::cout << toWrite;
    }

    void StdCoutCharacterWriteStream::writeLine()
    {
        this->writeString("\n");
    }

    void StdCoutCharacterWriteStream::writeLine(const char* toWrite)
    {
        this->writeString(toWrite);
        this->writeLine();
    }

    void StdCoutCharacterWriteStream::writeInt(int toWrite)
    {
        std::cout << toWrite;
    }
}