#ifndef _DOLCESDK_PSP2_SHACCCG_TYPES_H_
#define _DOLCESDK_PSP2_SHACCCG_TYPES_H_

#include <stddef.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus


///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

typedef struct SceShaccCgCompileOptions SceShaccCgCompileOptions;
typedef struct SceShaccCgSourceFile SceShaccCgSourceFile;
typedef struct SceShaccCgSourceLocation SceShaccCgSourceLocation;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/**	@brief	A callback used when the compiler needs to open a file.

	The includedFrom location will either be 0, if a primary file is being
	opened, or it will point to the location of the #include directive.
	If the file could not be opened, 0 is returned and errorString will be
	updated to point to a representative message, explaining why the file
	could not be opened.
	On success, a non-zero pointer is returned. The caller takes ownership,
	calling SceShaccCgCallbackReleaseFile when the returned SceShaccCgSourceFile
	is no longer required.

	@param[in] fileName
		The absolute path of the file to be opened.

	@param[in] includedFrom
		The include location. Set to 0 for a primary file.

	@param[in] compileOptions
		The original options pointer used to invoke this compile.

	@param[in] userData
		Opaque pointer to user data.

	@param[out] errorString
		If 0 is returned and this pointer is non-zero, this output param should
		be updated to contain a diagnostic message.

	@return
		A SceShaccCgSourceFile object to be destroyed later with
		SceShaccCgCallbackReleaseFile.

	@ingroup shacccg
*/
typedef SceShaccCgSourceFile* (*SceShaccCgCallbackOpenFile)(
	const char *fileName,
	const SceShaccCgSourceLocation *includedFrom,
	const SceShaccCgCompileOptions *compileOptions,
	void *userData,
	const char **errorString);

/**	@brief	A callback used when the compiler needs to release file data.

	This function is used to release memory that was previously allocated as
	part of a call to SceShaccCgCallbackOpenFile. This will be called once per
	"fileName" associated with that SceShaccCgSourceFile object when the
	resources for the compile session are released.

	@param[in] file
		The SceShaccCgSourceFile object to be destroyed.

	@param[in] compileOptions
		The original options pointer used to invoke this compile.

	@param[in] userData
		Opaque pointer to user data.

	@ingroup shacccg
*/
typedef void (*SceShaccCgCallbackReleaseFile)(
	const SceShaccCgSourceFile *file,
	const SceShaccCgCompileOptions *compileOptions,
	void *userData);

/**	@brief	A callback used to search for a named file.

	This function will search in all provided paths for the named file. If the
	file could not be located, 0 is returned and errorString will have been
	updated to a representative message, explaining why the file could not be
	located.
	On success, a non-zero string is returned. The caller takes ownership and
	will release the allocation via the SceShaccCgCallbackReleaseFileName
	callback.

	@param[in] fileName
		The name of the file to be located.

	@param[in] includedFrom
		The location of the include directive. Set to 0 for primary files.

	@param[in] searchPathCount
		The number of search paths provided via 'searchPaths'.

	@param[in] searchPaths
		The array of search paths. The size is provided via 'searchPathCount'.

	@param[in] compileOptions
		The original options pointer used to invoke this compile.

	@param[in] userData
		Opaque pointer to user data.

	@param[out] errorString
		If 0 is returned and if this pointer is non-zero, it should be updated
		to contain a diagnostic message.

	@return
		A relative or absolute path to the file or 0 if the file could not be
		located.

 	@ingroup shacccg
*/
typedef const char* (*SceShaccCgCallbackLocateFile)(
	const char *fileName,
	const SceShaccCgSourceLocation *includedFrom,
	uint32_t searchPathCount,
	const char *const*searchPaths,
	const SceShaccCgCompileOptions *compileOptions,
	void *userData,
	const char **errorString);

/**	@brief	A callback used to retrieve the absolute path name for a given file.

	Files are uniquely identified by absolute paths. If two include files lead
	to the same absolute path, the previously found file is used and no call
	to SceShaccCgCallbackOpenFile will be made. This function allows for a
	translation from a relative path scheme to an absolute path scheme.

	If there is no valid absolute path for the given file, 0 should be returned.
	If a non-zero string is returned, the caller takes ownership and will release
	the allocation via the SceShaccCgCallbackReleaseFileName callback.
	This string will be the name passed to SceShaccCgCallbackOpenFile.

	@param[in] fileName
		The (possibly relative) file path for an include file, as provided
		by SceShaccCgCallbackLocateFile.

	@param[in] includedFrom
		The location of the include directive.

	@param[in] compileOptions
		The original options pointer used to invoke this compile.

	@param[in] userData
		Opaque pointer to user data.

	@return
		The absolute file path or 0 if the file could not be located.

	@ingroup shacccg
*/
typedef const char* (*SceShaccCgCallbackAbsolutePath)(
	const char *fileName,
	const SceShaccCgSourceLocation *includedFrom,
	const SceShaccCgCompileOptions *compileOptions,
	void *userData);

