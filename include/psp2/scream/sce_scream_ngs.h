#ifndef _DOLCESDK_PSP2_SCREAM_SCE_SCREAM_NGS_H_
#define _DOLCESDK_PSP2_SCREAM_SCE_SCREAM_NGS_H_

#include <stdbool.h>

#include <psp2/scream/sce_snd_data.h>

// System Constants
/**
@defgroup ngsSystemConstants NGS System Constants
@brief NGS System constants impose limits for various system resources and frequently-used parameters.
@{*/
#define SCE_SCREAM_SND_MAX_REVERBS                              3           ///< The maximum number of reverb voices. See the SceScreamSystemParams structure's <c><i>numReverbs</i></c> member.
#define SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES                   4           ///< The maximum number of premaster submix voices. See the  Scream SceScreamSystemParams structure's <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members, as well as the Sndstream functions sceScreamStartStream() and sceScreamStartStreamByFileToken() <c><i>outputDest</i></c> parameter.
/**@}*/

// System defaults.
/**
@defgroup ngsSystemDefaults NGS System Defaults
@brief NGS System defaults are values used by the sceScreamFillDefaultScreamPlatformInitArgsEx2() function when filling a SceScreamPlatformInitEx2 structure with default values.
@{*/
#define SCE_SCREAM_SND_DEFAULT_THREAD_PRIORITY          128                 ///< Default thread priority. See the Scream SceScreamSystemParams <c><i>tickThreadPriority</i></c> member, and the Sndstream <c>SceScreamSndStreamPlatformInit</c> structure’s <c><i>streaming_thread_priority</i></c> and <c><i>parsing_thread_priority</i></c> members.

#define SCE_SCREAM_SND_DEFAULT_THREAD_AFFINITY          -1                  ///< Default thread affinity CPU. See the SceScreamSystemParams <c><i>tickThreadAffinity</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_THREAD_STACK_SIZE        (128*1024)          ///< Default thread stack size. See the SceScreamSystemParams <c><i>tickThreadStackSize</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_NUM_VAG_MONO_VOICES      64                  ///< Default maximum number of mono VAG voices to allocate on the NGS synthesizer.
#define SCE_SCREAM_SND_DEFAULT_NUM_PCM_MONO_VOICES      16                  ///< Default maximum number of mono PCM voices to allocate on the NGS synthesizer.
#define SCE_SCREAM_SND_DEFAULT_NUM_AT9_MONO_VOICES      32                  ///< Default maximum number of mono ATRAC9&trade; voices to allocate on the NGS synthesizer.
#define SCE_SCREAM_SND_DEFAULT_NUM_VAG_STEREO_VOICES    8                   ///< Default maximum number of stereo VAG voices to allocate on the NGS synthesizer.
#define SCE_SCREAM_SND_DEFAULT_NUM_PCM_STEREO_VOICES    8                   ///< Default maximum number of stereo PCM voices to allocate on the NGS synthesizer.
#define SCE_SCREAM_SND_DEFAULT_NUM_AT9_STEREO_VOICES    8                   ///< Default maximum number of stereo ATRAC9&trade; voices to allocate on the NGS synthesizer.

#define SCE_SCREAM_SND_DEFAULT_NUM_REVERBS              1                   ///< Default number of reverb voices. See the SceScreamSystemParams <c><i>numReverbs</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_NUM_PREMASTER_COMP_SUBMIXES      0           ///< Default number of pre-master compressor submix voices to create.  See the SceScreamSystemParams <c><i>numPremasterCompSubmixes</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_NUM_PREMASTER_SC_COMP_SUBMIXES   0           ///< Default number of pre-master side-chain compressor submix voices to create.  See the SceScreamSystemParams <c><i>numPremasterScCompSubmixes</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_SYNTH_INIT_FLAGS                 0           ///< Default NGS synth initialization flags. See the SceScreamSystemParams <c><i>initFlags</i></c> member.
/**@}*/

// Synth initialization flags
/**
@defgroup ngsInitializationFlags NGS Initialization Flags
@brief
You apply NGS synth initialization flags to the SceScreamSystemParams <c><i>initFlags</i></c> member when initializing Scream.
@{*/
#define SCE_SCREAM_SND_SYNTH_INIT_FLAG_VALIDATE_PARAMS          (1L << 0)   ///< Enables validation of DSP parameter arguments with respect to the NGS synthesizer. If out-of-range values are encountered, appropriate warnings are output to the TTY.
#define SCE_SCREAM_SND_SYNTH_INIT_FLAG_THREAD_MODE_DUAL         (1L << 1)   ///< Causes the Scream tick to run in a separate thread from the synthesizer update/audio output thread. Both threads share the same priority, CPU affinity, and stack size settings.
#define SCE_SCREAM_SND_SYNTH_INIT_FLAG_DISABLE_LEVELS           (1L << 2)   ///< Prevents Scream from calculating peak or RMS output levels arising from synthesizer output. Valid for NGS only.
/**@}*/


// Voice data type constants
/**
@defgroup ngsVoiceDataTypeConstants Voice Data Type Constants
@brief NGS voice data type constants are values you can use for the sceScreamGetAllocatedVoiceCountByType() function's <c><i>dataType</i></c> parameter.
@{*/
#define SCE_SCREAM_SND_VOICE_DATA_TYPE_VAG              (0)         ///< Mono VAG-encoded (ADPCM) voice data type.
#define SCE_SCREAM_SND_VOICE_DATA_TYPE_PCMI16           (1)         ///< Mono 16-bit fixed-point PCM voice data type.
#define SCE_SCREAM_SND_VOICE_DATA_TYPE_AT9              (2)         ///< Mono ATRAC9&trade;-encoded (AT9) voice data type.
#define SCE_SCREAM_SND_VOICE_DATA_TYPE_VAG_STEREO       (3)         ///< Stereo (two-channel) VAG-encoded (ADPCM) voice data type.
#define SCE_SCREAM_SND_VOICE_DATA_TYPE_PCMI16_STEREO    (4)         ///< Stereo (two-channel) 16-bit fixed-point PCM voice data type.
#define SCE_SCREAM_SND_VOICE_DATA_TYPE_AT9_STEREO       (5)         ///< Stereo (two-channel) ATRAC9&trade;-encoded (AT9) voice data type.
#define SCE_SCREAM_SND_VOICE_DATA_TYPE_COUNT            (6)         ///< Total number of supported voice types.
/**@}*/

#define SCE_SCREAM_SND_POLPAN_MAX_SPEAKERS             8       ///< Maximum length of an array of custom speaker azimuths.

