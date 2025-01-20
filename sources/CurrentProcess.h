#ifndef E1_CURRENTPROCESS_H
#define E1_CURRENTPROCESS_H

#include "Action.h"
#include "Allocator.h"
#include "FileSystem.h"
#include "HeapAllocator.h"
#include "Pointer.h"
#include "StdCoutCharacterWriteStream.h"

namespace e1
{
    /**
     * An object that encapsulates the resources available to the running application.
     */
    class CurrentProcess
        : HasThisPointer
    {
    public:
        /**
         * Run the provided function and pass in a new CurrentProcess object. The exit code that is set
         * on the provided CurrentProcess will be returned.
         * @param function The function that will be run.
         */
        static int run(const Action<P<CurrentProcess>> action);

        CurrentProcess(const CurrentProcess&) = delete;
        CurrentProcess& operator=(const CurrentProcess&) = delete;

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
         * Get this CurrentProcess's FileSystem object.
         */
        FileSystem& getFileSystem();

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
        /**
         * Create a new CurrentProcess object.
         */
        CurrentProcess();

        const P<CurrentProcess> getThisPointer() const;

        P<Allocator> allocator;
        int exitCode;
        FileSystem fileSystem;
        P<CharacterWriteStream> outputWriteStream;
    };
}

#endif