/**	@brief	A callback for the compiler to release a file name.

	This function is used to release memory that was previously allocated as
	part of a call to SceShaccCgCallbackLocateFile or
	SceShaccCgCallbackAbsolutePath.

	@param[in] fileName
		The file name string to be destroyed.

	@param[in] compileOptions
		The original options pointer used to invoke this compile.

	@param[in] userData
		Opaque pointer to user data.

	@ingroup shacccg
*/
typedef void (*SceShaccCgCallbackReleaseFileName)(
	const char *fileName,
	const SceShaccCgCompileOptions *compileOptions,
	void *userData);

/**	@brief	Provides date information for the named file.

	If the date attributes could not be read, 0 is returned and the results
	will be considered invalid.
	On success, timeLastStatusChange and timeLastModified will have been
	updated and a non-zero value is returned.
	The time values are encoded as time_t.

	@param[in] file
		A file object returned from SceShaccCgCallbackOpenFile.

	@param[in] includedFrom
		The location of the include directive.

	@param[in] compileOptions
		The original options pointer used to invoke this compile.

	@param[in] userData
		Opaque pointer to user data.

	@param[out] timeLastStatusChange
		A pointer to the time of last status change (i.e. creationTime).

	@param[out] timeLastModified
		A pointer to the time of last modification.

	@return
		Non-zero for success, 0 on failure.

	@ingroup shacccg
*/
typedef int32_t (*SceShaccCgCallbackFileDate)(
	const SceShaccCgSourceFile *file,
	const SceShaccCgSourceLocation *includedFrom,
	const SceShaccCgCompileOptions *compileOptions,
	void *userData,
	int64_t *timeLastStatusChange,					///< using time_t
	int64_t *timeLastModified);						///< using time_t

/**	@brief	A callback used when the compiler needs to allocate memory.

	This function is used to allocate memory. Memory must be 8 bytes aligned.

	@param[in] memSize
		Memory size.

	@ingroup shacccg
*/
typedef void *(*SceShaccCgAllocator)(
	size_t memSize);

/**	@brief	A callback used when the compiler needs to free memory.

	This function is used to free memory.

	@param[in] memPtr
		Pointer to a memory block previously allocated with SceShaccCgAllocator

	@ingroup shacccg
*/
typedef void (*SceShaccCgDeallocator)(
	void *memPtr);

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

/** @brief	Classifies the severity of a diagnostic

	@ingroup shacccg
*/
typedef enum SceShaccCgDiagnosticLevel {
	SCE_SHACCCG_DIAGNOSTIC_LEVEL_INFO,				///< Informational message
	SCE_SHACCCG_DIAGNOSTIC_LEVEL_WARNING,			///< Warning
	SCE_SHACCCG_DIAGNOSTIC_LEVEL_ERROR				///< Error
} SceShaccCgDiagnosticLevel;

/** @brief	Classifies the target profiles

	@ingroup shacccg
*/
typedef enum SceShaccCgTargetProfile {
	SCE_SHACCCG_PROFILE_VP,							///< vertex program
	SCE_SHACCCG_PROFILE_FP							///< fragment program
} SceShaccCgTargetProfile;

/** @brief	Classifies default callbacks

	@ingroup shacccg
*/
typedef enum SceShaccCgCallbackDefaults {
	SCE_SHACCCG_SYSTEM_FILES,						///< Default callback functions for using system files and paths.
	SCE_SHACCCG_TRIVIAL								///< Default callback functions for using only the "openFile" callback.
} SceShaccCgCallbackDefaults;

/** @brief	Classifies language

	@ingroup shacccg
*/
typedef enum SceShaccCgLocale {
	SCE_SHACCCG_ENGLISH,							///< English language setting.
	SCE_SHACCCG_JAPANESE							///< Japanese language setting.
} SceShaccCgLocale;


///////////////////////////////////////////////////////////////////////////////
// Structs
///////////////////////////////////////////////////////////////////////////////

/**	@brief	Describes a source file

	@note	If the source file is referenced only through a #line directive,
			the compiler will generate a SceShaccCgSourceFile object with a
			NULL 'text' field and a 'size' field of 0.
	@ingroup shacccg
*/
typedef struct SceShaccCgSourceFile {
	const char *fileName;							///< The relative or absolute name of the file.
	const char *text;								///< The contents of the source file.
	uint32_t size;									///< The size of the 'text' array in bytes.
} SceShaccCgSourceFile;


/**	@brief	Describes a location in the source code.

	@ingroup shacccg
*/
typedef struct SceShaccCgSourceLocation {
	const SceShaccCgSourceFile *file;				///< The file containing the location.
	uint32_t lineNumber;							///< The line number of the location.
	uint32_t columnNumber;							///< The column number of the location.
} SceShaccCgSourceLocation;

