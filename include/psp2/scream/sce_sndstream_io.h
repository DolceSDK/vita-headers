#ifndef _DOLCESDK_PSP2_SCREAM_SCE_SNDSTREAM_IO_H_
#define _DOLCESDK_PSP2_SCREAM_SCE_SNDSTREAM_IO_H_

#include <psp2/scream/sce_scream.h>

// ERROR_OK is zero -- all other error codes defined in scream_error.h
/// @ingroup sndStreamFileIOErrors
#define SCE_SCREAM_SND_STREAM_FILE_ERROR_OK        0   ///< No error occurred. Returned by many of the custom file I/O prototypes.

/**
@defgroup sndStreamFileIOConstants File I/O Constants
@brief File I/O constants define optional values used by Sndstream when calling the file I/O custom functions.
@{*/
#define SCE_SCREAM_SND_STREAM_FILE_INVALID_HANDLE ((void *)-1) ///< Indicates an invalid file handle. See the SceScreamSndStreamFileOpenFunction() or SceScreamSndStreamFileAsyncOpenFunction() prototypes.


#define SCE_SCREAM_SND_STREAM_FILE_SEEK_SET 0           ///< A seek operation begins from the beginning of the file. See the SceScreamSndStreamFileSeekFunction() prototype <c><i>whence</i></c> parameter.
#define SCE_SCREAM_SND_STREAM_FILE_SEEK_CUR 1           ///< A seek operation begins from the current offset in the file. See the SceScreamSndStreamFileSeekFunction() prototype <c><i>whence</i></c> parameter.
#define SCE_SCREAM_SND_STREAM_FILE_SEEK_END 2           ///< A seek operation begins from the end of the file. See the SceScreamSndStreamFileSeekFunction() prototype <c><i>whence</i></c> parameter.

#define SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_START       (-2) ///< The file being opened will start a new stream. See the SceScreamSndStreamFileOpenFunction() and SceScreamSndStreamFileAsyncOpenFunction() prototypes <c><i>priority</i></c> parameter.
#define SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_APPEND      (-3) ///< The file being opened will be appended onto an existing stream. See the SceScreamSndStreamFileOpenFunction() and SceScreamSndStreamFileAsyncOpenFunction() prototypes <c><i>priority</i></c> parameter.
#define SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_PARSE       (-4) ///< The purpose of the file read is for parsing header information. See the SceScreamSndStreamFileReadFunction() and SceScreamSndStreamFileAsyncReadFunction() prototypes <c><i>priority</i></c> parameter.
#define SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_DATA_FILL   (-5) ///< The purpose of the file read is for initial filling of the playback buffer. See the SceScreamSndStreamFileReadFunction() and SceScreamSndStreamFileAsyncReadFunction() prototypes <c><i>priority</i></c> parameter.
#define SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_DATA_APPEND (-6) ///< The purpose of the file read is to add data to the playback buffer. See the SceScreamSndStreamFileReadFunction() and SceScreamSndStreamFileAsyncReadFunction() prototypes <c><i>priority</i></c> parameter.
#define SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_MIDI        (-7) ///< The file being opened is a MIDI file associated with a stream file. See the SceScreamSndStreamFileOpenFunction() or SceScreamSndStreamFileAsyncOpenFunction() prototypes <c><i>priority</i></c> parameter.
#define SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_MIDI        (-8) ///< The purpose of the file read is to load into memory a MIDI file associated with a stream file. See the SceScreamSndStreamFileReadFunction() and SceScreamSndStreamFileAsyncReadFunction() prototypes <c><i>priority</i></c> parameter.

#define SCE_SCREAM_SND_STREAM_FILE_MAX_BUFFER_IDS            (16) ///< The maximum number of buffer IDs per Stream available to the custom asynchronous file I/O functions. See the SceScreamSndStreamPlatformInit <c><i>subBufferCount</i></c> member.
#define SCE_SCREAM_SND_STREAM_FILE_DEFAULT_BUFFER_IDS        (8)  ///< The default number of buffer IDs per Stream available to the custom asynchronous file I/O functions. See the SceScreamSndStreamPlatformInit <c><i>subBufferCount</i></c> member.

#define SCE_SCREAM_SND_STREAM_FILE_OPEN_PENDING              (0)  ///< A file open operation is pending. See SceScreamSndStreamFileAsyncOpenFunction() or SceScreamSndStreamFileAsyncIsOpenCompleteFunction().
#define SCE_SCREAM_SND_STREAM_FILE_OPEN_COMPLETE             (1)  ///< A file open operation is complete. See SceScreamSndStreamFileAsyncOpenFunction() or SceScreamSndStreamFileAsyncIsOpenCompleteFunction().
/**@}*/

