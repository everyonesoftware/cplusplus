#ifndef E1_STDCOUTCHARACTERWRITESTREAM_H
#define E1_STDCOUTCHARACTERWRITESTREAM_H

#include "CharacterWriteStream.h"

namespace e1
{
    class StdCoutCharacterWriteStream : public CharacterWriteStream
    {
    public:
        explicit StdCoutCharacterWriteStream();

        virtual void writeString(const char* toWrite);

        virtual void writeLine();

        virtual void writeLine(const char* toWrite);

        virtual void writeInt(int toWrite);
    };
}

#endif