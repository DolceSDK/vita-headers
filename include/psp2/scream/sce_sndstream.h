#ifndef _DOLCESDK_PSP2_SCREAM_SCE_SNDSTREAM_H_
#define _DOLCESDK_PSP2_SCREAM_SCE_SNDSTREAM_H_

#include <psp2/scream/sce_sndstream_io.h>
#include <psp2/scream/scream_error.h>

////////////////////////////////////////////////////////////////////////////////
// Constants

// ERROR_OK is zero -- all other error codes defined in scream/scream_error.h
/// @ingroup sndStreamGeneralErrors
#define SCE_SCREAM_SND_STREAM_ERROR_OK                      (0)         ///< No error occurred.

// System Constants.
/**
@defgroup sndStreamSystemConstants System Constants
@brief System constants impose limits for various system resources and frequently-used parameters.
@{*/
#define SCE_SCREAM_SND_STREAM_MAX_CHANNELS                  (8)         ///< The maximum number of audio channels available for a single Stream.
#define SCE_SCREAM_SND_FILE_QUEUE_MAX                       (15)        ///< The maximum number of files that can be queued on a single Stream handle. <b>Note:</b> This number does not include the currently playing file, even if it is paused.
#define SCE_SCREAM_SND_STREAM_MAX_PATH                      (256)       ///< The maximum length of a file path string, including the terminating zero. See the SceScreamSndFileParams <c><i>file</i></c> member.
#define SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER              (24)        ///< The number of sync clocks in a quarter-note.
#define SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS                (16)        ///< The maximum number of individual Bitstreams that can be associated with a multi-Layer Stream file. This number may be further constrained by bandwidth limitations. <b>Note:</b> Do not confuse this constant with the sceScreamInitStreaming() function's <c><i>handleCount</i></c> parameter, which sets the system-wide maximum number of simultaneously active Bitstreams that can occur in your game.
#define SCE_SCREAM_SND_STREAM_INVALID_FILE_TOKEN            (NULL)      ///< An invalid #SceScreamSndStreamFileToken value. Potentially returned by the sceScreamParseStreamFile() or sceScreamGetFileTokenFromStorage() functions.
#define SCE_SCREAM_SND_STREAM_DEFAULT_MIDI_BUFFER_SIZE      (2048)      ///< Default size of the buffer used for Stream-associated MIDI files. See the SceScreamSndStreamPlatformInit <c><i>midiBufferSize</i></c> member.
/**@}*/

// Queuing Constants
/**
@defgroup sndStreamQueuingConstants Queuing Constants
@brief Queuing constants define a range of values for the sceScreamQueueToStream() or sceScreamQueueToStreamByFileToken() functions' <c><i>queueIndex</i></c> parameter, when queuing Stream files to play on an active Stream.
@{*/
#define SCE_SCREAM_SND_QUEUE_INDEX_HEAD     0                               ///< Specifies the index position at the start of a Stream queue, that is, the location of the next file to play after the currently playing file.
#define SCE_SCREAM_SND_QUEUE_INDEX_TAIL     SCE_SCREAM_SND_FILE_QUEUE_MAX   ///< Specifies the index position at the end of a Stream queue, that is, the location of the last file to play in a queue of up to #SCE_SCREAM_SND_FILE_QUEUE_MAX files.
/**@}*/

// Memory use type.
/**
@defgroup sndStreamMemoryAllocationConstants Memory Allocation Constants
@brief Memory allocation constants are passed to the Scream Library memory allocation prototype <c>SceScreamExternSndMemAlloc</c> <c><i>use</i></c> parameter to indicate subsystem memory consumption.
@{*/
#define SCE_SCREAM_SND_STREAM_MEM_USE_ALL 0x200             ///< Indicates that allocated memory is to be used for Sndstream.
/**@}*/

// Initialization flags for use with sceScreamInitStreaming.
/**
@defgroup sndStreamInitializationFlags Initialization Flags
@brief Initialization flags provide a way to initialize Sndstream with certain behaviors. You apply the initialization flags to the SceScreamSndStreamPlatformInit <c><i>flags</i></c> member.
@{*/
#define SCE_SCREAM_SND_SS_INIT_NO_PATH_COPY            (1L<<2) ///< Initializes Sndstream to not allocate memory for file path storage. Instead, Sndstream stores a filename pointer in application memory.
#define SCE_SCREAM_SND_SS_INIT_NO_MULTISTREAMS         (1L<<3) ///< Initializes Sndstream without the capability to play multi-Layer Stream files. This reduces memory consumption slightly.
/**@}*/

/**
@ingroup sndStreamDataStructures
@brief
Stores the platform-specific parameter values required for initializing Sndstream.

This data structure contains values for all parameters required to initialize Sndstream.
It is used when calling sceScreamInitStreaming(), and can be initialized with default values by calling sceScreamFillDefaultPlatformInitArgs().

For a detailed discussion of starting a Stream, see the &quot;Configuration, Initialization, and Shutdown&quot; chapter of the <i>Sndstream Library Overview</i>.

@note
Stream stealing is based on priorities specified in Bank contents or in the SceScreamSndStartParams.priority member when starting a Stream.
Stream stealing involves starting a new Stream while a stolen Stream finishes, and therefore requires buffer management as well as voice management.
For this reason, an additional internal structure is needed for every Bitstream being stolen. The memory cost per additional internal structure is only a few hundred bytes.

@see
sceScreamFillDefaultPlatformInitArgs(), sceScreamInitStreaming()
*/
typedef struct SceScreamSndStreamPlatformInit
{
    int32_t  size;                          ///< Size of the structure in bytes. Must be correctly initialized by the application. For guidance on setting this member, see &quot;Setting SceScreamSndStreamPlatformInit Structure Members&quot; in the &quot;Configuration, Initialization, and Shutdown&quot; chapter of the <i>Sndstream Library Overview</i>.
    int32_t  streaming_thread_priority;     ///< Priority to use when creating a streaming thread. The higher the specified value, the higher the thread priority. Defaults to the synthesizer-specific Scream constant <c>SCE_SCREAM_SND_DEFAULT_THREAD_PRIORITY</c> + 1. See &quot;Setting SceScreamSndStreamPlatformInit Structure Members&quot; in the &quot;Configuration, Initialization, and Shutdown&quot; chapter of the <i>Sndstream Library Overview</i> for a discussion of priority.
    int32_t  streaming_thread_affinity;     ///< Processor affinity to use when creating a streaming thread. To specify a particular CPU core, use a zero-based index. To specify all available CPU cores, use -1. Defaults to the synthesizer-specific Scream constant <c>SCE_SCREAM_SND_DEFAULT_THREAD_AFFINITY</c>.
    int32_t  parsing_thread_priority;       ///< Priority to use when creating a stream parsing thread. The higher the specified value, the higher the thread priority. Defaults to the synthesizer-specific Scream constant <c>SCE_SCREAM_SND_DEFAULT_THREAD_PRIORITY</c> + 1. See &quot;Setting SceScreamSndStreamPlatformInit Structure Members&quot; in the &quot;Configuration, Initialization, and Shutdown&quot; chapter of the <i>Sndstream Library Overview</i> for a discussion of priority.
    int32_t  parsing_thread_affinity;       ///< Processor affinity to use when creating a stream parsing thread. To specify a particular CPU core use a zero-based index. To specify all available CPU cores use -1. Defaults to the synthesizer-specific Scream constant <c>SCE_SCREAM_SND_DEFAULT_THREAD_AFFINITY</c>.
    uint32_t  midiBufferCount;              ///< A count of the number of Streams that have an associated MIDI file. Defaults to zero.
    uint32_t  midiBufferSize;               ///< The size in bytes to allocate for each MIDI buffer. Defaults to 2048 (2K).
    uint32_t  flags;                        ///< Use this member to initialize Sndstream with alternative behaviors. Defaults to zero. Use one or more of the \link #SCE_SCREAM_SND_SS_INIT_NO_PATH_COPY Initialization Flags\endlink.
    uint32_t  parsedFileCount;              ///< A count of the number of pre-parsed files that have memory pre-allocated for them. Defaults to zero.  For more information on tokens, see the “Working with File Tokens” chapter in the <i>Sndstream Library Overview</i>.
    uint32_t  subBufferCount;               ///< The number of sub-buffers into which to divide each stream's buffer. Defaults to #SCE_SCREAM_SND_STREAM_FILE_DEFAULT_BUFFER_IDS. Can be zero, or in the range: 2 to #SCE_SCREAM_SND_STREAM_FILE_MAX_BUFFER_IDS. If you specify zero, an optimum value is chosen internally. File reads try to fill a sub-buffer, subject to alignment restrictions.
    uint32_t  parsingThreadStackSize;       ///< The number of bytes to use for the file header parsing thread. Defaults to zero, in which case an optimal value is chosen internally.
    uint32_t  extraStreamsForStealing;      ///< The number of additional internal structures to allocate for Stream stealing. Range: zero to the value passed to the sceScreamInitStreaming() function's <c><i>handleCount</i></c> parameter. Defaults to zero. See &quot;Notes&quot; below.
}SceScreamSndStreamPlatformInit;

/**
@defgroup sndStreamFileParametersConstants File Parameters Constants
@brief File parameters constants define optional Stream file behaviors.
@{*/
#define SCE_SCREAM_SND_SS_FILE_HAS_MIDI_FILE (1L<< 0)  ///< Indicates that a Stream file has an associated MIDI file of the same name. Apply to the #SceScreamSndFileParams <c><i>flags</i></c> member. <b>Note:</b> The naming convention for associated MIDI files is to match the name of the Stream file, replacing the file's extension with a .mid extension. For example, an associated MIDI file for a Stream file named <c>musicClip1.vag</c> would be named <c>musicClip1.mid</c>.
#define SCE_SCREAM_SND_SS_FILE_ALLOCATION_OK (1L<< 1)  ///< Allows the sceScreamParseStreamFile() function to allocate memory for storing parsed file information, that is, if sufficient memory is allocated at initialization time. Apply to the #SceScreamSndFileParams <c><i>flags</i></c> member.

#define SCE_SCREAM_SND_SS_LOOP_INFINITE      (-1)      ///< Indicates that a Stream file should loop indefinitely. Apply to functions and structures with a loop count parameter, such as the #SceScreamSndFileParams <c><i>loopCount</i></c> member or to the sceScreamSetStreamFileLoopingCount() <c><i>loopCount</i></c> parameter.
#define SCE_SCREAM_SND_SS_LOOP_TILL_QUEUED   (-2)      ///< Indicates that a Stream file should loop until a new file is added to the &ndash; currently empty &ndash; queue on the same handle. Apply to functions and structures with a loop count parameter, such as the #SceScreamSndFileParams <c><i>loopCount</i></c> member or to the sceScreamSetStreamFileLoopingCount() <c><i>loopCount</i></c> parameter.
/**@}*/