/**
@ingroup typeDefinitions
@brief
Data type for an opaque pointer or integer used to reference a Stream file.

This type is used to reference a Stream file in the custom file I/O function prototypes.

@see
SceScreamSndStreamUserFileAsyncHandle, SceScreamSndStreamFileOpenFunction(), SceScreamSndStreamFileInfoCBFunction(), SceScreamSndStreamFileSeekFunction(), SceScreamSndStreamFileReadFunction(), SceScreamSndStreamFileCloseFunction()
*/
typedef void *SceScreamSndStreamUserFileHandle;

/**
@ingroup typeDefinitions
@brief
Data type for an opaque pointer or integer used to reference an asynchronously opened Stream file.

This type is used to reference an asynchronously opened Stream file in the custom file I/O function prototypes.

@see
SceScreamSndStreamUserFileHandle, SceScreamSndStreamFileAsyncOpenFunction(), SceScreamSndStreamFileAsyncIsOpenCompleteFunction(), SceScreamSndStreamFileAsyncReadFunction(), SceScreamSndStreamFileAsyncIsReadCompleteFunction(), SceScreamSndStreamFileAsyncCloseFunction(), SceScreamSndStreamFileAsyncOpenBitstreamFunction(), SceScreamSndStreamFileAsyncCloseBitstreamFunction()
*/
typedef void *SceScreamSndStreamUserFileAsyncHandle;

/**
@ingroup typeDefinitions
@brief
Data type for an opaque pointer or integer used to reference a user context value.

This type is used to reference a user context value.
It is widely used to store custom user data. This data type is used in a wide variety of structures and functions.
In some cases, the #SceScreamSndStreamUserContext value is returned later in another function.

For example, the <c><i>userContext</i></c> member of the #SceScreamSndFileParams structure takes a #SceScreamSndStreamUserContext value.
In turn, #SceScreamSndFileParams is used as a parameter to the sceScreamStartStream() function to start a Stream.
When the sceScreamGetStreamFileLengthInSeconds() function called on this Stream returns,
its <c><i>outContext</i></c> parameter contains the #SceScreamSndStreamUserContext value from the <c><i>userContext</i></c> member of the #SceScreamSndFileParams structure passed to sceScreamStartStream().

In other cases, the #SceScreamSndStreamUserContext value is used in a structure and later passed to related functions. For example, the #SceScreamSndFileParams structure
also takes a #SceScreamSndFileInterface structure that contains custom I/O function prototypes, such as SceScreamSndStreamFileAsyncOpenFunction().
SceScreamSndStreamFileAsyncOpenFunction() then takes this #SceScreamSndStreamUserContext value in its <c><i>userContext</i></c> parameter.

@see
SceScreamSndFileParams, SceScreamSndStreamParseParams, sceScreamGetStreamFileLengthInSeconds(), sceScreamGetStreamFileLocationInSeconds(), sceScreamGetStreamFileLoopingCount(), sceScreamGetStreamFileSecondsRemaining()
*/
typedef void *SceScreamSndStreamUserContext;

/**
@defgroup sndStreamFunctionPrototypes Function Prototypes
@brief
Prototypes for custom file I/O functions.
@{*/
/**
@brief
Prototype for creating a custom file open function.

SceScreamSndStreamFileOpenFunction() is a prototype for creating a custom file open function.
The custom function should synchronously open a file and return a valid file handle stored
at the address specified by <c><i>pReturnedHandle</i></c>. The file handle can then be used with
other file I/O functions.

@param
filePath (Input)
Pointer to a zero terminated string containing the fully qualified file path to open.

@param
pReturnedHandle (Output)
Pointer to a #SceScreamSndStreamUserFileHandle variable in which to store the file handle. Used to reference the opened file.

@param
millisecondDeadline (Input)
Remaining time in milliseconds until the valid data in the playback buffer is played out. May be zero if no data is currently playing.

@param
priority (Input)
One of the following defined priority values.
<ul>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_START: The file being opened is to initiate a new playing stream, but playback has not yet begun.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_APPEND: The file being opened is to be appended to a currently playing stream.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_MIDI: The file being opened is a MIDI file associated with a stream file.</li>
</ul>

@param
userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure, user defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@return
If the file open operation is successful, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OK.
If an error occurred, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OPEN.

@note
If an error occurred, the value of #SCE_SCREAM_SND_STREAM_FILE_INVALID_HANDLE should be stored in the <c><i>pReturnedHandle</i></c> parameter.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileInfoCBFunction(), SceScreamSndStreamFileSeekFunction(), SceScreamSndStreamFileReadFunction(), SceScreamSndStreamFileCloseFunction(), SceScreamSndStreamFileAsyncOpenFunction()
*/
typedef int32_t SceScreamSndStreamFileOpenFunction( const char* filePath, SceScreamSndStreamUserFileHandle* pReturnedHandle,
                                           int32_t millisecondDeadline, int8_t priority, SceScreamSndStreamUserContext userContext);
/**@}*/

/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating an optional custom file information callback function

