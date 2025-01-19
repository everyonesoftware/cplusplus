#ifndef E1_CHARACTERWRITESTREAM_H
#define E1_CHARACTERWRITESTREAM_H

namespace e1
{
    /**
     * A stream that writes characters.
     */
    class CharacterWriteStream
    {
    public:
        /**
         * Write the provided null-terminated string to the stream.
         * @param toWrite The null-terminated string to write.
         */
        virtual void writeString(const char* toWrite) = 0;

        /**
         * Write a newline sequence.
         */
        virtual void writeLine() = 0;

        /**
         * Write the provided null-terminated string to the stream followed by a newline sequence.
         * @param toWrite The null-terminated string to write.
         */
        virtual void writeLine(const char* toWrite) = 0;

        /**
         * Write the string-representation of the provided int value.
         * @param toWrite The int to write.
         */
        virtual void writeInt(int toWrite) = 0;
    };
}

#endif