/**
@ingroup sndStreamDataStructures
@brief
Stores Stream file parameter values.

This structure stores parameter values related to a Stream file.  It is used to provide information for starting streams from files.
The #SceScreamSndStreamUserContext value in <c><i>userContext</i></c> is returned in various status functions, such as sceScreamGetStreamFileLocationInSeconds().

@note
The <c><i>fileInterface</i></c> member allows file I/O specification on a per Stream basis.

@note
Sndstream recognizes loop points embedded in ATRAC9&#8482; Stream files.
And if found, instead of looping around the entire file from start to end, looping playback takes place between the loop points.
For further details, see &quot;Working with Embedded Loop Points in Stream Files&quot; in the &quot;Starting a Stream&quot; chapter of the <i>Sndstream Library Overview</i>.

@see
SceScreamSndFileInterface, sceScreamStartStream(), sceScreamStartStreamFromTransition(), sceScreamQueueToStream()
*/
typedef struct SceScreamSndFileParams
{
    const char                      *file;                  ///< ASCIIZ string pointer to the fully qualified path of the Stream file. For example, <c>mydir/mysubdir/mysound.wav</c>. Maximum length: #SCE_SCREAM_SND_STREAM_MAX_PATH.
    SceScreamSndFileInterface       *fileInterface;         ///< A pointer to a #SceScreamSndFileInterface structure specifying the file interface to use for a Stream file. If <C>NULL</C>, the default file interface is used.
    uint32_t                        flags;                  ///< Optional Stream file behaviors. Us the <c>OR</c> operator to combine multiple values: #SCE_SCREAM_SND_SS_FILE_HAS_MIDI_FILE, #SCE_SCREAM_SND_SS_FILE_ALLOCATION_OK.
    int32_t                         loopCount;              ///< Specifies a number of additional loops to play. That is, 0 to play once without looping, 1 to play twice, 2 to play 3 times, and so on. To loop indefinitely, use the #SCE_SCREAM_SND_SS_LOOP_INFINITE constant; to loop until another file has been queued on the handle, use #SCE_SCREAM_SND_SS_LOOP_TILL_QUEUED. See &quot;Notes&quot; below.
    uint64_t                        seekOffset;             ///< Offset number of bytes into the file at which point to start reading. Used in cases where the streamed audio file is embedded in a larger container file. Points to the location of the beginning of the header of an embedded audio file. If the audio file is not embedded, set to zero.
    float                           startSecond;            ///< Offset number of seconds into the file at which point to start playback. Used in cases where the desired audio data starts other than at the beginning of the file (including where <c><i>seekOffset</i></c> &gt; zero). Expressed in seconds. <b>Note:</b> applies to WAV and VAG file formats only.
    SceScreamSndStreamUserContext   userContext;            ///< User defined data that is passed to the file I/O interfaces.
}SceScreamSndFileParams;


/**
@ingroup sndStreamDataStructures
@brief
Stores parameter values used when parsing a Stream file.

This structure stores parameter values related to parsing the header of an audio file.
You initialize this structure with appropriate values for the sceScreamParseStreamFile() function's <c><i>parseParams</i></c> parameter.
Note that this structure has some of the same members as #SceScreamSndFileParams and #SceScreamSndFileParams.

@note
The <c><i>fileInterface</i></c> member allows file I/O specification on a per file basis.

@see
sceScreamParseStreamFile(), sceScreamGetFileTokenFromStorage()
*/
typedef struct SceScreamSndStreamParseParams
{
    // This is the same as SceScreamSndFileParams but without the runtime loopCount and startSeconds.
    const char                      *file;                  ///< ASCIIZ string pointer to the fully qualified path of the Stream file. For example, <c>mydir/mysubdir/mysound.wav</c>. Maximum length: #SCE_SCREAM_SND_STREAM_MAX_PATH.
    SceScreamSndFileInterface       *fileInterface;         ///< A pointer to a SceScreamSndFileInterface structure specifying the file interface to use for a Stream file. If <C>NULL</C>, the default file interface is used.
    uint32_t                        flags;                  ///< If the file has an associated MIDI file, use #SCE_SCREAM_SND_SS_FILE_HAS_MIDI_FILE. This is currently the only valid flag.
    uint64_t                        seekOffset;             ///< Offset number of bytes into the file at which point to start reading. Used in cases where the streamed audio file is embedded in a larger container file. Points to the location of the beginning of the header of an embedded audio file. If the audio file is not embedded, set to zero.
    SceScreamSndStreamUserContext   userContext;            ///< User defined data that is passed to the file I/O interfaces.
}SceScreamSndStreamParseParams;


/**
@ingroup sndStreamDataStructures
@brief
Stores playback information used when starting a new Stream or queuing a file to an existing Stream.

This structure stores playback information used when starting a new Stream by reference to a file token with the sceScreamStartStreamByFileToken() function or queuing a
file to an existing Stream by reference to a file token with the sceScreamQueueToStreamByFileToken() function.
You initialize this structure with appropriate values and use it in sceScreamStartStreamByFileToken() or sceScreamQueueToStreamByFileToken() function's <c><i>queueParams</i></c> parameter.

@note
Alternatively, you can queue a Stream, referencing the file by path, using the sceScreamQueueToStream() function.
And you can start a Stream from a file, referencing the file by a token, using the sceScreamStartStreamByFileToken() function.

@note
Sndstream recognizes loop points embedded in ATRAC9&#8482; Stream files.
And if found, instead of looping around the entire file from start to end, looping playback takes place between the loop points.
For further details, see &quot;Working with Embedded Loop Points in Stream Files&quot; in the &quot;Starting a Stream&quot; chapter of the <i>Sndstream Library Overview</i>.

@see
sceScreamStartStreamByFileToken(), sceScreamQueueToStreamByFileToken()
*/
typedef struct SceScreamSndStreamQueueParams
{
    int32_t             loopCount;              ///< Specifies a number of additional loops to play. That is, 0 to play once without looping, 1 to play twice, 2 to play 3 times, and so on. To loop indefinitely, use the #SCE_SCREAM_SND_SS_LOOP_INFINITE constant; to loop until another file has been queued on the handle, use #SCE_SCREAM_SND_SS_LOOP_TILL_QUEUED. See &quot;Notes&quot; below.
    float               startSecond;            ///< Offset number of seconds into the file at which point to start playback. Used in cases where the desired audio data starts other than at the beginning of the specified file. Expressed in seconds. <b>Note:</b> applies to WAV and VAG file formats only.
}SceScreamSndStreamQueueParams;

/**
@defgroup sndStreamDataStructures Data Structures
@brief Sndstream data structures store data referenced in Sndstream functions.
@{*/
/**
@brief
Stores gain, azimuth, and focus parameter values for one or more Stream Layers.

This structure stores gain, azimuth, and focus parameter values for one or more Stream Layers.
Its members store parameter values in arrays, one value for each Layer.
The maximum length of the arrays is #SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS, which is the maximum number of Layers that can be contained in a Stream.

You can set Stream Layers parameters collectively (using the sceScreamSetStreamLayerParams() and sceScreamAutoStreamLayerParams() functions) or individually (using the Scream sceScreamSetSoundParamsEx(), sceScreamAutoGain(), and sceScreamAutoPan() functions).
These functions allow you to manipulate Stream Layers as if live-mixing a multi-track recording.

@note
Setting parameter values with this structure overrides any corresponding default settings or settings arising from Bank contents.
For example, setting azimuth values for a stereo file would override the default channel speaker assignments (that is, to front left/right speakers).

@see
SceScreamSndStartParams, sceScreamStartStream(), sceScreamSetStreamLayerParams(), sceScreamGetStreamLayerParams(), sceScreamAutoStreamLayerParams()
*/
typedef struct SceScreamSndBitstreamParams
{
    uint32_t    mask;                                           ///< A mask indicating which of the subsequent members have active settings. One or more of the following Scream Sound parameter bitmask constants: #SCE_SCREAM_SND_MASK_GAIN, #SCE_SCREAM_SND_MASK_PAN_AZIMUTH, #SCE_SCREAM_SND_MASK_PAN_FOCUS. Use the <c>OR</c> operator to specify multiple selections. Set to <c>NULL</c> to leave existing (default, Bank contents, or Layer-specific) settings unchanged.
    float       gain[SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS];     ///< An array of gain values for each Layer. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    uint32_t    azimuth[SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS];  ///< An array of azimuth values for each Layer. Expressed in degrees clockwise relative to the screen. Range: 0 to 359. Alternatively, you can set specific Output Speaker Targets. For further details, see  “Output Speaker Targets” in the <i>Scream Library Reference (NGS2)</i> and the <i>Scream Library Reference (NGS)</i>.
    uint32_t    focus[SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS];    ///< An array of pan focus values for each Layer. Range: 0 to 360. Ignored if <c>focus</c> is set to an Output Speaker Target.
}SceScreamSndBitstreamParams;
/**@}*/

// Stream initialization Constants
/**
@defgroup sndStreamStreamInitializationConstants Stream Initialization Constants
@brief Stream initialization constants specify optional behaviors with which you can initialize a Stream.
@{*/
#define SCE_SCREAM_SND_SS_START_PAUSED          (1L<< 0)    ///< Specifies that a Stream should start in a paused state. This can be useful for prebuffering a number of files to be started simultaneously. To begin playing a paused Stream, use the Scream Library functions sceScreamContinueSound() or sceScreamContinueAllSoundsInGroup(). Initialization option for starting a Stream that applies to the #SceScreamSndStartParams <c><i>flags</i></c> member. Not valid when queuing a Stream to an active handle.
#define SCE_SCREAM_SND_SS_START_VOICE_NO_STEAL  (1L<< 1)    ///< Specifies that voices allocated to a Stream handle cannot be stolen for other Scream or Sndstream voice requests. Initialization option for starting a Stream that applies to the #SceScreamSndStartParams <c><i>flags</i></c> member.
#define SCE_SCREAM_SND_SS_START_SMART_PAN       (1L<< 2)    ///< Initialization option for starting a Stream. Apply to the #SceScreamSndStartParams <c><i>flags</i></c> member. For further information, see &quot;Smart Pan&quot; in the &quot;Starting a Stream&quot; chapter of the <i>Sndstream Library Overview</i>.
#define SCE_SCREAM_SND_SS_START_SYNC_CLOCK      (1L<< 3)    ///< Sets a Stream as the current sync clock. Apply to the #SceScreamSndStartParams <c><i>flags</i></c> member. The sync clock is used for Stream transitions using the sceScreamStartStreamFromTransition() function or for playing synchronized Scream Sounds using the sceScreamPlaySoundSyncedByIndexEx() and sceScreamPlaySoundSyncedByNameEx() functions. <b>Note:</b> A sync clock Stream must have an associated MIDI file specifying tempo and meter information.
#define SCE_SCREAM_SND_SS_START_GET_VOICE_LEVEL (1L<< 4)    ///< Specifies that a Stream's current voice level is available for retrieval by the sceScreamGetStreamLevel() function. Applicable to mono Streams only. Apply to the SceScreamSndStartParams <c><i>flags</i></c> member.
#define SCE_SCREAM_SND_SS_START_ADSR1_DEFAULT   0x80FF      ///< Specifies the note-on (attack, decay, sustain) portion of a default Stream-specific envelope. Apply to the SceScreamSndStartParams <c><i>adsr1</i></c> member.
#define SCE_SCREAM_SND_SS_START_ADSR2_DEFAULT   0xDFE0      ///< Specifies the note-off (release) portion of a default Stream-specific envelope. Apply to the SceScreamSndStartParams <c><i>adsr2</i></c> member.
/**@}*/