SceScreamSndStreamFileInfoCBFunction() is a prototype for creating an optional custom file information callback function.
If specified in the SceScreamSndFileInterface <c><i>SceScreamSndStreamFileInfoCBFunction</i></c> member, the custom file information callback function is called once per Stream file, immediately after it is opened.

@param
fileHandle (Output)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileOpenFunction() function's <c><i>pReturnedHandle</i></c> parameter.

@param
dataRate (Output)
A <c>uint32_t</c> variable in which to store the data rate of the file, in bits-per-second. This value is zero for VBR-encoded MP3 streams.

@param
loopCount (Output)
A <c>uint32_t</c> variable in which to store looping information, as set in the SceScreamSndFileParams <c><i>loopCount</i></c> member.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileOpenFunction(), SceScreamSndStreamFileSeekFunction(), SceScreamSndStreamFileReadFunction(), SceScreamSndStreamFileCloseFunction()

*/
typedef void SceScreamSndStreamFileInfoCBFunction(SceScreamSndStreamUserFileHandle fileHandle, uint32_t dataRate, int32_t loopCount);

/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom file seek function.

SceScreamSndStreamFileSeekFunction() is a prototype for creating a custom file seek function.
The custom function should synchronously seek in an open a file, and
almost immediately return either the new current location in the file or, if an error occurred, a value less than zero.

@param
fileHandle (Input)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileOpenFunction() function's <c><i>pReturnedHandle</i></c> parameter.

@param
offset (Input)
Count of bytes to seek over.

@param
whence (Input)
Starting point of the seek operation. Must be one of the following constants: #SCE_SCREAM_SND_STREAM_FILE_SEEK_SET, #SCE_SCREAM_SND_STREAM_FILE_SEEK_CUR, or #SCE_SCREAM_SND_STREAM_FILE_SEEK_END.

@param
userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure (user defined data) passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@return
If the file seek operation is successful, the custom function should return the current position,
in bytes from the beginning of the file. If an error occurred, the function should return
#SCE_SCREAM_SND_STREAM_FILE_ERROR_SEEK.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileOpenFunction(), SceScreamSndStreamFileInfoCBFunction(), SceScreamSndStreamFileReadFunction(), SceScreamSndStreamFileCloseFunction()
*/
typedef int64_t SceScreamSndStreamFileSeekFunction(SceScreamSndStreamUserFileHandle fileHandle, int64_t offset, uint32_t whence, SceScreamSndStreamUserContext userContext);


/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom file read function.

SceScreamSndStreamFileReadFunction() is a prototype for creating a custom file read function.
The custom function should synchronously read from an open file, and return the size of the data actually read into
the buffer referenced by the supplied pointer.

@param
fileHandle (Input)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileOpenFunction() function's <c><i>pReturnedHandle</i></c> parameter.

@param
pDestBuffer (Output)
Pointer to a buffer in which to receive the data.

@param
sizeToRead (Input)
Number of bytes to read from the file.

