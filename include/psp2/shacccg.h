/**
 * \usergroup{SceShaccCg}
 * \usage{psp2/shacccg.h,SceShaccCg_stub}
 */

#ifndef _DOLCESDK_PSP2_SHACCCG_H_
#define _DOLCESDK_PSP2_SHACCCG_H_

#include <psp2/shacccg/types.h>
#include <psp2/shacccg/paramquery.h>

/** @file	shacccg.h

	The PRX version of psp2cgc allows applications to compile shaders without
	having to compile them at build time. Users must use a set of callbacks for
	file handling.
	The compiler may be invoked by the following function:

	sceShaccCgCompileProgram
		Performs a full compile, returning a sceShaccCgCompileOutput object
		containing the binary.

	There is a corresponding destroy function, sceShaccCgDestroyCompileOutput.
	This function must be called in order to free the resources associated
	with a job.
	Creation and destruction do not have to be performed on the same thread.

	This function depends chiefly on two inputs:

	sceShaccCgCompileOptions
		This structure is the equivalent of the command-line options for the
		standalone compiler. It may also be used as a compilation ID by
		extending the struct and passing the appropriate pointer to SceShaccCg.
		This pointer will be provided on all callbacks.

	sceShaccCgCallbackList
		Provides the compiler with an interface to the file system - whether
		it is interface provided by the operating system or a virtualized one.
		For details regarding the individual callbacks, please refer to the
		documentation of sceShaccCgCallbackList.
		Please note that if a callback list is provided, it should always be
		initialized via sceShaccCgInitializeCallbackList.
		Please noted that where indicated, the callbacks argument is required.
*/

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/**	@brief	Describes the output of a compilation process.

	On failure, programData will be 0 and the diagnosticCount will be non-zero.
	On success, programData will be non-zero and one or more non-error
	diagnostics may be present.

	@ingroup shacccg
*/
typedef struct SceShaccCgCompileOutput {
	const uint8_t *programData;						///< The compiled program binary data.
	uint32_t programSize;							///< The compiled program size.
	int32_t diagnosticCount;						///< The number of diagnostics.
	const SceShaccCgDiagnosticMessage *diagnostics;	///< The diagnostic message array.
} SceShaccCgCompileOutput;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

/**	@brief	Compiles a Cg program for PSP2

	Compiles a program for PSP2 using the options provided.

	@param[in] options
		Indicates the compile options for compiling a program.
		Also doubles as a session id where multiple compiles are being run.

	@param[in] callbacks
		Defines the callbacks to be used for file system access. If not provided,
		the default file system of the OS will be used (optional).

	@param[in] userData
		Opaque pointer to user data that will be passed back to callbacks.

	@return
		A SceShaccCgCompileOutput object, containing the binary and sdb
		outputs of the compile. Must be destroyed using
		sceShaccCgDestroyCompileOutput. If 0 is returned, the input arguments were
		malformed.

	@ingroup shacccg
*/
SceShaccCgCompileOutput const* sceShaccCgCompileProgram(
	const SceShaccCgCompileOptions *options,
	const SceShaccCgCallbackList *callbacks,
	void *userData);

/**	@brief	Releases all allocations associated with a compiled program.

	@param[in] output
		The result from a call to sceShaccCgCompileProgram, to be destroyed.

	@ingroup shacccg
*/
void sceShaccCgDestroyCompileOutput(
	SceShaccCgCompileOutput const *output);

/**	@brief	Sets memory allocation callbacks

	Sets memory allocation callbacks for SceShaccCg library

	@param[in] allocate
		Function used for memory allocation.

	@param[in] deallocate
		Function used to free memory.

	@ingroup shacccg
*/
int32_t sceShaccCgSetMemAllocator(
	SceShaccCgAllocator allocate,
	SceShaccCgDeallocator deallocate);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif /* _DOLCESDK_PSP2_SHACCCG_H_ */