/**
@ingroup sndStreamDataStructures
@brief
Stores the parameter values required for starting a Stream.

A data structure used to store parameter values used when initializing a Stream.
It is used by all the Stream starting functions: sceScreamStartStream(), sceScreamStartStreamByFileToken(), and sceScreamStartStreamFromTransition().

@note
In Scream, voice allocation priority is scaled according to gain. That is, if two sounds share the same priority value,
but one is louder than the other, the louder voice is given a higher priority, making it less susceptible
to voice stealing. The <c><i>priorityReductionScale</i></c> member scales the extent to which Scream can reduce voice allocation
priority based on gain.

@note
Setting the #SCE_SCREAM_SND_SS_START_VOICE_NO_STEAL <c><i>flags</i></c> option has no bearing on the allocation of voices for the Stream.
This option simply prevents the Stream's voices from being stolen for subsequent Scream or Sndstream voice requests.

@see
sceScreamStartStream(), sceScreamStartStreamByFileToken(), sceScreamStartStreamFromTransition(), SceScreamSndBitstreamParams
*/
typedef struct SceScreamSndStartParams
{
    uint32_t                        flags;                      ///< One or more of the following Stream Initialization constants (use the OR operator to make multiple selections):<br>#SCE_SCREAM_SND_SS_START_PAUSED,<br>#SCE_SCREAM_SND_SS_START_VOICE_NO_STEAL,<br>#SCE_SCREAM_SND_SS_START_SMART_PAN,<br>#SCE_SCREAM_SND_SS_START_SYNC_CLOCK.
    int8_t                          volumeGroup;                ///< One of the Scream Library Volume Group constants. See  “Volume Groups” in the <i>Scream Library Reference (NGS2)</i> and the <i>Scream Library Reference (NGS)</i> for details.
    int8_t                          priority;                   ///< Voice allocation priority. Range: 0 to 127. Higher values indicate higher priorities, making allocated voices less likely to be stolen for new voice requests. If there are no free voices when the Stream is initialized, active voices with lower priority values are more likely to be stolen. A value of 127 can only be set from the API, and is therefore guaranteed to be of a higher priority than <i>Stream</i> Grain settings made in Scream Tool.
    float                           priorityReductionScale;     ///< Determines the extent to which Scream can reduce voice allocation priority based on gain. Range: 0.0 to 1.0. A value of 1.0 specifies maximum gain-based voice priority reduction. A value of 0.0 specifies zero gain-based voice priority reduction. For more information, see “Voice Prioritization” in “Scream Sounds and Synthesizer Voices” in the “System Overview”chapter of the <i>Scream Library Overview</i>.
    uint16_t                        adsr1;                      ///< Note-on portion of a Stream-specific gain envelope. Currently, must be set to #SCE_SCREAM_SND_SS_START_ADSR1_DEFAULT.
    uint16_t                        adsr2;                      ///< Note-off portion of a Stream-specific gain envelope. Currently, must be set to #SCE_SCREAM_SND_SS_START_ADSR2_DEFAULT.
    SceScreamSndBitstreamParams     bitstreamParams;            ///< A #SceScreamSndBitstreamParams structure specifying Bitstream parameter values.
    SceScreamSndBitstreamParams     layerParams;                ///< A #SceScreamSndBitstreamParams structure specifying Layer parameter values.
    SceScreamSoundParams            soundParams;                ///< A Scream Library #SceScreamSoundParams structure specifying Sound-specific parameter values. See the <i>Scream Library Reference (NGS2)</i> and the <i>Scream Library Reference (NGS)</i> for details on this structure.
}SceScreamSndStartParams;

/**
@defgroup sndStreamSynchronizationConstants Synchronization Constants
@brief Synchronization constants specify optional behaviors for the synchronized Stream transition and playback functions.
@{*/
#define SCE_SCREAM_SND_SYNC_FLAG_START_IF_NO_CLOCK   (1L << 0) ///< Synchronization behavior flag. Indicates that synchronized content should still play if there is no sync clock Stream to synchronize to. Used in the #SceScreamSndSyncParams <c><i>syncFlags</i></c> member. <b>Note:</b> If there is no sync clock Stream and you do not set this flag, pending synchronized events do not play.
#define SCE_SCREAM_SND_SYNC_FLAG_START_IF_CLOCK_ENDS (1L << 1) ///< Synchronization behavior flag. Indicates that synchronized content should still play if the sync clock Stream terminates before a legal sync point is reached. Used in the #SceScreamSndSyncParams <c><i>syncFlags</i></c> member. <b>Note:</b> If the sync clock Stream terminates and you do not set this flag, pending synchronized events do not play.

#define SCE_SCREAM_SND_SYNC_UNIT_CONTENT  0  ///< Specifies that the synchronization points are as defined in the content, that is, in accordance with marker(s) in the sync clock Stream's associated MIDI file. Used in the #SceScreamSndSyncParams <c><i>syncUnit</i></c> member.
#define SCE_SCREAM_SND_SYNC_UNIT_CLOCK    1  ///< Specifies that the basic synchronization unit is a sync clock; that is, the synchronization point falls on a sync clock boundary. Used in the #SceScreamSndSyncParams <c><i>syncUnit</i></c> member. See #SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER.
#define SCE_SCREAM_SND_SYNC_UNIT_BEAT     2  ///< Specifies that the basic synchronization unit is a beat, that is, the synchronization point falls on a beat boundary. Used in the #SceScreamSndSyncParams <c><i>syncUnit</i></c> member.
#define SCE_SCREAM_SND_SYNC_UNIT_MEASURE  3  ///< Specifies that the basic synchronization unit is a measure, that is, the synchronization point falls on a measure boundary. Used in the #SceScreamSndSyncParams <c><i>syncUnit</i></c> member.
#define SCE_SCREAM_SND_SYNC_UNIT_MARKER   4  ///< Specifies that the basic synchronization unit is a marker (in the sync clock Stream's associated MIDI file), that is, the synchronization point falls on a MIDI marker boundary. Used in the #SceScreamSndSyncParams <c><i>syncUnit</i></c> member.

#define SCE_SCREAM_SND_UNIT_CLOCK_MULTIPLE_QUARTER_NOTE(m)   (m*SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER)   ///< A macro for calculating the number of sync clocks in a given number of quarter-notes. See the #SceScreamSndSyncParams <c><i>unitMultiple</i></c> member and #SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER.
#define SCE_SCREAM_SND_UNIT_CLOCK_MULTIPLE_EIGHTH_NOTE(m)    (m*SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER/2) ///< A macro for calculating the number of sync clocks in a given number of eighth-notes. See the #SceScreamSndSyncParams <c><i>unitMultiple</i></c> member and #SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER.
#define SCE_SCREAM_SND_UNIT_CLOCK_MULTIPLE_SIXTEENTH_NOTE(m) (m*SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER/4) ///< A macro for calculating the number of sync clocks in a given number of sixteenth-notes. See the #SceScreamSndSyncParams <c><i>unitMultiple</i></c> member and #SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER.
/**@}*/

/**
@ingroup sndStreamDataStructures
@brief
Stores synchronization properties for Stream transitions or synchronized play of Scream Sounds.

The sceScreamStartStreamFromTransition() function allows you to start a new Stream as a coordinated transition from a master Stream. You can also overlay a new Stream in synchronization with a master Stream.
The sceScreamPlaySoundSyncedByIndexEx() and sceScreamPlaySoundSyncedByNameEx() functions allow you to trigger Scream Sounds in synchronization with a master Stream.
This structure stores synchronization points and behaviors for use with these functions.

To use synchronization points defined in the sync clock Stream's associated MIDI file, set <c><i>syncUnit</i></c> to #SCE_SCREAM_SND_SYNC_UNIT_CONTENT.
Setting <c><i>syncUnit</i></c> to any of the other synchronization unit constants overrides any synchronization points defined in the sync clock Stream's associated MIDI file.

To set synchronization points from the API, you specify them in terms of a number of multiples (<c><i>unitMultiple</i></c>) of a basic synchronization unit (<c><i>syncUnit</i></c>).
For example, to specify synchronization points occurring every two beats, set <c><i>syncUnit</i></c> to #SCE_SCREAM_SND_SYNC_UNIT_BEAT, and <c><i>unitMultiple</i></c> to 2.

For <c><i>syncUnit</i></c> values smaller than a quarter-note, the resolution is in sync clocks (1/24<sup>th</sup> subdivisions of a quarter-note; see #SCE_SCREAM_SND_SYNC_CLOCKS_PER_QUARTER).
For example, an eighth-note is 12 sync clocks, a triplet-eighth-note is 8 sync clocks, and a sixteenth-note is 6 sync clocks, and so on.
The sync clock macros may be of help in calculating multiples of quarter-notes and quarter-note subdivisions in terms of sync clocks.
See #SCE_SCREAM_SND_UNIT_CLOCK_MULTIPLE_QUARTER_NOTE, and so on.

@note
If <c><i>syncUnit</i></c> is set to #SCE_SCREAM_SND_SYNC_UNIT_CONTENT, <c><i>unitMultiple</i></c> is ignored.

@see
sceScreamStartStreamFromTransition(), sceScreamPlaySoundSyncedByIndexEx(), sceScreamPlaySoundSyncedByNameEx()
*/
typedef struct SceScreamSndSyncParams
{
    uint32_t    syncFlags;      ///< One or both of the synchronization behavior flags: <br>#SCE_SCREAM_SND_SYNC_FLAG_START_IF_NO_CLOCK <br>#SCE_SCREAM_SND_SYNC_FLAG_START_IF_CLOCK_ENDS <br>Alternatively, set to 0 if, in the absence of a sync clock Stream, you do not want a synchronized event to play out of synchronization.
    uint32_t    syncUnit;       ///< One of the synchronization unit constants: <br>#SCE_SCREAM_SND_SYNC_UNIT_CONTENT <br>#SCE_SCREAM_SND_SYNC_UNIT_CLOCK <br>#SCE_SCREAM_SND_SYNC_UNIT_BEAT <br>#SCE_SCREAM_SND_SYNC_UNIT_MEASURE <br>#SCE_SCREAM_SND_SYNC_UNIT_MARKER
    uint32_t    unitMultiple;   ///< Defines synchronization point boundaries. A multiple of the <c><i>syncUnit</i></c> value. See &quot;Notes&quot; below.
}SceScreamSndSyncParams;

/**
@defgroup sndStreamTransitionModeConstants Transition Mode Constants
@brief Transition mode constants specify optional behaviors for the SceScreamSndTransitionParams <c><i>transitionMode</i></c> member.
@{*/
#define SCE_SCREAM_SND_TRANSITION_MODE_PLAY_WITH_MASTER 0   ///< Specifies that a transitioned (new) Stream actually plays along with a master (existing) Stream as the latter continues.
#define SCE_SCREAM_SND_TRANSITION_MODE_FADEOUT_MASTER   1   ///< Specifies that the master (existing) Stream fades out in accordance with the #SceScreamSndTransitionParams <c><i>fadeOutTime</i></c> and <c><i>fadeOutGain</i></c> members.
#define SCE_SCREAM_SND_TRANSITION_MODE_KEYOFF_MASTER    2   ///< Specifies that the master (existing) Stream keys-off, that is, it enters the Release stage of an ADSR setting, rather than fading out at the transition point.
/**@}*/