// Buss type definitions
/**
@defgroup ngsBussTypes NGS Buss Types
@brief NGS buss types are return values for the sceScreamGetBussPresetType() function.
@{*/
#define SCE_SCREAM_SND_BUSS_TYPE_UNKNOWN                (-1)        ///< A specified name is invalid or the system was unable to determine the buss type.
#define SCE_SCREAM_SND_BUSS_TYPE_MASTER_BUSS            (0)         ///< The master buss.
#define SCE_SCREAM_SND_BUSS_TYPE_PREMASTER_SUBMIX       (1)         ///< A pre-master submix buss.
#define SCE_SCREAM_SND_BUSS_TYPE_REVERB                 (2)         ///< An auxiliary (or reverb) buss.
#define SCE_SCREAM_SND_BUSS_TYPE_COUNT                  (3)         ///< The number of buss types.
/**@}*/

/**
@defgroup ngsDataStructures NGS Data Structures
@brief NGS data structures store NGS-specific API data.
@{*/

/**
@brief
Stores rendering synthesizer parameters values for the NGS synthesizer. This is embedded in the SceScreamPlatformInitEx2 structure used when calling sceScreamStartSoundSystemEx2() to initialize Scream.

This structure stores parameter values for the NGS rendering synthesizer running on PlayStation&reg;Vita.
It is embedded in the SceScreamPlatformInitEx2 structure in the <c><i>synthParams</i></c> member.
And, along with SceScreamPlatformInitEx2, it is initialized with default values with a call to sceScreamFillDefaultScreamPlatformInitArgsEx2().

@note
The <c><i>voiceTypeCount</i></c> member takes an array of values specifying a maximum number of voices to allocate for each respective voice type.
In the event that an application requests more voices at one time than are available on the synthesizer, voice management is controlled by prioritization.
It is permissible for the combined total of <c><i>voiceTypeCount</i></c> array values to be greater than the number of voices that Scream can simultaneously address, as returned by sceScreamGetMaxPolyphony().
For further details, see &quot;Allocating Synthesizer Voice Types&quot; in the &quot;Configuration, Initialization, and Shutdown&quot; chapter of the <i>Scream Library Overview</i>.

@see
SceScreamPlatformInitEx2, sceScreamFillDefaultScreamPlatformInitArgsEx2(), sceScreamGetMaxPolyphony()
*/
typedef struct SceScreamSystemParams
{
    int32_t               tickThreadPriority;           ///< Priority value to use when creating the synthesizer thread that ticks the Scream runtime. Defaults to #SCE_SCREAM_SND_DEFAULT_THREAD_PRIORITY.
    int32_t               tickThreadAffinity;           ///< CPU affinity with which to create the synthesizer thread that ticks the Scream runtime. Range: -1 to 2. A value of -1 indicates all cores.  Defaults to #SCE_SCREAM_SND_DEFAULT_THREAD_AFFINITY.
    uint32_t              tickThreadStackSize;          ///< Size of the stack used for audio output and the Scream tick thread. Defaults to #SCE_SCREAM_SND_DEFAULT_THREAD_STACK_SIZE.
    uint32_t              voiceTypeCount[SCE_SCREAM_SND_VOICE_DATA_TYPE_COUNT];     ///< A count of the maximum number of voices of each respective type to allocate on the synthesizer. Expressed as an array, of length #SCE_SCREAM_SND_VOICE_DATA_TYPE_COUNT, indexed in the order of the \link #SCE_SCREAM_SND_VOICE_DATA_TYPE_VAG Voice Data Type Constants\endlink. Range for each voice type: 0 to SceScreamPlatformInitEx2.maxPolyphony. Defaults to [#SCE_SCREAM_SND_DEFAULT_NUM_VAG_MONO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_PCM_MONO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_AT9_MONO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_VAG_STEREO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_PCM_STEREO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_AT9_STEREO_VOICES]. See &quot;Notes&quot; below.
    uint32_t              numReverbs;                   ///< The number of I3DL2 reverb voices to instantiate. Range: 0 to #SCE_SCREAM_SND_MAX_REVERBS. Defaults to #SCE_SCREAM_SND_DEFAULT_NUM_REVERBS.
    uint32_t              numPremasterCompSubmixes;     ///< The number of pre-master compressor submix voices to instantiate. Range: 0 to #SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES. Defaults to #SCE_SCREAM_SND_DEFAULT_NUM_PREMASTER_COMP_SUBMIXES.
    uint32_t              numPremasterScCompSubmixes;   ///< The number of pre-master side-chain compressor submix voices to instantiate. Range: 0 to (#SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES minus <c><i>numPremasterCompSubmixes</i></c>). Defaults to #SCE_SCREAM_SND_DEFAULT_NUM_PREMASTER_SC_COMP_SUBMIXES.
    uint32_t              numExternalRacks;             ///< The number of NGS racks to create. Note that NGS racks must be managed outside of Scream. Defaults to zero.
    uint32_t              numExternalVoices;            ///< The number of voices across all external racks to create. Note that NGS racks must be managed outside of Scream. Defaults to zero.
    uint32_t              initFlags;                    ///< Any combination of the \link #SCE_SCREAM_SND_SYNTH_INIT_FLAG_VALIDATE_PARAMS NGS Initialization Flags\endlink. Defaults to #SCE_SCREAM_SND_DEFAULT_SYNTH_INIT_FLAGS.
    uint32_t              reserved0;                    ///< Reserved for internal use. Set to 0.
}SceScreamSystemParams;
/**@}*/

// Filter Mode Indices
// Filter mode indices are values for the SceScreamSndIIRFilterParams type member.
/**
@defgroup ngsFilterModeIndices NGS Filter Mode Indices
@brief Filter mode indices are values for the SceScreamSndIIRFilterParams <c><i>type</i></c> member.
@{*/
#define SCE_SCREAM_FLT_BQ_OFF       0                           ///< Specifies a filter bypass (transparent).
#define SCE_SCREAM_FLT_BQ_LPF       1                           ///< Specifies a low-pass filter.
#define SCE_SCREAM_FLT_BQ_HPF       2                           ///< Specifies a high-pass filter.
#define SCE_SCREAM_FLT_BQ_APF       3                           ///< Specifies an all-pass filter.
#define SCE_SCREAM_FLT_BQ_BPF       4                           ///< Specifies a band-pass filter.
#define SCE_SCREAM_FLT_BQ_NOTCH     5                           ///< Specifies a notch filter.
#define SCE_SCREAM_FLT_BQ_PEQ       6                           ///< Specifies a peaking-EQ filter.
#define SCE_SCREAM_FLT_BQ_LSH       7                           ///< Specifies a low-shelf filter.
#define SCE_SCREAM_FLT_BQ_HSH       8                           ///< Specifies a high-shelf filter.
/**@}*/

