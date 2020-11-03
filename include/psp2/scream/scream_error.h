#ifndef _DOLCESDK_PSP2_SCREAM_SCREAM_ERROR_H_
#define _DOLCESDK_PSP2_SCREAM_SCREAM_ERROR_H_

 /*
SCE Error Code Info
*/
/**
@defgroup errorCodeMacros Error Code Macros
@brief
Macros used to create Scream error codes.
@{*/
#define SCE_ERROR_ERROR_FLAG               0x80000000                                      ///< SDK base error code identifier.
#define SCE_ERROR_MAKE_ERROR(_fac,_sts)   (SCE_ERROR_ERROR_FLAG | ((_fac)<<16) | (_sts))   ///< Macro to create an error code.
#define SCE_ERROR_FACILITY_SCREAM          0x100                                           ///< Scream facility code identifier.
/**@}*/

/*
Helper macros to create a Scream facility codes
*/
/**
@ingroup errorCodeMacros
*/
#define SCE_SCREAM_MAKE_ERROR(_rc) SCE_ERROR_MAKE_ERROR(SCE_ERROR_FACILITY_SCREAM,(_rc))   ///< Helper macro to create Scream-specific error code values. The #SCE_SCREAM_MAKE_ERROR macro bit-combines #SCE_ERROR_ERROR_FLAG and a shifted #SCE_ERROR_FACILITY_SCREAM with a Scream-specific error value. For example, #SCE_SCREAM_MAKE_ERROR(0x101) evaluates to <c>0x81000101</c>.

// Error codes used with sceScreamGetLastLoadError.
/**
@defgroup screamErrorCodes Error Codes
@brief
Error codes used with the sceScreamGetLastLoadError() function.
@{*/
#define SCE_SCREAM_SND_LOAD_ERROR_COULDNT_OPEN_FILE         SCE_SCREAM_MAKE_ERROR(0x000)        ///< A file could not be opened. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERROR_READING_FILE              SCE_SCREAM_MAKE_ERROR(0x001)        ///< A problem occurred reading a file. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERROR_MEMORY                    SCE_SCREAM_MAKE_ERROR(0x002)        ///< Memory could not be allocated to load a file. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERROR_ALIGNMENT                 SCE_SCREAM_MAKE_ERROR(0x003)        ///< A Bank is not aligned on a 16-byte boundary. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERROR_INVALID_FORMAT            SCE_SCREAM_MAKE_ERROR(0x004)        ///< A file has an invalid format. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERROR_ALREADY_LOADED            SCE_SCREAM_MAKE_ERROR(0x005)        ///< A Bank at the specified memory address is already loaded. Returned by the sceScreamGetLastLoadError() function.

#define SCE_SCREAM_SS_ERROR_SYSTEM_ALREADY_STARTED          SCE_SCREAM_MAKE_ERROR(0x101)        ///< Scream is already initialized, or that initialization failed. Returned by the sceScreamStartSoundSystemEx2() function.
#define SCE_SCREAM_SS_ERROR_SYSTEM_NOT_STARTED              SCE_SCREAM_MAKE_ERROR(0x102)        ///< Scream is not currently running. Returned by the sceScreamStopSoundSystem() function.
#define SCE_SCREAM_SS_ERROR_SYNTH_INIT_FAILED               SCE_SCREAM_MAKE_ERROR(0x103)        ///< Underlying synthesizer failed to initialize. Returned by the sceScreamStartSoundSystemEx2() function.
#define SCE_SCREAM_SS_ERROR_INVALID_PARAMETER               SCE_SCREAM_MAKE_ERROR(0x104)        ///< Invalid parameter detected. Returned by numerous functions.
#define SCE_SCREAM_SS_ERROR_UNSUPPORTED                     SCE_SCREAM_MAKE_ERROR(0x105)        ///< Indicates that a requested operation is not supported.
/**@}*/

