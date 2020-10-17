/**
 * \usergroup{SceShaccCg}
 * \usage{psp2/shacccg.h,SceShaccCg_stub}
 */

#ifndef _DOLCESDK_PSP2_SHACCCG_H_
#define _DOLCESDK_PSP2_SHACCCG_H_

#include "psp2/shacccg/types.h"
#include "psp2/shacccg/paramquery.h"
#include "psp2common/types.h"

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/**	@brief	Describes the output of dependency generation.

	@ingroup shacccg
*/
typedef struct SceShaccCgDependencyOutput {
	SceInt32 dependencyTargetCount;					///< The number of dependencies.
	const SceChar8* const *dependencyTargets;		///< The individual target rules.
	SceInt32 diagnosticCount;						///< The number of diagnostics.
	const SceShaccCgDiagnosticMessage *diagnostics;	///< The diagnostic message array.
} SceShaccCgDependencyOutput;

/**	@brief	Describes the output of a compilation process.

	On failure, programData will be 0 and the diagnosticCount will be non-zero.
	On success, programData will be non-zero and one or more non-error
	diagnostics may be present.

	@ingroup shacccg
*/
typedef struct SceShaccCgCompileOutput {
	const SceUInt8 *programData;					///< The compiled program binary data.
	SceInt32 programSize;							///< The compiled program size.
	SceInt32 diagnosticCount;						///< The number of diagnostics.
	const SceShaccCgDiagnosticMessage *diagnostics;	///< The diagnostic message array.
} SceShaccCgCompileOutput;

/**	@brief	Describes the output of a preprocessor process.

	On failure, program will be 0 and the diagnosticCount will be non-zero.
	On success, program will be non-zero and one or more non-error
	diagnostics may be present.

	@ingroup shacccg
*/
typedef struct SceShaccCgPreprocessOutput {
	const SceChar8 *program;						///< The preprocessor output.
	SceInt32 programSize;							///< The preprocessor output size.
	SceInt32 diagnosticCount;						///< The number of diagnostics.
	const SceShaccCgDiagnosticMessage *diagnostics;	///< The diagnostic message array.
} SceShaccCgPreprocessOutput;

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
	ScePVoid userData);

/**	@brief	Releases all allocations associated with a compiled program.

	@param[in] output
		The result from a call to sceShaccCgCompileProgram, to be destroyed.

	@ingroup shacccg
*/
SceVoid sceShaccCgDestroyCompileOutput(
	SceShaccCgCompileOutput const *output);

/**	@brief	Preprocesses a Cg program for PSP2

	Compiles a program for PSP2 using the options provided. Callbacks may be
	provided, but are optional. (see note on struct SceShaccCgCallbackList)

	@param options
		Indicates the compile options for preprocessing a program. 
		Also doubles as a session id where multiple compiles are being run.

	@param callbacks
		Defines the callbacks to be used for file system access. If not provided,
		the default PSP2 file system will be used (optional).

	@param userData
		Opaque pointer to user data that will be passed back to callbacks.

	@param emitLineDirectives
		Indicates whether to emit #line directives in the output.

	@param emitComments
		Indicates whether to retain comments in the output.

	@return
		A SceShaccCgPreprocessOutput object, containing the UTF-8 encoded
		text of the preprocessed program. Must be destroyed using
		sceShaccCgDestroyPreprocessOutput. If 0 is returned the input arguments were
		malformed.

	@ingroup shacccg
*/
SceShaccCgPreprocessOutput const* sceShaccCgPreprocessProgram(
	const SceShaccCgCompileOptions *options,
	const SceShaccCgCallbackList *callbacks,
	ScePVoid userData,
	SceInt32 emitLineDirectives,
	SceInt32 emitComments);

/**	@brief	Releases all allocations associated with a compiled program.

	@param[in] output
		The result from a call to sceShaccCgPreprocessProgram, to be destroyed.

	@ingroup shacccg
*/
SceVoid sceShaccCgDestroyPreprocessOutput(
	SceShaccCgPreprocessOutput const *output);

/**	@brief	Generates dependency information for a program.

	Generates dependency information for the given compilation options.

	@param[in] options
		Indicates the compile options for generating the file dependencies for a
		program. Also doubles as a session id where multiple compiles are being run.

	@param[in] callbacks
		Defines the callbacks to be used for file system access. If not provided,
		the default PSP2 file system will be used (optional).

	@param userData
		Opaque pointer to user data that will be passed back to callbacks.

	@param[in] targetName
		The name of the main target rule. Because we have no concept of the final
		binary name at this point, this must always be provided.

	@param[in] emitPhonies
		Non-zero indicates that phony dependencies should be generated.

	@return
		A SceShaccCgDependencyOutput object, containing a list of file names and
		their dependent files. Should be destroyed using 
		sceShaccCgDestroyDependencyOutput. If 0 is returned, the input arguments
		were malformed.

	@ingroup shacccg
*/
SceShaccCgDependencyOutput const* sceShaccCgGenerateDependencies(
	const SceShaccCgCompileOptions *options,
	const SceShaccCgCallbackList *callbacks,
	ScePVoid userData,
	const SceChar8 *targetName,
	SceInt32 emitPhonies);

/**	@brief	Releases all allocations associated with the dependency output.

	@param[in] output
		The result from a call to sceShaccCgGenerateDependencies, to be destroyed.

	@ingroup shacccg
*/
SceVoid sceShaccCgDestroyDependencyOutput(
	SceShaccCgDependencyOutput const *output);

/**	@brief	Sets memory allocation callbacks

	Sets memory allocation callbacks for SceShaccCg library

	@param[in] memAlloc
		Function used for memory allocation.

	@param[in] memFree
		Function used to free memory.

	@ingroup shacccg
*/
SceInt32 sceShaccCgSetMemAllocator(
	SceShaccCgMemAllocator memAlloc,
	SceShaccCgMemFree memFree);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif /* _DOLCESDK_PSP2_SHACCCG_H_ */