// Synthesizer Constants
// Synthesizer constants impose limits for various synthesizer resources and parameters.
/**
@defgroup ngsSynthParameterConstants NGS Synth Parameter Constants
@brief These constants impose limits for various NGS synthesizer resources and parameters.
@{*/
#define SCE_SCREAM_BQ_MIN_GAIN       0.0f                       ///< The minimum value for peaking or shelving filters gain parameter. See the SceScreamSndIIRFilterParams <c><i>gain</i></c> member.
#define SCE_SCREAM_BQ_MAX_GAIN       16.0f                      ///< The maximum value for peaking or shelving filters gain parameter. See the SceScreamSndIIRFilterParams <c><i>gain</i></c> member.
#define SCE_SCREAM_BQ_MIN_RESONANCE  0.5f                       ///< The minimum value for filter resonance (or Q) parameter. See the SceScreamSndIIRFilterParams <c><i>resonance</i></c> member.
#define SCE_SCREAM_BQ_MAX_RESONANCE  10.0f                      ///< The maximum value for filter resonance (or Q) parameter. See the SceScreamSndIIRFilterParams <c><i>resonance</i></c> member.

#define SCE_SCREAM_NUM_AUX_SENDS    3                           ///< The maximum number of auxiliary sends per voice. See the SceScreamSynthParams <c><i>auxSendGain</i></c> and <c><i>auxSendDests</i></c> members.
#define SCE_SCREAM_NUM_AUX_BUSSES   3                           ///< The maximum number of system-wide auxiliary busses (that is, auxiliary send destinations). See the SceScreamSynthParams <c><i>auxSendDests</i></c> member.

#define SCE_SCREAM_SND_DIST_MIN_AB          0.0f                ///< The minimum A or B coefficient value for the pre-send distortion effect. See the SceScreamSndDistortionParams <c><i>a</i></c> and <c><i>b</i></c> members.
#define SCE_SCREAM_SND_DIST_MAX_AB          10.0f               ///< The maximum A or B coefficient value for the pre-send distortion effect. See the SceScreamSndDistortionParams <c><i>a</i></c> and <c><i>b</i></c> members.
#define SCE_SCREAM_SND_DIST_MIN_CLIP_GATE   0.0f                ///< The minimum clip or gate values for the pre-send distortion effect. See the SceScreamSndDistortionParams <c><i>clip</i></c> and <c><i>gate</i></c> members.
#define SCE_SCREAM_SND_DIST_MAX_CLIP_GATE   1.0f                ///< The maximum clip or gate value for the pre-send distortion effect. See the SceScreamSndDistortionParams <c><i>clip</i></c> and <c><i>gate</i></c> members.
#define SCE_SCREAM_SND_DIST_MIN_GAIN        0.0f                ///< The minimum (linear) dry gain or wet gain values for the pre-send distortion effect. See the SceScreamSndDistortionParams <c><i>dryGain</i></c> and <c><i>wetGain</i></c> members.
#define SCE_SCREAM_SND_DIST_MAX_GAIN        4.0f                ///< The maximum (linear) dry gain or wet gain values for the pre-send distortion effect. See the SceScreamSndDistortionParams <c><i>dryGain</i></c> and <c><i>wetGain</i></c> members.

#define SCE_SCREAM_SND_DISTORTION_ENABLED (1L<<0)               ///< A flag used to enable the pre-send distortion effect. See the SceScreamSndDistortionParams <c><i>flags</i></c> member.
/**@}*/

/**
@defgroup ngsTypeDefinitions NGS Type Definitions
@brief NGS type definitions define data types for NGS-specific APIs.
@{*/
/**
@brief
Data type for a reverb handle.

Defines the data type used for a reverb handle.
Obtain a handle with the sceScreamReverbGetHandleByBuss() function. This handle is used by the General Reverb Functions.

@see
sceScreamReverbGetHandleByBuss()
*/
typedef uint32_t    SceScreamReverbHandle;
/**@}*/

/**
@ingroup ngsTypeDefinitions

@brief
Data type for an effect handle.

Defines the data type used for an effect handle.

@see
sceScreamEffectSetAllProperties(), sceScreamEffectSetStockPreset(), sceScreamEffectSetCustomPreset(), sceScreamEffectSetCustomPresetByName(), sceScreamEffectSetVolumePolar(), sceScreamEffectPause(), sceScreamEffectContinue(), sceScreamApplyEffectPreset()
*/
typedef uint32_t SceScreamEffectHandle;

/**
@ingroup ngsTypeDefinitions

@brief
Data type for an INI-formatted presets file handle.

Defines the data type used for an INI-formatted presets file handle.
You obtain a SceScreamIniHandle by calling sceScreamPresetFileLoad() or sceScreamPresetFileLoadFromMem(). This handle is used by the Presets File (INI) Functions.

@see
sceScreamPresetFileLoad(), sceScreamPresetFileLoadFromMem(), sceScreamPremasterSubmixSetCustomPreset(), sceScreamReverbSetCustomPresetByName()
*/
typedef void* SceScreamIniHandle;


/**
@ingroup ngsDataStructures

@brief Stores parameter values for the pre-send and post-send filters.

This structure stores parameter values for the pre-send and post-send biquad filters.
You use this structure when setting or retrieving pre- and post-send filter values with the sceScreamSetSoundParamsEx() and sceScreamGetSoundParamsEx() functions.
Several SceScreamSndIIRFilterParams structures are embedded in the SceScreamSynthParams structure, which in turn is embedded in the SceScreamSoundParams structure, which is referenced (in the <c><i>params</i></c> parameter) when calling the sceScreamSetSoundParamsEx() and sceScreamGetSoundParamsEx() functions.

Biquad filters are infinite impulse response (IIR) filters with a roll-off of 12dB per octave.

Note that the specific meaning of the parameters varies with the different filter types.
And in the case of the #SCE_SCREAM_FLT_BQ_LPF, #SCE_SCREAM_FLT_BQ_HPF, #SCE_SCREAM_FLT_BQ_APF, #SCE_SCREAM_FLT_BQ_BPF, and #SCE_SCREAM_FLT_BQ_NOTCH filters,
the <c><i>gain</i></c> parameter is not applicable.

For important information on using the pre-send and post-send filters, see &quot;Available Filter Types and
Their Parameters&quot; in the &quot;Working with Pre- and Post-Send Filters and Effects&quot; chapter of the <i>Scream Library Overview</i>.

Run the Scream example program, Runtime Filter, to hear the effect of different parameter values for
the various filter types. For further information on
Scream example programs, see the introductory chapter of the <i>Scream Library Overview</i>.

@see
sceScreamSetSoundParamsEx(), sceScreamGetSoundParamsEx(), SceScreamSynthParams, SceScreamSoundParams
*/
typedef struct SceScreamSndIIRFilterParams
{
    int32_t     type;                                   ///< Filter type. One of the \link #SCE_SCREAM_FLT_BQ_OFF Filter Modes Indices\endlink.
    float       gain;                                   ///< Filter gain. Range (where applicable): #SCE_SCREAM_BQ_MIN_GAIN to #SCE_SCREAM_BQ_MAX_GAIN. For further information, see the &quot;Working with Pre- and Post-Send Filters and Effects&quot; chapter of the <i>Scream Library Overview</i>.
    float       cutoff;                                 ///< Filter cut-off frequency. Range 10.0 to 23999.0 (that is, less than the half sampling rate).
    float       resonance;                              ///< Filter resonance or Q. Range: #SCE_SCREAM_BQ_MIN_RESONANCE to #SCE_SCREAM_BQ_MAX_RESONANCE.
}SceScreamSndIIRFilterParams;