// Error codes used with sceScreamInitStreaming.
/**
@defgroup sndStreamInitializationAndShutdownErrors Initialization and Shutdown Errors
@{*/
#define SCE_SCREAM_SND_STREAM_INIT_ERROR_UNKNOWN            SCE_SCREAM_MAKE_ERROR(0x200)        ///< Unknown system error occurred while attempting to initialize Sndstream. Returned by sceScreamInitStreaming().
#define SCE_SCREAM_SND_STREAM_INIT_ERROR_MEMORY             SCE_SCREAM_MAKE_ERROR(0x201)        ///< sceScreamInitStreaming() was unable to allocate memory.
#define SCE_SCREAM_SND_STREAM_INIT_ERROR_THREADS            SCE_SCREAM_MAKE_ERROR(0x202)        ///< sceScreamInitStreaming() was unable to create a thread.
#define SCE_SCREAM_SND_STREAM_INIT_ERROR_ALREADY_INITED     SCE_SCREAM_MAKE_ERROR(0x203)        ///< Sndstream has already been initialized. Returned by sceScreamInitStreaming().
#define SCE_SCREAM_SND_STREAM_INIT_ERROR_INVALID_ARGS       SCE_SCREAM_MAKE_ERROR(0x204)        ///< Some specified parameter(s) used with sceScreamInitStreaming() or sceScreamFillDefaultPlatformInitArgs() are out of range.
/**@}*/

// General error codes.
/**
@defgroup sndStreamGeneralErrors General Errors
@{*/
#define SCE_SCREAM_SND_STREAM_ERROR_UNKNOWN                 SCE_SCREAM_MAKE_ERROR(0x301)        ///< An unknown error occurred.
#define SCE_SCREAM_SND_STREAM_ERROR_NOT_INITED              SCE_SCREAM_MAKE_ERROR(0x302)        ///< Sndstream has not been initialized.
#define SCE_SCREAM_SND_STREAM_ERROR_NOT_FOUND               SCE_SCREAM_MAKE_ERROR(0x303)        ///< A specified file was not found.
#define SCE_SCREAM_SND_STREAM_ERROR_CORRUPT                 SCE_SCREAM_MAKE_ERROR(0x304)        ///< A specified file was found but contained invalid data.
#define SCE_SCREAM_SND_STREAM_ERROR_UNSUPPORTED             SCE_SCREAM_MAKE_ERROR(0x305)        ///< A specified file type is not supported.
#define SCE_SCREAM_SND_STREAM_ERROR_UNREADABLE              SCE_SCREAM_MAKE_ERROR(0x306)        ///< Sndstream failed to seek in or read from file.
#define SCE_SCREAM_SND_STREAM_ERROR_INTERNAL                SCE_SCREAM_MAKE_ERROR(0x307)        ///< An unexpected internal error.
#define SCE_SCREAM_SND_STREAM_ERROR_UNRECOGNIZED            SCE_SCREAM_MAKE_ERROR(0x308)        ///< The specified reference is not recognized.
#define SCE_SCREAM_SND_STREAM_ERROR_OUT_OF_RANGE            SCE_SCREAM_MAKE_ERROR(0x309)        ///< A parameter index is out of range.
#define SCE_SCREAM_SND_STREAM_ERROR_NULL_POINTER            SCE_SCREAM_MAKE_ERROR(0x30A)        ///< A specified address was <C>NULL</C>.
#define SCE_SCREAM_SND_STREAM_ERROR_VERSION_MISMATCH        SCE_SCREAM_MAKE_ERROR(0x30B)        ///< The version of a specified data structure is not supported.
#define SCE_SCREAM_SND_STREAM_ERROR_ENDIANNESS              SCE_SCREAM_MAKE_ERROR(0x30C)        ///< Data with incorrect endianness was used.
#define SCE_SCREAM_SND_STREAM_ERROR_VOICE_UNAVAILABLE       SCE_SCREAM_MAKE_ERROR(0x30D)        ///< A voice could not be allocated for this data.
#define SCE_SCREAM_SND_STREAM_ERROR_ALLOCATION              SCE_SCREAM_MAKE_ERROR(0x30E)        ///< A resource could not be allocated.
#define SCE_SCREAM_SND_STREAM_ERROR_NOT_ACTIVE              SCE_SCREAM_MAKE_ERROR(0x30F)        ///< The handle or other object is no longer active.
#define SCE_SCREAM_SND_STREAM_ERROR_NOT_BIG_ENOUGH          SCE_SCREAM_MAKE_ERROR(0x310)        ///< A buffer or other resource is not big enough.
/**@}*/