/**
@ingroup sndStreamDataStructures
@brief
Stores properties for a Stream transition.

The structure is used to store transition mode and fade in/out properties for a Stream transition. Used in conjunction with the sceScreamStartStreamFromTransition() function.

@note
If <c><i>transitionMode</i></c> is <i>not</i> set to #SCE_SCREAM_SND_TRANSITION_MODE_FADEOUT_MASTER, <c><i>fadeOutTime</i></c> and <c><i>fadeOutGain</i></c> are ignored.

@see
sceScreamStartStreamFromTransition()
*/
typedef struct SceScreamSndTransitionParams
{
    uint32_t    transitionMode;   ///< One of the Transition Mode Constants: <br>#SCE_SCREAM_SND_TRANSITION_MODE_PLAY_WITH_MASTER <br>#SCE_SCREAM_SND_TRANSITION_MODE_FADEOUT_MASTER <br>#SCE_SCREAM_SND_TRANSITION_MODE_KEYOFF_MASTER
    float       fadeInTime;       ///< Fade-in time of the transitioned (new) Stream. Expressed in seconds.
    float       fadeInGain;       ///< Target gain of the transitioned (new) Stream on completion of its fade-in. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float       fadeOutTime;      ///< Fade-out time of the existing Stream. Expressed in seconds. See &quot;Notes&quot; below.
    float       fadeOutGain;      ///< Target gain of the existing Stream on completion of its fade-out. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN. See &quot;Notes&quot; below.
}SceScreamSndTransitionParams;


/**
@defgroup typeDefinitions Type Definitions
@brief
The type definitions define data types for various Sndstream APIs.
@{*/
/**
@brief
Data type for an opaque pointer to a pre-parsed Stream file.

Use this type to reference a Stream file, pre-parsed using the sceScreamParseStreamFile() function.
You can also obtain a token by calling sceScreamGetFileTokenFromStorage(). The constant #SCE_SCREAM_SND_STREAM_INVALID_FILE_TOKEN designates an invalid token.

@see
sceScreamStartStreamByFileToken(), sceScreamQueueToStreamByFileToken(), sceScreamParseStreamFile(), sceScreamDeleteStreamFileToken(), sceScreamGetFileTokenFromStorage(), #SCE_SCREAM_SND_STREAM_INVALID_FILE_TOKEN
*/
typedef void * SceScreamSndStreamFileToken;
/**@}*/

/**
@ingroup typeDefinitions
@brief
Data type for an opaque pointer to a storage for pre-parsed file tokens.

Use this type to reference a file token storage.
You can create the storage at build time and then load it from a file to be used at run time.
Create tokens by calling sceScreamParseStreamFile().

@see
sceScreamCreateFileTokenStorage(), sceScreamByteReverseFileTokenStorage(), sceScreamDeleteFileTokenStorage(), sceScreamValidateFileTokenStorage(), sceScreamGetFileTokenFromStorage(), sceScreamParseStreamFile()
*/
typedef void SceScreamSndStreamFileTokenStorage;