/**
@ingroup ngsDataStructures

@brief Stores parameter values for the pre-send distortion effect.

This structure stores parameter values for the pre-send distortion effect.
You use this structure when setting or retrieving pre-send distortion effect values with the sceScreamSetSoundParamsEx() and sceScreamGetSoundParamsEx() functions.
SceScreamSndDistortionParams is embedded in the SceScreamSynthParams structure, which in turn is embedded in the SceScreamSoundParams structure, which is referenced (in the <c><i>params</i></c> parameter) when calling the sceScreamSetSoundParamsEx() and sceScreamGetSoundParamsEx() functions.

For more information on distortion, see &quot;Configuring the Distortion Effect&quot; in the &quot;Working with Pre- and Post-Send Filters and Effects&quot;
chapter of the <i>Scream Library Overview</i>.

@see
sceScreamSetSoundParamsEx(), sceScreamGetSoundParamsEx(), SceScreamSynthParams, SceScreamSoundParams
*/
typedef struct SceScreamSndDistortionParams
{
    float       a;                                          ///< Distortion coefficient A. Range: #SCE_SCREAM_SND_DIST_MIN_AB (0) to #SCE_SCREAM_SND_DIST_MAX_AB (10.0).
    float       b;                                          ///< Distortion coefficient B. Range: #SCE_SCREAM_SND_DIST_MIN_AB (0) to #SCE_SCREAM_SND_DIST_MAX_AB (10.0).
    float       clip;                                       ///< Limiter on the audio output of the polynomial stage. Range: #SCE_SCREAM_SND_DIST_MIN_CLIP_GATE (0) to #SCE_SCREAM_SND_DIST_MAX_CLIP_GATE (1.0).
    float       gate;                                       ///< Noise gate on the audio output. Range: #SCE_SCREAM_SND_DIST_MIN_CLIP_GATE (0) to #SCE_SCREAM_SND_DIST_MAX_CLIP_GATE (1.0).
    float       wetGain;                                    ///< Wet (distorted signal) gain factor. Range: #SCE_SCREAM_SND_DIST_MIN_GAIN (0) to #SCE_SCREAM_SND_DIST_MAX_GAIN (4.0), where 1.0 is unity gain.
    float       dryGain;                                    ///< Dry (original signal) gain factor. Range: #SCE_SCREAM_SND_DIST_MIN_GAIN (0) to #SCE_SCREAM_SND_DIST_MAX_GAIN (4.0), where 1.0 is unity gain.
    uint32_t    flags;                                      ///< Must be set to #SCE_SCREAM_SND_DISTORTION_ENABLED to enable the pre-send distortion effect.
}SceScreamSndDistortionParams;

/**
@ingroup ngsDataStructures

@brief
Stores synthesizer parameter values.

This structure stores synthesizer parameter values.
You use it when setting or retrieving synthesizer parameter values
through the sceScreamSetSoundParamsEx() and sceScreamGetSoundParamsEx() functions.
These functions take a SceScreamSoundParams parameter, which contains a SceScreamSynthParams parameter.

The <c><i>preSendFilter0</i></c>, <c><i>preSendFilter1</i></c>, <c><i>preSendFilter2</i></c>, <c><i>preSendFilter3</i></c>,
and <c><i>postSendFilter</i></c> members point to SceScreamSndIIRFilterParams structures, initialized with parameter values for the
respective pre-send and post-send filters. The <c><i>preSendDistortion</i></c> points to a SceScreamSndDistortionParams structure, initialized with
parameter values for the pre-send distortion effect.

On the NGS synthesizer, there are #SCE_SCREAM_NUM_AUX_SENDS (3) auxiliary sends with fixed routing to #SCE_SCREAM_NUM_AUX_BUSSES (3) corresponding auxiliary busses.
The <c><i>auxSendGain</i></c> member is an array of gain values for each auxiliary send.
Because auxiliary sends have fixed destinations, there is no need to set auxiliary send destinations.
On the NGS synth, settings to the <c><i>auxSendDests</i></c> member are ignored.

@note
Setting any of the pre-send filters (filters 0 to 3, and the distortion effect) from the Scream API overrides any settings
on a Sound that may have been made in Bank contents. It is generally good practice to coordinate filter settings with your audio design team.

@see
SceScreamSndIIRFilterParams, SceScreamSndDistortionParams, SceScreamSoundParams, sceScreamSetSoundParamsEx(), sceScreamGetSoundParamsEx()

*/
typedef struct SceScreamSynthParams
{
    uint32_t                      mask;                         ///< A bit mask value indicating which of the following members are active. One or more of the \link #SCE_SCREAM_SND_MASK_PRESEND_FILTER_0 Synthesizer Parameter Bit Masks\endlink. Use the bitwise <c>OR</c> operator for multiple selections.
    SceScreamSndIIRFilterParams   preSendFilter0;               ///< A SceScreamSndIIRFilterParams structure, initialized with parameter values for pre-send filter 0.
    SceScreamSndIIRFilterParams   preSendFilter1;               ///< A SceScreamSndIIRFilterParams structure, initialized with parameter values for pre-send filter 1.
    SceScreamSndIIRFilterParams   preSendFilter2;               ///< A SceScreamSndIIRFilterParams structure, initialized with parameter values for pre-send filter 2.
    SceScreamSndIIRFilterParams   preSendFilter3;               ///< A SceScreamSndIIRFilterParams structure, initialized with parameter values for pre-send filter 3.
    SceScreamSndDistortionParams  preSendDistortion;            ///< A SceScreamSndDistortionParams structure, initialized with parameter values for the pre-send distortion effect.
    float                         auxSendGain[SCE_SCREAM_NUM_AUX_SENDS];    ///< An array of auxiliary send gain values, of length #SCE_SCREAM_NUM_AUX_SENDS. These values scale the level of signal that is branched into a Sound's respective auxiliary send busses. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    uint32_t                      auxSendDests[SCE_SCREAM_NUM_AUX_SENDS];   ///< An array of auxiliary send destinations, of length #SCE_SCREAM_NUM_AUX_SENDS. Range: 0 to (#SCE_SCREAM_NUM_AUX_BUSSES &ndash; 1). For details, see &quot;Configuring Auxiliary Sends&quot; in the &quot;Working with the I3DL2 Reverb&quot; chapter of the <i>Scream Library Overview</i>.
    float                         directSendGain;               ///< Direct send gain. This value scales the level of a Sound's direct path signal as it passes through the pre- and post-send filters. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    SceScreamSndIIRFilterParams   postSendFilter;               ///< A SceScreamSndIIRFilterParams structure, initialized with parameter values for the post-send filter.
    float                         lfeGain;                      ///< LFE (low frequency effect) gain. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
}SceScreamSynthParams;