// Error codes used with sceScreamCloseStreaming.
/**
@defgroup sndStreamInitializationAndShutdownErrors Initialization and Shutdown Errors
@{*/
#define SCE_SCREAM_SND_STREAM_CLOSE_ERROR_NOT_INITED        SCE_SCREAM_MAKE_ERROR(0x400)        ///< Returned by sceScreamCloseStreaming() to indicate that Sndstream has not been initialized.
/**@}*/

/**
@defgroup sndStreamFileIOErrors File I/O Errors
@{*/
#define SCE_SCREAM_SND_STREAM_FILE_ERROR_PASS               SCE_SCREAM_MAKE_ERROR(0x600)        ///< The file I/O system passed on (omitted) a read request. Returned by SceScreamSndStreamFileReadFunction() or SceScreamSndStreamFileAsyncReadFunction().
#define SCE_SCREAM_SND_STREAM_FILE_ERROR_UNKNOWN            SCE_SCREAM_MAKE_ERROR(0x601)        ///< An error of unknown origin occurred. Returned by any of the custom file I/O prototypes.
#define SCE_SCREAM_SND_STREAM_FILE_ERROR_OPEN               SCE_SCREAM_MAKE_ERROR(0x602)        ///< A file open error occurred. Returned by SceScreamSndStreamFileOpenFunction(), SceScreamSndStreamFileAsyncOpenFunction(), SceScreamSndStreamFileAsyncIsOpenCompleteFunction(), or SceScreamSndStreamFileAsyncOpenBitstreamFunction().
#define SCE_SCREAM_SND_STREAM_FILE_ERROR_SEEK               SCE_SCREAM_MAKE_ERROR(0x603)        ///< A file seek error occurred. Returned by SceScreamSndStreamFileSeekFunction().
#define SCE_SCREAM_SND_STREAM_FILE_ERROR_READ               SCE_SCREAM_MAKE_ERROR(0x604)        ///< A file read error occurred. Returned by SceScreamSndStreamFileReadFunction(), SceScreamSndStreamFileAsyncReadFunction(), or SceScreamSndStreamFileAsyncIsReadCompleteFunction().
#define SCE_SCREAM_SND_STREAM_FILE_ERROR_CLOSE              SCE_SCREAM_MAKE_ERROR(0x605)        ///< A file close error occurred. Returned by SceScreamSndStreamFileCloseFunction(), SceScreamSndStreamFileAsyncCloseBitstreamFunction(), or SceScreamSndStreamFileAsyncCloseFunction().
/**@}*/

// Legacy definitions for use with old code -- the new "LOAD_ERROR" definitions are preferred
#ifndef DOXYGEN_IGNORE
#define SCE_SCREAM_SND_LOAD_ERR_COULDNT_OPEN_FILE           SCE_SCREAM_MAKE_ERROR(0x000)        // A file could not be opened. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERR_READING_FILE                SCE_SCREAM_MAKE_ERROR(0x001)        // A problem occurred reading a file. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERR_MEMORY                      SCE_SCREAM_MAKE_ERROR(0x002)        // Memory could not be allocated to load a file. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERR_ALIGNMENT                   SCE_SCREAM_MAKE_ERROR(0x003)        // A Bank is not aligned on a 16-byte boundary. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERR_INVALID_FORMAT              SCE_SCREAM_MAKE_ERROR(0x004)        // A file has an invalid format. Returned by the sceScreamGetLastLoadError() function.
#define SCE_SCREAM_SND_LOAD_ERR_ALREADY_LOADED              SCE_SCREAM_MAKE_ERROR(0x005)        // A Bank at the specified memory address is already loaded. Returned by the sceScreamGetLastLoadError() function.
#endif // DOXYGEN_IGNORE

#define SCE_SCREAM_EFFECT_ERROR_NOT_ENABLE          SCE_SCREAM_MAKE_ERROR(0x701) // temporary

#endif //_DOLCESDK_PSP2_SCREAM_SCREAM_ERROR_H_