#if (defined(_cplusplus) || defined(__cplusplus))
extern "C"
{
#endif

// System

/**
@defgroup systemFunctions System Functions
@brief
The system functions initialize and shutdown Sndstream.
@{*/
/**
@brief
Shuts down Sndstream.

Use this function to completely shut down Sndstream. This function
stops all Streams, destroys all streaming threads, and releases all
allocated memory.

@return
Returns 0 if Sndstream shutdown was successful. Returns #SCE_SCREAM_SND_STREAM_CLOSE_ERROR_NOT_INITED if Sndstream was not initialized.

@note
This function uses sceScreamStopAllStreams() to stop all streaming
threads, which blocks the calling thread until all Streams are
stopped.

@see
sceScreamInitStreaming(), sceScreamStopAllStreams()
*/
int32_t  sceScreamCloseStreaming(void);
/**@}*/

/**
@ingroup systemFunctions
@brief
Initializes a SceScreamSndStreamPlatformInit data structure for use in a call to sceScreamInitStreaming().

Use this function to initialize a SceScreamSndStreamPlatformInit data structure with the following default values:<br>
<table border="0">
<!-- SceScreamSndStreamPlatformInit defaults -->
<tr>
<td><c><i>size</i></c></td>
<td>sizeof(#SceScreamSndStreamPlatformInit)</td>
</tr>
<tr>
<td><c><i>thread_priority</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_THREAD_PRIORITY + 1</td>
</tr>
<tr>
<td><c><i>thread_affinity</i></c></td>
<td>-1</td>
</tr>
<tr>
<td><c><i>midiBufferCount</i></c></td>
<td>0</td>
</tr>
<tr>
<td><c><i>midiBufferSize</i></c></td>
<td>#SCE_SCREAM_SND_STREAM_DEFAULT_MIDI_BUFFER_SIZE</td>
</tr>
<tr>
<td><c><i>flags</i></c></td>
<td>0</td>
</tr>
<tr>
<td><c><i>parsedFileCount</i></c></td>
<td>0</td>
</tr>
<tr>
<td><c><i>subBufferCount</i></c></td>
<td>4</td>
</tr>
<tr>
<td><c><i>parsingThreadStackSize</i></c></td>
<td>0</td>
</tr>
<tr>
<td><c><i>extraStreamsForStealing</i></c></td>
<td>0</td>
</tr>
</table>

@param args (Input/Output)
Pointer to a SceScreamSndStreamPlatformInit data structure to be initialized. See &quot;Notes&quot; below.

@return
Returns 0 if the SceScreamSndStreamPlatformInit data structure is successfully initialized.
Returns #SCE_SCREAM_SND_STREAM_INIT_ERROR_INVALID_ARGS if the <c><i>size</i></c> member of the specified SceScreamSndStreamPlatformInit structure is incorrect.

@note
You can override the default settings after initialization, as desired.

@see
SceScreamSndStreamPlatformInit, sceScreamInitStreaming()
*/
int32_t  sceScreamFillDefaultPlatformInitArgs(SceScreamSndStreamPlatformInit *args);

/**
@ingroup systemFunctions
@brief
Initializes Sndstream for use by an application.

Prepares the library for streaming, instantiates threads, and allocates memory.
This is the only Sndstream function that allocates memory.

@param  handleCount (Input)
Number of Stream handles to allocate.
Set to the maximum number of simultaneously active Streams that occur in your game.

@param  bufferSize  (Input)
Size in bytes of one Stream buffer.
Each Stream handle has a buffer of this size associated with it.
See &quot;Notes&quot; below.

@param  args (Input)
Pointer to an initialized SceScreamSndStreamPlatformInit structure.
Call sceScreamFillDefaultPlatformInitArgs() to initialize this structure.

@return
Returns 0 if Sndstream was initialized successfully. Otherwise, returns one of the Initialization Errors; see #SCE_SCREAM_SND_STREAM_INIT_ERROR_INVALID_ARGS, and so on.

@note
The <c><i>handleCount</i></c> parameter must include any cross-fading Bitstreams in the overall count of simultaneously playing Bitstreams.

@note
The specified <c><i>bufferSize</i></c> is subdivided into sub-buffers, the number of which is determined by the SceScreamSndStreamPlatformInit <c><i>subBufferCount</i></c> member.
Sub-buffers are used to fill individual Stream data reads.

For a full discussion of using this function, see the &quot;Configuration, Initialization, and Shutdown&quot; chapter of the <i>Sndstream Library Overview</i>.

@see
SceScreamSndStreamPlatformInit, sceScreamFillDefaultPlatformInitArgs(), sceScreamCloseStreaming()
*/
int32_t  sceScreamInitStreaming(uint32_t handleCount, uint32_t bufferSize, const SceScreamSndStreamPlatformInit *args);

// Start and stop

/**
@defgroup startAndStopFunctions Start and Stop Functions
@brief
These functions start and stop Streams.
@{*/
/**
@brief
Seeks to a time offset in the currently playing file and immediately continues playback.

This function causes the Stream to jump from the current
playback position to a new playback position, specified by a time increment from the beginning of the file,
and immediately continue playback.

@param
handle (Input)
Handle of the Stream upon which to perform the cue operation. A value returned by the sceScreamStartStream(), sceScreamQueueToStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
seconds (Input)
Floating point value, in seconds, of an offset position from the beginning of the file to seek to and continue playback.

@note
Depending on the playback data type, the time position offset may be
rounded to the nearest valid sample or compression frame starting
boundary.

@note
Audible artifacts can occur if there is a discontinuity between the
current playback position and the new offset position.

@return
Returns #SCE_SCREAM_SND_STREAM_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SND_STREAM_ERROR_OUT_OF_RANGE if parameter value was out of range.

@see
sceScreamGetStreamFileLengthInSeconds(), sceScreamGetStreamFileSecondsRemaining(), sceScreamGetStreamFileLocationInSeconds()
*/
int32_t sceScreamCueStreamToTime(uint32_t handle, float seconds);
/**@}*/

/**
@ingroup startAndStopFunctions
@brief
Inserts a Stream file, referenced by path, into the queue of an existing Stream handle.

This function inserts a Stream file, referenced by path, into the queue of an active Stream handle.
The <c><i>queueIndex</i></c> parameter allows you to specify an index point in the queue
at which to position the new Stream file. You can obtain the number of files currently queued to
an active Stream using the sceScreamGetStreamQueueCount() function. Specifying #SCE_SCREAM_SND_QUEUE_INDEX_HEAD
always inserts the file at the start of the queue. Specifying #SCE_SCREAM_SND_QUEUE_INDEX_TAIL
always inserts the file at the end of the queue, regardless of the current number of files in the queue.

@param
queueHandle (Input)
Handle of an active Stream, into the queue of which to insert the Stream file. A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
queueIndex (Input)
Zero-based index indicating a position in the queue at which point to insert the Stream file. Range: #SCE_SCREAM_SND_QUEUE_INDEX_HEAD to #SCE_SCREAM_SND_QUEUE_INDEX_TAIL.
Use #SCE_SCREAM_SND_QUEUE_INDEX_TAIL to insert the file at the end of the queue.

@param
fileParams (Input)
Pointer to a SceScreamSndFileParams structure initialized with appropriate Stream file parameter values.

@param
startParams (Input)
Pointer to a SceScreamSndStartParams structure initialized with Stream parameter values to use in the
event that the Stream to which you are queuing is already dead.
Set to <c>NULL</c> if you do not want the new Stream to play if the parent Stream has expired.
<b>Note:</b> if not <c>NULL</c>, and the parent Stream is still active, <c><i>startParams</i></c> settings
are ignored.

@return
If successful, returns the supplied handle of the queue-inserted Stream. If not successful, returns 0.

@note
While this function accepts specification of a Stream file by path (expressed in the <c><i>fileParams</i></c> SceScreamSndFileParams structure's <c><i>file</i></c> member),
it automatically pre-parses the file's header to produce a file token, by which the file is actually referenced internally.
As an alternative, you can explicitly create the file token (at build or load time) using the sceScreamParseStreamFile() function,
and then use the sceScreamQueueToStreamByFileToken() function to insert a Stream file, referenced by token, into the queue of an existing Stream handle.

@see
sceScreamGetStreamQueueCount(), sceScreamStartStream(), sceScreamQueueToStreamByFileToken()
*/
uint32_t  sceScreamQueueToStream(uint32_t queueHandle, uint32_t queueIndex, const SceScreamSndFileParams *fileParams, const SceScreamSndStartParams *startParams);

/**
@ingroup startAndStopFunctions
@brief
Inserts a Stream file, referenced by token, into the queue of an existing Stream handle.

This function inserts a specified Stream file, referenced by token, into the queue of an active Stream handle.
The <c><i>queueIndex</i></c> parameter allows you to specify an index point in the queue
at which to position the new Stream file. You can obtain the number of files currently queued to
an active Stream using the sceScreamGetStreamQueueCount() function. Specifying #SCE_SCREAM_SND_QUEUE_INDEX_HEAD
always inserts the file at the start of the queue. Specifying #SCE_SCREAM_SND_QUEUE_INDEX_TAIL
always inserts the file at the end of the queue, regardless of the current number of files in the queue.

@param
queueHandle (Input)
Handle of an active Stream, into the queue of which to insert the Stream file.
A value returned by the sceScreamStartStreamByFileToken(), sceScreamStartStream(), or sceScreamStartStreamFromTransition() functions.

@param
queueIndex (Input)
Zero-based index indicating a position in the queue at which point to insert the Stream file. Range: #SCE_SCREAM_SND_QUEUE_INDEX_HEAD to #SCE_SCREAM_SND_QUEUE_INDEX_TAIL.
Use #SCE_SCREAM_SND_QUEUE_INDEX_TAIL to insert the file at the end of the queue.

@param
fileToken (Input)
A token that represents a Stream file, containing information from the file's header.
You create a Stream file token using the sceScreamParseStreamFile() function.

@param
queueParams (Input)
Pointer to an appropriately initialized SceScreamSndStreamQueueParams structure, specifying playback information for the inserted stream.

@param
startParams (Input)
Pointer to a SceScreamSndStartParams structure initialized with Stream parameter values to use in the
event that the Stream to which you are queuing is already dead.
Set to <c>NULL</c> if you do not want the new Stream to play if the parent Stream has expired.
<b>Note:</b> if not <c>NULL</c>, and the parent Stream is still active, <c><i>startParams</i></c> settings
are ignored.

@return
If successful, returns the supplied handle of the queue-inserted Stream. If not successful, returns 0.

@see
SceScreamSndStreamQueueParams, SceScreamSndStartParams, sceScreamStartStreamByFileToken(), sceScreamParseStreamFile(), sceScreamGetStreamQueueCount(), sceScreamQueueToStream()
*/
uint32_t  sceScreamQueueToStreamByFileToken(uint32_t queueHandle, uint32_t queueIndex, SceScreamSndStreamFileToken fileToken, const SceScreamSndStreamQueueParams *queueParams, const SceScreamSndStartParams *startParams);

/**
@ingroup startAndStopFunctions
@brief
Initializes a Stream and starts playback of a file referenced by path.

This function initializes a Stream and starts playback of a file referenced by path.

The returned handle is used as input to numerous Sndstream functions that manipulate or retrieve
information about a Stream. The handle can also be used as input to Scream Library functions, enabling
functionality from the Scream Library API to be applied.

@param
fileParams (Input)
Pointer to a SceScreamSndFileParams structure, initialized with appropriate Stream file parameter values.

@param
startParams (Input)
Pointer to a SceScreamSndStartParams structure, initialized with parameter values for the new Stream.

@param outputDest (Input)
Index of an output destination.
Defaults to #SCE_SCREAM_SND_OUTPUT_DEST_MASTER for master output.
To inherit an output destination from the Group to which the Sound is assigned, use #SCE_SCREAM_SND_OUTPUT_DEST_BY_GROUP.
To specify an allocated pre-master submix buss, use the number of the desired submix, indexing from zero, and within the range: #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 to (#SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES &ndash; 1).
See &quot;Notes&quot; below.

@return
If successful, returns the handle of the initialized Stream. If not successful, returns 0.

@note
While this function accepts specification of a Stream file by path (expressed in the <c><i>fileParams</i></c> SceScreamSndFileParams structure's <c><i>file</i></c> member),
it automatically pre-parses the file's header to produce a file token, by which the file is actually referenced internally.
As an alternative, you can explicitly create the file token (at build or load time) using the sceScreamParseStreamFile() function,
and then use the sceScreamStartStreamByFileToken() function to initialize a Stream and start playback of a file referenced by token.

@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the Scream <c>SceScreamSystemParams</c> structure.
Make sure that you do not set a pre-master submix output destination that has not been allocated.

@see
SceScreamSndFileParams, SceScreamSndStartParams, sceScreamQueueToStream(), sceScreamStartStreamFromTransition(), sceScreamStartStreamByFileToken()
*/
uint32_t  sceScreamStartStream(const SceScreamSndFileParams *fileParams, const SceScreamSndStartParams *startParams, int32_t outputDest /* = SCE_SCREAM_SND_OUTPUT_DEST_MASTER */);

/**
@ingroup startAndStopFunctions
@brief
Initializes a Stream and starts playback of a file referenced by token.

This function initializes a Stream and starts playback of a file referenced by a token.

The returned handle is used as input to numerous Sndstream functions that manipulate or retrieve
information about a Stream. The handle can also be used as input to Scream Library functions, enabling
functionality from the Scream Library API to be applied.

@param
fileToken (Input)
A token that represents a Stream file, containing information from the file's header.
You create a Stream file token using the sceScreamParseStreamFile() function.

@param
queueParams (Input)
Pointer to an appropriately initialized SceScreamSndStreamQueueParams structure, specifying playback information.

@param
startParams (Input)
Pointer to a SceScreamSndStartParams structure, initialized with parameter values for the new Stream.

@param outputDest (Input)
Index of an output destination.
Defaults to #SCE_SCREAM_SND_OUTPUT_DEST_MASTER for master output.
To inherit an output destination from the Group to which the Sound is assigned, use #SCE_SCREAM_SND_OUTPUT_DEST_BY_GROUP.
To specify an allocated pre-master submix buss, use the number of the desired submix, indexing from zero, and within the range: #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 to (#SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES &ndash; 1).
See &quot;Notes&quot; below.

@return
If successful, returns the handle of the initialized Stream. If not successful, returns 0.

@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the Scream <c>SceScreamSystemParams</c> structure.
Make sure that you do not set a pre-master submix output destination that has not been allocated.

@see
SceScreamSndStreamQueueParams, SceScreamSndStartParams, SceScreamSndStreamFileToken, sceScreamQueueToStreamByFileToken(), sceScreamParseStreamFile(), sceScreamStartStream(), sceScreamStartStreamFromTransition()
*/
uint32_t  sceScreamStartStreamByFileToken(SceScreamSndStreamFileToken fileToken, const SceScreamSndStreamQueueParams *queueParams, const SceScreamSndStartParams *startParams, int32_t outputDest /* = SCE_SCREAM_SND_OUTPUT_DEST_MASTER*/);

/**
@ingroup startAndStopFunctions
@brief
Starts a new Stream as a synchronized transition from an existing Stream, or overlays a new Stream in synchronization with an existing Stream.

This function either starts a new Stream in a synchronized transition from an existing Stream, or overlays a new Stream in synchronization with the sync clock Stream.

The returned handle is used as input to numerous Sndstream functions that manipulate or retrieve
information about a Stream. You can also use the handle as input to Scream Library functions, enabling
functionality from the Scream Library API to be applied.

@param
transitionHandle (Input)
Handle of the existing Stream to transition from or to play along with. See &quot;Notes&quot; below.

@param
syncParams (Input)
Pointer to a SceScreamSndSyncParams structure, initialized with appropriate synchronization properties for the new Stream.

@param
transitionParams (Input)
Pointer to a SceScreamSndTransitionParams structure, initialized with appropriate transition properties for the new Stream.

@param
fileParams (Input)
Pointer to a SceScreamSndFileParams structure, initialized with appropriate Stream file parameter values for the new Stream.

@param
startParams (Input)
Pointer to a SceScreamSndStartParams structure, initialized with parameter values for the new Stream. See &quot;Notes&quot; below.

@return
If successful, returns the handle of the new Stream. If not successful, returns 0.

@note
Only one Stream transition on a given Stream handle can be pending at a time.
That is, if you call this function while a previous call with the same
<c><i>transitionHandle</i></c> is still pending (has not yet reached a transition point),
the previous call is flushed in favor of the more recent call, and so on.

@note
If transitioning from a Stream that is set as the current sync clock Stream, note that, at the transition point, the current sync clock Stream therefore terminates.
You have the following options:
<ul>
<li>set the transitioned Stream to become the sync clock Stream following the transition point</li>
<li>continue without a sync clock Stream</li>
<li>start another new Stream and set it as the sync clock Stream</li>
</ul>

@note
To set the transitioned Stream to become the sync clock Stream, include #SCE_SCREAM_SND_SS_START_SYNC_CLOCK in the <c><i>flags</i></c> member of the
SceScreamSndStartParams structure pointed to in the <c><i>startParams</i></c> parameter.

@note
To continue without a sync clock Stream, use #SCE_SCREAM_SND_SYNC_FLAG_START_IF_NO_CLOCK in the <c><i>syncFlags</i></c> member of the #SceScreamSndSyncParams structure pointed to in the <c><i>syncParams</i></c> parameter.

@note
To start another new Stream and set it as the sync clock Stream, start a new Stream by calling sceScreamStartStream().
In this call, use #SCE_SCREAM_SND_SS_START_SYNC_CLOCK in the <c><i>flags</i></c> member of the #SceScreamSndStartParams structure pointed to by the <c><i>startParams</i></c> parameter.

@note
When setting up game-interactive Stream transitions, it is sometimes programmatically possible that a Stream may ultimately transition to the file it is currently playing.
If a Stream attempts to transition back to the beginning of the file it is currently playing, the transition is automatically canceled, allowing the Stream to simply continue playing its current file. This prevents unwanted discontinuities in musical intensity.

@note
For more details, see “Starting a Stream as a Transition from or Overlay with an Existing Stream” in the “Synchronizing Stream Transitions, Overlays, and Scream Sounds” chapter in the <i>Sndstream Library Overview</i>.

@see
SceScreamSndFileParams, SceScreamSndStartParams, sceScreamQueueToStream(), sceScreamStartStream(), sceScreamStartStreamByFileToken(), SceScreamSndSyncParams, SceScreamSndTransitionParams

*/
uint32_t  sceScreamStartStreamFromTransition(uint32_t transitionHandle, const SceScreamSndSyncParams *syncParams, const SceScreamSndTransitionParams *transitionParams, const SceScreamSndFileParams *fileParams, const SceScreamSndStartParams *startParams);

/**
@ingroup startAndStopFunctions
@brief
Stops all currently playing Streams.

Use this function to stop all currently playing Streams.
The sceScreamCloseStreaming() function calls this function.

@note
This function blocks the calling thread until all Streams are stopped.

@note
To stop a single Stream, call the Scream Library function sceScreamStopSound().

@return
Returns #SCE_SCREAM_SND_STREAM_ERROR_OK.

@see
sceScreamWaitForStreamToBeDone(), sceScreamCloseStreaming()
*/
int32_t sceScreamStopAllStreams(void);

/**
@ingroup startAndStopFunctions
@brief
Waits for a Stream to complete playback.

This function blocks the calling thread until the specified Stream has
completed all playback. Since there may be a slight latency involved
in closing a Stream, this function enables coordination of subsequent
actions immediately, but not before, the completion of a
specified Stream. If you call the Scream Library function <c>sceScreamStopSound(<i>handle</i>)</c> and then
call this function with the same handle, your code blocks until
the Stream has actually finished stopping.

@param
handle  (Input)
Handle of the Stream for which to wait for completion.
A value returned by the sceScreamStartStream() or sceScreamStartStreamFromTransition() functions.

@note
To simply check whether a Stream is still playing, use the Scream Library function <c>sceScreamSoundIsStillPlaying()</c>,
with the Stream handle as its only parameter.

@note
This function does not issue any kind of stop command on the Stream.
To stop a single Stream, call the Scream Library function sceScreamStopSound().

@return
Returns #SCE_SCREAM_SND_STREAM_ERROR_OK.

@see
sceScreamStopAllStreams(), sceScreamCloseStreaming()
*/
int32_t sceScreamWaitForStreamToBeDone(uint32_t handle);

// Status

/**
@defgroup statusFunctions Status Functions
@brief
The status functions retrieve information about Streams.
@{*/
/**
@brief
Retrieves the total duration, in seconds, of the currently playing file on a Stream.

This function retrieves the duration of the currently playing file on a Stream.
It stores a floating-point value, representing the total duration (in seconds) of the file, in a user-supplied variable.

@param
handle (Input)
Handle of the Stream to query. A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
outSeconds (Output)
Pointer to a <c>float</c> variable in which to receive the total duration, in seconds, of the currently playing file on the Stream.

@param
outContext (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the user context value assigned to the file by the application in the <c><i>userContext</i></c> member of the SceScreamSndFileParams structure. Can be <c>NULL</c>.

@return
Returns the specified Stream handle if the time information was successfully retrieved.
Otherwise, returns 0.

@note
The duration is obtained in respect of one iteration of the file. Any loop count setting is not considered.

@see
sceScreamCueStreamToTime(), sceScreamGetStreamFileSecondsRemaining(), sceScreamGetStreamFileLocationInSeconds()
*/
uint32_t  sceScreamGetStreamFileLengthInSeconds(uint32_t handle, float *outSeconds, SceScreamSndStreamUserContext *outContext);
/**@}*/

/**
@ingroup statusFunctions
@brief
Retrieves the current playback position, in seconds, of the currently playing file on a Stream.

This function retrieves the current playback position of the currently playing file on a Stream.
It stores a floating-point value, representing the current playback position (in seconds) from the beginning of the file, in a user-supplied variable.
The time is calculated from the current read position as reported by the playback voice being used.

@param
handle (Input)
Handle of the Stream to query. A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
outLocation (Output)
Pointer to a <c>float</c> variable in which to receive the current playback position from the beginning of the file, in seconds, of the currently playing file.

@param
outContext (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the user context value assigned to the file by the application in the <c><i>userContext</i></c> member of the SceScreamSndFileParams structure. Can be <c>NULL</c>.

@return
Returns the specified Stream handle if the time information was successfully retrieved.
Otherwise, returns 0.

@note
Any loop count setting is not considered.

@see
sceScreamCueStreamToTime(), sceScreamGetStreamFileLengthInSeconds(), sceScreamGetStreamFileSecondsRemaining()
*/
uint32_t  sceScreamGetStreamFileLocationInSeconds(uint32_t handle, float *outLocation, SceScreamSndStreamUserContext *outContext);

/**
@ingroup statusFunctions
@brief
Retrieves the number of loops initially assigned and the number of completed loops of the currently playing file on a Stream.

This function retrieves the number of completed loops played on the current file on a specified Stream handle.
The <c><i>outSetting</i></c> parameter receives the initial loop setting assigned to the file by the application
in the <c><i>loopCount</i></c> member of the SceScreamSndFileParams structure. The <c><i>outCount</i></c> parameter receives the number of
completed loops that have already played. If the value received by <c><i>outSetting</i></c> is greater than zero,
you can determine the remaining number of complete loops still to play by subtracting <c><i>outCount</i></c> from
<c><i>outSetting</i></c>.

The initial loop count is set by the #SceScreamSndFileParams <c><i>loopCount</i></c> member.

@param
handle (Input)
Handle of the Stream that the loop count should be retrieved from. A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
outSetting (Output)
Pointer to an <c>int32_t</c> variable in which to receive the loop setting currently assigned to the file by the application in the <c><i>loopCount</i></c> member of the SceScreamSndFileParams structure.
Return values can be interpreted as follows:
<ul>
<li><b>&ndash;2</b>: The file is set to loop until a new file is queued on the same handle; see #SCE_SCREAM_SND_SS_LOOP_TILL_QUEUED.</li>
<li><b>&ndash;1</b>: The file is set to loop indefinitely; see #SCE_SCREAM_SND_SS_LOOP_INFINITE.</li>
<li><b>&ge;0</b>: The file is set to loop a finite number of times. 0 means it was set to play once without looping; 1 means to play twice; 2 means to play 3 times, and so on.</li>
</ul>

@param
outCount (Output)
Pointer to an <c>int32_t</c> variable in which to receive the completed loop count of the playing file.
This value starts at zero and is incremented each time the synthesizer plays the end of the file and starts over.

@param
outContext (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the user context value assigned to the file by the application in the <c><i>userContext</i></c> member of the SceScreamSndFileParams structure. Can be <c>NULL</c>.

@return
Returns the specified Stream handle if the looping information was successfully retrieved. Otherwise, returns 0.

@see
sceScreamSetStreamFileLoopingCount(), sceScreamGetStreamQueueCount(), SceScreamSndFileParams
*/
uint32_t  sceScreamGetStreamFileLoopingCount(uint32_t handle, int32_t *outSetting, int32_t *outCount, SceScreamSndStreamUserContext *outContext);

/**
@ingroup statusFunctions
@brief
Retrieves the remaining duration, in seconds, of the currently playing file on a Stream.

This function retrieves the remaining duration of the currently playing file on a Stream.
It stores a floating-point value, representing the duration (in seconds) from the current playback position to the end of the file, in a user-supplied variable.
The time is calculated from the current read position as reported by the playback voice being used.

@param
handle (Input)
Handle of the Stream to query. A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
outSeconds (Output)
Pointer to a <c>float</c> variable in which to receive the remaining duration, in seconds, of the currently playing file on the Stream.

@param
outContext (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the user context value assigned to the file by the application in the <c><i>userContext</i></c> member of the SceScreamSndFileParams structure. Can be <c>NULL</c>.

@return
Returns the specified Stream handle if the time information was successfully retrieved. Otherwise, returns 0.

@note
Any loop count setting is not considered.

@see
sceScreamCueStreamToTime(), sceScreamGetStreamFileLengthInSeconds(), sceScreamGetStreamFileLocationInSeconds()
*/
uint32_t  sceScreamGetStreamFileSecondsRemaining(uint32_t handle, float *outSeconds, SceScreamSndStreamUserContext *outContext);

/**
@ingroup statusFunctions
@brief
Sets the remaining number of loops for the currently playing file on a Stream.

This function sets or updates the remaining number of complete loops for the currently playing file
on a specified Stream handle. A Stream can have multiple queued files, however, the new loop count is
applied only to the currently playing file.

Setting a value of zero stops playback of the file at the end of its current cycle,
then immediately begins playback of the next queued file on the same handle, if
any. A value of 1 specifies playback of one more complete loop after the current
cycle.  A value of 2 specifies playback of two more complete loops after the current
cycle, and so on. Setting #SCE_SCREAM_SND_SS_LOOP_INFINITE specifies indefinite looping.
Setting #SCE_SCREAM_SND_SS_LOOP_TILL_QUEUED specifies looping until a new file is queued on the same handle;
at which time playback continues to the end of the current cycle, and then begins playback of
the new file.

The initial loop count is set by the #SceScreamSndFileParams <c><i>loopCount</i></c> member.

@param
handle (Input)
Handle of the Stream to which the loop count should be applied. A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
loopCount (Input)
New loop count value to apply to the Stream. See &quot;Description&quot; below for possible settings.

@return
Returns the specified Stream handle if the Stream is still active. Otherwise, returns 0.

@note
Use the sceScreamGetStreamFileLoopingCount() function to retrieve the number of completed loops and to determine the remaining number of remaining loops.
Use the sceScreamGetStreamQueueCount() function to get the number of files currently queued on the Stream.

@see
sceScreamGetStreamFileLoopingCount(), sceScreamGetStreamQueueCount(), SceScreamSndFileParams
*/
uint32_t  sceScreamSetStreamFileLoopingCount(uint32_t handle, int32_t loopCount);

/**
@ingroup statusFunctions
@brief
Retrieves buffered status, Bitstream count, channel count, and sample rate information from a Stream handle.

This function queries a Stream, then stores buffered status, Bitstream count, channel count, and sample rate information in user-supplied variables.
The function checks the Stream handle to see if it is still valid, and if so, the Stream's buffered status is queried.
If the Stream is buffered, the Stream file's Bitstream count, channel count, and sample rate are also queried.
If the Stream is not buffered, zero is stored in the variables referenced in the <c><i>outBufferedStatus</i></c>, <c><i>outBitstreamCount</i></c>, <c><i>outChannelCount</i></c>, and <c><i>outSampleRate</i></c> parameters.

@param  handle  (Input)
Handle of the Stream to query.
A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param  outBufferedStatus  (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the buffered status. If the Stream is buffered,
a non-zero value is returned.

@param  outBitstreamCount  (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the number of Bitstreams in the
Stream. If the Stream is not buffered, a zero value is returned. Can be <c>NULL</c>. <b>Note:</b> Multiple Bitstreams are not supported in this release. Bitstream count is therefore 1.

@param  outChannelCount  (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the number of channels (per Bitstream) in the Stream.
If the Stream is not buffered, a zero value is returned. Can be <c>NULL</c>.

@param  outSampleRate  (Output)
Pointer to a <c>float</c> variable in which to receive the sample rate of the Stream. If the
Stream is not buffered, a zero value is returned. Can be <c>NULL</c>.

@return
Returns the specified Stream handle if the handle is still valid.
Otherwise, returns 0.

@see
sceScreamStartStream(), sceScreamGetStreamQueueCount()
*/
uint32_t  sceScreamGetStreamInfo(uint32_t handle, uint32_t *outBufferedStatus, uint32_t *outBitstreamCount,
                                 uint32_t *outChannelCount, float *outSampleRate);

/**
@ingroup statusFunctions

@brief
Retrieves the number of files queued on a Stream.

This function retrieves the count of queued files on the specified Stream handle that have not yet played, not including the actively
playing Stream, even if it is paused. A maximum of #SCE_SCREAM_SND_FILE_QUEUE_MAX files can be queued on a Stream handle.

@param
handle (Input)
Handle of the Stream to query. A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
outQueueCount (Output)
Pointer to a <c>uint32_t</c> variable in which to receive count of items queued on the Stream handle.
A value of zero can indicate either that the handle has no queued items but may still be playing an active Stream, or is not active at all.

@return
Returns the specified Stream handle if the queue count was successfully retrieved.
Otherwise, returns 0.

@see
sceScreamGetStreamInfo(), sceScreamQueueToStream(), sceScreamQueueToStreamByFileToken()
*/
uint32_t  sceScreamGetStreamQueueCount(uint32_t handle, uint32_t *outQueueCount);

/**
@ingroup statusFunctions

@brief
Retrieves the current voice level of a Stream.

This function retrieves the current voice level of a Stream.
The returned voice level is either a RMS or instantaneous peak level, and expressed either on a linear or decibel (dB) scale.

@param
handle (Input)
Handle of the Stream to query. A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param
rms (Input)
Set to <c>TRUE</c> if you want the result as an averaged RMS level. Otherwise, the result is an instantaneous peak level.

@param
linear (Input)
Set to <c>TRUE</c> if you want the result on a linear scale. Otherwise, the result is expressed in decibels (dB).

@return
If successful, returns a Stream's current voice level in the requested format. Otherwise, returns 0.

@note
To retrieve voice level from a Stream, it must have been initialized with the #SCE_SCREAM_SND_SS_START_GET_VOICE_LEVEL option included in the Stream's SceScreamSndStartParams <c><i>flags</i></c> member.

@see
sceScreamGetStreamInfo(), SceScreamSndStartParams, #SCE_SCREAM_SND_SS_START_GET_VOICE_LEVEL
*/
float  sceScreamGetStreamLevel(uint32_t handle, bool rms, bool linear);


// Pre-parsed Sound Files

/**
@defgroup fileTokenFunctions File Token Functions
@brief
These functions manipulate Stream file tokens.
@{*/

/**
@brief
Parses an audio file and stores header information in a file token.

This function parses an audio file (intended for streaming), gathering information from the file's header and storing it in a file token.
The returned token can be used as input to the sceScreamStartStreamByFileToken() and sceScreamQueueToStreamByFileToken() functions, which respectively, start or queue Stream files by reference to a file token.
Tokens can be stored for future use in a #SceScreamSndStreamFileTokenStorage with the sceScreamCreateFileTokenStorage() function and then retrieved by sceScreamGetFileTokenFromStorage().

For further information about working with file tokens, see the &quot;Working with File Tokens&quot; chapter of the <i>Sndstream Library Overview</i>
or the Pre-parse sample program.

@param
parseParams (Input)
Pointer to a SceScreamSndStreamParseParams structure, appropriately initialized for the associated Stream file.

@param
errorCodePtr (Output)
Pointer to a variable in which to receive an error code (see \link #SCE_SCREAM_SND_STREAM_ERROR_OK General Errors\endlink ), or zero if no error occurs.

@return
If successful, returns a valid #SceScreamSndStreamFileToken. Otherwise returns #SCE_SCREAM_SND_STREAM_INVALID_FILE_TOKEN.

@see
sceScreamStartStreamByFileToken(), sceScreamQueueToStreamByFileToken(), SceScreamSndStreamParseParams, sceScreamDeleteStreamFileToken(), sceScreamCreateFileTokenStorage(), sceScreamGetFileTokenFromStorage()
*/
SceScreamSndStreamFileToken sceScreamParseStreamFile(const SceScreamSndStreamParseParams *parseParams, int32_t *errorCodePtr );
/**@}*/

/**
@ingroup fileTokenFunctions
@brief
Marks a file token as unused.

This function deletes (marks as unused) a file token.
You can delete a file token any time after the corresponding Stream file is queued.
This is because the pre-parsed header information that is contained in the token and needed during playback is copied into the queue.

@param
fileToken (Input)
The file token to delete, as returned by the sceScreamParseStreamFile() or sceScreamGetFileTokenFromStorage() functions.

@return
Returns #SCE_SCREAM_SND_STREAM_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SND_STREAM_ERROR_NOT_FOUND if the file token was not found.

@see
sceScreamParseStreamFile(), sceScreamGetFileTokenFromStorage(), sceScreamStartStreamByFileToken(), sceScreamQueueToStreamByFileToken()
*/
int32_t sceScreamDeleteStreamFileToken(SceScreamSndStreamFileToken fileToken);

/**
@ingroup fileTokenFunctions
@brief
Creates a Stream file token storage.

This function creates a Stream file token storage that can contain one or more file tokens.
You can create a storage at build time, and save it in a file.
At run time, you can then use the file token storage to reduce processing load.

For further information about working with file tokens, see the &quot;Working with File Tokens&quot; chapter of the <i>Sndstream Library Overview</i>
or the Pre-parse sample program.

@param
tokens (Input)
Pointer to an array of file tokens. Obtain a file token with the sceScreamParseStreamFile() function.

@param
numTokens (Input)
Number of file tokens in the array specified in <c><i>tokens</i></c>.

@param
sizePtr (Output)
Pointer to a variable in which to receive the size of the resulting structure.
This is needed if you want to save the storage to disk.

@return
If successful, returns a pointer to a file token storage. Otherwise returns <c>NULL</c>.

@see
sceScreamValidateFileTokenStorage(), sceScreamByteReverseFileTokenStorage(), sceScreamDeleteFileTokenStorage(), sceScreamGetFileTokenFromStorage(), sceScreamParseStreamFile()
*/
SceScreamSndStreamFileTokenStorage *sceScreamCreateFileTokenStorage( SceScreamSndStreamFileToken *tokens,
                                                                     uint32_t numTokens, uint32_t *sizePtr );

/**
@ingroup fileTokenFunctions
@brief
Reverses the endianness of values contained in a file token storage.

The function reverses the endianness of values contained in a file token storage.
You use this function if you are creating a storage on a computer with a different endianness from that of the target platform.
For example, if you build on Windows and run on the PlayStation®3 platform, you would need to reverse the endianness.
This can be done once on the build machine, avoiding use of runtime cycles on the target platform.

Create a #SndStreamFileTokenStorage instance by calling sceScreamCreateFileTokenStorage().

@param
storage (Input)
#SceScreamSndStreamFileTokenStorage pointer to a storage to be endianness-reversed.

@return
If successful, returns zero. Otherwise returns a negative error code.

@see
sceScreamCreateFileTokenStorage(), sceScreamDeleteFileTokenStorage(), sceScreamValidateFileTokenStorage(), sceScreamGetFileTokenFromStorage()
*/
int32_t sceScreamByteReverseFileTokenStorage( SceScreamSndStreamFileTokenStorage *storage );

/**
@ingroup fileTokenFunctions
@brief
Deletes a file token storage.

This function deletes a file token storage.
After calling this function, the specified storage is invalidated, so that any tokens contained within it are unusable.

Use this function only for storage areas created using the sceScreamCreateFileTokenStorage() function.

@note
Stream files that have already been queued or started playback are unaffected by deletion of an associated file token storage.
This is because the contents of file tokens are copied into the corresponding queue.

@param
storage (Input)
#SceScreamSndStreamFileTokenStorage pointer to a storage to delete.

@return
If successful, returns #SCE_SCREAM_SND_STREAM_ERROR_OK. Otherwise returns a negative error code.

@see
sceScreamCreateFileTokenStorage(), sceScreamValidateFileTokenStorage(), sceScreamGetFileTokenFromStorage()
*/
int32_t sceScreamDeleteFileTokenStorage( SceScreamSndStreamFileTokenStorage *storage );

/**
@ingroup fileTokenFunctions
@brief
Validates the correctness of a file token storage.

This function verifies the correctness of a file token storage.
You call this function before retrieving a file token from a storage with the sceScreamGetFileTokenFromStorage() function.
The function verifies the appropriate endianness, version, and integrity of the storage.
The function may also make changes in the storage, so the storage should reside in read-write memory.

@param
storage (Input)
Pointer to a file token storage.
Returned by the sceScreamCreateFileTokenStorage() function when the storage was created.

@param
storageSize (Input)
The size, in bytes, that the storage occupies.
Saved by the sceScreamCreateFileTokenStorage() function into a variable specified by its <c><i>sizePtr</i></c> parameter.
<b>Note:</b> To bypass file token storage size checking, you can set this parameter to zero.

@return
If successful, returns zero. Otherwise returns a negative error code.

@see
sceScreamCreateFileTokenStorage(), sceScreamDeleteFileTokenStorage(), sceScreamByteReverseFileTokenStorage(), sceScreamGetFileTokenFromStorage()
*/
int32_t sceScreamValidateFileTokenStorage( SceScreamSndStreamFileTokenStorage *storage, uint32_t storageSize );

/**
@ingroup fileTokenFunctions
@brief
Retrieves a file token from a specified storage loaded from a file.

This function retrieves a file token from a specified file token storage loaded from a file.
The returned token can be used as input to the sceScreamStartStreamByFileToken() and sceScreamQueueToStreamByFileToken() functions,
which respectively, start or queue Stream files by reference to a file token.

Note that a file token is an opaque pointer into an associated file token storage.
So if you delete a token storage with sceScreamDeleteFileTokenStorage(), the tokens it contains become invalid.

@param
storage (Input)
Pointer to a file token storage.
Returned by the sceScreamCreateFileTokenStorage() function when the storage was created.

@param
tokenIndex (Input)
Zero-based index of the token to retrieve.

@param
parseParams (Input)
Pointer to a SceScreamSndStreamParseParams structure, initialized when the file token being retrieved was created with the sceScreamParseStreamFile() function.
The SceScreamSndStreamParseParams structure contains a path pointer that is used to reopen the Stream file in asynchronous mode when streaming.

@return
If successful, returns a valid #SceScreamSndStreamFileToken. Otherwise returns #SCE_SCREAM_SND_STREAM_INVALID_FILE_TOKEN.

@see
SceScreamSndStreamParseParams, sceScreamCreateFileTokenStorage(), sceScreamDeleteFileTokenStorage(), sceScreamValidateFileTokenStorage(), sceScreamStartStreamByFileToken(), sceScreamQueueToStreamByFileToken(), sceScreamParseStreamFile()
*/
SceScreamSndStreamFileToken sceScreamGetFileTokenFromStorage( SceScreamSndStreamFileTokenStorage *storage, uint32_t tokenIndex,
                                                              const SceScreamSndStreamParseParams *parseParams );

// File IO

/**
@defgroup fileSystemFunctions File System Functions
@brief
Sets a custom file i/o interface.
@{*/
/**
@brief
Overrides the default file I/O functions with custom file I/O functions.

This function allows the default file I/O functions to be overridden with custom file I/O functions.
To override the defaults and use custom file I/O functions:
<ol>
<li>Ensure that your custom file functions match the file I/O type definitions. See #SceScreamSndStreamFileOpenFunction, and so on.</li>
<li>Store their addresses as the corresponding members of the #SceScreamSndFileInterface data structure.</li>
<li>After initializing Sndstream and before calling any other Sndstream functions, call this function with the initialized #SceScreamSndFileInterface data structure as its argument.</li>
</ol>

For further information, see “Using Custom File I/O Functions” in &quot;Working with System Globals&quot; chapter of the <i>Sndstream Library Overview</i>.

@param fileInterface (Input) Pointer to a SceScreamSndFileInterface structure initialized with the addresses of the custom file I/O functions.

@return
Returns #SCE_SCREAM_SND_STREAM_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SND_STREAM_ERROR_OUT_OF_RANGE if <c><i>fileInterface</i></c> is NULL.

@see
SceScreamSndFileInterface, SceScreamSndStreamFileOpenFunction(), SceScreamSndStreamFileInfoCBFunction(), SceScreamSndStreamFileSeekFunction(), SceScreamSndStreamFileReadFunction(), SceScreamSndStreamFileCloseFunction()
*/
int32_t sceScreamSetDefaultFileInterface(SceScreamSndFileInterface *fileInterface);

/**@}*/

// Sync Play

/**
@defgroup synchronizedPlayFunctions Synchronized Play Functions
@brief
Synchronized play functions play Scream Sounds in synchronization with Streams.
@{*/

/**
@brief
Retrieves the handle of the current sync clock Stream.

This function retrieves the handle of the Stream currently providing the master sync clock.
The sceScreamStartStreamFromTransition() function sets the current sync clock Stream.

@return
Returns the sync clock Stream handle, if there is one.
Otherwise, returns 0.

@see
sceScreamPlaySoundSyncedByIndexEx(), sceScreamPlaySoundSyncedByNameEx(), sceScreamStartStreamFromTransition()
*/
uint32_t  sceScreamGetCurrentSyncClockStreamHandle(void);
/**@}*/

/**
@ingroup synchronizedPlayFunctions
@brief
Plays a Scream Sound in synchronization with the sync clock, by reference to its index.

This function plays a Scream Sound in synchronization with the sync clock, and by reference to its index within a Sound Bank.

@param bank (Input)
SceScreamSFXBlock2 pointer to the bank that contains the Sound to play. A <c>SceScreamSFXBlock2</c> handle is returned by the Scream Library functions <c>sceScreamBankLoadEx()</c>, <c>sceScreamBankLoadFromMemEx()</c>, or <c>sceScreamFindLoadedBankByName()</c>.

@param index (Input)
Zero-based index of the requested Sound within its bank.

@param params (Input)
Pointer to an initialized Scream Library <c>SceScreamSoundParams</c> structure containing Sound parameter settings.

@param syncParams (Input)
Pointer to an initialized #SceScreamSndSyncParams structure containing synchronization properties.

@return
Returns the handle of the requested Sound. Returns 0 if the specified <c><i>index</i></c> is out of range or if SceScreamSoundParams.size specified in the <c><i>params</i></c> member is invalid.

@note
To play a Scream Sound by reference to its index within a Sound Bank &mdash; without synchronization &mdash; use the Scream Library function <c>sceScreamPlaySoundByIndexEx()</c>.

@see
sceScreamGetCurrentSyncClockStreamHandle(), sceScreamPlaySoundSyncedByNameEx()
*/
uint32_t  sceScreamPlaySoundSyncedByIndexEx(const SceScreamSFXBlock2 *bank, int16_t index, const SceScreamSoundParams *params, const SceScreamSndSyncParams *syncParams);

/**
@ingroup synchronizedPlayFunctions
@brief
Plays a Scream Sound in synchronization with the sync clock, by reference to its name.

This function plays a Scream Sound in synchronization with the sync clock, and by reference to its name within a Sound Bank.

@param bank (Input)
SceScreamSFXBlock2 pointer to the bank that contains the Sound to play. A <c>SceScreamSFXBlock2</c> handle is returned by the Scream Library functions <c>sceScreamBankLoadEx()</c>, <c>sceScreamBankLoadFromMemEx()</c>, or <c>sceScreamFindLoadedBankByName()</c>.
Can also be <c>NULL</c>. See &quot;Notes&quot; below.

@param name (Input)
Name of the requested Sound within its bank.

@param params (Input)
Pointer to an initialized Scream Library <c>SceScreamSoundParams</c> data structure containing Sound parameter settings.

@param syncParams (Input)
Pointer to an initialized #SceScreamSndSyncParams structure containing synchronization properties.

@return
Returns the handle of the requested Sound. Returns 0 if the specified <c><i>name</i></c> or SceScreamSoundParams.size specified in the <c><i>params</i></c> member is invalid.

@note
If <c><i>bank</i></c> is <c>NULL</c>, this function searches through all registered Sound Banks
and plays the first Sound it finds having the specified <c><i>name</i></c>.

@note
To play a Scream Sound by reference to its name within a Sound Bank &mdash; without synchronization &mdash; use the Scream Library function <c>sceScreamPlaySoundByNameEx()</c>.

@see
sceScreamGetCurrentSyncClockStreamHandle(), sceScreamPlaySoundSyncedByIndexEx()
*/
uint32_t  sceScreamPlaySoundSyncedByNameEx(const SceScreamSFXBlock2 *bank, const char *name, const SceScreamSoundParams *params, const SceScreamSndSyncParams *syncParams);



// Layer Support

/**
@defgroup layerFunctions Layer Functions
@brief
These functions retrieve information, and manipulate Layers in a multi-Layer Stream file.
@{*/
/**
@ingroup layerFunctions

@brief
Retrieves the number of Layers associated with a Stream handle.

This function retrieves the number of Layers associated with a specified Stream handle.

@note
For standard Streams that do not contain multiple Layers, the returned count is 1.

@note
The maximum number of Layers permissible on a Stream is defined by the system constant #SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS.

@param handle (Input)
Handle of a Stream to query. A value returned by the sceScreamStartStream(), sceScreamQueueToStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@return
If successful, returns the number of Layers. Otherwise, returns zero.

@see
sceScreamGetStreamLayerCountByFileToken(), sceScreamGetStreamLayerHandle()
*/
int32_t sceScreamGetStreamLayerCountByHandle( uint32_t handle );

/**
@ingroup layerFunctions

@brief
Retrieves the number of Layers associated with a Stream by file token reference.

This function retrieves the number of Layers associated with a Stream, referenced by its file token.

@note
The maximum number of Layers permissible on a Stream is defined by the system constant #SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS.

@param
fileToken (Input)
The file token to query, as returned by the sceScreamParseStreamFile() or sceScreamGetFileTokenFromStorage() functions.

@return
If successful, returns the number of Layers. Otherwise, returns #SCE_SCREAM_SND_STREAM_INVALID_FILE_TOKEN.

@see
SceScreamSndStreamFileToken, sceScreamParseStreamFile(), sceScreamGetFileTokenFromStorage(), sceScreamGetStreamLayerCountByHandle(), sceScreamGetStreamLayerHandle()
*/
int32_t sceScreamGetStreamLayerCountByFileToken( SceScreamSndStreamFileToken fileToken );

/**
@ingroup layerFunctions

@brief
Retrieves the handle of an individual Stream Layer.

This function retrieves the handle of an individual Layer contained within a multi-Layer Stream.

You can reference Stream Layer handles when using the Scream functions sceScreamSetSoundParamsEx(), sceScreamAutoGain(), and sceScreamAutoPan().
This allows you to set parameters or to automate gain and pan changes on individual Layers.
For further details, see the &quot;Working with Multi-Layer Streams&quot; chapter of the <i>Sndstream Library Overview</i>.

@param handle (Input)
Handle of a Stream from which to retrieve a Layer handle.
A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param layerIndex (Input)
Zero-based index of a Layer for which to obtain a handle.
Range: Zero to the number of Layers in the Stream minus one.
You can obtain the number of Layers using the sceScreamGetStreamLayerCountByHandle() or sceScreamGetStreamLayerCountByFileToken() functions.

@note
For standard Streams that contain one Layer only, the returned Layer handle is the same as the specified Stream <c><i>handle</i></c>.

@note
Layer handles can only be used with the following Scream functions: sceScreamSetSoundParamsEx(), sceScreamAutoGain(), and sceScreamAutoPan().

@note
Do not use Layer handles as arguments to the Scream sceScreamStopSound() function to stop a Layer.
You cannot stop individual Layers. You must stop Layers collectively by stopping the containing Stream.

@return
If successful, returns the specified Layer handle. Otherwise, returns 0.

@see
sceScreamGetStreamLayerCountByHandle(), sceScreamGetStreamLayerCountByFileToken()
*/
uint32_t sceScreamGetStreamLayerHandle( uint32_t handle, uint32_t layerIndex );

/**
@brief
Retrieves Layer gain, azimuth, and focus parameters values.

This function retrieves gain, azimuth, and focus parameter values for all Layers associated with a Stream handle.
The function stores retrieved parameter values in a SceScreamSndBitstreamParams structure.

@param handle (Input)
Handle of a Stream from which to retrieve Layer parameter values.
A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param params (Output)
Pointer to a SceScreamSndBitstreamParams structure into which to store the retrieved parameter values.

@param layerCountPtr (Output)
Pointer to a <c>uint32_t</c> variable in which to store a count of the number of Layers from which parameters were retrieved.
Set to <c>NULL</c> if count information is not required.

@return
Returns the specified Stream <c><i>handle</i></c> if its Layer parameters were successfully retrieved.
Otherwise, returns 0 if the specified <c><i>handle</i></c> is invalid.

@see
SceScreamSndBitstreamParams, sceScreamSetStreamLayerParams()
*/
uint32_t sceScreamGetStreamLayerParams( uint32_t handle, SceScreamSndBitstreamParams *params, uint32_t* layerCountPtr );
/**@}*/

/**
@ingroup layerFunctions

@brief
Sets Layer gain, azimuth, and focus parameters.

This function sets Layer gain, azimuth, and focus parameter values, individually, for a specified number of Layers associated with a Stream handle, starting at the first Layer.

@param handle (Input)
Handle of a Stream containing Layers upon which to set parameters.
A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param params (Input)
Pointer to a SceScreamSndBitstreamParams structure, specifying parameter values for each Layer.

@param layerCount (Input)
The number of Layers upon which to set parameters.
Specifies the length of the arrays used in the SceScreamSndBitstreamParams structure pointed to in <c><i>params</i></c>.
You can obtain the number of Layers using the sceScreamGetStreamLayerCountByHandle() or sceScreamGetStreamLayerCountByFileToken() functions.

@return
Returns a count of the number of Layers upon which parameters were successfully set.
Otherwise, returns 0 if the specified <c><i>handle</i></c> or <c><i>params</i></c> structure is invalid.

@see
SceScreamSndBitstreamParams, sceScreamGetStreamLayerParams(), sceScreamAutoStreamLayerParams()
*/
uint32_t sceScreamSetStreamLayerParams( uint32_t handle, const SceScreamSndBitstreamParams *params, uint32_t layerCount );

/**
@ingroup layerFunctions

@brief
Automates Layer gain and azimuth changes over a specified time.

This function automates smooth gain and azimuth changes on Layers over time periods specified in the <c><i>timeToTarget</i></c> parameter.
Changes are made to the specified number of Layers associated with the Stream handle, starting at the first Layer.

@param handle (Input)
Handle of a Stream containing Layers upon which to automate parameter changes.
A value returned by the sceScreamStartStream(), sceScreamStartStreamByFileToken(), or sceScreamStartStreamFromTransition() functions.

@param params (Input)
Pointer to a SceScreamSndBitstreamParams structure, specifying target parameter values for each Layer.

@param layerCount (Input)
The number of Layers upon which to automate parameters.
Specifies the length of the arrays used in the SceScreamSndBitstreamParams structure pointed to in <c><i>params</i></c>.

@param timeToTarget (Input)
Time taken to reach the target parameter values. Expressed in seconds, as an array of time values, one for each Layer.

@param behaviorFlags (Input)
Zero or more of the \link #SCE_SCREAM_SND_AUTO_STOP_AT_DESTINATION Automated Parameter Change Flags\endlink, expressed in an array, one value per Layer.
Use the <c>OR</c> operator for multiple selections.

@return
Returns the number of Layers upon which parameters were successfully automated.
Otherwise, returns 0 if the specified <c><i>handle</i></c> is invalid.

@note
The <c><i>timeToTarget</i></c> and <c><i>behaviorFlags</i></c> parameters apply to gain and azimuth changes only. That is, they do not affect focus settings.

@note
Azimuth values must be expressed in degrees &mdash;, not as specific speaker target constants.

@see
SceScreamSndBitstreamParams, sceScreamGetStreamLayerParams(), sceScreamSetStreamLayerParams()
*/
uint32_t sceScreamAutoStreamLayerParams( uint32_t handle, const SceScreamSndBitstreamParams *params,
                                         uint32_t layerCount,
                                         float32_t timeToTarget[SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS],
                                         uint32_t behaviorFlags[SCE_SCREAM_SND_STREAM_MAX_BITSTREAMS] );

#if (defined(_cplusplus) || defined(__cplusplus))
}
#endif


#endif // _DOLCESDK_PSP2_SCREAM_SCE_SNDSTREAM_H_