/////////////////////////////////////////////////////////////////////////////////////////////////

// Used in mask member of SceScreamSynthParams struct
// Synthesizer parameter bit masks are values for the SceScreamSynthParams structure's mask member.
/**
@defgroup ngsSynthParamBitMasks NGS Synth Param Bit Masks
@brief You apply NGS synthesizer parameter bit masks to the SceScreamSynthParams structure's <c><i>mask</i></c> member in order to specify which other members of the structure are being set.
@{*/
#define SCE_SCREAM_SND_MASK_PRESEND_FILTER_0   (1L<< 0)                 ///< The <c><i>preSendFilter0</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_PRESEND_FILTER_1   (1L<< 1)                 ///< The <c><i>preSendFilter1</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_PRESEND_FILTER_2   (1L<< 2)                 ///< The <c><i>preSendFilter2</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_PRESEND_FILTER_3   (1L<< 3)                 ///< The <c><i>preSendFilter3</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_PRESEND_DISTORTION (1L<< 4)                 ///< The <c><i>preSendDistortion</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_AUXSEND_GAIN_0     (1L<< 5)                 ///< The <c><i>auxSendGain[0]</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_AUXSEND_GAIN_1     (1L<< 6)                 ///< The <c><i>auxSendGain[1]</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_AUXSEND_GAIN_2     (1L<< 7)                 ///< The <c><i>auxSendGain[2]</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_AUXSEND_GAINS      (SCE_SCREAM_SND_MASK_AUXSEND_GAIN_0|SCE_SCREAM_SND_MASK_AUXSEND_GAIN_1|SCE_SCREAM_SND_MASK_AUXSEND_GAIN_2)///< All <c><i>auxSendGain</i></c> members have been set.
#define SCE_SCREAM_SND_MASK_AUXSEND_DEST_0     (1L<< 8)                 ///< The <c><i>auxSendDests[0]</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_AUXSEND_DEST_1     (1L<< 9)                 ///< The <c><i>auxSendDests[1]</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_AUXSEND_DEST_2     (1L<< 10)                    ///< The <c><i>auxSendDests[2]</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_AUXSEND_DESTS      (SCE_SCREAM_SND_MASK_AUXSEND_DEST_0|SCE_SCREAM_SND_MASK_AUXSEND_DEST_1|SCE_SCREAM_SND_MASK_AUXSEND_DEST_2)///< All <c><i>auxSendDests</i></c> members have been set.
#define SCE_SCREAM_SND_MASK_DIRECTSEND_GAIN    (1L<< 11)                    ///< The <c><i>directSendGain</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_POSTSEND_FILTER    (1L<< 12)                    ///< The <c><i>postSendFilter</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_RENDERING_FILTER   SCE_SCREAM_SND_MASK_POSTSEND_FILTER  ///< The rendering filter has been set. <b>Note:</b> This is just an alias for the <c><i>postSendFilter</i></c> member being set.
#define SCE_SCREAM_SND_MASK_LFE_GAIN           (1L<< 13)                    ///< The <c><i>lfeGain</i></c> member has been set.
/**@}*/
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
@defgroup ngsReverbEnumerations NGS Reverb Enumerations
@{*/
/**
@brief
The I3DL2 reverb stock presets provide parameter settings for a variety of commonly used reverb effects &ndash; indoor and outdoor.
Apply the macros as optional values for sceScreamReverbSetStockPreset() <c><i>presetIndex</i></c> parameter.
*/
typedef enum SceScreamI3DL2StockPresets
{
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_DEFAULT             = 0,                ///< The default preset. <b>Note:</b> this preset sets the I3DL2 Room parameter to -10,000 mB. Reverb output level is therefore inaudible.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_GENERIC             = 1,                ///< A generic preset.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL          = 2,                ///< Padded cell.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_ROOM                = 3,                ///< Basic room.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_BATHROOM            = 4,                ///< Bathroom.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM          = 5,                ///< Living room.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_STONEROOM           = 6,                ///< Stone room.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM          = 7,                ///< Auditorium.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL         = 8,                ///< Concert hall.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_CAVE                = 9,                ///< Cave.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_ARENA               = 10,               ///< Sports arena.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_HANGAR              = 11,               ///< Aircraft hangar.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY     = 12,               ///< Carpeted hallway.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_HALLWAY             = 13,               ///< Hallway.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR       = 14,               ///< Stone corridor.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_ALLEY               = 15,               ///< Alley.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_FOREST              = 16,               ///< Forest.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_CITY                = 17,               ///< City.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS           = 18,               ///< Mountains.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_QUARRY              = 19,               ///< Quarry.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_PLAIN               = 20,               ///< Plain.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT          = 21,               ///< Parking lot.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE           = 22,               ///< Sewer pipe.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_UNDERWATER          = 23,               ///< Underwater.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_SMALLROOM           = 24,               ///< Small room.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM          = 25,               ///< Medium room.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_LARGEROOM           = 26,               ///< Large room.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL          = 27,               ///< Medium hall.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_LARGEHALL           = 28,               ///< Large hall.
    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_PLATE               = 29,               ///< Plate.

    SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_NB                  = 30                ///< (Number of reverb presets in stock library).
}SceScreamI3DL2StockPresets;
/**@}*/

/**
@ingroup ngsDataStructures
@brief Stores I3DL2 reverb parameter values.

This structure stores parameter values used in the I3DL2 reverb. You can set I3DL2 reverb parameters directly by
storing desired values in this structure, and calling the sceScreamReverbSetAllProperties() function.

You can also set I3DL2 reverb parameters by setting a stock preset.
To set a stock preset, use the sceScreamReverbSetStockPreset() function, and select from the list of \link #SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_DEFAULT SceScreamI3DL2StockPresets\endlink.

@see
sceScreamReverbSetAllProperties(), \link #SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_DEFAULT SceScreamI3DL2StockPresets\endlink, sceScreamReverbSetStockPreset()

*/
typedef struct SceScreamSndReverbProps
{
    float Room;                         ///< Output level of wet (reverb-treated) signal, in mB (milliBells; 100 mB = 1 dB). Range: -10000.0 to 0.0 mB.
    float Room_HF;                      ///< Attenuation of high-frequencies, in mB, with respect to the <c><i>HF_reference</i></c> value. Range -10000.0 to 0.0 mB, where 0.0 mB produces no coloration.
    float Decay_time;                   ///< Late reverberation (diffuse tail) decay time. Larger, more reflective environments have longer decay times. Smaller, less reflective environments have shorter decay times. Range: 0.1 to 20 seconds.
    float Decay_HF_ratio;               ///< Ratio of late reverberation high-frequency decay to low-frequency decay with respect to the <c><i>HF_reference</i></c> value. Range: 0.1 to 2.0.
    float Reflections;                  ///< Early reflections level, in mB. Use this parameter in conjunction with the <c><i>Reverb</i></c> value to set the balance between early reflections and late reverberation. Range: -10000 to +1000 mB.
    float Reflections_delay;            ///< Pre-delay time before the onset of early reflections. Simulates room size. Larger spaces have a longer pre-delay before the onset of early reflections. Range: 0.0 to 0.3 seconds.
    float Reverb;                       ///< Late reverberation level, in mB. Use this parameter in conjunction with the <c><i>Reflections</i></c> value to set the balance between early reflections and late reverberation. Range: -10000 to +2000 mB.
    float Reverb_delay;                 ///< Delay time before the onset of late reverberation. Simulates room size; larger spaces have a longer delay before the onset of late reverberation. Range: 0.0 to 0.1 seconds.
    float Diffusion;                    ///< Echo density of late reverberation. Simulates the reflectivity of the environment surfaces. Range: 0 to 100%, where 0% means minimal reflection.
    float Density;                      ///< Modal density of late reverberation. Range: 0 to 100%, where 0% means minimal late reverberation.
    float HF_reference;                 ///< Reference high frequency. Used in conjunction with <c><i>Room_HF</i></c> and <c><i>Decay_HF_ratio</i></c>. Range: 20 to 20000 Hertz.
    int32_t EarlyReflectionPattern[2];  ///< (Optional) One of the \link #SCE_SCREAM_SND_I3DL2_REVERB_ROOM1_LEFT Early Reflections Pattern Constants\endlink per channel. <c>EarlyReflectionPattern[0]</c> is for the left and <c>EarlyReflectionPattern[1]</c> is for the right channel.
    float EarlyReflectionScalar;        ///< Scales the early reflections spread. Higher values produce more spread-out early reflections (as found in larger spaces); lower values produce more tightly-packed early reflections (as found in smaller spaces). Range: 0 to 100%, where 0% specifies single reflection, and 100% specifies widely spread reflections.
    float LF_reference;                 ///< Reference low frequency. Used in conjunction with <c><i>Room_LF</i></c>. Range: 20 to 20000 Hertz.
    float Room_LF;                      ///< Attenuation of low-frequencies with respect to the <c><i>LF_reference</i></c> value. Range: -10000 to 0 mB.
    float DryMB;                        ///< Output level of dry (untreated) signal, in mB. Range: -10000 to 0 mB.
}SceScreamSndReverbProps;

// I3DL2 Reverb Early Reflections Pattern Constants
// NOTE: The left and right variations have slight differences designed to prevent interference between channels.
/**
@defgroup ngsI3DL2ReverbConstants I3DL2 Reverb Early Reflections Constants
@brief Early reflections pattern constants are values for the SceScreamSndReverbProps <c><i>EarlyReflectionPattern</i></c> member.
@{*/
#define SCE_SCREAM_SND_I3DL2_REVERB_ROOM1_LEFT      0       ///< Room template 1, left channel.
#define SCE_SCREAM_SND_I3DL2_REVERB_ROOM1_RIGHT     1       ///< Room template 1, right channel.
#define SCE_SCREAM_SND_I3DL2_REVERB_ROOM2_LEFT      2       ///< Room template 2, left channel.
#define SCE_SCREAM_SND_I3DL2_REVERB_ROOM2_RIGHT     3       ///< Room template 2, right channel.
#define SCE_SCREAM_SND_I3DL2_REVERB_ROOM3_LEFT      4       ///< Room template 3, left channel.
#define SCE_SCREAM_SND_I3DL2_REVERB_ROOM3_RIGHT     5       ///< Room template 3, right channel.
/**@}*/

/**
@ingroup ngsDataStructures
@brief Stores pre-master submix property values.

This structure stores pre-master submix property values.
You use this structure when setting all pre-master submix buss effect properties directly using the sceScreamPremasterSubmixSetAllProperties() function.

You can also set pre-master submix property values with the sceScreamSynthPremasterSubmixSetupCompressor() function.
Its parameters are nearly identical to the members in SceScreamSndPremasterSubmixProps.

@note
The compressor property values apply to pre-master submix effects with both standard and side-chain compressors.

@note
Channel linking preserves the panning image, but is a more intrusive compression mode because each channel is compressed equally based on the <c><i>compPeakMode</i></c> setting.

@note
In peak mode, the compressor responds to the instantaneous level of the input signal. Peak mode can produce more quick-reacting and obvious results.
In RMS mode, the compressor responds to an averaged level of the input signal. RMS mode can produce more relaxed and subtle results.

@see
sceScreamPremasterSubmixSetAllProperties(), sceScreamSynthPremasterSubmixSetupCompressor()
*/
typedef struct SceScreamSndPremasterSubmixProps
{
    // Compressor (side-chain or standard)
    BOOL        compEffectOn;               ///< Compressor enable. A Boolean value that specifies whether the compressor is on or off. <c>TRUE</c> for on; <c>FALSE</c> for off.
    BOOL        compLinkedChannels;         ///< Compressor channel linking. A Boolean value that specifies whether to link the input channels to retain the original panning image. <c>TRUE</c> for channel linking; <c>FALSE</c> for channel independence. See &quot;Notes&quot; below.
    BOOL        compPeakMode;               ///< Compressor peak mode. A Boolean value that specifies whether or not to use peak mode. <c>TRUE</c> for peak mode; <c>FALSE</c> for RMS mode. See &quot;Notes&quot; below.
    float       compThresholdDB;            ///< Compressor operation threshold. Expressed in dB. Range: -100.0 to 0.0.
    float       compRatio;                  ///< Compression ratio. For input signal compression, use values greater than 1.0; for expansion, use values less than 1.0. For example, for a compression ratio of 2:1, use 2.0. Must be greater than 0.0 and less than or equal to 10.0.
    float       compAttackTimeMS;           ///< Compressor attack time. Expressed in milliseconds. Range: 0 to 10.0. Typically within the range of around 0 to 5 milliseconds.
    float       compReleaseTimeMS;          ///< Compressor release time. Expressed in milliseconds. Range: 0 to 2000.0. Typically within the range of around 500 to 1000 milliseconds.
    float       compMakeupGainDB;           ///< Compressor output make-up gain. Expressed in dB. Range: -100.0 to 100.0.
    float       compSoftKneeDB;             ///< Compressor soft knee. Defines the limits of an amplitude range, centered around the <c><i>compThresholdDB</i></c> level, over which the compression response curve operates. Range: -100.0 to 0.0 dB, where 0 dB produces no softening of the compression response curve (that is, a 'hard knee').
}SceScreamSndPremasterSubmixProps;

#if (defined(_cplusplus) || defined(__cplusplus))
extern "C"
{
#endif

////////////////////////////////////////////////////////////////////////////////
// Synth Master/Premaster API
/**
@defgroup preMasterSubmixFunctions Pre-Master Submix Functions
@brief
Pre-master submix functions set pre-master submix buss effects individually and collectively, by setting presets and setting all properties.
@{*/
/**
@brief
Connects a pre-master submix side-chain compression input to another pre-master submix.

This function sets output signal from a pre-master submix as side-chain compression input signal on another pre-master submix.
You specify the index of the pre-master submix to serve as side-chain input signal in the <c><i>premasterScCompSubmixID</i></c> parameter,
as well as the index of the pre-master submix into which it feeds in the <c><i>premasterCompSubmixID</i></c> parameter.

You specify values for the <c><i>premasterCompSubmixID</i></c> and <c><i>premasterScCompSubmixID</i></c> parameters using zero-based indices.
The range of index values you can specify depends on the number of pre-master submix busses allocated in the <c><i>numPremasterCompSubmixes</i></c> member of the SceScreamSystemParams structure.
The first pre-master submix index is always #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 (zero).
The last pre-master submix index is (<c><i>n</i></c> &ndash; 1), where <c><i>n</i></c> is the number of allocated pre-master submix busses.

@param premasterCompSubmixID (Input)
Zero-based index of the destination pre-master submix, that is, the submix containing the compressor into which to receive side-chain input signal.

@param premasterScCompSubmixID (Input)
Zero-based index of the source pre-master submix, that is, the side-chain input signal to drive the destination compressor.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamSynthPremasterSubmixSetupCompressor(), sceScreamSynthPremasterSubmixSetOutputGain()
*/
int32_t sceScreamSynthPremasterSubmixConnectSideChainInput( uint32_t premasterCompSubmixID, uint32_t premasterScCompSubmixID );
/**@}*/

/**
@ingroup preMasterSubmixFunctions

@brief
Sets a pre-master submix output gain.

This function sets a pre-master submix output gain to the master buss.

The <c><i>premasterSubmixID</i></c> parameter identifies a pre-master submix buss using a zero-based index.
The range of index values you can specify depends on the number of pre-master submix busses allocated in the <c><i>numPremasterCompSubmixes</i></c> member of the SceScreamSystemParams structure.
The first pre-master submix index is always #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 (zero).
The last pre-master submix index is (<i>n</i> &ndash; 1), where <i>n</i> is the number of allocated pre-master submix busses.

@param premasterSubmixID (Input)
Zero-based index of the pre-master submix upon which to set output gain level.

@param gainLinear (Input)
Output gain, expressed on a linear scale. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected
or #SCE_SCREAM_SS_ERROR_SYNTH_INIT_FAILED if the call cannot proceed due to a synth configuration error.

@see
sceScreamSynthPremasterSubmixConnectSideChainInput(), sceScreamSynthPremasterSubmixSetupCompressor()
*/
int32_t sceScreamSynthPremasterSubmixSetOutputGain( uint32_t premasterSubmixID, float gainLinear );

/**
@ingroup preMasterSubmixFunctions

@brief
Sets up a pre-master submix compressor.

This function sets up a pre-master submix compressor.

The <c><i>premasterSubmixID</i></c> parameter identifies a pre-master submix buss using a zero-based index.
The range of index values you can specify depends on the number of pre-master submix busses allocated in the <c><i>numPremasterCompSubmixes</i></c> member of the SceScreamSystemParams structure.
The first pre-master submix index is always #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 (zero).
The last pre-master submix index is (<c><i>n</i></c> &ndash; 1), where <c><i>n</i></c> is the number of allocated pre-master submix busses.

You can also set up parameters in a SceScreamSndPremasterSubmixProps structure and call sceScreamPremasterSubmixSetAllProperties() to set pre-master submix compressor values.
The members in SceScreamSndPremasterSubmixProps are nearly identical to this function's parameters.

@param premasterSubmixID (Input)
Zero-based index of the pre-master submix upon which to set up a compressor.

@param effectOn (Input)
A Boolean value that determines whether the compressor is on or off. Set to <c>TRUE</c> for on; set to <c>FALSE</c> for off.

@param linkedChannels (Input)
A Boolean value that determines whether to link the input channels to retain the original panning image. Set to <c>TRUE</c> for channel linking; set to <c>FALSE</c> for channel independence. See &quot;Notes&quot; below.

@param peakMode (Input)
A Boolean value that determines whether to use peak mode. Set to <c>TRUE</c> for peak mode; set to <c>FALSE</c> for RMS mode. See &quot;Notes&quot; below.

@param thresholdDB (Input)
Operation threshold of the compressor. Expressed in dB. Range: -100.0 to 0.0.

@param ratio (Input)
Compression ratio. Must be greater than 0.0. For input signal compression use values greater than 1.0; for expansion use values less than 1.0. For example, for a compression ratio of 2:1, use 2.0.

@param attackTimeMS (Input)
Attack time of the compressor. Expressed in milliseconds. Must be greater than or equal to 0.0. Typically within the range of around 0 to 5 milliseconds.

@param releaseTimeMS (Input)
Release time of the compressor. Expressed in milliseconds. Must be greater than or equal to 0.0. Typically within the range of around 500 to 1000 milliseconds.

@param makeupGainDB (Input)
Output make-up gain. Expressed in dB. Range: -100.0 to 100.0.

@param softKneeDB (Input)
Defines the limits of an amplitude range, centered around the <c><i>thresholdDB</i></c> level, over which the compression response curve operates.
Range: -100.0 to 0.0 dB, where 0 dB produces no softening of the compression response curve (that is, a 'hard knee').

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@note
Channel linking preserves the panning image, but is a more intrusive compression mode because each channel is compressed equally based on the <c><i>peakMode</i></c> setting.

@note
In peak mode, the compressor responds to the instantaneous level of the input signal.
Peak mode can produce more quick-reacting and obvious results.
In RMS mode, the compressor responds to an averaged level of the input signal.
RMS mode can produce more relaxed and subtle results.

@see
sceScreamSynthPremasterSubmixConnectSideChainInput(), sceScreamSynthPremasterSubmixSetOutputGain(),
SceScreamSndPremasterSubmixProps, sceScreamPremasterSubmixSetAllProperties(), sceScreamSynthMasterSetupCompressor()
*/
int32_t sceScreamSynthPremasterSubmixSetupCompressor( uint32_t premasterSubmixID, bool effectOn, bool linkedChannels, bool peakMode, float thresholdDB, float ratio, float attackTimeMS, float releaseTimeMS, float makeupGainDB, float softKneeDB /* = 0.0f */ );

/**
@defgroup masterSpeakersBussFunctions Master Speakers Buss Functions
@brief
Master speakers buss functions set master speakers buss effects and retrieve levels.
@{*/
/**
@brief
Sets up the master buss compressor.

This function sets up the master buss compressor.

@param effectOn (Input)
A Boolean value that determines whether the compressor is on or off. Set to <c>TRUE</c> for on; set to <c>FALSE</c> for off.

@param linkedChannels (Input)
A Boolean value that determines whether to link the input channels to retain the original panning image. Set to <c>TRUE</c> for channel linking; set to <c>FALSE</c> for channel independence. See &quot;Notes&quot; below.

@param peakMode (Input)
A Boolean value that determines whether to use peak mode. Set to <c>TRUE</c> for peak mode; set to <c>FALSE</c> for RMS mode. See &quot;Notes&quot; below.

@param thresholdDB (Input)
Operation threshold of the compressor. Expressed in dB. Range: -100.0 to 0.0.

@param ratio (Input)
Compression ratio. Must be greater than 0.0. For input signal compression use values greater than 1.0; for expansion use values less than 1.0. For example, for a compression ratio of 2:1, use 2.0.

@param attackTimeMS (Input)
Attack time of the compressor. Expressed in milliseconds. Must be greater than or equal to 0.0. Typically within the range of around 0 to 5 milliseconds.

@param releaseTimeMS (Input)
Release time of the compressor. Expressed in milliseconds. Must be greater than or equal to 0.0. Typically within the range of around 500 to 1000 milliseconds.

@param makeupGainDB (Input)
Output make-up gain. Expressed in dB. Range: -100.0 to 100.0.

@param softKneeDB (Input)
Defines the limits of an amplitude range, centered around the <c><i>thresholdDB</i></c> level, over which the compression response curve operates.
Range: -100.0 to 0.0 dB, where 0 dB produces no softening of the compression response curve (that is, a 'hard knee').

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@note
Channel linking preserves the panning image but is a more intrusive compression mode because each channel is compressed equally based on the RMS averaging of all channels.

@note
In peak mode, the compressor responds to the instantaneous level of the input signal.
Peak mode can produce more quick-reacting and obvious results.
In RMS mode, the compressor responds to an averaged level of the input signal.
RMS mode can produce more relaxed and subtle results.

@see
sceScreamSynthPremasterSubmixSetupCompressor()
*/
int32_t sceScreamSynthMasterSetupCompressor( bool effectOn, bool linkedChannels, bool peakMode, float thresholdDB, float ratio, float attackTimeMS, float releaseTimeMS, float makeupGainDB, float softKneeDB /* = 0.0f */ );
/**@}*/

////////////////////////////////////////////////////////////////////////////////
// System/Master/Premaster Direct Access API
/**
@defgroup ngsDirectAccessFunctions NGS Direct Access Functions
@brief
NGS direct access functions allow you to route external NGS voices to the Scream master buss and pre-master submix busses.
@{*/
/**
@brief
Retrieves the NGS system handle.

This function retrieves the NGS system handle.

@return
Returns the NGS system handle.

@note
Cast the return value to a <c>SceNgsHSynSystem</c> type.
This handle is necessary in order to create NGS voice racks.

@see
sceScreamSynthGetMasterVoiceHandle(), sceScreamSynthGetPremasterSubmixVoiceHandle()
*/
void* sceScreamSynthGetNGSSystemHandle(void);
/**@}*/

/**
@ingroup ngsDirectAccessFunctions

@brief
Retrieves the Scream master voice handle.

This function retrieves the Scream master voice handle.
You use the master voice handle to route external NGS voices to the Scream master voice.

@return
Returns the master voice handle.

@note
Cast the return value to a <c>SceNgsHSynSystem</c> type.

@see
sceScreamSynthGetNGSSystemHandle(), sceScreamSynthGetPremasterSubmixVoiceHandle()
*/
void* sceScreamSynthGetMasterVoiceHandle(void);

/**
@ingroup ngsDirectAccessFunctions

@brief
Retrieves a pre-master submix voice handle.

This function retrieves a pre-master submix voice handle.
You use pre-master submix voice handles to route to the corresponding Scream pre-master submixes.

@param premasterSubmixID (Input)
Zero-based index of a pre-master submix from which to retrieve a handle.

@return
Returns the specified pre-master submix voice handle.

@note
Cast the return value to a <c>SceNgsHSynSystem</c> type.

@see
sceScreamSynthGetNGSSystemHandle(), sceScreamSynthGetMasterVoiceHandle()
*/
void* sceScreamSynthGetPremasterSubmixVoiceHandle( uint32_t premasterSubmixID );

////////////////////////////////////////////////////////////////////////////////




#if (defined(_cplusplus) || defined(__cplusplus))
}
#endif


#endif // _DOLCESDK_PSP2_SCREAM_SCE_SCREAM_NGS_H_