@param
pReturnedSizeRead (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the actual count of bytes read. May be <C>NULL</C>.

@param
millisecondDeadline (Input)
Remaining time in milliseconds until the valid data in the playback buffer is played out. May be zero if no data is currently playing.

@param
priority (Input)
One of the following defined constants values.
<ul>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_PARSE: The purpose of the file read is to parse the header information of the file. <b>Note:</b> The <c><i>millisecondDeadline</i></c> parameter is not valid when this priority is used, and defaults to zero.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_DATA_FILL: The purpose of the file read is to initially fill the playback buffer. <b>Note:</b> The <c><i>millisecondDeadline</i></c> parameter is not valid when this priority is used, and defaults to zero.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_DATA_APPEND: The purpose of the file read is to add data to the playback buffer.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_MIDI: The purpose of the file read is to load into memory a MIDI file associated with a stream file. <b>Note</b>: The <c><i>millisecondDeadline</i></c> parameter is not valid when this priority is used, and defaults to zero.</li>
</ul>

@param
userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure, user defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@return
If the file read operation is successful, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OK.
If an error occurred, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_READ.
If the file I/O system decided to pass on (that is, to omit) the read request, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_PASS. In this case,
Sndstream reiterates the read request in the next processing pass.
<b>Note:</b> This return code can only be used if the <c><i>priority</i></c> parameter is set to #SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_DATA_APPEND.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileOpenFunction(), SceScreamSndStreamFileInfoCBFunction(), SceScreamSndStreamFileSeekFunction(), SceScreamSndStreamFileCloseFunction()
*/
typedef int32_t SceScreamSndStreamFileReadFunction(SceScreamSndStreamUserFileHandle fileHandle, void* pDestBuffer, uint32_t sizeToRead, uint32_t* pReturnedSizeRead, int32_t millisecondDeadline, int8_t priority, SceScreamSndStreamUserContext userContext);


/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom file close function.

SceScreamSndStreamFileCloseFunction() is a prototype for creating a custom file close function.
The custom function should synchronously close a file, and return almost instantly.

@param
fileHandle (Input)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileOpenFunction() function's <c><i>pReturnedHandle</i></c> parameter.

@param
userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure, user defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@return
If the file close operation is successful, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OK.
If an error occurred, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_CLOSE.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileOpenFunction(), SceScreamSndStreamFileInfoCBFunction(), SceScreamSndStreamFileSeekFunction(), SceScreamSndStreamFileReadFunction()
*/
typedef int32_t SceScreamSndStreamFileCloseFunction(SceScreamSndStreamUserFileHandle fileHandle, SceScreamSndStreamUserContext userContext);

/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom function to open a file for subsequent asynchronous reading.

SceScreamSndStreamFileAsyncOpenFunction() is a prototype for creating a custom function to open a file for subsequent asynchronous reading.
The custom function itself should operate synchronously, opening a file for asynchronous I/O, and upon return storing a valid #SceScreamSndStreamUserFileAsyncHandle at the address specified by <c><i>pReturnedAsyncHandle</i></c>.
The #SceScreamSndStreamUserFileAsyncHandle is then used with other asynchronous file I/O functions.

@param filePath (Input)
Pointer to a zero terminated string containing the fully qualified file path to open.

@param pReturnedAsyncHandle (Output)
Pointer to a #SceScreamSndStreamUserFileAsyncHandle variable in which to store the asynchronous file handle. Used to reference the opened file (see &quot;Notes&quot; below).
The value stored by your custom function can either be a real handle or just a pointer to a structure being used to track files opened for asynchronous reading.
If an error occurred, your custom function should store #SCE_SCREAM_SND_STREAM_FILE_INVALID_HANDLE in the <c><i>pReturnedAsyncHandle</i></c> output variable.

@param millisecondDeadline (Input)
Remaining time in milliseconds until the valid data in the playback buffer is played out. May be zero if no data is currently playing.

@param priority (Input)
One of the following defined priority values.
<ul>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_START: The file being opened is to initiate a new playing stream, but playback has not yet begun.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_APPEND: The file being opened is to be appended to a currently playing stream.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_OPEN_MIDI: The file being opened is a MIDI file associated with a stream file.</li>
</ul>

@param userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure, user defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@param bitstreamId (Input)
Zero-based index of the target Bitstream.
Range: 0 to (<c><i>handleCount</i></c> &ndash; 1), where <c><i>handleCount</i></c> is a value set when initializing SndStream, as an argument to the sceScreamInitStreaming() function.
See &quot;Notes&quot; below.

@retval #SCE_SCREAM_SND_STREAM_FILE_OPEN_COMPLETE       The file open operation is complete
@retval #SCE_SCREAM_SND_STREAM_FILE_OPEN_PENDING        The file open operation is still pending
@retval #SCE_SCREAM_SND_STREAM_FILE_ERROR_OPEN          An error occurred

@note
For efficiency purposes when opening or closing files containing multiple Bitstreams, Sndstream selects one <c><i>bitstreamId</i></c> to serve as a reference.
For further details, see “Multi-Layer/Bitstream Files and the Asynchronous File I/O Functions” in the “Working with Multi-Layer Streams” chapter of the <i>Sndstream Library Overview</i> document.

@note
The #SceScreamSndStreamUserFileAsyncHandle returned in <c><i>pReturnedAsyncHandle</i></c> applies to all Bitstreams contained within the same file.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileAsyncIsOpenCompleteFunction(), SceScreamSndStreamFileAsyncReadFunction(), SceScreamSndStreamFileAsyncIsReadCompleteFunction(), SceScreamSndStreamFileAsyncCloseFunction(), SceScreamSndStreamFileAsyncOpenBitstreamFunction()
*/
typedef int32_t SceScreamSndStreamFileAsyncOpenFunction( const char* filePath, SceScreamSndStreamUserFileAsyncHandle *pReturnedAsyncHandle,
                                                int32_t millisecondDeadline, int8_t priority,
                                                SceScreamSndStreamUserContext userContext, int32_t bitstreamId );
/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom function for polling asynchronous file open completion.

SceScreamSndStreamFileAsyncIsOpenCompleteFunction() is a prototype for creating a custom function for polling asynchronous file open completion.
If the custom SceScreamSndStreamFileAsyncOpenFunction() function returns #SCE_SCREAM_SND_STREAM_FILE_OPEN_PENDING, Sndstream polls for completion of the asynchronous file open operation by calling this custom function.

@param
asyncFileHandle (Input)
Asynchronous file handle to query. Stored by the SceScreamSndStreamFileAsyncOpenFunction() function in an output variable specified by the <c><i>pReturnedAsyncHandle</i></c> argument.

@param userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndStreamParseParams structure, which is user supplied data passed
to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@param bitstreamId (Input)
Zero-based index of the target Bitstream. Range: 0 to (<c><i>handleCount</i></c> &ndash; 1), where <c><i>handleCount</i></c> is a value set when initializing Sndstream, as an
argument to the sceScreamInitStreaming() function. See &quot;Notes&quot; below.

@retval #SCE_SCREAM_SND_STREAM_FILE_OPEN_COMPLETE       The file open operation is complete
@retval #SCE_SCREAM_SND_STREAM_FILE_OPEN_PENDING        The file open operation is still pending
@retval #SCE_SCREAM_SND_STREAM_FILE_ERROR_OPEN          An error occurred

@note
For efficiency purposes when opening or closing files containing multiple Bitstreams, Sndstream selects one <c><i>bitstreamId</i></c> to serve as a reference.
For further details, see “Multi-Layer/Bitstream Files and the Asynchronous File I/O Functions” in the “Working with Multi-Layer Streams” chapter of the <i>Sndstream Library Overview</i>.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileAsyncOpenFunction(), SceScreamSndStreamFileAsyncReadFunction(), SceScreamSndStreamFileAsyncCloseFunction()
*/
typedef int32_t SceScreamSndStreamFileAsyncIsOpenCompleteFunction( SceScreamSndStreamUserFileAsyncHandle asyncFileHandle,
                                                                   SceScreamSndStreamUserContext userContext, int32_t bitstreamId );

/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom function to initialize Bitstream data for asynchronous reading.

SceScreamSndStreamFileAsyncOpenBitstreamFunction() is a prototype for creating a custom function to initialize Bitstream data for asynchronous reading.
The custom function itself should operate synchronously.

@param asyncFileHandle (Input)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileAsyncOpenFunction() function's <c><i>pReturnedAsyncHandle</i></c> parameter.

@param userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure, user defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@param bitstreamId (Input)
Zero-based index of the target Bitstream.
Range: 0 to (<c><i>handleCount</i></c> &ndash; 1), where <c><i>handleCount</i></c> is a value set when initializing Sndstream, as an argument to the sceScreamInitStreaming() function.
See &quot;Notes&quot; below.

@return
If the open operation is successful, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OK.
If an error occurred, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OPEN.

@note
For efficiency purposes when opening or closing files containing multiple Bitstreams, Sndstream selects one <c><i>bitstreamId</i></c> to serve as a reference.
Sndstream calls SceScreamSndStreamFileAsyncOpenBitstreamFunction() however, in respect of all Bitstreams in a file, in preparation for reading Bitstream data.
For further details, see “Multi-Layer/Bitstream Files and the Asynchronous File I/O Functions” in the “Working with Multi-Layer Streams” chapter of the <i>Sndstream Library Overview</i>.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileAsyncOpenFunction(), SceScreamSndStreamFileAsyncIsOpenCompleteFunction(), SceScreamSndStreamFileAsyncReadFunction(), SceScreamSndStreamFileAsyncIsReadCompleteFunction(), SceScreamSndStreamFileAsyncCloseBitstreamFunction(), SceScreamSndStreamFileAsyncCloseFunction()
*/
typedef int32_t SceScreamSndStreamFileAsyncOpenBitstreamFunction( SceScreamSndStreamUserFileAsyncHandle asyncFileHandle, SceScreamSndStreamUserContext userContext, int32_t bitstreamId );

/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom asynchronous file read function.

SceScreamSndStreamFileAsyncReadFunction() is a prototype for creating a custom asynchronous file read function.
The custom function should asynchronously read from an open file.

@param asyncFileHandle (Input)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileAsyncOpenFunction() function's <c><i>pReturnedAsyncHandle</i></c> parameter.

@param pDestBuffer (Output)
Pointer to a buffer in which to receive the data.

@param sizeToRead (Input)
Data size, in bytes, to read from the Stream file.
<b>Note:</b> While Sndstream should not attempt to read beyond the end of a Stream file, SCE recommends that a custom SceScreamSndStreamFileAsyncReadFunction() function validates the <c><i>sizeToRead</i></c> argument to ensure it remains within the bounds of available data. And if not, the function should return an error.

@param offset (Input)
Offset number of bytes into the Stream file at which point Sndstream begins reading data.

@param millisecondDeadline (Input)
Remaining time in milliseconds until the valid data in the playback buffer is played out.
May be zero if no data is currently playing.

@param priority (Input)
One of the following defined constants values.
<ul>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_PARSE: The purpose of the file read is to parse the header information of the file. <b>Note:</b> The <c><i>millisecondDeadline</i></c> parameter is not valid when this priority is used, and defaults to zero.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_DATA_FILL: The purpose of the file read is to initially fill the playback buffer. <b>Note:</b> The <c><i>millisecondDeadline</i></c> parameter is not valid when this priority is used, and defaults to zero.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_DATA_APPEND: The purpose of the file read is to add data to the playback buffer.</li>
<li>#SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_MIDI: The purpose of the file read is to load into memory a MIDI file associated with a stream file. <b>Note</b>: The <c><i>millisecondDeadline</i></c> parameter is not valid when this priority is used, and defaults to zero.</li>
</ul>

@param userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure, user defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@param bitstreamId (Input)
Zero-based index of the target Bitstream.
Range: 0 to (<c><i>handleCount</i></c> &ndash; 1), where <c><i>handleCount</i></c> is a value set when initializing Sndstream, as an argument to the sceScreamInitStreaming() function.
See &quot;Notes&quot; below.

@param bufferId (Input)
Identifies an asynchronous read request for the specified <c><i>bitstreamId</i></c>.
Sndstream can issue multiple read requests at the same time.
Each request is identified by a combination of the <c><i>bitstreamId</i></c> and <c><i>bufferId</i></c> values.
Range: 0 to (#SCE_SCREAM_SND_STREAM_FILE_MAX_BUFFER_IDS &ndash; 1). See &quot;Notes&quot; below.

@return
If the file read operation is successful, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OK.
If an error occurred, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_READ.
If the file I/O system decided to omit the read request, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_PASS. In this case,
Sndstream reiterates the read request in the next processing pass.
<b>Note:</b> This return code can only be used if the <c><i>priority</i></c> parameter is set to #SCE_SCREAM_SND_STREAM_FILE_PRIORITY_READ_DATA_APPEND.

@note
When reading files containing multiple Bitstreams, Sndstream uses multiple <c><i>bitstreamId</i></c> values; only one of which is the same as the <c><i>bitstreamId</i></c> used for file open and close operations.
For further details, see “Multi-Layer/Bitstream Files and the Asynchronous File I/O Functions” in the “Working with Multi-Layer Streams” chapter of the <i>Sndstream Library Overview</i>.

@note
An application might use the <c><i>bufferId</i></c> value to index into an array of structures that are tracking asynchronous read requests for each Stream.

@note
A read request is not issued for a specific <c><i>bufferId</i></c> unless a previous read operation for the same <c><i>bufferId</i></c> has completed.
Sndstream polls for completion of an asynchronous read request by calling the custom SceScreamSndStreamFileAsyncIsReadCompleteFunction() function with the corresponding <c><i>bufferId</i></c> value.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileAsyncOpenFunction(), SceScreamSndStreamFileAsyncIsOpenCompleteFunction(), SceScreamSndStreamFileAsyncIsReadCompleteFunction(), SceScreamSndStreamFileAsyncCloseFunction()
*/
typedef int32_t SceScreamSndStreamFileAsyncReadFunction( SceScreamSndStreamUserFileAsyncHandle asyncFileHandle, void* pDestBuffer,
                                                         uint32_t sizeToRead, int64_t offset,
                                                         int32_t millisecondDeadline, int8_t priority,
                                                         SceScreamSndStreamUserContext userContext, int32_t bitstreamId, int32_t bufferId );

/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom function for polling asynchronous file read completion.

SceScreamSndStreamFileAsyncIsReadCompleteFunction() is a prototype for creating a custom function for polling asynchronous file read completion.
Sndstream polls for completion of an asynchronous read request by calling this custom function.
A new read request is not issued for a given <c><i>bufferId</i></c> until any previous read operation for that <c><i>bufferId</i></c> is complete.

@param asyncFileHandle (Input)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileAsyncOpenFunction() function's <c><i>pReturnedAsyncHandle</i></c> parameter.

@param userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndStreamParseParams structure.
User defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or
sceScreamStartStreamFromTransition() functions.

@param bitstreamId (Input)
Zero-based index of the target Bitstream.
Range: 0 to (<c><i>handleCount</i></c> &ndash; 1), where <c><i>handleCount</i></c> is a value set when initializing Sndstream, as an argument to the sceScreamInitStreaming() function.
See &quot;Notes&quot; below.

@param bufferId (Input)
Identifies an asynchronous read request for the specified <c><i>bufferId</i></c>.
Range: 0 to (#SCE_SCREAM_SND_STREAM_FILE_MAX_BUFFER_IDS &ndash; 1).

@return
Returns a positive value if the file read operation is complete.
Returns 0 if the read operation is still pending.
Otherwise, returns a negative value if an error occurred.
For example, return #SCE_SCREAM_SND_STREAM_FILE_ERROR_READ if the full amount of requested data cannot be read.

@note
When reading files containing multiple Bitstreams, Sndstream uses multiple <c><i>bitstreamId</i></c> values; only one of which is the same as the <c><i>bitstreamId</i></c> used for file open and close operations.
For further details, see “Multi-Layer/Bitstream Files and the Asynchronous File I/O Functions” in the “Working with Multi-Layer Streams” chapter of the <i>Sndstream Library Overview</i>.

@note
A possible implementation of the asynchronous file I/O functions might create an array of structures for tracking asynchronous read requests.
The <c><i>bufferId</i></c> value could then serve is an index into such an array.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileAsyncOpenFunction(), SceScreamSndStreamFileAsyncIsOpenCompleteFunction(), SceScreamSndStreamFileAsyncReadFunction(), SceScreamSndStreamFileAsyncCloseFunction()
*/
typedef int32_t SceScreamSndStreamFileAsyncIsReadCompleteFunction( SceScreamSndStreamUserFileAsyncHandle asyncFileHandle, SceScreamSndStreamUserContext userContext, int32_t bitstreamId, int32_t bufferId );

/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom function to reset Bitstream data following asynchronous reading.

SceScreamSndStreamFileAsyncCloseBitstreamFunction() is a prototype for creating a custom function to reset Bitstream data following asynchronous reading.
The custom function should operate synchronously, and should not wait for any pending reads to complete.

@param asyncFileHandle (Input)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileAsyncOpenFunction() function's <c><i>pReturnedAsyncHandle</i></c> parameter.

@param userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure, user defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@param bitstreamId (Input)
Zero-based index of the target Bitstream.
Range: 0 to (<c><i>handleCount</i></c> &ndash; 1), where <c><i>handleCount</i></c> is a value set when initializing Sndstream, as an argument to the sceScreamInitStreaming() function.
See &quot;Notes&quot; below.

@return
If the close operation is successful, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OK.
If an error occurred, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_CLOSE.

@note
For efficiency purposes when opening or closing files containing multiple Bitstreams, Sndstream selects one <c><i>bitstreamId</i></c> to serve as a reference.
Sndstream calls SceScreamSndStreamFileAsyncCloseBitstreamFunction(), however, in respect of all Bitstreams in a file, to reset the Bitstreams' data after reading.
By the time Sndstream calls this function, any data read operations should have completed.
This mechanism allows the application to verify the status of pending data read operations.
For further details, see “Multi-Layer/Bitstream Files and the Asynchronous File I/O Functions” in the “Working with Multi-Layer Streams” chapter of the <i>Sndstream Library Overview</i> document.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileAsyncOpenFunction(), SceScreamSndStreamFileAsyncIsOpenCompleteFunction(), SceScreamSndStreamFileAsyncReadFunction(), SceScreamSndStreamFileAsyncIsReadCompleteFunction(), SceScreamSndStreamFileAsyncCloseFunction(), SceScreamSndStreamFileAsyncOpenBitstreamFunction()
*/
typedef int32_t SceScreamSndStreamFileAsyncCloseBitstreamFunction( SceScreamSndStreamUserFileAsyncHandle asyncFileHandle, SceScreamSndStreamUserContext userContext, int32_t bitstreamId );

/**
@ingroup sndStreamFunctionPrototypes
@brief
Prototype for creating a custom function to close a file that was opened for asynchronous reading.

SceScreamSndStreamFileAsyncCloseFunction() is a prototype for creating a custom function to close a file that was opened for asynchronous reading.
The custom function itself should operate synchronously, closing a file that was opened for asynchronous I/O.
This function should not wait for any pending reads to complete.

@param asyncFileHandle (Input)
Handle reference to the Stream file. Stored in an output variable specified by the SceScreamSndStreamFileAsyncOpenFunction() function's <c><i>pReturnedAsyncHandle</i></c> parameter.

@param userContext (Input)
The <c><i>userContext</i></c> member of the SceScreamSndFileParams data structure, user defined data passed to the sceScreamStartStream(), sceScreamQueueToStream(), or sceScreamStartStreamFromTransition() functions.

@param bitstreamId (Input)
Zero-based index of the target Bitstream.
Range: 0 to (<c><i>handleCount</i></c> &ndash; 1), where <c><i>handleCount</i></c> is a value set when initializing Sndstream, as an argument to the sceScreamInitStreaming() function.
See &quot;Notes&quot; below.

@return
If the file close operation is successful, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_OK.
If an error occurred, the custom function should return #SCE_SCREAM_SND_STREAM_FILE_ERROR_CLOSE.

@note
For efficiency purposes when opening or closing files containing multiple Bitstreams, Sndstream selects one <c><i>bitstreamId</i></c> to serve as a reference.
Sndstream uses the same <c><i>bitstreamId</i></c> to close a file as was to open it.
For further details, see “Multi-Layer/Bitstream Files and the Asynchronous File I/O Functions” in the “Working with Multi-Layer Streams” chapter of the <i>Sndstream Library Overview</i> document.

@see
SceScreamSndFileInterface, sceScreamSetDefaultFileInterface(), SceScreamSndStreamFileAsyncOpenFunction(), SceScreamSndStreamFileAsyncIsOpenCompleteFunction(), SceScreamSndStreamFileAsyncReadFunction(), SceScreamSndStreamFileAsyncIsReadCompleteFunction(), SceScreamSndStreamFileAsyncCloseBitstreamFunction(), SceScreamSndStreamFileAsyncOpenBitstreamFunction()
*/
typedef int32_t SceScreamSndStreamFileAsyncCloseFunction( SceScreamSndStreamUserFileAsyncHandle asyncFileHandle, SceScreamSndStreamUserContext userContext, int32_t bitstreamId );

/**
@ingroup sndStreamDataStructures
@brief
Stores the addresses of custom file I/O functions.

The SceScreamSndFileInterface structure stores the addresses of custom file I/O functions.
The structure stores addresses for both synchronous functions (used for parsing the file headers), and asynchronous functions (used for asynchronous reading of Stream data).

By default, SceScreamSndStream uses the FIOS file I/O functions on the PlayStation®Vita and PlayStation®PS4 platforms.
To override the defaults and use custom file I/O functions:
<ol>
<li>Ensure that your custom file I/O functions match the file I/O type definitions. See #SceScreamSndStreamFileOpenFunction, and so on.</li>
<li>Store their addresses as the corresponding members of the #SceScreamSndFileInterface data structure.</li>
<li>After initializing Sndstream, and before calling any other Sndstream functions, call sceScreamSetDefaultFileInterface() with the initialized #SceScreamSndFileInterface data structure as its argument.</li>
</ol>

For further details, see &quot;Using Custom File I/O Functions&quot; in the &quot;Working with System Globals&quot; chapter of the <i>Sndstream Library Overview</i>.

@note
You can use this structure as a value for the #SceScreamSndFileParams <c><i>fileInterface</i></c> member
and then use that #SceScreamSndFileParams in sceScreamStartStream() to start a stream for a file, allowing file I/O specification on a per file basis.

@see
sceScreamSetDefaultFileInterface(), SceScreamSndFileParams, SceScreamSndStreamFileOpenFunction(), SceScreamSndStreamFileInfoCBFunction(), SceScreamSndStreamFileSeekFunction(),
SceScreamSndStreamFileReadFunction(), SceScreamSndStreamFileCloseFunction()
*/
typedef struct
{
    // These are used for parsing the file headers.
    SceScreamSndStreamFileOpenFunction        *m_pFileOpen;                             ///< Initialize with the address of a custom SceScreamSndStreamFileOpenFunction() function.
    SceScreamSndStreamFileInfoCBFunction      *m_pFileInfoCB;                           ///< Initialize with the address of a custom SceScreamSndStreamFileInfoCBFunction() function. Optional.
    SceScreamSndStreamFileSeekFunction        *m_pFileSeek;                             ///< Initialize with the address of a custom SceScreamSndStreamFileSeekFunction() function.
    SceScreamSndStreamFileReadFunction        *m_pFileRead;                             ///< Initialize with the address of a custom SceScreamSndStreamFileReadFunction() function.
    SceScreamSndStreamFileCloseFunction       *m_pFileClose;                            ///< Initialize with the address of a custom SceScreamSndStreamFileCloseFunction() function.

    // These are used for asynchronous operation when reading the stream data.
    SceScreamSndStreamFileAsyncOpenFunction             *m_pFileAsyncOpen;              ///< Initialize with the address of a custom SceScreamSndStreamFileAsyncOpenFunction() function.
    SceScreamSndStreamFileAsyncIsOpenCompleteFunction   *m_pFileAsyncIsOpenComplete;    ///< Initialize with the address of a custom SceScreamSndStreamFileAsyncIsOpenCompleteFunction() function.
    SceScreamSndStreamFileAsyncOpenBitstreamFunction    *m_pFileAsyncOpenBitstream;     ///< Initialize with the address of a custom SceScreamSndStreamFileAsyncOpenBitstreamFunction() function.
    SceScreamSndStreamFileAsyncReadFunction             *m_pFileAsyncRead;              ///< Initialize with the address of a custom SceScreamSndStreamFileAsyncReadFunction() function.
    SceScreamSndStreamFileAsyncIsReadCompleteFunction   *m_pFileAsyncIsReadComplete;    ///< Initialize with the address of a custom SceScreamSndStreamFileAsyncIsReadCompleteFunction() function.
    SceScreamSndStreamFileAsyncCloseBitstreamFunction   *m_pFileAsyncCloseBitstream;    ///< Initialize with the address of a custom SceScreamSndStreamFileAsyncCloseBitstreamFunction() function.
    SceScreamSndStreamFileAsyncCloseFunction            *m_pFileAsyncClose;             ///< Initialize with the address of a custom SceScreamSndStreamFileAsyncCloseFunction() function.

} SceScreamSndFileInterface;

#endif // _DOLCESDK_PSP2_SCREAM_SCE_SNDSTREAM_IO_H_
