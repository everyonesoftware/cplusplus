#pragma once

#include "Action.h"
#include "Allocator.h"
#include "Array.h"
#include "FileSystem.h"
#include "HeapAllocator.h"
#include "NotCopyable.h"
#include "Pointer.h"
#include "StdCoutCharacterWriteStream.h"

namespace e1
{
    /**
     * An object that encapsulates the resources available to the running application.
     */
    class CurrentProcess : HasThisPointer, NotCopyable
    {
    public:
        /**
         * Run the provided function and pass in a new CurrentProcess object. The exit code that is set
         * on the provided CurrentProcess will be returned.
         * @param argc The number of command line arguments that were passed.
         * @param argv The const char* pointers for the command line arguments.
         * @param function The function that will be run.
         */
        static int run(int argc, const char** argv, const Action<P<CurrentProcess>> action);

        /**
         * Create a new empty CurrentProcess object.
         */
        CurrentProcess();

        /**
         * Set the command line arguments for this CurrentProcess.
         * @param argc The argument count.
         * @param argv The pointers to the individual zero-terminated command line arguments.
         */
        const P<CurrentProcess> setCommandLineArguments(int argc, const char** argv);

        /**
         * Get the number of command line arguments.
         */
        int getCommandLineArgumentCount() const;

        /**
         * Get the points to the individual zero-terminated command line arguments.
         */
        const char** getCommandLineArguments() const;

        /**
         * Set the exit code that this CurrentProcess will return when the application is finished.
         * Returns a Pointer to this object for method chaining.
         * @param exitCode The exit code.
         */
        const P<CurrentProcess> setExitCode(int exitCode);

        /**
         * Get the exit code that this CurrentProcess will return when the application is finished.
         */
        int getExitCode() const;

        /**
         * Get the Allocator that this CurrentProcess uses to allocate memory and create new
         * objects.
         */
        const P<Allocator>& getAllocator() const;
        /**
         * Set the Allocator that this CurrentProcess uses to allocate memory and create new
         * objects. Returns a Pointer to this object for method chaining.
         * @param allocator The new Allocator to use.
         */
        const P<CurrentProcess> setAllocator(const P<Allocator>& allocator);

        /**
         * Get this CurrentProcess's FileSystem object.
         */
        const P<FileSystem>& getFileSystem() const;

        /**
         * Get this CurrentProcess's CharacterWriteStream that writes to standard out.
         */
        const P<CharacterWriteStream>& getOutputWriteStream() const;

        /**
         * Set this CurrentProcess's CharacterWriteStream that writes to standard out.
         * @param outputWriteStream The CharacterWriteStream that writes to standard out.
         */
        const P<CurrentProcess> setOutputWriteStream(const P<CharacterWriteStream>& outputWriteStream);

    private:
        const P<CurrentProcess> getThisPointer() const;

        int argc;
        const char** argv;
        int exitCode;
        P<Allocator> allocator;
        P<FileSystem> fileSystem;
        P<CharacterWriteStream> outputWriteStream;
    };
}