/** @brief	Describes the input data for a compilation job.

	@ingroup shacccg
*/
typedef struct SceShaccCgCompileOptions {
	const char *mainSourceFile;						///< The main Cg source file to compile.
	SceShaccCgTargetProfile targetProfile;			///< The target profile.
	const char *entryFunctionName;					///< The name of the entry function. Usually "main".
	uint32_t searchPathCount;						///< The number of search paths for include files.
	const char* const *searchPaths;					///< The search paths for include files.
	uint32_t macroDefinitionCount;					///< The number of macro definitions provided.
	const char* const *macroDefinitions;			///< The macro definitions in the form: MACRONAME or MACRONAME=VALUE
	uint32_t includeFileCount;						///< The number of files to force include.
	const char* const *includeFiles;				///< The files to include before the main source file.
	uint32_t suppressedWarningsCount;				///< The number of warnings to suppressed.
	const uint32_t *suppressedWarnings;				///< The id numbers of the warnings to be suppressed.

	SceShaccCgLocale locale;						///< The language to use in diagnostics.

	int32_t useFx;									///< Equivalent to -fx if non-zero, -nofx otherwise.
	int32_t noStdlib;								///< Equivalent to -nostdlib if non-zero.

	int32_t optimizationLevel;						///< Equivalent to -O?. Valid range is 0-4.
	int32_t useFastmath;							///< Equivalent to -fastmath if non-zero.
	int32_t useFastprecision;						///< Equivalent to -fastprecision if non-zero.
	int32_t useFastint;								///< Equivalent to -fastint if non-zero.
	int32_t positionInvariant;						///< Equivalent to -invpos if non-zero.

	int32_t warningsAsErrors;						///< Equivalent to -Werror if non-zero.
	int32_t performanceWarnings;					///< Equivalent to -Wperf if non-zero.
	int32_t warningLevel;							///< Equivalent to -W?. Valid range is 0-4.
	int32_t pedantic;								///< Equivalent to -pedantic if non-zero.
	int32_t pedanticError;							///< Equivalent to -pedantic-error if non-zero.
	int32_t xmlCache;								///< Equivalent to -xmlcache if non-zero.
	int32_t stripSymbols;							///< When set to non zero compilation will produce a stripped gxp file
} SceCgcCompileOptions;

/**	@brief	Lists the user defined callbacks for compiler operations.

	The SceShaccCgCallbackList structure is used in each of
	sceShaccCgCompileProgram, SceShaccCgPreprocessProgram and
	sceShaccCgGenerateDependencies in the same fashion.
	In order to initialize instances of this structure, please always use
	sceShaccCgInitializeCallbackList.

	For details regarding the individual callbacks, please refer to their
	respective documentations.

	@ingroup shacccg
*/
typedef struct SceShaccCgCallbackList {
	SceShaccCgCallbackOpenFile openFile;				///< The callback used to open a file.
	SceShaccCgCallbackReleaseFile releaseFile;			///< The callback used to release an opened file (optional).
	SceShaccCgCallbackLocateFile locateFile;			///< The callback used to indicate a file exists (optional).
	SceShaccCgCallbackAbsolutePath absolutePath;		///< The callback used to indicate the absolute path of a file (optional).
	SceShaccCgCallbackReleaseFileName releaseFileName;	///< The callback used to release an absolute path string (optional).
	SceShaccCgCallbackFileDate fileDate;				///< The callback used to indicate file modification date (optional).
} SceShaccCgCallbackList;

/**	@brief	Describes a single compiler diagnostic.

	@ingroup shacccg
*/
typedef struct SceShaccCgDiagnosticMessage {
	SceShaccCgDiagnosticLevel level;				///< The severity of the diagnostic.
	uint32_t code;									///< A unique code for each kind of diagnostic.
	const SceShaccCgSourceLocation *location;		///< The location for which the diagnostic is reported (optional).
	const char *message;							///< The diagnostic message.
} SceShaccCgDiagnosticMessage;


///////////////////////////////////////////////////////////////////////////////
// Functions for initializing common types
///////////////////////////////////////////////////////////////////////////////

/**	@brief	Initializes the compile options with the default values.

	The following fields must be initialized by the user:
	- mainSourceFile
	- targetProfile

	All other fields may be left in the state set by this function.

	@param[out] options
		The option structure that should be initialized.

	@ingroup shacccg
*/
void sceShaccCgInitializeCompileOptions(
	SceShaccCgCompileOptions *options);

/**	@brief	Initializes the callback list with the default values.

	There are two kinds of defaults available:
	- SCE_SHACCCG_SYSTEM_FILES uses the native file system of the operating
		system in the same manner as the command-line version of psp2cgc.
		This is the default behavior if no callback structure is provided for
		a compilation/pre-processing/dependency job.
	- SCE_SHACCCG_TRIVIAL provides placeholder implementations of all callbacks
		but 'openFile'. The latter must always be provided by the user.

	In the trivial case, the following defaults will be used:
	- releaseFile:		Does nothing.
	- locateFile:		Returns the same path it was called with.
	- absolutePath:		Returns the same path it was called with.
	- releaseFileName:	Does nothing.
	- fileDate:			Returns the current time.

	@param[in] callbacks
		The callbacks structure to be initialized.

	@param[in] defaults
		Indicates which set of default callbacks to initialize from.

	@ingroup shacccg
*/
void sceShaccCgInitializeCallbackList(
	SceShaccCgCallbackList *callbacks,
	SceShaccCgCallbackDefaults defaults);

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif /* _DOLCESDK_PSP2_SHACCCG_TYPES_H_ */
