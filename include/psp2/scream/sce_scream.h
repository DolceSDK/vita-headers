#ifndef _DOLCESDK_PSP2_SCREAM_SCE_SCREAM_H_
#define _DOLCESDK_PSP2_SCREAM_SCE_SCREAM_H_

#include <stdio.h>
#include <stddef.h>

#include <psp2/scream/scream_error.h>
#include <psp2/scream/sce_snd_data.h>

#include <psp2/scream/sce_scream_ngs.h>

////////////////////////////////////////////////////////////////////////////////
// Constants

// ERROR_OK is zero -- all other error codes defined in scream_error.h
/**
@ingroup screamErrorCodes
*/
#define SCE_SCREAM_SS_ERROR_OK                              (0)             ///< Successful operation. No error detected. Returned by numerous functions.

/**
@defgroup initializationFlags Initialization Flags
@brief  You apply Scream initialization flags to the SceScreamPlatformInitEx2 <c><i>initFlags</i></c> member when initializing Scream with the sceScreamStartSoundSystemEx2() function.
@{*/
#define SCE_SCREAM_SSS_FLAGS_SILENT                         (1L << 1)       ///< Prevents Scream from outputting text messages to the TTY. Optional Scream initialization flag.
#define SCE_SCREAM_SSS_FLAGS_RETURN_ON_BAD_PARAM            (1L << 2)       ///< Causes all functions to return immediately if any parameter is invalid. Optional Scream initialization flag for function-level parameter validation. This flag is set by default. <b>Note:</b> Set this flag, or #SCE_SCREAM_SSS_FLAGS_HALT_ON_BAD_PARAM, or neither, but not both. For further details, see the &quot;Notes&quot; section of SceScreamPlatformInitEx2.
#define SCE_SCREAM_SSS_FLAGS_HALT_ON_BAD_PARAM              (1L << 3)       ///< Causes Scream to halt immediately if any parameter is invalid. Optional Scream initialization flag for function-level parameter validation. <b>Note:</b> Set this flag, or #SCE_SCREAM_SSS_FLAGS_RETURN_ON_BAD_PARAM, or neither, but not both. For further details, see the &quot;Notes&quot; section of SceScreamPlatformInitEx2.
#define SCE_SCREAM_SSS_FLAGS_TICK_CALLBACK                  (1L << 12)      ///< Causes Scream to make an application callback on each tick using the SceScreamSndEventCallback() mechanism. See SceScreamSndEventCallback() and SceScreamPlatformInitEx2. For information on setting up this callback, see &quot;Configuring Per-Tick Callbacks&quot; in the &quot;Working with System Globals&quot; chapter of the <i>Scream Library Overview</i>. You can also define callbacks triggered by certain Sound events by setting the callback condition in the SceScreamSoundParams <c><i>flags</i></c> member.
/**@}*/

/**
@defgroup screamSystemConstants Scream System Constants
@brief  System constants impose limits for various system resources and frequently-used parameters.
@{*/
#define SCE_SCREAM_SND_MAX_STREAMING_FILE_DIRECTORIES           16          ///< The maximum number of streaming file directory paths. See sceScreamGetStreamingFileDirectory(), sceScreamSetStreamingFileDirectory().
#define SCE_SCREAM_SND_MAX_GAIN                                 1.0f        ///< The maximum gain level for Scream and Sndstream API functions and structures that set gain. See the Scream SceScreamGainComponents, SceScreamSoundParams, SceScreamSynthParams, sceScreamSetMasterVolume(), sceScreamAutoGain(), and the Sndstream SceScreamSndBitstreamParams and SceScreamSndTransitionParams, among others.
#define SCE_SCREAM_SND_MIN_GAIN                                 0.0f        ///< The minimum gain level for Scream and Sndstream API functions and structures that set gain. See the Scream SceScreamGainComponents, SceScreamSoundParams, SceScreamSynthParams, sceScreamSetMasterVolume(), sceScreamAutoGain(), and the Sndstream SceScreamSndBitstreamParams and SceScreamSndTransitionParams, among others.
#define SCE_SCREAM_SND_MAX_GLOBAL_REGISTERS                     64          ///< The total number of global registers.  See sceScreamGetSFXGlobalReg(), and sceScreamSetSFXGlobalReg().
#define SCE_SCREAM_SND_MAX_LOCAL_VARIABLES                      16          ///< The maximum number of local variables per Sound instance. See sceScreamSetLocalVariableByHash(), and sceScreamGetLocalVariableByHash().
#define SCE_SCREAM_SND_MAX_REGISTERS                            8           ///< The total number of Sound-specific registers. Sound-specific registers are set in Bank contents, and also through the SceScreamSoundParams <c><i>registers</i></c> member.
#define SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR                    1.0f        ///< The maximum pitchbend factor; upper limit for the SceScreamSoundParams <c><i>pitchBendFactor</i></c> member.
#define SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR                    (-1.0f)     ///< The minimum pitchbend factor; lower limit for the SceScreamSoundParams <c><i>pitchBendFactor</i></c> member.
#define SCE_SCREAM_SND_FINES_PER_OCTAVE                         1536        ///< Fines are 128<sup>th</sup> microtonal subdivisions of a semitone. Given 12 semitones per octave, there are 1536 fines per octave.
#define SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE   (SCE_SCREAM_SND_FINES_PER_OCTAVE   * 5)    ///< The maximum pitch transpose amount &ndash; up or down from original pitch &ndash; is 5 octaves, expressed in fines. See the SceScreamSoundParams <c><i>pitchTranspose</i></c> member, and sceScreamAutoPitchTranspose(). <b>Note:</b> Transposition amounts up to 5 octaves may not always be possible due to sampling rate constraints and/or limits of audibility.
#define SCE_SCREAM_SND_MAX_DUCKERS                              32          ///< The total number of volume duckers available for simultaneous activation. See sceScreamSetMasterVolumeDucker().
#define SCE_SCREAM_SND_MAX_LFOS_PER_INSTANCE                    4           ///< The maximum number of LFOs allowed per Sound instance. See the SceScreamLFOParameters structure's <c><i>whichLFO</i></c> member.
#define SCE_SCREAM_SND_MAX_VOLUME_GROUPS                        32          ///< The maximum number of system-wide Volume Groups. See sceScreamGetMasterVolume(), sceScreamSetMasterVolume(), sceScreamSetGroupVoiceRange().
#define SCE_SCREAM_SND_MAXLISTENERS                             16          ///< The maximum number of system-wide 3-D sound spatialization listeners. See sceScreamCreateListener().
#define SCE_SCREAM_SND_MAX_NAME_LENGTH                          257         ///< Maximum character length of a Sound name (256), plus one extra character for NULL-termination. See the sceScreamBankGetSoundNameByIndex() <c><i>soundName</i></c> parameter. <b>Note:</b> Use of many Sounds with long names may result in a small processor overhead.
#define SCE_SCREAM_SND_MAX_BANK_NAME_LENGTH                     9           ///< Maximum character length of a Bank (8), plus one extra character for NULL-termination. See the sceScreamFindLoadedBankNameByPointer() <c><i>outBankName</i></c> parameter.
/**@}*/

// System defaults.
/**
@defgroup screamSystemDefaults Scream System Defaults
@brief System defaults are values used by the sceScreamFillDefaultScreamPlatformInitArgsEx2() function when filling a SceScreamPlatformInitEx2 structure with default values.
@{*/
#define SCE_SCREAM_SND_DEFAULT_INIT_FLAGS                       SCE_SCREAM_SSS_FLAGS_RETURN_ON_BAD_PARAM    ///< Default initialization flags. See SceScreamPlatformInitEx2 <c><i>initFlags</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_PLAYBACK_MODE                    SCE_SCREAM_SPEAKER_MODE_STEREO              ///< Default playback mode. See the SceScreamPlatformInitEx2 <c><i>playbackMode</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MAX_LFOS                         10                                          ///< Default maximum allowable number of system-wide LFOs. See the SceScreamPlatformInitEx2 <c><i>maxLFOs</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_LFO_UPDATE                       0.0084f                                     ///< Default LFO update interval. Expressed in seconds (equivalent to 2 Scream ticks). See the SceScreamPlatformInitEx2 <c><i>lfoUpdateRate</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_DUCKER_UPDATE                    0.0167f                                     ///< Default ducker update interval. Expressed in seconds (equivalent to 4 Scream ticks). See the SceScreamPlatformInitEx2 <c><i>duckerUpdateRate</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_GROUP_MIXER_UPDATE               0.0167f                                     ///< Default group mixer update interval. Expressed in seconds (equivalent to 4 Scream ticks). See the SceScreamPlatformInitEx2 <c><i>groupMixerUpdateRate</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_CCSOUND_UPDATE                   0.0084f                                     ///< Default CCSound update interval. Expressed in seconds (equivalent to 2 Scream ticks). See the SceScreamPlatformInitEx2 <c><i>ccSoundUpdateRate</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MIN_RIPOFF_TIME                  0.25f                                       ///< Default minimum time a voice must be allowed to play before it can be stolen. Expressed in seconds. See the SceScreamPlatformInitEx2 <c><i>minRipoffTime</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MEM_ALLOC                        NULL                                        ///< Use default memory allocation function. <b>Note:</b> For platforms other than Windows, the application must provide memory allocation and free functions that conform to SceScreamExternSndMemAlloc() and SceScreamExternSndMemFree(). See the SceScreamPlatformInitEx2 <c><i>memAlloc</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MEM_FREE                         NULL                                        ///< Use default memory free function. <b>Note:</b> For platforms other than Windows, the application must provide memory allocation and free functions that conform to SceScreamExternSndMemAlloc() and SceScreamExternSndMemFree(). See the SceScreamPlatformInitEx2 <c><i>memFree</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MAX_BANKS                        1024                                        ///< Default maximum allowable number of loaded Banks. See the SceScreamPlatformInitEx2 <c><i>maxBanks</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MAX_SNAPSHOTS                    32                                          ///< Default maximum allowable number of simultaneously active group mixer snapshots. See the SceScreamPlatformInitEx2 <c><i>maxActiveSnapshots</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MAX_GLOBAL_VARIABLES             64                                          ///< Default maximum allowable number of global variables. See the SceScreamPlatformInitEx2 <c><i>maxGlobalVariables</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MAX_CCSOUNDS                     32                                          ///< Default maximum allowable number of simultaneously active CCSounds. See the SceScreamPlatformInitEx2 <c><i>maxCCSounds</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_DOPPLER_SLEW_RATE                240.0f                                      ///< Default Doppler velocity slew rate. Constrains the rate of change for Doppler velocity calculations. Expressed in meters-per-second squared. See the SceScreamPlatformInitEx2 <c><i>dopplerSlewRate</i></c> member.
#define SCE_SCREAM_SND_DEFAULT_MAX_POLYPHONY                    64                                          ///< Default maximum number of simultaneously playable voices, beyond which voice stealing is required. See the SceScreamPlatformInitEx2 <c><i>maxPolyphony</i></c> member.
/**@}*/

// TTY diagnostic print flags
/**
@defgroup ttyOutputFlags TTY Output Flags
@brief TTY output flags specify diagnostic output options. Apply them to the sceScreamOutputHandlerInfoToTTY() or sceScreamOutputAllPlayingSoundInfoToTTY() function's <c><i>flags</i></c> parameter.
@{*/
#define SCE_SCREAM_SND_OUTPUT_TTY_FLAGS      (1L <<  0)   ///< Include Sound instance flag information in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_TICK       (1L <<  1)   ///< Include the tick count time stamp when the Sound instance was started in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_GROUP      (1L <<  2)   ///< Include Sound instance Group index in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_GAIN       (1L <<  3)   ///< Include Sound instance gain factors in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_AZIMUTH    (1L <<  4)   ///< Include Sound instance pan azimuth information in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_FOCUS      (1L <<  5)   ///< Include Sound instance focus information in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_TRANSPOSE  (1L <<  6)   ///< Include Sound instance pitch transpose information in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_PITCHBEND  (1L <<  7)   ///< Include Sound instance pitchbend factors in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_REGISTERS  (1L <<  8)   ///< Include Sound instance registers information in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_VOICE_INFO (1L <<  9)   ///< Include Sound instance voice information in TTY output.
#define SCE_SCREAM_SND_OUTPUT_TTY_ALL        (SCE_SCREAM_SND_OUTPUT_TTY_FLAGS | SCE_SCREAM_SND_OUTPUT_TTY_TICK | SCE_SCREAM_SND_OUTPUT_TTY_GROUP | SCE_SCREAM_SND_OUTPUT_TTY_GAIN |\
                                   SCE_SCREAM_SND_OUTPUT_TTY_AZIMUTH | SCE_SCREAM_SND_OUTPUT_TTY_FOCUS | SCE_SCREAM_SND_OUTPUT_TTY_TRANSPOSE | SCE_SCREAM_SND_OUTPUT_TTY_PITCHBEND |\
                                   SCE_SCREAM_SND_OUTPUT_TTY_REGISTERS | SCE_SCREAM_SND_OUTPUT_TTY_VOICE_INFO) ///< Include all diagnostic data in TTY output.
/**@}*/

// Volume group definitions.
/**
@defgroup volumnGroups Volume Groups
@brief
Volume groups enable collective manipulation of constituent Sounds, including, but not limited to their volumes.
Sounds are assigned to Groups in Scream Tool, and saved with Bank contents.
@{*/
#define SCE_SCREAM_GROUP_VOLUME_SFX       0       ///< Sound effects Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_MUSIC     1       ///< Music Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_DIALOG    2       ///< Dialog Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_1    3       ///< User 1 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_2    4       ///< User 2 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_3    5       ///< User 3 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_4    6       ///< User 4 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_5    7       ///< User 5 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_6    8       ///< User 6 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_7    9       ///< User 7 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_8    10      ///< User 8 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_9    11      ///< User 9 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_10   12      ///< User 10 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_11   13      ///< User 11 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_12   14      ///< User 12 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_13   15      ///< User 13 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_14   16      ///< User 14 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_15   17      ///< User 15 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_16   18      ///< User 16 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_17   19      ///< User 17 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_18   20      ///< User 18 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_19   21      ///< User 19 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_20   22      ///< User 20 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_21   23      ///< User 21 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_22   24      ///< User 22 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_23   25      ///< User 23 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_24   26      ///< User 24 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_25   27      ///< User 25 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_26   28      ///< User 26 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_27   29      ///< User 27 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_USER_28   30      ///< User 28 Volume Group.
#define SCE_SCREAM_GROUP_VOLUME_EXTERNAL  31      ///< External Volume Group.
#define SCE_SCREAM_GROUP_MASTER_VOLUME    32      ///< Volume Groups master. Scales all other Volume Groups.
/**@}*/

/**
@defgroup groupFlags Group Flags
@brief
Group flags allow you to specify multiple groups as a single bit field value.
@{*/
#define SCE_SCREAM_GROUP_FLAG_SFX     (1L << SCE_SCREAM_GROUP_VOLUME_SFX)           ///< Sound effects Group flag.
#define SCE_SCREAM_GROUP_FLAG_MUSIC   (1L << SCE_SCREAM_GROUP_VOLUME_MUSIC)         ///< Music Group flag.
#define SCE_SCREAM_GROUP_FLAG_DIALOG  (1L << SCE_SCREAM_GROUP_VOLUME_DIALOG)        ///< Dialog Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_1  (1L << SCE_SCREAM_GROUP_VOLUME_USER_1)        ///< User 1 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_2  (1L << SCE_SCREAM_GROUP_VOLUME_USER_2)        ///< User 2 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_3  (1L << SCE_SCREAM_GROUP_VOLUME_USER_3)        ///< User 3 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_4  (1L << SCE_SCREAM_GROUP_VOLUME_USER_4)        ///< User 4 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_5  (1L << SCE_SCREAM_GROUP_VOLUME_USER_5)        ///< User 5 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_6  (1L << SCE_SCREAM_GROUP_VOLUME_USER_6)        ///< User 6 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_7  (1L << SCE_SCREAM_GROUP_VOLUME_USER_7)        ///< User 7 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_8  (1L << SCE_SCREAM_GROUP_VOLUME_USER_8)        ///< User 8 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_9  (1L << SCE_SCREAM_GROUP_VOLUME_USER_9)        ///< User 9 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_10 (1L << SCE_SCREAM_GROUP_VOLUME_USER_10)       ///< User 10 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_11 (1L << SCE_SCREAM_GROUP_VOLUME_USER_11)       ///< User 11 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_12 (1L << SCE_SCREAM_GROUP_VOLUME_USER_12)       ///< User 12 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_13 (1L << SCE_SCREAM_GROUP_VOLUME_USER_13)       ///< User 13 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_14 (1L << SCE_SCREAM_GROUP_VOLUME_USER_14)       ///< User 14 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_15 (1L << SCE_SCREAM_GROUP_VOLUME_USER_15)       ///< User 15 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_16 (1L << SCE_SCREAM_GROUP_VOLUME_USER_16)       ///< User 16 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_17 (1L << SCE_SCREAM_GROUP_VOLUME_USER_17)       ///< User 17 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_18 (1L << SCE_SCREAM_GROUP_VOLUME_USER_18)       ///< User 18 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_19 (1L << SCE_SCREAM_GROUP_VOLUME_USER_19)       ///< User 19 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_20 (1L << SCE_SCREAM_GROUP_VOLUME_USER_20)       ///< User 20 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_21 (1L << SCE_SCREAM_GROUP_VOLUME_USER_21)       ///< User 21 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_22 (1L << SCE_SCREAM_GROUP_VOLUME_USER_22)       ///< User 22 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_23 (1L << SCE_SCREAM_GROUP_VOLUME_USER_23)       ///< User 23 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_24 (1L << SCE_SCREAM_GROUP_VOLUME_USER_24)       ///< User 24 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_25 (1L << SCE_SCREAM_GROUP_VOLUME_USER_25)       ///< User 25 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_26 (1L << SCE_SCREAM_GROUP_VOLUME_USER_26)       ///< User 26 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_27 (1L << SCE_SCREAM_GROUP_VOLUME_USER_27)       ///< User 27 Group flag.
#define SCE_SCREAM_GROUP_FLAG_USER_28 (1L << SCE_SCREAM_GROUP_VOLUME_USER_28)       ///< User 28 Group flag.
#define SCE_SCREAM_GROUP_FLAG_EXTERNAL (1L << SCE_SCREAM_GROUP_VOLUME_EXTERNAL)     ///< External Group flag.
#define SCE_SCREAM_GROUP_FLAG_ALL     (0xFFFFFFFF)                                  ///< Global Group flag. Includes all other Group flags.
/**@}*/

// Speaker output modes
/**
@defgroup playbackModes Playback Modes
@brief You use the playback mode constants when setting or retrieving the current playback mode with the sceScreamSetPlaybackMode() and sceScreamGetPlaybackMode() functions. It is initially set in the <c><i>playbackMode</i></c> member of the SceScreamPlatformInitEx2 structure.
@{*/
#define SCE_SCREAM_SPEAKER_MODE_STEREO     (0)              ///< Stereo output mode.
#define SCE_SCREAM_SPEAKER_MODE_DPL2       (2)              ///< Dolby Pro Logic II surround sound output mode.
#define SCE_SCREAM_SPEAKER_MODE_BEST       (6)              ///< Auto-configures optimal playback mode at initialization time. <b>Note:</b> This option is valid only at initialization time, and cannot be used as an argument to sceScreamSetPlaybackMode(). To verify the chosen playback mode, you can call sceScreamGetPlaybackMode() after initializing Scream.

// Speaker output targets
/**
@defgroup outputSpeakerTargets Output Speaker Targets
@brief The output speaker targets allow you to set the SceScreamSoundParams <c><i>azimuth</i></c> member to a specific speaker target, rather than a panning azimuth. Combine the #SCE_SCREAM_SND_PAN_TO_SPEAKER flag with one of the specific speaker targets.
@{*/
#define SCE_SCREAM_SND_PAN_TO_SPEAKER 0x80000000                                    ///< Indicates a specific speaker target, rather than a panning azimuth. Must be combined, using the bitwise <c>OR</c> operator, with any one of the output speaker targets below.
#define SCE_SCREAM_SND_PAN_FL         (SCE_SCREAM_SND_PAN_TO_SPEAKER | 1)           ///< The Front Left speaker.
#define SCE_SCREAM_SND_PAN_FR         (SCE_SCREAM_SND_PAN_TO_SPEAKER | 2)           ///< The Front Right speaker.

// Used with sceScreamSetScriptSpeedFactor
/**
@defgroup scriptSpeedFlags Script Speed Flags
@brief
Script speed flags provide optional behaviors for variable speed replays.
@{*/
#define SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_PITCH     (1L << 0)               ///< Flag option for sceScreamSetScriptSpeedFactor() and sceScreamSetGroupScriptSpeedFactor(). By default, variable speed replay affects time domain scripting properties only. Set this flag if you want variable speed replay to affect the pitch domain also.
#define SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_ADSR      (1L << 1)               ///< Flag option for sceScreamSetScriptSpeedFactor() and sceScreamSetGroupScriptSpeedFactor(). By default, variable speed replay does not affect ADSR envelope durations. Set this flag if you want variable speed replay to scale the durations of ADSR segments also.
/**@}*/

// Automated parameter change.
/**
@defgroup automatedParameterChangeFlags Automated Parameter Change Flags
@brief Optional behavior flags for the automated parameter change functions. For Scream details, see &quot;Applying Automated Changes to Parameter Values&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>. For Sndstream details, see &quot;Automated Incremental Settings&quot; in the &quot;Manipulating an Active Stream&quot; chapter of the <i>Sndstream Library Overview</i>.
@{*/
#define SCE_SCREAM_SND_AUTO_STOP_AT_DESTINATION     (1L << 0)           ///< Specifies that, upon reaching its target value, a Sound should stop. See  the Scream functions sceScreamAutoPan(), sceScreamAutoPitchTranspose(), sceScreamAutoPitchBend(), sceScreamAutoGain(), and the Sndstream function sceScreamAutoStreamLayerParams().
#define SCE_SCREAM_SND_AUTO_REVERT_IF_ACTIVE        (1L << 1)           ///< Specifies that an automated parameter change that is still active (has not yet reached its target value) should return to its original value at the same rate of change as it set out with. See the Scream functions sceScreamAutoPan(), sceScreamAutoPitchTranspose(), sceScreamAutoPitchBend(), sceScreamAutoGain(), and the Sndstream function sceScreamAutoStreamLayerParams().
#define SCE_SCREAM_SND_AUTO_COUNTER_CLOCKWISE       (1L << 2)           ///< Specifies that a panning parameter change should go in reverse direction, producing a counter-clockwise panning motion. See the Scream function sceScreamAutoPan() and the Sndstream function sceScreamAutoStreamLayerParams().
#define SCE_SCREAM_SND_AUTO_TAKE_SHORTEST_PATH      (1L << 3)           ///< Specifies that a panning parameter change should go in whichever direction, clockwise or counter-clockwise, that provides the shortest path to the target. See the Scream function sceScreamAutoPan() and the Sndstream function sceScreamAutoStreamLayerParams().
#define SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR     (1L << 5)           ///< Specifies that an automated parameter change uses an automation-specific parameter factor in the appropriate structure, rather than the default API parameter factor. See the Scream functions sceScreamAutoPan(), sceScreamAutoPitchTranspose(), sceScreamAutoPitchBend(), sceScreamAutoGain(), and the Sndstream function sceScreamAutoStreamLayerParams(). For more information, see &quot;Use Separate Factor&quot; in the &quot;Working with Sounds&quot; chapter of <i>Scream Library Overview</i>.
/**@}*/

// Memory usage subsystems
/**
@defgroup memoryAllocationConstants Memory Allocation Constants
@brief Memory allocation constants are passed to the memory allocation prototype SceScreamExternSndMemAlloc() <c><i>use</i></c> parameter to indicate subsystem memory consumption. When Scream calls the application’s SceScreamExternSndMemAlloc() function, it uses the appropriate constant in the <c><i>use</i></c> parameter, depending on how Scream will be using that memory.
@{*/
#define SCE_SCREAM_SND_MEM_USE_SYNTH                    0               ///< Indicates that requested memory is to be used for the underlying synthesizer (does not include reverb instances).  The application receives this constant in the <c><i>use</i></c> parameter when calling sceScreamStartSoundSystemEx2() to start the sound system.
#define SCE_SCREAM_SND_MEM_USE_BANK                     1               ///< Indicates that requested memory is to be used for Banks. The application receives this constant in the <c><i>use</i></c> parameter when calling sceScreamBankLoadEx() to load a Bank.
#define SCE_SCREAM_SND_MEM_USE_REVERB                   2               ///< Indicates that requested memory is to be used for reverb instance processing. The application receives this constant in the <c><i>use</i></c> parameter when allocating a reverb instance.
#define SCE_SCREAM_SND_MEM_USE_PRESETS                  3               ///< Indicates that requested memory is to be used for storing effects presets.
#define SCE_SCREAM_SND_MEM_USE_DECODE                   4               ///< Indicates that requested memory is to be used for storing temporary decoded data.
#define SCE_SCREAM_SND_MEM_USE_CCS                      5               ///< Indicates that requested memory is to be used for managing the Continuous Controller Sound system.
#define SCE_SCREAM_SND_MEM_USE_GLOBAL_VARS              6               ///< Indicates that requested memory is to be used for managing the global variable system. See the SceScreamPlatformInitEx2 <c><i>maxGlobalVariables</i></c> member.
/**@}*/

// Event callback reasons
/**
@defgroup callbackConstants Callback Constants
@brief
Callback constants are used to communicate state information back to the host application.
@{*/
#define SCE_SCREAM_SND_EVENT_CB_REASON_FINISHED         0               ///< An event callback is issued because the specified Sound instance has completely finished and is about to be deactivated and a Sound event callback was set up. See the SceScreamSndEventCallback() type definition's <c><i>reason</i></c> parameter. For information on setting up this callback, see &quot;Configuring Sound Event Callbacks&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.
#define SCE_SCREAM_SND_EVENT_CB_REASON_DESTROYED        1               ///< An event callback is issued because the specified effect instance has been completely destroyed, and it is now safe to recover the associated memory. See the SceScreamSndEventCallback() type definition's <c><i>reason</i></c> parameter.
#define SCE_SCREAM_SND_EVENT_CB_REASON_SCREAM_TICK      2               ///< An event callback is issued because Scream was initialized with #SCE_SCREAM_SSS_FLAGS_TICK_CALLBACK, requesting a system-wide per-tick application callback. See the SceScreamSndEventCallback() type definition's <c><i>reason</i></c> parameter. For information on setting up this callback, see &quot;Configuring Per-Tick Callbacks&quot; in the &quot;Working with System Globals&quot; chapter of the <i>Scream Library Overview</i>.
#define SCE_SCREAM_SND_EVENT_CB_REASON_POST_SYNTH_INIT  3               ///< This event callback provides an opportunity for applications to make direct synthesizer calls: after Scream has initialized the underlying synth &mdash; but before synth processing begins. It is issued from the application's main thread during the sceScreamStartSoundSystemEx2() function call. See the SceScreamSndEventCallback() type definition's <c><i>reason</i></c> parameter.
#define SCE_SCREAM_SND_EVENT_CB_REASON_NO_RENDER_SUBMIX 4               ///< An event callback is issued because Scream was unable to allocate the requested rendering submix voice for the specified Sound. See the SceScreamSndEventCallback() type definition's <c><i>reason</i></c> parameter.
/**@}*/

// Sound output destinations for use when specifying the outputDest member of SceScreamSynthParams
#ifdef LIBSCREAM_API
/**
@defgroup outputDestinations Output Destinations
@brief You use Sound output destinations when specifying a value for the <c><i>outputDest</i></c> parameter in such functions as sceScreamSetGroupVoiceOutputDest(), sceScreamPlaySoundByIndexEx(), and sceScreamPlaySoundByNameEx().
@{*/
#endif
#ifdef LIBSNDSTREAM_API
/**
@defgroup outputDestinations Output Destinations
@brief You use Sound output destinations when specifying a value for the <c><i>outputDest</i></c> parameter in such functions as sceScreamStartStream() and sceScreamStartStreamByFileToken().
@{*/
#endif
#define SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0          0               ///< Specifies that a Sound's output destination is a pre-master submix. This constant expresses the first pre-master submix index. Add 1 to this value for each additional pre-master submix index. The number of available pre-master submixes is determined at initialization time using the  Scream SceScreamSystemParams structure's <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members.
#define SCE_SCREAM_SND_OUTPUT_DEST_MASTER               (-1)            ///< Specifies that a Sound's output destination is the master output.
#define SCE_SCREAM_SND_OUTPUT_DEST_BY_GROUP             (-2)            ///< Specifies that a Sound's output destination is inherited from that specified for the Group the Sound belongs to.
/**@}*/

// Polar pan channel indices and count
/**
@defgroup polarPanSpeakerChannelIndices Speaker Channel Indices
@brief These constants identify channel data per target speaker.
They are used when retrieving output levels with the sceScreamGetMasterOutputLevel() function.
*/
#define SCE_SCREAM_SND_POLPAN_INDEX_FL                 1       ///< Index of the Front-Left channel.
#define SCE_SCREAM_SND_POLPAN_INDEX_FR                 6       ///< Index of the Front-Right channel.

// Signal level constants used when interpreting return values from sceScreamGetMasterOutputLevel
/**
@defgroup outputLevelConstants Output Level Constants
@brief The output level constants define ranges of dB and linear output level values returned by the sceScreamGetMasterOutputLevel() function.
@{*/
#define SCE_SCREAM_SND_LEVEL_DB_MINIMUM        (-90.0f)        ///< Minimum decibel value. Indicates silence.
#define SCE_SCREAM_SND_LEVEL_DB_NOMINAL        (0.0f)          ///< Nominal decibel value. Indicates full-scale signal level. Values &ge; to this value indicate clipping.
#define SCE_SCREAM_SND_LEVEL_LINEAR_MINIMUM    (0.0f)          ///< Minimum linear value. Indicates silence.
#define SCE_SCREAM_SND_LEVEL_LINEAR_NOMINAL    (1.0f)          ///< Nominal linear value. Indicates full-scale signal level. Values &ge; to this value indicate clipping.
/**@}*/

// Polar pan reverb tiling modes and output target exclusions
// The reverb tiling modes are used for upmixing multi-channel reverb input to a greater number of multi-channel outputs. They are optional values for sceScreamLR1SetVolumePolar() mode parameter.
// The output target exclusion flags exclude the designated channels as reverb polar-panning targets. They are optional values for sceScreamLR1SetVolumePolar() excludeTargets parameter.
// See the section 'Reverb Tiling Mode and Output Target Exclusion' in Chapter 11 of the <i>Scream Library Overview</i> for further information.
#define SCE_SCREAM_SND_POLPAN_MODE_TILE_LOOP            1       ///< Loop mode maps input channels in a forward looping pattern around the output speaker index.
#define SCE_SCREAM_SND_POLPAN_MODE_TILE_MIRROR          2       ///< Mirror mode is the same as loop mode except the pattern repeats in retrograde on reaching the last input channel.
#define SCE_SCREAM_SND_POLPAN_MODE_TILE_SPLITSTEREO     3       ///< Split stereo mode discards the Surround Left/Right input channels, and maps the Front Left/Right channels across the center median of the output speakers.

#define SCE_SCREAM_SND_POLPAN_EXCLUDE_CENTER    (1L << 0)       ///< Excludes the Center channel as a reverb polar-panning target.
#define SCE_SCREAM_SND_POLPAN_EXCLUDE_FL_FR     (1L << 1)       ///< Excludes both the Front Left and Front Right channels as reverb polar-panning targets. Exclusion of the Front Left and Front Right channels from reverb polar-panning targets allows you to apply reverb to the rear surround sound channels only if they are present. That is, with the Front-Left and Front-Right channels excluded, and focus set to 360, reverb will come from the rear surround speakers <i>only</i> &mdash; with no reverb at all in stereo Playback mode.
////////////////////////////////////////////////////////////////////////////////
// Data Types
/**
@defgroup screamTypeDefinitions Scream Type Definitions
@brief
Scream type definitions define data types for APIs that are common to all supported platforms and synthesizers.
@{*/
/**
@brief
Prototype for a Scream debug text output function.

Scream invokes this function prototype whenever text output occurs, enabling applications to funnel all TTY output to a single location (for example, screen, log file, custom application, and so on).
Set this function by calling sceScreamSetDebugHandler().

@param message (Input)
A pre-formatted text string containing debug or general information.

@note
If no application-defined SceScreamSndDebugHandler() is specified, a standard <c>printf()</c>-like function is used by default.

@note
You can set this application-defined SceScreamSndDebugHandler() prior to initializing Scream.
This is recommended, as much information is produced during the initialization process.

@see
sceScreamSetDebugHandler(), sceScreamOutputHandlerInfoToTTY(), sceScreamOutputAllPlayingSoundInfoToTTY()
*/
typedef void (*SceScreamSndDebugHandler)(const char* message);
/**@}*/

/**
@ingroup screamTypeDefinitions

@brief
Prototype for a Scream memory allocation callback function.

Scream invokes the SceScreamExternSndMemAlloc() callback function prototype whenever memory allocation is required.
This provides a way to customize memory allocation functionality. The required type of memory allocation
is passed to the function, allowing you to determine how best to allocate the memory.

@param bytes (Input)
The number of bytes required.

@param use (Input)
The type of memory required. One of the \link #SCE_SCREAM_SND_MEM_USE_BANK Memory Allocation Constants\endlink.

@return
The return value is a <c>void</c> pointer to the allocated memory.

@note
Allocated memory should be 16-byte aligned.

@see
SceScreamExternSndMemFree()

*/
typedef void* (*SceScreamExternSndMemAlloc)(int32_t bytes, int32_t use);

/**
@ingroup screamTypeDefinitions

@brief
Prototype for a Scream memory release callback function.

Scream invokes the SceScreamExternSndMemFree() callback function prototype whenever memory release is required.
This provides a way to customize memory release functionality.

@param mem (Input)
Void pointer to memory allocated by the prototype SceScreamExternSndMemAlloc() function.

@see
SceScreamExternSndMemAlloc()
*/
typedef void  (*SceScreamExternSndMemFree)(void *mem);

/**
@ingroup screamTypeDefinitions

@brief
Prototype for the Scream event callback function.

This is a prototype for the Scream event callback function.
If registered in the SceScreamPlatformInitEx2 <c><i>eventCallback</i></c> member, Scream invokes this callback function whenever an event takes place for which a given Sound or Effect instance has requested a callback.
The Sound or Effect handle, along with a user-specified context value, and a reason value are passed to the client.

For information on using this callback, see &quot;Configuring Sound Event Callbacks&quot; in the &quot;Working with Sounds&quot; chapter, and &quot;Configuring Per-Tick Callbacks&quot; in the &quot;Working with System Globals&quot; chapter of the <i>Scream Library Overview</i>.

@param handle (Output)
Handle of the Sound or Effect for which the callback is being issued.

@param userCtx (Output)
The user context value most recently set in the Sound's SceScreamSoundParams structure’s <c><i>userCtx</i></c> member, or <c>NULL</c> if the handle is for an Effect instance.

@param reason (Output)
One of the \link #SCE_SCREAM_SND_EVENT_CB_REASON_FINISHED Callback Constants\endlink specifying the reason this callback is being issued.

@note
<b>WARNING</b>: Because this function may be called from the synthesizer thread, it is critical that processing performed
within this callback be kept to an absolute minimum! Otherwise, audio dropouts may occur.

@see
SceScreamPlatformInitEx2, SceScreamSoundParams
*/
typedef void (*SceScreamSndEventCallback)(uint32_t handle, void* userCtx, uint32_t reason);

/**
@defgroup screamDataStructures Scream Data Structures
@brief Scream data structures store data applicable to APIs that are common to all supported platforms and synthesizers.
@{*/

/**
@brief
Stores Scream platform initialization values.

This structure stores initialization values for the Scream platform. It is used in a call to sceScreamFillDefaultScreamPlatformInitArgsEx2(),
which initializes the structure with default values for each member, as specified above. sceScreamFillDefaultScreamPlatformInitArgsEx2() also
initializes the embedded SceScreamSystemParams structure with default values.
The sceScreamStartSoundSystemEx2() function uses this structure to initialize Scream.

@note
The <c><i>initFlags</i></c> member provides two &ndash; mutually exclusive &ndash; options for function-level parameter validation:
#SCE_SCREAM_SSS_FLAGS_RETURN_ON_BAD_PARAM (default), and #SCE_SCREAM_SSS_FLAGS_HALT_ON_BAD_PARAM. Users can also set <c><i>initFlags</i></c> to include <i>neither</i> of these options,
which allows execution to proceed even if one or more parameter values are bad. Note however, that this may produce unpredictable behaviors or cause Scream to crash.

@note
When initializing Scream, you can set <c><i>playbackMode</i></c> to #SCE_SCREAM_SPEAKER_MODE_BEST, which auto-configures Scream to use the optimal playback mode on the host system.
Playback mode can also be changed at run time with a call to sceScreamSetPlaybackMode(); call sceScreamGetPlaybackMode() to determine which mode was selected.

@note
The <c><i>lfoUpdateRate</i></c> and <c><i>duckerUpdateRate</i></c> members are expressed as floating-point values in fractions of a second.
In practice, however, specified values are rounded to the nearest Scream tick (equivalent to one 240<sup>th</sup> of a second).

@note
There is no upper limit to the value specified for the <c><i>maxBanks</i></c> member.
The memory cost on the PlayStation&reg;Vita/NGS platform is 4 bytes per Bank.

@note
The approximate memory overhead for a single voice of polyphony is 120 bytes.
So, for example, with default maximum polyphony, the dynamic memory requirement when calling sceScreamStartSoundSystemEx2() is around 7.5 kB.

@see
sceScreamFillDefaultScreamPlatformInitArgsEx2(), SceScreamSystemParams, sceScreamStartSoundSystemEx2(), SceScreamExternSndMemAlloc(), SceScreamExternSndMemFree(), SceScreamSndEventCallback()
*/
typedef struct SceScreamPlatformInitEx2
{
    uint32_t                            size;                   ///< The size of this data structure; use <c>sizeof(SceScreamPlatformInitEx2)</c> to determine.
    uint32_t                            initFlags;              ///< Any combination of the \link #SCE_SCREAM_SSS_FLAGS_SILENT Initialization Flags\endlink. Defaults to #SCE_SCREAM_SND_DEFAULT_INIT_FLAGS. See &quot;Notes&quot; below.
    uint32_t                            playbackMode;           ///< Initial \link #SCE_SCREAM_SPEAKER_MODE_STEREO Playback Mode\endlink. Defaults to #SCE_SCREAM_SND_DEFAULT_PLAYBACK_MODE. See &quot;Notes&quot; below.
    uint32_t                            maxLFOs;                ///< Maximum allowable number of system-wide LFOs. Minimum: 0. Defaults to #SCE_SCREAM_SND_DEFAULT_MAX_LFOS.
    float                               lfoUpdateRate;          ///< Interleave LFO update interval. Expressed in fractions of a second. Range: 0.0 to 1.0. Set to 0.0 for no LFO processing. Defaults to #SCE_SCREAM_SND_DEFAULT_LFO_UPDATE.
    float                               duckerUpdateRate;       ///< Volume ducker update interval. Expressed in fractions of a second. Range: 0.0 to 1.0. Set to 0.0 for no ducker processing. Defaults to #SCE_SCREAM_SND_DEFAULT_DUCKER_UPDATE.
    float                               groupMixerUpdateRate;   ///< Group mixer update interval. Expressed in fractions of a second. Range: 0.0 to 1.0. Set to 0.0 for no group mixer processing. Defaults to #SCE_SCREAM_SND_DEFAULT_GROUP_MIXER_UPDATE.
    float                               ccSoundUpdateRate;      ///< Continuous Controller Sound (CCSound) update interval. Expressed in fractions of a second. Range: 0.0 to 1.0. Set to 0.0 for no CCSound processing. Defaults to #SCE_SCREAM_SND_DEFAULT_CCSOUND_UPDATE.
    float                               minRipoffTime;          ///< Minimum time that a voice must be allowed to play before it can be stolen. Expressed in seconds. Recommended range: 0.25 to 5.0. Setting to 0.0 specifies that voices are immediately available for stealing. Defaults to #SCE_SCREAM_SND_DEFAULT_MIN_RIPOFF_TIME.
    SceScreamExternSndMemAlloc          memAlloc;               ///< Address of an application-defined memory allocation function. See SceScreamExternSndMemAlloc(). Defaults to #SCE_SCREAM_SND_DEFAULT_MEM_ALLOC. <b>Note:</b> For platforms other than Windows, the application must provide a memory allocation function. On Windows, you can set <c><i>memAlloc</i></c> to <c>NULL</c> to use an internal memory allocation function.
    SceScreamExternSndMemFree           memFree;                ///< Address of an application-defined memory free function. See SceScreamExternSndMemFree(). Defaults to #SCE_SCREAM_SND_DEFAULT_MEM_FREE. <b>Note:</b> For platforms other than Windows, the application must provide a memory free function. On Windows, you can set <c><i>memFree</i></c> to <c>NULL</c> to use an internal memory free function.
    SceScreamSndEventCallback           eventCallback;          ///< Address of a single application-defined event callback function. See SceScreamSndEventCallback(). Defaults to <c>NULL</c>. For information on using this callback, see &quot;Configuring Sound Event Callbacks&quot; in the &quot;Working with Sounds&quot; chapter, and &quot;Configuring Per-Tick Callbacks&quot; in the &quot;Working with System Globals&quot; chapter of the <i>Scream Library Overview</i>.
    uint32_t                            maxBanks;               ///< Maximum allowable number of loaded banks.  Minimum: 1.  Defaults to #SCE_SCREAM_SND_DEFAULT_MAX_BANKS. See &quot;Notes&quot; below.
    uint32_t                            maxPolyphony;           ///< Maximum allowable number of simultaneous voices (of all types). Range: 1 to 512. Defaults to #SCE_SCREAM_SND_DEFAULT_MAX_POLYPHONY. See &quot;Notes&quot; below.
    uint32_t                            maxActiveSnapshots;     ///< Maximum allowable number of simultaneously active group mixer snapshots. Defaults to #SCE_SCREAM_SND_DEFAULT_MAX_SNAPSHOTS. You can effectively disable the group mixer system by setting this member to zero.
    uint32_t                            maxGlobalVariables;     ///< Maximum allowable number of global variables. Defaults to #SCE_SCREAM_SND_DEFAULT_MAX_GLOBAL_VARIABLES.
    uint32_t                            maxCCSounds;            ///< Maximum allowable number of simultaneously active CCSounds. Defaults to #SCE_SCREAM_SND_DEFAULT_MAX_CCSOUNDS.
    float                               dopplerSlewRate;        ///< The slew rate for Doppler velocity calculations, specifying the maximum allowable velocity change per second. Expressed in meters-per-second squared. Defaults to #SCE_SCREAM_SND_DEFAULT_DOPPLER_SLEW_RATE.
    void*                               pGroupMixerFile;        ///< Optional memory pointer to a pre-loaded group mixer file (<c>GMX</c>). Defaults to <c>NULL</c>. See sceScreamActivateMixSnapshot() and other group mix functions.
    uint32_t                            groupMixerFileSize;     ///< Values for this member are ignored. It is no longer necessary to specify the size of a group mixer file.
    void*                               pBussConfigFile;        ///< Optional memory pointer to a pre-loaded buss configuration file (<c>BUS</c>); also known as an effect presets file. Defaults to <c>NULL</c>. See sceScreamApplyBussPreset().
    uint32_t                            bussConfigFileSize;     ///< Values for this member are ignored. It is no longer necessary to specify the size of a buss configuration file.
    void*                               pDistanceModelFile;     ///< Optional memory pointer to a pre-loaded distance model file (<c>DML</c>). Defaults to <c>NULL</c>.
    // synth-specific parameters
    SceScreamSystemParams               synthParams;            ///< An embedded SceScreamSystemParams structure, containing parameters required for configuring the underlying synthesizer.
} SceScreamPlatformInitEx2;
/**@}*/

/**
@ingroup screamDataStructures

@brief
Stores volume ducker parameter values.

This structure stores parameter values used for initializing a volume ducker. Scream provides for up to #SCE_SCREAM_SND_MAX_DUCKERS simultaneous volume duckers.

You reference the pointer returned on instantiating a SceScreamDuckerDef structure as an argument to the
sceScreamSetMasterVolumeDucker() function.

Volume ducking is the technique of reducing the volume of certain Sounds in order to highlight other Sounds.
For example, in a sports game, the volume level of crowd Sounds might be reduced during an announcement or commentary.

@see
sceScreamSetMasterVolumeDucker()
*/
typedef struct SceScreamDuckerDef
{
    int32_t         source_group;      ///< The \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Group\endlink that controls the volume ducker.
    uint32_t        target_groups;     ///< The Volume Group(s) to duck when <c><i>source_group</i></c> is playing sound. One or more of the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.
    float           full_duck_amt;     ///< The volume level of the <c><i>target_groups</i></c> when fully ducked.  Range: 0.0 to 1.0, where 0.0 is equal to a 100% volume duck; 0.5 is equal to a 50% volume duck; 1.0 is equal to a 0% volume duck, and so on.
    float           attack_time;       ///< The time taken for the <c><i>target_groups</i></c> volume to change from non-ducked to ducked level. Expressed in seconds. Range: 0.0 to 10.0.
    float           release_time;      ///< The time taken for the <c><i>target_groups</i></c> volume to return from ducked to non-ducked level. Expressed in seconds. Range: 0.0 to 10.0.
}SceScreamDuckerDef;

/**
@ingroup screamDataStructures
@brief
Stores the constituent gain components of a Sound instance.

This structure stores the constituent gain components of a Sound instance and is filled by a call to sceScreamGetSoundGainComponents().

@note
You can determine a Sound's aggregate gain level by multiplying together the values of its constituent gain components &mdash; with the exception of the <c><i>directSendGain</i></c> member, which relates to the synthesizer's auxiliary buss mechanism.

@note
By default, the automated gain change function sceScreamAutoGain() targets the <c><i>apiGain</i></c> component.
However, if you set the #SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR behavior flag when calling sceScreamAutoGain(), the function instead targets the <c><i>autoGain</i></c> component.

@see
sceScreamGetSoundGainComponents(), sceScreamAutoGain()
*/
typedef struct SceScreamGainComponents
{
    float         masterVolume;     ///< Master volume setting, Scream's global volume (as set by sceScreamSetMasterVolume(), with #SCE_SCREAM_GROUP_MASTER_VOLUME as the <c><i>which</i></c> parameter). Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float         snapshotsMaster;  ///< Group Mixer Master level based on currently active mix snapshots. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float         sfxGain;          ///< Original gain level set on the Sound instance by the content (that is, as defined in the Sound's data when loaded from a Bank). Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float         apiGain;          ///< Gain level set on the Sound instance from an API call, such as sceScreamAutoGain(). Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float         lfoGain;          ///< Gain factor created by an active LFO that is targeting the Sound (SceScreamLFOParameters <c><i>targetParam</i></c> parameter set to #SCE_SCREAM_SND_LFO_TARGET_VOL when calling sceScreamSetSoundInstanceLFO()). Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN. If no active LFO, value is set to 1.0f.
    float         autoGain;         ///< Gain factor of an automated gain change applied to the Sound. See &quot;Notes&quot; below. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float         groupGain;        ///< Gain level of the Sound's Volume Group set by sceScreamSetMasterVolume(). Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float         snapshotsGain;    ///< Gain level of the Group to which a Sound instance is assigned: Group's aggregate level from active mix snapshots. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float         duckerGain;       ///< Gain factor created by an active ducker activated by sceScreamSetMasterVolumeDucker(). Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN. If no active ducker, value is set at 1.0f.
    float         directSendGain;   ///< Level of the Sound's direct send gain (as set in the SceScreamSynthParams <c><i>directSendGain</i></c> member). Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
}SceScreamGainComponents;

/**
@ingroup screamDataStructures

@brief
Stores dynamic Sound instance 3D attenuation components.

This structure stores dynamic 3D attenuation component values, resulting from an active distance model on a Sound instance.
You can retrieve 3D component values from a Sound instance by calling the sceScreamSoundInstanceGet3DComponents() function, which stores its results in an array of SceScreamSnd3DComponents structures, one structure per Grain queried.

@see
sceScreamSoundInstanceGet3DComponents(), sceScreamSoundIndexGet3DDesignerParams(), sceScreamSoundNameGet3DDesignerParams(), sceScreamSoundInstanceGet3DDesignerParams(), SceScreamSnd3DGrainData
*/
typedef struct SceScreamSnd3DComponents
{
    float       dryGainFactor;      ///< Dry (or direct) signal gain factor applied to a Grain. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float       wetGainFactor;      ///< Wet (or auxiliary) signal gain factor applied to a Grain. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float       lfeGainFactor;      ///< LFE gain factor applied to a Grain. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    float       lpfCutoff;          ///< Air absorption (or direct path) low-pass filter cut-off frequency applied to a Grain. Range: 0.0 to 23,999.0 Hz.
    float       spreadFactor;       ///< Spread factor applied to a Grain. Range: 0.0 to 100.0. This factor maps to smart pan for split-channel assets, and to focus for multi-channel assets.
}SceScreamSnd3DComponents;

/**
@ingroup screamDataStructures
@brief
Stores LFO parameter values.

This structure stores parameter values used for setting an LFO on a Sound instance.
Scream provides for up to #SCE_SCREAM_SND_MAX_LFOS_PER_INSTANCE simultaneous LFOs per Sound instance.
To initialize or modify an LFO, you use the sceScreamSetSoundInstanceLFO() function, pointing to this structure in its <c><i>params</i></c> parameter.

@note
When modifying the parameters of a running LFO (whether set up from Bank contents or from the Scream API), only changes to rate and depth can be performed seamlessly.
Changes to all other parameters (for example, <c><i>shape</i></c>, <c><i>targetParam</i></c>, <c><i>startOffset</i></c>, and so on) cause the LFO to restart from the beginning of its shape.

@note
When using an LFO to modulate the <c><i>rate</i></c> or <c><i>depth</i></c> parameter of another LFO within the same Sound instance, you must ensure that the LFO you
specify in the <c><i>targetLFO</i></c> member is not the same LFO that you are setting in the <c><i>whichLFO</i></c> member.

@note
For further details about setting these parameters, see &quot;Initializing and Controlling Sound LFOs&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.

@see
sceScreamSetSoundInstanceLFO()
*/
typedef struct SceScreamLFOParameters
{
    uint8_t     whichLFO;               ///< One-based index of a Sound instance LFO to set.  Range: 1 to #SCE_SCREAM_SND_MAX_LFOS_PER_INSTANCE.
    uint8_t     targetParam;            ///< Target parameter to be modulated by the LFO. One of the \link #SCE_SCREAM_SND_LFO_TARGET_NONE LFO Target Constants\endlink.
    uint8_t     targetLFO;              ///< Where the LFO is modulating a parameter on another LFO (that is, <c><i>targetParam</i></c> is set to #SCE_SCREAM_SND_LFO_TARGET_LFO_RATE or #SCE_SCREAM_SND_LFO_TARGET_LFO_DEPTH), this member specifies the one-based index of the target LFO. Range: 1 to #SCE_SCREAM_SND_MAX_LFOS_PER_INSTANCE. See &quot;Notes&quot; below.
    uint8_t     setupFlags;             ///< Optional LFO shape behaviors. One or more of the \link #SCE_SCREAM_SND_LFO_SETUP_FLAG_INVERT LFO Setup Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.
    uint8_t     shape;                  ///< Shape of the LFO waveform.  One of the \link #SCE_SCREAM_SND_LFO_SHAPE_OFF LFO Shape Constants\endlink.
    int8_t      depth;                  ///< Modulation depth of the LFO. Expressed as a percentage of the target parameter's range. Range: 0 to 100.
    uint8_t     dutyCycle;              ///< Duty cycle of a square-shaped LFO waveform.  Applies only if <c><i>shape</i></c> is #SCE_SCREAM_SND_LFO_SHAPE_SQUARE. Range: 1 to 99. Default: 50. For further details about duty cycle, see &quot;Initializing and Controlling Sound LFOs&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.
    uint8_t     startOffset;            ///< A start offset into the LFO waveform. Expressed as a percentage of one cycle of the LFO <c><i>shape</i></c>.  Range: 0 to 100.
    float       rate;                   ///< Rate (or frequency) of the LFO. Expressed in Hertz (cycles per second). Range: 0.0 to 50.0.
    uint32_t    varNameHash;            ///< 32-bit hash of a named local variable to set. Applicable if <c><i>targetParam</i></c> is #SCE_SCREAM_SND_LFO_TARGET_LOCAL_VAR only. See the sceScreamGetHashFromName() function.
    float       varRangeMax;            ///< Maximum (upper) extent of local variable range when <c><i>depth</i></c> is 100. Applicable if <c><i>targetParam</i></c> is #SCE_SCREAM_SND_LFO_TARGET_LOCAL_VAR only.
    float       varRangeMin;            ///< Minimum (lower) extent of local variable range when <c><i>depth</i></c> is 100. Applicable if <c><i>targetParam</i></c> is #SCE_SCREAM_SND_LFO_TARGET_LOCAL_VAR only.
    uint32_t    paramMask;              ///< Specifies which members of this structure have valid settings. One or more of the \link #SCE_SCREAM_SND_LFO_MASK_TARGET_PARAM LFO Parameter Mask Constants\endlink. Use the bitwise <c>OR</c> operator for multiple selections.
}SceScreamLFOParameters;

// LFO shapes
/**
@defgroup lfoConstants LFO Constants
@brief LFO constants consist of LFO shapes, LFO target parameters, LFO setup flags, and LFO parameter masks.  For details about using these constants, see &quot;Initializing and Controlling Sound LFOs&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.
@{*/
#define SCE_SCREAM_SND_LFO_SHAPE_OFF            0                   ///< LFO shape is off. Apply to the SceScreamLFOParameters <c><i>shape</i></c> member.
#define SCE_SCREAM_SND_LFO_SHAPE_SINE           1                   ///< LFO shape is a sine wave. Apply to the SceScreamLFOParameters <c><i>shape</i></c> member.
#define SCE_SCREAM_SND_LFO_SHAPE_SQUARE         2                   ///< LFO shape is a square wave. Apply to the SceScreamLFOParameters <c><i>shape</i></c> member.
#define SCE_SCREAM_SND_LFO_SHAPE_TRIANGLE       3                   ///< LFO shape is a triangle wave. Apply to the SceScreamLFOParameters <c><i>shape</i></c> member.
#define SCE_SCREAM_SND_LFO_SHAPE_SAW            4                   ///< LFO shape is a sawtooth wave. Apply to the SceScreamLFOParameters <c><i>shape</i></c> member.
#define SCE_SCREAM_SND_LFO_SHAPE_RAND           5                   ///< LFO shape is a random wave. Apply to the SceScreamLFOParameters <c><i>shape</i></c> member.

// LFO targets
#define SCE_SCREAM_SND_LFO_TARGET_NONE          0                   ///< No LFO target.  Apply to the SceScreamLFOParameters <c><i>targetParam</i></c> member.
#define SCE_SCREAM_SND_LFO_TARGET_VOL           1                   ///< LFO target is a Sound's volume parameter. Apply to the SceScreamLFOParameters <c><i>targetParam</i></c> member.
#define SCE_SCREAM_SND_LFO_TARGET_PAN           2                   ///< LFO target is a Sound's pan (azimuth) parameter. Apply to the SceScreamLFOParameters <c><i>targetParam</i></c> member.
#define SCE_SCREAM_SND_LFO_TARGET_PITCH         3                   ///< LFO target is a Sound's pitch parameter. Apply to the SceScreamLFOParameters <c><i>targetParam</i></c> member.
#define SCE_SCREAM_SND_LFO_TARGET_PITCHBEND     4                   ///< LFO target is a Sound's pitchbend parameter. Apply to the SceScreamLFOParameters <c><i>targetParam</i></c> member.
#define SCE_SCREAM_SND_LFO_TARGET_LFO_RATE      5                   ///< LFO target is the rate parameter on another LFO within the same Sound instance. Apply to the SceScreamLFOParameters <c><i>targetParam</i></c> member.
#define SCE_SCREAM_SND_LFO_TARGET_LFO_DEPTH     6                   ///< LFO target is the depth parameter on another LFO within the same Sound instance. Apply to the SceScreamLFOParameters <c><i>targetParam</i></c> member.
#define SCE_SCREAM_SND_LFO_TARGET_LOCAL_VAR     7                   ///< LFO target is a named local variable belonging to a Sound instance. Apply to the SceScreamLFOParameters <c><i>targetParam</i></c> member.

// LFO setup flags
#define SCE_SCREAM_SND_LFO_SETUP_FLAG_INVERT                (1L << 0)   ///< Optional LFO behavior flag, specifies that the LFO shape is inverted. Apply to the SceScreamLFOParameters <c><i>setupFlags</i></c> member.
#define SCE_SCREAM_SND_LFO_SETUP_FLAG_RAND_START_OFFSET     (1L << 1)   ///< Optional LFO behavior flag, specifies that the LFO shape has a random start offset. Apply to the SceScreamLFOParameters <c><i>setupFlags</i></c> member.

// LFO parameter masks
#define SCE_SCREAM_SND_LFO_MASK_TARGET_PARAM    (1L << 0)           ///< The SceScreamLFOParameters <c><i>targetParam</i></c> member has been set. Apply one or more of the LFO member masks to the SceScreamLFOParameters <c><i>paramMask</i></c> member.
#define SCE_SCREAM_SND_LFO_MASK_TARGET_LFO      (1L << 1)           ///< The SceScreamLFOParameters <c><i>targetLFO</i></c> member has been set. Apply one or more of the LFO member masks to the SceScreamLFOParameters <c><i>paramMask</i></c> member.
#define SCE_SCREAM_SND_LFO_MASK_SHAPE           (1L << 2)           ///< The SceScreamLFOParameters <c><i>shape</i></c> member has been set. Apply one or more of the LFO member masks to the SceScreamLFOParameters <c><i>paramMask</i></c> member.
#define SCE_SCREAM_SND_LFO_MASK_RATE            (1L << 3)           ///< The SceScreamLFOParameters <c><i>rate</i></c> member has been set. Apply one or more of the LFO member masks to the SceScreamLFOParameters <c><i>paramMask</i></c> member.
#define SCE_SCREAM_SND_LFO_MASK_DEPTH           (1L << 4)           ///< The SceScreamLFOParameters <c><i>depth</i></c> member has been set. Apply one or more of the LFO member masks to the SceScreamLFOParameters <c><i>paramMask</i></c> member.
#define SCE_SCREAM_SND_LFO_MASK_START_OFFSET    (1L << 5)           ///< The SceScreamLFOParameters <c><i>startOffset</i></c> member has been set. Apply one or more of the LFO member masks to the SceScreamLFOParameters <c><i>paramMask</i></c> member.
#define SCE_SCREAM_SND_LFO_MASK_DUTY_CYCLE      (1L << 6)           ///< The SceScreamLFOParameters <c><i>dutyCycle</i></c> member has been set. Apply one or more of the LFO member masks to the SceScreamLFOParameters <c><i>paramMask</i></c> member.
#define SCE_SCREAM_SND_LFO_MASK_LOCAL_VAR       (1L << 7)           ///< The SceScreamLFOParameters <c><i>varNameHash</i></c>, <c><i>varRangeMax</i></c>, and <c><i>varRangeMin</i></c> members have been set. Apply one or more of the LFO member masks to the SceScreamLFOParameters <c><i>paramMask</i></c> member.
/**@}*/

/**
@ingroup screamDataStructures

@brief
Stores the basic designer parameters associated with a Sound.

This structure stores the basic designer parameters associated with a Sound, resulting from a call to sceScreamGetSoundIndexDesignerParams(), sceScreamGetSoundNameDesignerParams(), or sceScreamGetSoundInstanceDesignerParams().

@see
sceScreamGetSoundIndexDesignerParams(), sceScreamGetSoundNameDesignerParams(), sceScreamGetSoundInstanceDesignerParams()
*/
typedef struct SceScreamDesignerParams
{
    int8_t              vol;                ///< Original volume of the Sound as defined in the Sound's data when loaded from a Bank. Specified in linear units, ranging from 0 to 127.
    int8_t              volGroup;           ///< Volume Group to which the Sound is assigned as defined in the Sound's data when loaded from a Bank.  One of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants.
    int16_t             pan;                ///< Original panning azimuth of the Sound as defined in the Sound's data when loaded from a Bank. Range: 0 to 359 degrees.
    int8_t              instanceLimit;      ///< Instance limit count of the Sound as defined in the Sound's data when loaded from a Bank, or -1 if no instance limiting is applied.
    bool                muteAtOuterRadius;  ///< For 3D Sounds, indicates whether distance model attenuation reaches silence as distance input reaches a Sound's Outer Radius setting.
    float               probabilityOfPlay;  ///< The probability that a Sound actually plays upon attempting playback (using the sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx() functions). Default: 1.0 (100%; designers set this value as a percentage). Note that with a probability value of 0.0, a Sound would never actually play!
    float               dopplerFactor;      ///< Doppler Factor. A value of 1.0 indicates a natural Doppler effect. Greater-than 1.0 indicates an exaggerated Doppler effect, and less-than 1.0 indicates a diminished effect. 0.0 indicates no Doppler effect. Defaults to 1.0.
}SceScreamDesignerParams;


/**
@ingroup screamDataStructures
@brief
Stores the constituent panning azimuth components of a Sound instance.

This structure stores the constituent panning azimuth components of a Sound instance and is filled by a call to sceScreamGetSoundPanAzimuthComponents().

@note
You can determine a Sound's aggregate panning azimuth by adding together the values of its constituent azimuth components modulo 360.

@note
By default, the automated panning azimuth change function sceScreamAutoPan() targets the <c><i>apiPanAzimuth</i></c> component.
However, if you set the #SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR behavior flag when calling sceScreamAutoPan(), the function instead targets the <c><i>autoPanAzimuth</i></c> component.

@see
sceScreamGetSoundPanAzimuthComponents(), sceScreamAutoPan()
*/
typedef struct SceScreamPanAzimuthComponents
{
    uint32_t         sfxPanAzimuth;   ///< Original panning azimuth set on the Sound instance by the content (that is, as defined in the Sound's data when loaded from a Bank). Range: 0 to 359.
    uint32_t         apiPanAzimuth;   ///< Panning azimuth set on the Sound instance from an API call, such as sceScreamAutoPan(). Range: 0 to 359.
    uint32_t         lfoPanAzimuth;   ///< Panning azimuth produced by an active LFO that is targeting the Sound (SceScreamLFOParameters <c><i>targetParam</i></c> parameter set to #SCE_SCREAM_SND_LFO_TARGET_PAN when calling sceScreamSetSoundInstanceLFO()). Range: 0 to 359. If no active LFO, value is set at 0.
    uint32_t         autoPanAzimuth;  ///< Panning azimuth offset of an automated panning azimuth change applied to the Sound. See &quot;Notes&quot; below. Range: 0 to 359.
}SceScreamPanAzimuthComponents;

/**
@ingroup screamDataStructures
@brief
Stores the constituent pitch transpose components of a Sound instance.

This structure stores the constituent pitch transpose components of a Sound instance and is filled by a call to sceScreamGetSoundPitchTransposeComponents().

@note
You can determine a Sound's aggregate pitch transposition by adding together the values of its constituent pitch components and clamping to #SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE.

@note
By default, the automated pitch transpose change function sceScreamAutoPitchTranspose() targets the <c><i>apiPitchTranspose</i></c> component.
However, if you set the #SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR behavior flag when calling sceScreamAutoPitchTranspose(), the function instead targets the <c><i>autoPitchTranspose</i></c> component.

@see
sceScreamGetSoundPitchTransposeComponents(), sceScreamAutoPitchTranspose()
*/
typedef struct SceScreamPitchTransposeComponents
{
    int32_t         sfxPitchTranspose;   ///< Original pitch transposition amount set on the Sound instance by the content (that is, as defined in the Sound's data when loaded from a Bank). Range: &ndash;#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE to +#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE.
    int32_t         apiPitchTranspose;   ///< Pitch transposition amount set on the Sound instance from an API call, such as sceScreamAutoPitchTranspose(). Range: &ndash;#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE to +#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE.
    int32_t         lfoPitchTranspose;   ///< Pitch transposition amount created by an active LFO (SceScreamLFOParameters <c><i>targetParam</i></c> parameter set to #SCE_SCREAM_SND_LFO_TARGET_PITCH when calling sceScreamSetSoundInstanceLFO()). Range: &ndash;#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE to +#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE. If no active LFO, value is set at 0.
    int32_t         autoPitchTranspose;  ///< Pitch transposition offset of an automated pitch transpose change applied to the Sound. See &quot;Notes&quot; below. Range: &ndash;#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE to +#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE.
}SceScreamPitchTransposeComponents;

/**
@ingroup screamDataStructures
@brief
Stores the constituent pitchbend factor components of a Sound instance.

This structure stores the constituent pitchbend factor components of a Sound instance and is filled by a call to sceScreamGetSoundPitchBendFactorComponents().

@note
You can determine a Sound's aggregate pitchbend factor by multiplying together the values of its constituent pitchbend components and clamping between #SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR and #SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR.

@note
By default, the automated pitchbend change function sceScreamAutoPitchBend() targets the <c><i>apiPitchBendFactor</i></c> component.
However, if you set the #SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR behavior flag when calling sceScreamAutoPitchBend(), the function instead targets the <c><i>autoPitchBendFactor</i></c> component.

@see
sceScreamGetSoundPitchBendFactorComponents(), sceScreamAutoPitchBend()
*/
typedef struct SceScreamPitchBendFactorComponents
{
    float         sfxPitchBendFactor;   ///< Original pitchbend factor amount set on the Sound instance by the content (that is, as defined in the Sound's data when loaded from a Bank). Range: #SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR to #SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR.
    float         apiPitchBendFactor;   ///< Pitchbend factor amount set on the Sound instance from an API call, such as sceScreamAutoPitchBend(). Range: #SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR to #SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR.
    float         lfoPitchBendFactor;   ///< Pitchbend factor amount created by an active LFO (SceScreamLFOParameters <c><i>targetParam</i></c> parameter set to #SCE_SCREAM_SND_LFO_TARGET_PITCHBEND when calling sceScreamSetSoundInstanceLFO()). Range: #SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR to #SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR. If no active LFO, value is set at 0.
    float         autoPitchBendFactor;  ///< Pitchbend factor of an automated pitchbend change applied to the Sound. See &quot;Notes&quot; below. Range: #SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR to #SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR.
}SceScreamPitchBendFactorComponents;

/**
@ingroup screamDataStructures
@brief
Stores coordinates used for 3D sound spatialization.

This structure stores coordinates used for 3D sound spatialization.
Use this structure to specify the location of a listener, the front- and top-orientation vectors
relative to the listener, and the location of sound-emitting objects.

@see
sceScreamCreateListener(), sceScreamDeleteListener(), sceScreamGetListener(), sceScreamSetListener(), sceScreamCalcSoundAngles()

*/
typedef struct SceScreamSnd3DVector
{
    float       fX;                 ///< X coordinate. Specifies a position on the left&harr;right axis. With respect to a listener's view of the screen: negative values are left of center; positive values are right of center.
    float       fY;                 ///< Y coordinate. Specifies a position on the down&harr;up axis. With respect to a listener's view of the screen: negative values are below center; positive values are above center.
    float       fZ;                 ///< Z coordinate. Specifies a position on the backward&harr;forward axis. With respect to a listener's view of the screen: negative values are out of the screen; positive values are into the screen.
}SceScreamSnd3DVector;

/**
@ingroup screamDataStructures

@brief
Stores local variable descriptor data.

This structure stores descriptor data for local variables, and is used to set the value of one or more local variables belonging to a Sound instance.
The structure is embedded as the <c><i>localVariableData</i></c> member of the SceScreamSoundParams structure.

@note
Local variables initialize with a default value of 0.0.
If you wish to initialize a Sound's local variables to values other than 0.0, you can use this structure as the SceScreamSoundParams's <c><i>localVariableData</i></c> parameter in a call to sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@see
sceScreamPlaySoundByNameEx(), sceScreamPlaySoundByIndexEx(), sceScreamSetSoundParamsEx(), sceScreamSetLocalVariableByHash(), sceScreamGetLocalVariableByHash(), sceScreamGetHashFromName(),
SceScreamSoundParams, sceScreamSetSoundParamsEx(), sceScreamGetSoundParamsEx()
*/
typedef struct SceScreamSndLocalVarData
{
    uint32_t    numDescs;                       ///< The number of valid descriptors in this structure.  Range: 1 to #SCE_SCREAM_SND_MAX_LOCAL_VARIABLES
    struct
    {
        uint32_t namehash;                      ///< 32-bit hash of a named local variable to set. See the sceScreamGetHashFromName() function.
        float val;                              ///< A floating-point value to set the local variable to.
    } desc[SCE_SCREAM_SND_MAX_LOCAL_VARIABLES]; ///< Local variable descriptor.
}SceScreamSndLocalVarData;

/**
@ingroup screamDataStructures

@brief
Stores asset Grain 3D parameter data.

This structure stores 3D parameter data belonging to asset Grains (<i>Waveform</i> and <i>Stream</i> Grains).
You can query Sounds for 3D parameter data using the sceScreamSoundIndexGet3DDesignerParams(), sceScreamSoundNameGet3DDesignerParams(), and sceScreamSoundInstanceGet3DDesignerParams() functions.
These functions store retrieved 3D parameter data in array of SceScreamSnd3DGrainData structures.

@note
If distance in your game is expressed in units other than meters, you must convert values stored in the <c><i>innerRadius</i></c> and <c><i>outerRadius</i></c> members back to your game's distance units.
See the sceScreamGetWorldUnitsPerMeter() function.

@see
sceScreamSoundIndexGet3DDesignerParams(), sceScreamSoundNameGet3DDesignerParams(), sceScreamSoundInstanceGet3DDesignerParams(), sceScreamSetWorldUnitsPerMeter(), sceScreamGetWorldUnitsPerMeter()
*/
typedef struct SceScreamSnd3DGrainData
{
    float       innerRadius;            ///< Inner radius for the assigned distance model. Expressed in meters. See &quot;Notes&quot; below.
    float       outerRadius;            ///< Outer radius for the assigned distance model. Expressed in meters. See &quot;Notes&quot; below.
    float       dryRolloffFactor;       ///< Rolloff factor for the assigned distance model's dry level curve.
    float       wetRolloffFactor;       ///< Rolloff factor for the assigned distance model's wet level curve.
    float       lfeRolloffFactor;       ///< Rolloff factor for the assigned distance model's LFE level curve.
    float       airAbsorptionFactor;    ///< Rolloff factor for the assigned distance model's air absorption (low-pass filter) curve.
}SceScreamSnd3DGrainData;

/////////////////////////////////////////////////////////////////////////////////////////////////
// Synth specific

// Sound Parameter Bit Masks
/**
@defgroup soundParameterBitMasks Sound Parameter Bit Masks
@brief You apply sound parameter bit masks to the SceScreamSoundParams structure's <c><i>mask</i></c> member to specify which other members of the structure are being set.
@{*/
#define SCE_SCREAM_SND_MASK_PITCH_TRANSPOSE     (1L << 0)           ///< The <c><i>pitchTranspose</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_PITCH_BEND_FACTOR   (1L << 1)           ///< The <c><i>pitchBendFactor</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_GAIN                (1L << 2)           ///< The <c><i>gain</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_PAN_AZIMUTH         (1L << 3)           ///< The <c><i>azimuth</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_PAN_FOCUS           (1L << 4)           ///< The <c><i>focus</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_SYNTH_PARAMS        (1L << 5)           ///< The <c><i>synthParams</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_USERCTX             (1L << 6)           ///< The <c><i>userCtx</i></c> member has been set.

#define SCE_SCREAM_SND_MASK_REGISTERS_0         (1L << 16)          ///< The <c><i>registers</i></c>[0] member has been set.
#define SCE_SCREAM_SND_MASK_REGISTERS_1         (1L << 17)          ///< The <c><i>registers</i></c>[1] member has been set.
#define SCE_SCREAM_SND_MASK_REGISTERS_2         (1L << 18)          ///< The <c><i>registers</i></c>[2] member has been set.
#define SCE_SCREAM_SND_MASK_REGISTERS_3         (1L << 19)          ///< The <c><i>registers</i></c>[3] member has been set.
#define SCE_SCREAM_SND_MASK_REGISTERS_4         (1L << 20)          ///< The <c><i>registers</i></c>[4] member has been set.
#define SCE_SCREAM_SND_MASK_REGISTERS_5         (1L << 21)          ///< The <c><i>registers</i></c>[5] member has been set.
#define SCE_SCREAM_SND_MASK_REGISTERS_6         (1L << 22)          ///< The <c><i>registers</i></c>[6] member has been set.
#define SCE_SCREAM_SND_MASK_REGISTERS_7         (1L << 23)          ///< The <c><i>registers</i></c>[7] member has been set.

#define SCE_SCREAM_SND_MASK_FLAGS               (1L << 24)          ///< The <c><i>flags</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_LOCAL_VARIABLES     (1L << 25)          ///< The <c><i>localVariableData</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_LISTENER            (1L << 26)          ///< The <c><i>listenerHandle</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_POSITION            (1L << 27)          ///< The <c><i>position</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_DOPPLER_FACTOR      (1L << 28)          ///< The <c><i>dopplerFactor</i></c> member has been set.
#define SCE_SCREAM_SND_MASK_REGISTERS           (SCE_SCREAM_SND_MASK_REGISTERS_0 | SCE_SCREAM_SND_MASK_REGISTERS_1 | SCE_SCREAM_SND_MASK_REGISTERS_2 | SCE_SCREAM_SND_MASK_REGISTERS_3 |\
                                    SCE_SCREAM_SND_MASK_REGISTERS_4 | SCE_SCREAM_SND_MASK_REGISTERS_5 | SCE_SCREAM_SND_MASK_REGISTERS_6 | SCE_SCREAM_SND_MASK_REGISTERS_7)      ///< All <c><i>registers</i></c> members are in use and have been set.
/**@}*/

// Sound Flags
/**
@defgroup soundFlags Sound Flags
@brief
Sound flags provide optional behaviors for Sounds.
@{*/
#define SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF                 (0L)            ///< Specifies a graceful stop. Triggers any <i>On Stop Marker</i> Grain events and issues key-off messages to active voices with ADSR Release settings. Apply to the <c><i>behavior</i></c> parameter of the sceScreamStopSound(), sceScreamStopAllSoundsInBank(), and sceScreamStopAllSoundsInGroup() functions.
#define SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE                (1L)            ///< Specifies an instantaneous stop. Does <i>not</i> trigger <i>On Stop Marker</i> Grain events or <i>Waveform</i> and <i>Stream</i> Grains with ADSR Release settings. Apply to the <c><i>behavior</i></c> parameter of the sceScreamStopSound(), sceScreamStopAllSoundsInBank(), and sceScreamStopAllSoundsInGroup() functions.

#define SCE_SCREAM_SND_FLAG_DO_FINISHED_CALLBACK            (1L << 0)       ///< Sets up a callback that is made upon completion of a Sound. Apply to the SceScreamSoundParams <c><i>flags</i></c> member. For details, see &quot;Configuring Sound Event Callbacks&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.
#define SCE_SCREAM_SND_FLAG_START_STREAM_PAUSED             (1L << 1)       ///< On initiation of playback, Scream finds the first <i>Stream</i> grain in a Sound's script and immediately starts the associated stream in a paused state. This mechanism helps prevent possible stream buffering delays. Apply to the SceScreamSoundParams <c><i>flags</i></c> member.
#define SCE_SCREAM_SND_FLAG_STREAM_GET_VOICE_LEVEL          (1L << 2)       ///< Enables level detection for <i>Stream</i> Grains contained in a Sound's script. Apply to the SceScreamSoundParams <c><i>flags</i></c> member.
#define SCE_SCREAM_SND_FLAG_DIST_MODEL_NO_FILTER            (1L << 3)       ///< Instructs Scream's distance modeling system not to apply air absorption filtering. Apply to the SceScreamSoundParams <c><i>flags</i></c> member.
#define SCE_SCREAM_SND_FLAG_DIST_MODEL_PRESEND_FILTER_3     (1L << 4)       ///< Instructs Scream's distance modeling system to use the last of the 4 pre-send filters for air absorption. This avoids conflict over the SceScreamSynthParams.postSendFilter member (the default for air absorption) when a game is using it for obstruction/occlusion simulation. Apply to the SceScreamSoundParams <c><i>flags</i></c> member.
#define SCE_SCREAM_SND_FLAG_DOPPLER_CAMERA_CUT              (1L << 5)       ///< Indicates that a discontinuity in emitter location has occurred. This avoids the potential for a large instantaneous Doppler shift that might otherwise result. Apply to the SceScreamSoundParams <c><i>flags</i></c> member. You can also specify a camera cut when there has been a discontinuity in listener location. For further details, see the sceScreamSetListener() function's <c><i>cameraCut</i></c> parameter.
/**@}*/

/**
@ingroup screamDataStructures
@brief
Stores Sound-specific parameter values.

This structure stores Sound-specific parameter values.
You use this structure when setting or retrieving Sound parameters with the sceScreamSetSoundParamsEx() and sceScreamGetSoundParamsEx() functions.
You also use it when you play a sound with sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@note
Setting <c><i>focus</i></c> to 360 makes <c><i>azimuth</i></c> irrelevant for mono assets or multi-channel assets in which the Mix Mode property is set to Discrete in Bank contents. For multi-channel assets in which the Mix Mode property is set to Diffuse, <c><i>azimuth</i></c> does have an effect with respect to the image of the multi-channel asset. For example, setting <c><i>azimuth</i></c> to 180 degrees and <c><i>focus</i></c> to 360 degrees inverts the multi-channel image.

@note
Setting <c><i>azimuth</i></c> to a speaker target overrides and nullifies any Bank contents pan settings.
An <c><i>azimuth</i></c> setting expressed in degrees will be added (modulo 360) to any Bank contents pan settings.

@note
<c><i>pitchBendFactor</i></c> settings have no effect on a Sound unless one or more of its component <i>Waveform</i> or <i>Stream</i> Grains has a corresponding upper/lower pitchbend range setting.

@note
Sound distance calculations are based on SceScreamSnd3DVector coordinates set in the <c><i>position</i></c> member, relative to those set on a listener specified in the <c><i>listenerHandle</i></c> member.

@see
sceScreamSetSoundParamsEx(), sceScreamGetSoundParamsEx(), sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx(), \link #SCE_SCREAM_SND_MASK_PITCH_TRANSPOSE Sound Parameter Bit Masks\endlink, sceScreamCreateListener()
*/
typedef struct SceScreamSoundParams
{
    uint32_t                    size;                                       ///< The size of this data structure; use <c>sizeof(SceScreamSoundParams)</c> to determine.
    uint32_t                    mask;                                       ///< A mask indicating which of the following members have active settings. One or more of the \link #SCE_SCREAM_SND_MASK_PITCH_TRANSPOSE Sound Parameter Bit Masks\endlink. Use the bitwise <c>OR</c> operator for multiple selections.
    uint32_t                    flags;                                      ///< Zero or more of the following behavior options: #SCE_SCREAM_SND_FLAG_DO_FINISHED_CALLBACK, #SCE_SCREAM_SND_FLAG_START_STREAM_PAUSED, #SCE_SCREAM_SND_FLAG_STREAM_GET_VOICE_LEVEL, #SCE_SCREAM_SND_FLAG_DIST_MODEL_NO_FILTER, #SCE_SCREAM_SND_FLAG_DIST_MODEL_PRESEND_FILTER_3, #SCE_SCREAM_SND_FLAG_DOPPLER_CAMERA_CUT.
    void*                       userCtx;                                    ///< A user-defined context value that will be passed back with any event callbacks made on this Sound instance. Can be <c>NULL</c>. See SceScreamSndEventCallback() and SceScreamPlatformInitEx2.
    float                       gain;                                       ///< Overall gain setting. Scales the levels of a Sound's SceScreamSynthParams <c><i>auxSendGain</i></c> and <c><i>directSendGain</i></c> members. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.
    uint32_t                    azimuth;                                    ///< Panning azimuth of Sound, expressed in degrees clockwise relative to the listener. Range: 0 to 359. A value of 0 specifies that Sound is straight ahead; 90 specifies directly to the right; 180 specifies behind, and so on. Alternatively, you can specify a single speaker target using one of the \link #SCE_SCREAM_SND_PAN_FL Output Speaker Targets\endlink. See &quot;Notes&quot; below.
    uint32_t                    focus;                                      ///< Width of panning focus of Sound, expressed in degrees. Range: 0 to 360. A value of 0 specifies a point source; 360 specifies Sound coming from all directions. <b>Note:</b> Setting <c><i>focus</i></c> to 360 makes <c><i>azimuth</i></c> irrelevant for mono assets or multi-channel assets if Mix Mode is set to <c>Discrete</c> in Bank contents. Also, if <c><i>azimuth</i></c> is set to one or more specific Output Speaker Targets, <c><i>focus</i></c> is ignored. See &quot;Notes&quot; below.
    int32_t                     pitchTranspose;                             ///< Transposition amount in fines above/below original pitch. Range: &ndash;#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE to +#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE. Zero specifies original pitch.
    float                       pitchBendFactor;                            ///< Pitchbend amount. Range: #SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR to #SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR. For details on setting pitchbend, see the &quot;Notes&quot; section of the sceScreamAutoPitchBend() function.
    int8_t                      registers[SCE_SCREAM_SND_MAX_REGISTERS];    ///< Sound-specific register settings. An array of length #SCE_SCREAM_SND_MAX_REGISTERS, with values in the range -128 to 127.
    SceScreamSndLocalVarData*   localVariableData;                          ///< A pointer to a SceScreamSndLocalVarData structure containing values for one or more local variables of a Sound instance.
    uint32_t                    listenerHandle;                             ///< Handle of a listener to which this Sound instance is relative in 3D space. See sceScreamCreateListener(). See &quot;Notes&quot; below.
    SceScreamSnd3DVector        position;                                   ///< A SceScreamSnd3DVector structure containing a Sound's world-space position. See &quot;Notes&quot; below.
    float                       dopplerFactor;                              ///< A scalar for the Doppler effect that is automatically generated by 3D <c><i>position</i></c> changes relative to a specified <c><i>listenerHandle</i></c>. Scales the Doppler Factor property set on a Sound in Bank contents. Set to 0.0 for no Doppler. Set to 1.0 for a natural Doppler effect or to leave the content setting unchanged. Set to greater than 1.0 for an exaggerated effect.
    SceScreamSynthParams        synthParams;                                ///< A SceScreamSynthParams data structure; holds Sound-specific synthesizer parameter settings.
}SceScreamSoundParams;
////////////////////////////////////////////////////////////////////////////////

#if (defined(_cplusplus) || defined(__cplusplus))
extern "C"
{
#endif

////////////////////////////////////////////////////////////////////////////////
// Global System

// Initialization and Shutdown.

/**
@defgroup screamSystemFunctions Scream System Functions
@brief
Scream system functions control system features, set and retrieve system states, and are common to all supported platforms and synthesizers.
@{*/

/**
@brief
Initializes a SceScreamPlatformInitEx2 data structure with default values.

SceScreamPlatformInitEx2 is a data structure used to store initialization values for the Scream platform.
This function initializes a SceScreamPlatformInitEx2 structure &ndash; including the SceScreamSystemParams
structure embedded in its <c><i>synthParams</i></c> member &ndash; with the following Scream and synthesizer-specific default values.<br>
*/
/**
<br>
<table border="0">
<!-- SceScreamPlatformInitEx2 defaults -->
<tr>
<td><c><i>size</i></c></td>
<td>No default</td>
</tr>
<tr>
<td><c><i>initFlags</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_INIT_FLAGS</td>
</tr>
<tr>
<td><c><i>playbackMode</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_PLAYBACK_MODE</td>
</tr>
<tr>
<td><c><i>maxLFOs</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_MAX_LFOS</td>
</tr>
<tr>
<td><c><i>lfoUpdateRate</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_LFO_UPDATE</td>
</tr>
<tr>
<td><c><i>duckerUpdateRate</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_DUCKER_UPDATE</td>
</tr>
<tr>
<td><c><i>groupMixerUpdateRate</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_GROUP_MIXER_UPDATE</td>
</tr>
<tr>
<td><c><i>ccSoundUpdateRate</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_CCSOUND_UPDATE</td>
</tr>
<tr>
<td><c><i>minRipoffTime</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_MIN_RIPOFF_TIME</td>
</tr>
<tr>
<td><c><i>memAlloc</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_MEM_ALLOC</td>
</tr>
<tr>
<td><c><i>memFree</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_MEM_FREE</td>
</tr>
<tr>
<td><c><i>eventCallback</i></c></td>
<td><c>NULL</c></td>
</tr>
<tr>
<td><c><i>maxBanks</i></c></td>
<td><c>#SCE_SCREAM_SND_DEFAULT_MAX_BANKS</c></td>
</tr>
<tr>
<td><c><i>maxPolyphony</i></c></td>
<td><c>#SCE_SCREAM_SND_DEFAULT_MAX_POLYPHONY</c></td>
</tr>
<tr>
<td><c><i>maxActiveSnapshots</i></c></td>
<td><c>#SCE_SCREAM_SND_DEFAULT_MAX_SNAPSHOTS</c></td>
</tr>
<tr>
<td><c><i>maxGlobalVariables</i></c></td>
<td><c>#SCE_SCREAM_SND_DEFAULT_MAX_GLOBAL_VARIABLES</c></td>
</tr>
<tr>
<td><c><i>maxCCSounds</i></c></td>
<td><c>#SCE_SCREAM_SND_DEFAULT_MAX_CCSOUNDS</c></td>
</tr>
<tr>
<td><c><i>dopplerSlewRate</i></c></td>
<td><c>#SCE_SCREAM_SND_DEFAULT_DOPPLER_SLEW_RATE</c></td>
</tr>
<tr>
<td><c><i>pGroupMixerFile</i></c></td>
<td><c>NULL</c></td>
</tr>
<tr>
<td><c><i>groupMixerFileSize</i></c></td>
<td><c>0</c></td>
</tr>
<tr>
<td><c><i>pBussConfigFile</i></c></td>
<td><c>NULL</c></td>
</tr>
<tr>
<td><c><i>bussConfigFileSize</i></c></td>
<td>0</td>
</tr>
<tr>
<td><c><i>pDistanceModelFile</i></c></td>
<td><c>NULL</c></td>
</tr>
<tr>
<td><c><i>synthParams</i></c></td>
<td>&nbsp;</td>
</tr>
<!-- SceScreamSystemParams defaults -->
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>tickThreadPriority</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_THREAD_PRIORITY</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>tickThreadAffinity</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_THREAD_AFFINITY</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>tickThreadStackSize</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_THREAD_STACK_SIZE</td>
</tr>
<tr valign="top">
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>voiceTypeCount</i></c></td>
<td>[#SCE_SCREAM_SND_DEFAULT_NUM_VAG_MONO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_PCM_MONO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_AT9_MONO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_VAG_STEREO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_PCM_STEREO_VOICES, #SCE_SCREAM_SND_DEFAULT_NUM_AT9_STEREO_VOICES]</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>numReverbs</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_NUM_REVERBS</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>numPremasterCompSubmixes</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_NUM_PREMASTER_COMP_SUBMIXES</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>numPremasterScCompSubmixes</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_NUM_PREMASTER_SC_COMP_SUBMIXES</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>numExternalRacks</i></c></td>
<td>0</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>numExternalVoices</i></c></td>
<td>0</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>initFlags</i></c></td>
<td>#SCE_SCREAM_SND_DEFAULT_SYNTH_INIT_FLAGS</td>
</tr>
<tr>
<td>&nbsp;&nbsp;&nbsp;&nbsp;<c><i>reserved0</i></c></td>
<td>0</td>
</tr>
</table>
*/
/**
@param platformInit (Input)
Pointer to a SceScreamPlatformInitEx2 structure to be initialized.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful. Returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if <c><i>platformInit</i></c> is <c>NULL</c> or if the <c><i>size</i></c> member of the SceScreamPlatformInitEx2 structure specified for the <c><i>platformInit</i></c> parameter is invalid.

@see
SceScreamPlatformInitEx2, SceScreamSystemParams, sceScreamStartSoundSystemEx2()
*/
int32_t sceScreamFillDefaultScreamPlatformInitArgsEx2(SceScreamPlatformInitEx2 *platformInit);
/**@}*/

/**
@ingroup screamSystemFunctions

@brief
Confirms whether Scream has been initialized and is running.

This is a status function that confirms whether Scream has been initialized and is running.

@return
Returns <c>TRUE</c> if Scream is running. Returns <c>FALSE</c> if Scream is not running.

@see
sceScreamStartSoundSystemEx2(), sceScreamStopSoundSystem()
*/
bool    sceScreamGetSystemRunning(void);

/**
@ingroup screamSystemFunctions

@brief
Initializes Scream for use by an application.

Use this function to initialize Scream for use by an application.

@param platformInit (Input)
Pointer to an initialized SceScreamPlatformInitEx2 data structure.

@return
Returns 0 if initialization was successful.
Returns #SCE_SCREAM_SS_ERROR_SYSTEM_ALREADY_STARTED if Scream is already initialized.
Returns #SCE_SCREAM_SS_ERROR_SYNTH_INIT_FAILED if the underlying synthesizer failed to initialize.

@see
SceScreamPlatformInitEx2, sceScreamFillDefaultScreamPlatformInitArgsEx2(), sceScreamStopSoundSystem(), sceScreamGetSystemRunning()
*/
int32_t   sceScreamStartSoundSystemEx2(const SceScreamPlatformInitEx2 *platformInit);

/**
@ingroup screamSystemFunctions

@brief
Shuts down the Scream runtime engine.

Use this function to completely shut down Scream. This function silences all Scream voices,
and releases all Scream-allocated memory.

@return
Returns 0 if shutdown was successful.
Returns #SCE_SCREAM_SS_ERROR_SYSTEM_NOT_STARTED if Scream is not currently running.

@see
sceScreamStartSoundSystemEx2(), sceScreamGetSystemRunning()
*/
int32_t   sceScreamStopSoundSystem(void);

// Misc

/**
@ingroup screamSystemFunctions

@brief
Retrieves the maximum number of synthesizer voices that can be simultaneously played by Scream.

The number of simultaneously playable voices on a synthesizer is known as polyphony.
This function retrieves the maximum number of voices that can be simultaneously played by Scream with respect to the NGS synthesizer.
You set the maximum polyphony at initialization time using the SceScreamPlatformInitEx2 structure's <c><i>maxPolyphony</i></c> member.
The default maximum polyphony is defined by the constant #SCE_SCREAM_SND_DEFAULT_MAX_POLYPHONY.
Calling this function after initializing Scream (with a call to sceScreamStartSoundSystemEx2()) returns the value set in the SceScreamPlatformInitEx2 structure's <c><i>maxPolyphony</i></c> member.

@note
The number of simultaneously addressable voices (polyphony) is conceptually different from the number of allocated voices of each type on the synthesizer; the sum of which may be greater than the number returned by this function.
In fact, to accommodate peak usage of single voice types, it may be desirable to set a total number of allocated synthesizer voices greater than the number of voices that can be simultaneously addressed by Scream.
For example, if you allocate 24 VAG, 24 PCM, and 16 ATRAC9&trade; voices (a total of 64), the synthesizer could not play more than the specified number of any one type simultaneously.
Conversely, if you allocate 64 voices of each type (a total of 192), the synthesizer can potentially play all 64 voices of a single type simultaneously (assuming default maximum polyphony).
For further details, see &quot;Allocating Synthesizer Voice Types&quot; in the &quot;Configuration, Initialization, and Shutdown&quot; chapter of the <i>Scream Library Overview</i>.

@return
Returns the maximum polyphony (number of simultaneously addressable voices).

@see
#SCE_SCREAM_SND_DEFAULT_MAX_POLYPHONY, sceScreamGetSynthName(), sceScreamSetGroupVoiceRange(), sceScreamGetSoundVoiceCount(),  SceScreamPlatformInitEx2, sceScreamGetVoiceTypeName()
*/
uint32_t    sceScreamGetMaxPolyphony(void);

/**
@ingroup screamSystemFunctions

@brief
Retrieves a count of allocated synthesizer voices by type.

The number of allocated synthesizer voices of each type depends on specified values for the SceScreamSystemParams structure's <c><i>voiceTypeCount</i></c> member (an array),
which is indexed by the \link #SCE_SCREAM_SND_VOICE_DATA_TYPE_VAG Voice Data Type Constants\endlink. The SceScreamSystemParams structure is embedded in the SceScreamPlatformInitEx2 structure's <c><i>synthParams</i></c> member, and in turn passed to the sceScreamStartSoundSystemEx2() function when initializing Scream.
@param dataType (Input)
One of the \link #SCE_SCREAM_SND_VOICE_DATA_TYPE_VAG Voice Data Type Constants\endlink.

@return
Returns the number of allocated voices of the specified type.

@see
SceScreamSystemParams, SceScreamPlatformInitEx2, sceScreamGetMaxPolyphony(), sceScreamGetVoiceTypeName()
*/
uint32_t    sceScreamGetAllocatedVoiceCountByType(uint32_t dataType);

/**
@ingroup screamSystemFunctions

@brief
Retrieves the name of the rendering synthesizer with which Scream is linked.

This function retrieves the name of the rendering synthesizer with which Scream is linked.
Scream processes control information, but all audio processing takes place on a rendering synthesizer.

@return
Returns the name of the rendering synthesizer.

@see
sceScreamGetMaxPolyphony(), sceScreamGetVoiceTypeName()
*/
const char* sceScreamGetSynthName(void);

/**
@ingroup screamSystemFunctions

@brief
Retrieves the name of a synthesizer voice type based on a specified data type.

This function retrieves the name of synthesizer voice type corresponding with a specified voice data type.

@param dataType (Input)
One of the \link #SCE_SCREAM_SND_VOICE_DATA_TYPE_VAG NGS Voice Data Type Constants\endlink.

@return
Returns a string representing the name of a synth voice type corresponding with the specified data type.

@see
sceScreamGetAllocatedVoiceCountByType(), sceScreamGetSynthName(), sceScreamGetMaxPolyphony()
*/
const char* sceScreamGetVoiceTypeName(uint32_t dataType);

/**
@ingroup screamSystemFunctions

@brief
Retrieves the current Scream tick count.

Scream ticks occur at a rate of 240 times per second. Each tick
increments an internal counter. This function returns the current value of the internal counter.

@return
Returns the current tick count.
*/
uint32_t    sceScreamGetTick(void);

/**
@ingroup screamSystemFunctions

@brief
Changes the system-wide minimum voice ripoff time.

This function changes the system-wide minimum voice ripoff time. The minimum ripoff time is the time a voice must be active before it is eligible for stealing.

You can also set the system wide minimum ripoff time at initialization time using SceScreamPlatformInitEx2.minRipoffTime.

@param minRipoffTimeSeconds (Input)
The number of seconds a voice must be active before it is eligible for stealing.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
SceScreamPlatformInitEx2
*/
int32_t     sceScreamSetMinRipoffTime(float minRipoffTimeSeconds);

/**
@ingroup screamSystemFunctions

@brief
Retrieves the current level of a master output channel.

This function retrieves the instantaneous peak level of a specified master output channel.
It returns the result either as a linear value or as a decibel (dB) value relative to full-scale.

@param channel (Input)
The channel output level to retrieve. One of the \link #SCE_SCREAM_SND_POLPAN_INDEX_FL Polar-Pan Speaker Channel Indices Constants\endlink.

@param rms (Input)
Currently, the result is an instantaneous peak level only (<c>FALSE</c>).
Attempting to set to <c>TRUE</c> (for an averaged RMS level) is ignored.

@param linear (Input)
Set to <c>TRUE</c> if you want the result on a linear scale. Otherwise, the result is expressed in decibels (dB).

@return
If <c><i>linear</i></c> is set to <c>TRUE</c>, returns a linear value that should fall between #SCE_SCREAM_SND_LEVEL_LINEAR_MINIMUM and #SCE_SCREAM_SND_LEVEL_LINEAR_NOMINAL, where values &ge; #SCE_SCREAM_SND_LEVEL_LINEAR_NOMINAL indicate clipping.
Otherwise, returns a value in decibels that should fall between #SCE_SCREAM_SND_LEVEL_DB_MINIMUM and #SCE_SCREAM_SND_LEVEL_DB_NOMINAL, where values &ge; #SCE_SCREAM_SND_LEVEL_DB_NOMINAL indicate clipping.
*/

/**
@note
The sceScreamGetMasterOutputLevel() function will not operate if Scream is initialized with the #SCE_SCREAM_SND_SYNTH_INIT_FLAG_DISABLE_LEVELS flag in the SceScreamSystemParams <c><i>initFlags</i></c> member.
*/

/**
@see
SceScreamSystemParams, SceScreamPlatformInitEx2
*/
float       sceScreamGetMasterOutputLevel(uint32_t channel, bool rms, bool linear);

/**
@ingroup screamSystemFunctions

@brief
Sets a custom debug text output function.

You can create a custom debug text output function that adheres to the SceScreamSndDebugHandler() prototype.
This function allows you to set your custom function to receive all Scream and associated synthesizer debug text output &ndash; diverting output that would otherwise go to the default <c>printf()</c>-like function.

You can unset the current debug handler by specifying <c>NULL</c> as the value of the <c><i>proc</i></c> argument.

It is recommended to set your custom debug text output function <i>prior</i> to initializing Scream, as much information is produced during the initialization process.

@param proc (Input)
Pointer to an application-defined function of type SceScreamSndDebugHandler().

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
SceScreamSndDebugHandler(), sceScreamOutputHandlerInfoToTTY(), sceScreamOutputAllPlayingSoundInfoToTTY()
*/
int32_t sceScreamSetDebugHandler(SceScreamSndDebugHandler proc);

// Output Mode
/**
@ingroup screamSystemFunctions

@brief
Retrieves the current playback mode.

Retrieves the current playback (output) mode setting.
If the playback mode was set to #SCE_SCREAM_SPEAKER_MODE_BEST at initialization time (in the <c><i>playbackMode</i></c> member of the SceScreamPlatformInitEx2 structure used
when calling sceScreamStartSoundSystemEx2()), the playback mode that was selected as best is returned.

@return
Returns one of the \link #SCE_SCREAM_SPEAKER_MODE_STEREO Playback Mode Constants\endlink.

@see
sceScreamSetPlaybackMode()
*/
uint32_t   sceScreamGetPlaybackMode(void);

/**
@ingroup screamSystemFunctions

@brief
Sets the playback mode.

This function sets the playback (output) mode.
Available Playback Modes are defined by the \link #SCE_SCREAM_SPEAKER_MODE_STEREO Playback Mode Constants\endlink.

@param  mode (Input)
One of the \link #SCE_SCREAM_SPEAKER_MODE_STEREO Playback Mode Constants\endlink, other than #SCE_SCREAM_SPEAKER_MODE_BEST,
which is only valid at initialization time as a value for the SceScreamPlatformInitEx2 <c><i>playbackMode</i></c> member.

@param customSpeakerAzimuths (Input)
<b>Note:</b> This parameter is ignored when running Scream on the NGS synthesizer.

@return
Returns one of the \link #SCE_SCREAM_SPEAKER_MODE_STEREO Playback Mode Constants\endlink.
If the call was successful, this value represents the new (specified) playback mode.
If not successful, the value is that of the current (unchanged) playback mode.

@see
sceScreamGetPlaybackMode()
*/
uint32_t   sceScreamSetPlaybackMode(uint32_t mode, uint32_t customSpeakerAzimuths[SCE_SCREAM_SND_POLPAN_MAX_SPEAKERS] );

// Random Seeding
/**

@ingroup screamSystemFunctions

@brief
Retrieves the current seed index of the Scream random number generator.

This function returns the current seed index of the Scream random number generator. The seed index can be used in relation
to variable speed replays, where some audio parameter values are determined by random numbers, and there is a need for identical
repetition of the original playback. To use the seed index for this purpose, before initiating a sequence you may later wish to replay,
call sceScreamGetRandomIndex() and store its return value. Then, before initiating the replay, call
sceScreamSetRandomIndex() with the previously stored value.

@return
Returns a seed index value within the range: -32,768 to +32,767.

@see
sceScreamSetRandomIndex(), sceScreamGetScriptSpeedFactor(), sceScreamSetScriptSpeedFactor()
*/
int16_t   sceScreamGetRandomIndex(void);

/**
@ingroup screamSystemFunctions

@brief
Sets the seed index of the Scream random number generator.

This function sets the seed index of the Scream random number generator. The seed index can be used in relation to
variable speed replays, where some audio parameter values are determined by random numbers, and
there is a need for identical repetition of the original playback, as in an action replay, for instance.
To use the seed index for this purpose, before initiating a sequence you may later wish to replay,
call sceScreamGetRandomIndex() and store its return value. Then, before initiating the replay, call
sceScreamSetRandomIndex() with the previously stored value.

@param iIndex (Input)
An <c>int16_t</c> within the range: -32,768 to +32,767.

@return
Returns 0 upon setting the seed index of the random number generator.

@see
sceScreamGetRandomIndex(), sceScreamGetScriptSpeedFactor(), sceScreamSetScriptSpeedFactor()
*/
int32_t   sceScreamSetRandomIndex(int16_t iIndex);

// Registers
/**
@ingroup screamSystemFunctions

@brief
Retrieves the value of a Scream global register.

This function retrieves the current value of the specified global register (not to be confused with the global variables used with CCSounds).
Scream maintains a set of global registers (the total number of which is #SCE_SCREAM_SND_MAX_GLOBAL_REGISTERS).
Global registers can be used to
communicate game engine state to Scream Sound scripts, either for direct
application to parameter values, or for more complex logical operations.

@param which (Input)
One-based index of the global register for which to retrieve the value.
Must be between 1 and #SCE_SCREAM_SND_MAX_GLOBAL_REGISTERS.

@return
Returns the value of the specified global register.

@see
sceScreamSetSFXGlobalReg()
*/
int8_t    sceScreamGetSFXGlobalReg(int32_t which);

/**

@ingroup screamSystemFunctions

@brief
Sets the value of a Scream global register.

This function sets the value of the specified global register.
Scream maintains a set of global registers (the total number of which is #SCE_SCREAM_SND_MAX_GLOBAL_REGISTERS).
Global registers (not to be confused with the global variables used with CCSounds) can be used to communicate game engine state to Scream Sound scripts, either for direct
application to parameter values, or for more complex logical operations.

@param which (Input)
One-based index of the global register to set. Must be between 1 and #SCE_SCREAM_SND_MAX_GLOBAL_REGISTERS.

@param val (Input)
Value to set the global register to. Must be between -128 and 127.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamGetSFXGlobalReg()

*/
int32_t   sceScreamSetSFXGlobalReg(int32_t which, int8_t val);

// Variables
/**
@ingroup screamSystemFunctions

@brief
Calculates a 32-bit string hash.

This function calculates a 32-bit hash based on a specified string.

@param name (Input)
String from which to calculate a hash.

@return
Returns the 32-bit hash of the specified string.

@see
sceScreamSetLocalVariableByHash(), sceScreamGetLocalVariableByHash()
*/
uint32_t sceScreamGetHashFromName(const char* name);

/**
@ingroup screamSystemFunctions

@brief
Retrieves the current number of global variables.

This function retrieves the current number of global variables.
The maximum number of global variables is defined at initialization time using the SceScreamPlatformInitEx2.maxGlobalVariables member,
which defaults to #SCE_SCREAM_SND_DEFAULT_MAX_GLOBAL_VARIABLES.

@return
Returns the current number of global variables, not to be confused with global registers.

@see
sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable(), sceScreamDeleteGlobalVariable()
*/
uint32_t sceScreamGetNumGlobalVariables(void);

/**
@ingroup screamSystemFunctions

@brief
Adds a global variable to the system.

This function adds a global variable to the system.

@param name (Input)
Name assigned to a global variable to add.

@param outVarIndex (Output)
An optional pointer in which to store the index associated with the global variable.
You use this index to reference the associated global variable with the sceScreamSetGlobalVariableByIndex() and sceScreamGetGlobalVariableByIndex() functions.
See &quot;Notes&quot; below.

@note
The <c><i>outVarIndex</i></c> is valid whether the global variable exists prior to this call or not.

@return
Returns <c>TRUE</c> if the specified global variable is created. Returns <c>FALSE</c> if a global variable with the specified name already exists.

@see
sceScreamAddSetGlobalVariable(), sceScreamSetGlobalVariableByIndex(), sceScreamGetGlobalVariableByIndex(), sceScreamDeleteGlobalVariable()
*/
bool  sceScreamAddGlobalVariable(const char* name, uint32_t* outVarIndex);

/**
@ingroup screamSystemFunctions

@brief
Deletes a global variable from the system.

This function deletes a global variable from the system.

@param name (Input)
Name of the global variable to delete.

@return
Returns <c>TRUE</c> if the global is successfully deleted. Returns <c>FALSE</c> otherwise.

@see
sceScreamAddSetGlobalVariable(), sceScreamAddGlobalVariable()
*/
bool  sceScreamDeleteGlobalVariable(const char* name);

/**
@ingroup screamSystemFunctions

@brief
Sets a global variable value, first adding it to the system if it does not yet exist.

This function sets a global variable value.
If the global variable does not yet exist, the function adds it to the system before setting its value.

@param name (Input)
Name of the global variable to add/set.

@param val (Input)
Value to set the specified global variable to.

@param outVarIndex (Output)
An optional pointer in which to store the index associated with the global variable.
You use this index to reference the associated global variable with the sceScreamSetGlobalVariableByIndex() and sceScreamGetGlobalVariableByIndex() functions.
See &quot;Notes&quot; below.

@note
The <c><i>outVarIndex</i></c> is valid whether the global variable exists prior to this call or not.

@return
Returns <c>TRUE</c> if the specified global variable is created or if a global variable with the specified name already exists.
Returns <c>FALSE</c> if the maximum number of global variables already exists or <c><i>name</i></c> is <c>NULL</c>.

@see
sceScreamAddGlobalVariable(), sceScreamSetGlobalVariableByIndex(), sceScreamGetGlobalVariableByIndex(), sceScreamDeleteGlobalVariable()
*/
bool  sceScreamAddSetGlobalVariable(const char* name, float val, uint32_t* outVarIndex);

/**
@ingroup screamSystemFunctions

@brief
Sets the value of a global variable.

This function sets the value of a global variable, specified by index.

@param varIndex (Input)
Index of a global variable to set.
A value stored in the <c><i>outVarIndex</i></c> parameter resulting from calls to any of the following functions: sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable().

@param val (Input)
A floating-point value to set the specified global variable to.

@return
Returns <c>TRUE</c> if the specified <c><i>index</i></c> is valid. Returns <c>FALSE</c> otherwise.

@see
sceScreamGetGlobalVariableByIndex(), sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable()
*/
bool  sceScreamSetGlobalVariableByIndex(uint32_t varIndex, float val);

/**
@ingroup screamSystemFunctions

@brief
Sets the value of a global variable.

This function sets the value of a global variable, specified by name.

@param name (Input)
Name of the global variable to set.

@param val (Input)
A floating-point value to set the specified global variable to.

@return
Returns <c>TRUE</c> if the variable specified by <c><i>name</i></c> exists. Returns <c>FALSE</c> otherwise.

@see
sceScreamGetGlobalVariableByIndex(), sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable(), sceScreamSetGlobalVariableByHash()
*/
bool  sceScreamSetGlobalVariableByName(const char* name, float val);

/**
@ingroup screamSystemFunctions

@brief
Sets the value of a global variable.

This function sets the value of a global variable, specified by hash.

@param nameHash (Input)
Hash of a global variable to set.

@param val (Input)
A floating-point value to set the specified global variable to.

@return
Returns <c>TRUE</c> if the variable specified by <c><i>nameHash</i></c> exists. Returns <c>FALSE</c> otherwise.

@see
sceScreamGetGlobalVariableByIndex(), sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable(), sceScreamSetGlobalVariableByName(), sceScreamGetHashFromName()
*/
bool  sceScreamSetGlobalVariableByHash(uint32_t nameHash, float val);

/**
@ingroup screamSystemFunctions

@brief
Retrieves the value of a global variable.

This function retrieves the value of a global variable, specified by index.

@param varIndex (Input)
Index of a global variable from which to retrieve a value.
A value stored in the <c><i>outVarIndex</i></c> parameter resulting from calls to any of the following functions: sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable().

@param outVal (Output)
A pointer to a floating-point variable in which to store the retrieved value.

@return
Returns <c>TRUE</c> if the specified <c><i>index</i></c> is valid. Returns <c>FALSE</c> otherwise.

@see
sceScreamSetGlobalVariableByIndex(), sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable()
*/
bool sceScreamGetGlobalVariableByIndex(uint32_t varIndex, float* outVal);

/**
@ingroup screamSystemFunctions

@brief
Retrieves the value of a global variable.

This function retrieves the value of a global variable, specified by name.

@param name (Input)
Name of a global variable from which to retrieve a value.

@param outVal (Output)
A pointer to a floating-point variable in which to store the retrieved value.

@return
Returns <c>TRUE</c> if the variable specified by <c><i>name</i></c> is valid. Returns <c>FALSE</c> otherwise.

@see
sceScreamGetGlobalVariableByIndex(), sceScreamGetGlobalVariableByHash(), sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable()
*/
bool sceScreamGetGlobalVariableByName(const char* name, float* outVal);

/**
@ingroup screamSystemFunctions

@brief
Retrieves the value of a global variable.

This function retrieves the value of a global variable, specified by hash.

@param nameHash (Input)
Hash of a global variable from which to retrieve a value.

@param outVal (Output)
A pointer to a floating-point variable in which to store the retrieved value.

@return
Returns <c>TRUE</c> if the variable specified by <c><i>nameHash</i></c> is valid. Returns <c>FALSE</c> otherwise.

@see
sceScreamGetGlobalVariableByIndex(), sceScreamAddGlobalVariable(), sceScreamAddSetGlobalVariable(), sceScreamGetGlobalVariableByName(), sceScreamGetHashFromName()
*/
bool sceScreamGetGlobalVariableByHash(uint32_t nameHash, float* outVal);

// Script Execution
/**
@ingroup screamSystemFunctions

@brief
Retrieves the global script speed factor for variable speed replays.

This function retrieves the global script speed factor. The script speed factor is used for variable speed replays.
A value of 1.0 indicates normal speed. Values greater than 1.0 indicate increasingly faster replays.
Values less than 1.0 indicate progressively slower replays.

@param outFlags (Output)
Pointer to a <c>uint32_t</c> in which to receive any current script speed flag values.
By default, variable speed replay affects time domain scripting properties only and does not affect pitch domain or ADSR envelope durations.
The #SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_PITCH flag set means variable speed replay also affects the pitch domain.
The #SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_ADSR flag set indicates variable speed replay scales the durations of ADSR segments.
Set to <c>NULL</c> if flag values are not required.

@return
Returns the current script speed factor and optionally, script speed flags.

@see
sceScreamSetScriptSpeedFactor(), sceScreamGetGroupScriptSpeedFactor(), sceScreamSetGroupScriptSpeedFactor(), sceScreamGetRandomIndex(), sceScreamSetRandomIndex()
*/
float   sceScreamGetScriptSpeedFactor(uint32_t *outFlags);

/**
@ingroup screamSystemFunctions

@brief
Sets the global script speed factor for variable speed replays.

In Scream you can set both global and volume group-specific script speed factors for variable-speed replays.
This function sets the global script speed factor.
Use the sceScreamSetGroupScriptSpeedFactor() function to set a group-specific script speed factor.

<c><i>speedFactor</i></c> functions similarly to the jog wheel on a video cassette player. It can either be at rest (where
playback is at normal speed), rotated clockwise (to speed up playback), or rotated counter-clockwise (to
slow down playback). A <c><i>speedFactor</i></c> value of 1.0 indicates normal speed. Values
greater than 1.0 increasingly speed up playback. Values less than 1.0 progressively slow down playback.

<c><i>speedFactor</i></c> must be greater than 0.0 (variable speed replay cannot stand still or play backwards).
While there are no other direct programmatic constraints on the <c><i>speedFactor</i></c> value, there are
some indirect and practical constraints.

At the upper extremes, pitch shift on the rendering synthesizer cannot exceed two octaves above the original pitch, so
the effective maximum <c><i>speedFactor</i></c> value for the pitch domain is 4.0. The time-based playback
parameters can be speeded up by factors in excess of 4&times;. Note however, that very high speeds with
many simultaneous Sounds rapidly consume processor cycles. A practical constraint at the high end of the time domain may
be to keep <c><i>speedFactor</i></c> value less than 20.0. Note also that envelope values (ADSR) are not affected
by variable speed replays, so long attacks, decays, and releases remain the same no matter what
the <c><i>speedFactor</i></c> is set to.

At the lower extremes, because <c><i>speedFactor</i></c> temporarily changes the Scream tick rate, very low <c><i>speedFactor</i></c>
values could cause a noticeable delay following the replay until the tick rate returns to 240
ticks-per-second. A practical constraint at the low end may be to keep the <c><i>speedFactor</i></c> value greater than
0.05. If you need a slower replay speed, use pause/continue functionality to affect frame-by-frame replays.

For more information, see &quot;Manipulating Script Speed&quot; in the &quot;Working with System Globals&quot; chapter of the <i>Scream Library Overview</i>.

@param speedFactor (Input)
A speed multiplier for variable speed replays. Must be greater than 0. A value of 1.0 indicates normal speed.

@param flags (Input)
By default, variable speed replay affects time domain scripting properties only and does not affect pitch domain or ADSR envelope durations.
Set the #SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_PITCH flag if you want variable speed replay to also affect the pitch domain.
Set the #SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_ADSR flag if you want variable speed replay to scale the durations of ADSR segments.

@return
Returns the script speed factor that was set, or the current script speed factor if the new value could not be set.

@see
sceScreamGetScriptSpeedFactor(), sceScreamGetGroupScriptSpeedFactor(), sceScreamSetGroupScriptSpeedFactor(), sceScreamGetRandomIndex(), sceScreamSetRandomIndex()
*/
float   sceScreamSetScriptSpeedFactor(float speedFactor, uint32_t flags);

// Sounds
/**
@ingroup screamSystemFunctions

@brief
Stops all Sounds in the active Scream Sound handlers list.

This function stops all Sounds being generated by the Scream runtime engine.
This function performs a <i>hard</i> stop. That is, audio
generation stops almost instantaneously, depending on how far ahead the rendering synthesizer has
buffered samples for playback.

For more information, see &quot;Stopping All Sounds&quot; in the &quot;Working with System Globals&quot; chapter of the <i>Scream Library Overview</i>.

@note
The scope of this function includes Scream Sounds in both internal and external handlers.
The sceScreamStopAllSounds() function does not stop Streams. Use the Sndstream function <c>sceScreamStopAllStreams()</c> to stop all Streams.

@return
Returns #SCE_SCREAM_SS_ERROR_OK.

@see
sceScreamStopSound(), sceScreamStopAllSoundsInBank(), sceScreamStopAllSoundsInGroup()
*/
int32_t  sceScreamStopAllSounds(void);

/**
@ingroup screamSystemFunctions

@brief
Stops all instances of a Sound as specified by Bank and index references.

This function stops all instances of a Sound as specified by Bank and index references, without the need to specify Sound handles.

The <c><i>behavior</i></c> parameter provides a choice of two stop behaviors:
<ul>
<li>#SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF: Performs a graceful stop, triggering any <i>On Stop Marker</i> grain events, and issuing key-off messages to active voices with ADSR Release settings.</li>
<li>#SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE: Performs an instantaneous stop.</li>
</ul>

This function is primarily used for looping Sounds; one-shot Sounds stop themselves.

@param bank (Input)
SceScreamSFXBlock2 pointer referencing the Bank from which the Sound(s) were instantiated.

@param index (Input)
Index of the Sound within the specified <c><i>bank</i></c> from which the Sound(s) were instantiated.

@param behavior (Input)
A choice of two stop behaviors: #SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF or #SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamStopAllSounds(), sceScreamStopAllSoundsInGroup(), sceScreamStopAllSoundsInBank(), sceScreamStopSound(), sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx()
*/
int32_t  sceScreamStopAllSoundsByIndex(SceScreamSFXBlock2 *bank, int16_t index, int32_t behavior);

// Streams
/**
@ingroup screamSystemFunctions

@brief
Retrieves the associated directory path string for a specified stream path group.

In Scream, every stream file (that is, a file imported into Scream Tool using the <i>Stream</i> Grain)
is associated with a stream path group. You reference stream path groups using a zero-based index. Directory
paths can be set for each stream path group using the sceScreamSetStreamingFileDirectory() function.
This function retrieves the current directory path setting for the specified
stream path group.

@param uiDirGroup (Input)
Zero-based index of a stream path group to retrieve the directory path for. Stream path group indexes are between 0 and (#SCE_SCREAM_SND_MAX_STREAMING_FILE_DIRECTORIES &ndash; 1).

@return
If successful, returns the directory path string for the specified stream path group. Otherwise, returns <c>NULL</c>.

@note
Stream path groups are set in the Scream Tool stream inspector panel.
For details, see &quot;Setting Stream Properties&quot; in the &quot;Streams&quot; chapter of <i>Scream Tool Help</i>.

@see
sceScreamSetStreamingFileDirectory()
*/
const char* sceScreamGetStreamingFileDirectory(uint32_t uiDirGroup);

/**
@ingroup screamSystemFunctions

@brief
Sets the directory path string for a specified stream path group.

In Scream, every stream file (that is, a file imported into Scream Tool using the <i>Stream</i> Grain)
is associated with a stream path group. You reference stream path groups using a zero-based index.
This function allows you to set the directory path for a specified stream path group.

@param uiDirGroup (Input)
Zero-based index of the stream path group to set. Stream path group indexes are between 0 and (#SCE_SCREAM_SND_MAX_STREAMING_FILE_DIRECTORIES &ndash; 1).

@param pDirectoryString (Input)
Pointer to a directory path to use for the stream path group.

@return
Returns 1 if the directory path was set. Returns -1 if the directory path was not set. Returns 0 if any arguments are invalid.

@note
Scream does not copy the directory path string, but instead just saves the passed-in pointer.
Therefore, the string pointed to by the pointer address must be in static data memory, such that it will exist
for the lifetime of the application.

@see
sceScreamGetStreamingFileDirectory()
*/
int32_t   sceScreamSetStreamingFileDirectory(uint32_t uiDirGroup, const char *pDirectoryString);
////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
// Groups
/**
@defgroup groupFunctions Group Functions
@brief
Group functions manipulate groups and the Sounds to which they are assigned. They also set and retrieve group state information.
@{*/
/**
@brief
Pauses one or more Groups.

This function pauses one or more target Groups, causing all active and inactive Sounds and Child Sounds contained in the Groups to pause.
You specify the target Group(s) using the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink.
Use the bitwise <c>OR</c> operator to make multiple selections to create a bit field of Groups to pause. Use the sceScreamContinueGroup() function to continue paused Groups.

For more details, see &quot;Pausing a Group&quot; in the &quot;Working with Groups&quot; chapter of the <i>Scream Library Overview</i>.

@param groups (Input)
A bit field value indicating the Group(s) to pause. One or more of the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.

@note
This function pauses a target Group itself, as opposed to sceScreamPauseAllSoundsInGroup(), which iterates over all playing Sounds belonging to a target Group,
and pauses their instances.  This Group pause can therefore be considered persistent. Sounds that are started after the Group they belong to is paused, start in a paused state.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
@see
sceScreamContinueGroup(), sceScreamPauseAllSoundsInGroup(), sceScreamContinueAllSoundsInGroup(), sceScreamPauseSound(), sceScreamContinueSound(), sceScreamReverbPause(), sceScreamReverbContinue()
*/
int32_t sceScreamPauseGroup(uint32_t groups);
/**@}*/

/**
@ingroup groupFunctions

@brief
Continues one or more paused Groups.

This function continues one or more Groups that have been paused using the sceScreamPauseGroup() function.
You specify the target Group(s) to continue using the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink.
Use the bitwise <c>OR</c> operator to make multiple selections to create a bit field of Groups to continue.

@param groups (Input)
A bit field value indicating the Group(s) to continue. One or more of the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.

@note
This function continues a Group itself, as distinct from sceScreamContinueAllSoundsInGroup(), which iterates over all paused Sounds belonging to a target Group,
and continues their instances.  <b>Note:</b> This function does not continue a paused Sound if that Sound's instance is still paused.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamPauseGroup(), sceScreamPauseAllSoundsInGroup(), sceScreamContinueAllSoundsInGroup(), sceScreamPauseSound(), sceScreamContinueSound(), sceScreamReverbPause(), sceScreamReverbContinue()
*/
int32_t sceScreamContinueGroup(uint32_t groups);

/**
@ingroup groupFunctions

@brief
Pauses all active Sounds belonging to one or more Groups.

This function pauses all playing Sounds belonging to one or more Groups. Any Child Sounds belonging
to the Group(s) are also paused. You specify the target Group(s) using the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink.
Use the bitwise <c>OR</c> operator to make multiple selections to create a bit field of Groups in which to pause constituent Sounds.
Use the sceScreamContinueAllSoundsInGroup() function to continue Group-constituent Sounds paused by this function.

For more details, see &quot;Pausing All Sounds in a Group&quot; in the &quot;Working with Groups&quot; chapter of the <i>Scream Library Overview</i>.

@param groups (Input)
A bit field value indicating the Group(s) in which to pause constituent Sounds. One or more of the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.

@note
The pause mechanism used in this function is not persistent. That is, a Sound started after the Group it belongs to has been paused (using this function) will still play.
For a persistent Group pause mechanism, use sceScreamPauseGroup().

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamContinueAllSoundsInGroup(), sceScreamPauseGroup(), sceScreamContinueGroup(), sceScreamPauseSound(), sceScreamContinueSound(), sceScreamReverbPause(), sceScreamReverbContinue()
*/
int32_t sceScreamPauseAllSoundsInGroup(uint32_t groups);

/**
@ingroup groupFunctions

@brief
Continues paused Sounds belonging to one or more Groups.

This function continues paused Sounds &ndash; belonging to one or more Groups &ndash; that have been paused using the sceScreamPauseAllSoundsInGroup() function.
You specify the target Group(s) using the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink.
Use the bitwise <c>OR</c> operator to make multiple selections to create a bit field of Groups in which to continue paused Sounds.

@param groups (Input)
A bit field indicating the Group(s) in which to continue paused Sounds. One or more of the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamPauseAllSoundsInGroup(), sceScreamPauseGroup(), sceScreamContinueGroup(), sceScreamPauseSound(), sceScreamContinueSound(), sceScreamReverbPause(), sceScreamReverbContinue()
*/
int32_t sceScreamContinueAllSoundsInGroup(uint32_t groups);

/**
@ingroup groupFunctions

@brief
Stops all Sounds in one or more Groups.

This function stops all Sounds belonging to the specified Group(s).

The <c><i>behavior</i></c> parameter provides a choice of two stop behaviors:
<ul>
<li>#SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF: Performs a graceful stop, triggering any <i>On Stop Marker</i> grain events, and issuing key-off messages to active voices with ADSR Release settings.</li>
<li>#SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE: Performs an instantaneous stop.</li>
</ul>

@param groups (Input)
A bit field indicating which Groups to stop. One or more of the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.

@param behavior (Input)
A choice of two stop behaviors: #SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF or #SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE.

@note
Because Scream Groups are not persistent, a Sound belonging to a Group that has been stopped, and that is played
after the sceScreamStopAllSoundsInGroup() call, will still play.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamStopSound(), sceScreamStopAllSounds(), sceScreamStopAllSoundsInBank()
*/
int32_t sceScreamStopAllSoundsInGroup(uint32_t groups, int32_t behavior);

/**
@ingroup groupFunctions

@brief
Sets the voice allocation range for a Group.

This function allows you to allocate a range of voices per
Group, and provides a way to guarantee voice availability. In the default
voice allocation, all Sounds share the full pool of voices
available on the synthesizer.

The <c><i>min</i></c> and <c><i>max</i></c> parameters specify the
lower and upper limits of an inclusive voice allocation range assigned
to the specified Group. The upper limit of this range is
Scream-specific, and can be determined using the
sceScreamGetMaxPolyphony() function. However, because the <c><i>min</i></c>
and <c><i>max</i></c> parameters specify a zero-based voice allocation
index, and the value returned from sceScreamGetMaxPolyphony() is a one-based
count of addressable voices, you must subtract 1 from the returned value.
For example, if sceScreamGetMaxPolyphony() returns 192, you would use 191 as the upper limit
of values for the <c><i>min</i></c> and <c><i>max</i></c> parameters.

For more information, see &quot;Setting Group Voices Ranges&quot; in the &quot;Working with Groups&quot; chapter of the <i>Scream Library Overview</i>.

@param group (Input)
Index of the Group to set a voice allocation range for.
One of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants.

@param min (Input)
Starting index of the voice allocation. Range: 0 to (sceScreamGetMaxPolyphony() &ndash; 1).

@param max (Input)
Ending index of the voice allocation. Range: <c><i>min</i></c> to (sceScreamGetMaxPolyphony() &ndash; 1).

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamGetMaxPolyphony(), sceScreamGetSoundVoiceCount()
*/
int32_t sceScreamSetGroupVoiceRange(int32_t group, int32_t min, int32_t max);

/**
@ingroup groupFunctions

@brief
Sets voice output destination for a Group.

This function sets voice output destination on a Group basis. It sets the output destination of all voices associated with all Sounds assigned to a Group.

To set a Group's output destination to master output, set <c><i>outputDest</i></c> to #SCE_SCREAM_SND_OUTPUT_DEST_MASTER.
To set output destination to one of the pre-master submixes, set <c><i>outputDest</i></c> to the (zero-based) index of the desired submix; counting from #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 for submix buss number 1.

@param group (Input)
Index of the target Group for which to set a voice output destination.
One of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants.

@param outputDest (Input)
Index of the output destination to set. For the master output, use #SCE_SCREAM_SND_OUTPUT_DEST_MASTER.
To specify an allocated pre-master submix buss, use the number of the desired submix, indexing from zero.
Range: #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 to (#SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES &ndash; 1).
*/

/**
@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the SceScreamSystemParams structure.
Make sure that you do not set a pre-master submix output destination in <c><i>outputDest</i></c> that has not been allocated.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamSetGroupVoiceRange(), sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx()
*/
int32_t sceScreamSetGroupVoiceOutputDest(int32_t group, int32_t outputDest);

/**
@ingroup groupFunctions

@brief
Retrieves the set of Groups currently routing to a specified output destination.

This function retrieves the set of Groups currently routing to a specified output destination, and stores corresponding Group Flag(s) in an output variable.
You can use the retrieved set of Groups as input to Group-based transport and other functions.

@param outputDest (Input)
An output destination against which to query for routing Groups.
One of the \link #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 Output Destinations\endlink constants.

@param outGroups (Output)
A pointer to a <c>uint32_t</c> output variable containing a bitwise combination of zero or more \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink indicating the Groups currently routing to the specified output destination.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@see
sceScreamSetGroupVoiceOutputDest(), \link #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 Output Destinations\endlink, \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink, sceScreamGetActiveVoiceCountByGroup(), sceScreamGetActiveSoundCountByGroup(), sceScreamPauseGroup(), sceScreamContinueGroup(), sceScreamPauseAllSoundsInGroup(), sceScreamContinueAllSoundsInGroup(), sceScreamSetGroupSolo(), sceScreamSetGroupMute(), sceScreamStopAllSoundsInGroup()
*/
int32_t sceScreamGetGroupsByOutputDest(int32_t outputDest, uint32_t *outGroups);

/**
@ingroup groupFunctions

@brief
Sets a distance model for a Group.

This function sets a distance model on a Group basis.
Group-assigned Sounds, upon which the Distance Model property in Bank contents is set to &quot;By Group&quot;, inherit their Group's distance model setting.
To set a Group's distance model, you specify a target Group, and a hash representing the name of a distance model to set.

@note
Designers can also set Group distance models in Bank contents, and export these settings as part of a group mixer file.
When setting Group distance models using this function, check with your audio designer to make sure you are not unintentionally overwriting their settings.

@param group (Input)
Index of the target Group for which to set a distance model.
One of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Group\endlink constants.

@param modelNameHash (Input)
A hash of the name of a distance model.
Your audio designer can supply you with a list of the names of distance models contained in a distance model file.
You can use the sceScreamGetHashFromName() function to obtain a hash from a distance model name.
You can assign no distance model to a Group by setting this parameter to 0, which is equivalent to setting &quot;2D (none)&quot; in Bank contents.
Sounds inheriting this setting do not attenuate based on distance.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@see
sceScreamGetHashFromName(), SceScreamPlatformInitEx2.pDistanceModelFile
*/
int32_t sceScreamSetGroupDistanceModel(int32_t group, uint32_t modelNameHash);

/**
@ingroup groupFunctions

@brief
Retrieves the current volume level of a Group, or the level of Scream's global volume.

This function returns the current volume of a Group, or the level of Scream's global volume.
The <c><i>which</i></c> parameter is the index of the Group to retrieve a volume level for, and can be specified
using one of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants.

@param which (Input)
One of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants.

@return
The function returns the specified volume level as a floating-point value in the range #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.

@see
sceScreamSetMasterVolume()
*/
float  sceScreamGetMasterVolume(int32_t which);

/**
@ingroup groupFunctions

@brief
Sets the volume level of a Group, or the level of Scream's global volume.

Sounds in Scream are assigned to a Group specified in Bank contents. Scream scales each Sound based on its Group volume setting.
The #SCE_SCREAM_GROUP_MASTER_VOLUME setting scales the volumes of all Groups.

This function sets the volume of a Group or the level of Scream's global volume.
The <c><i>which</i></c> parameter is the index of the Group to set a volume level for, and is specified
as one of the Volume Group constants; see \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink.
Values for the <c><i>vol</i></c> parameter are expressed as a <c>float</c>, and must be within the range #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.

@param which (Input)
One of the Volume Group constants; see \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink.

@param vol (Input)
Volume level to apply. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.

@note
This function fails if the <c><i>which</i></c> parameter is out of range. Because the function does not return a value,
function calls with out-of-range <c><i>which</i></c> parameter values are ignored, and an error message
is shown in standard output.

@note
Setting a volume for #SCE_SCREAM_GROUP_VOLUME_EXTERNAL has no affect.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamGetMasterVolume()
*/
int32_t sceScreamSetMasterVolume(int32_t which, float vol);

/**
@ingroup groupFunctions

@brief
Activates (or deactivates) a volume ducker.

Volume ducking is the technique of reducing the volume of certain Sounds in order to highlight other Sounds.
For example, in a sports game, the volume level of crowd Sounds might be reduced during an announcement or commentary.
Scream provides for up to #SCE_SCREAM_SND_MAX_DUCKERS simultaneous volume duckers.

Use this function to activate a volume ducker.
The <c><i>which</i></c> parameter is a zero-based index referencing one of the volume duckers.
The <c><i>state</i></c> parameter points to an initialized SceScreamDuckerDef data structure defining the volume ducker's parameters.
To deactivate a volume ducker, set the <c><i>state</i></c> parameter to <c>NULL</c>.

@param which (Input)
Zero-based index of the volume ducker to activate. Range: 0 to (#SCE_SCREAM_SND_MAX_DUCKERS &ndash; 1).

@param state (Input)
Pointer to an initialized SceScreamDuckerDef data structure with which to activate the volume ducker.
Set to <c>NULL</c> to deactivate the volume ducker.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
SceScreamDuckerDef, sceScreamGetMasterVolume(), sceScreamSetGroupVoiceRange(), sceScreamSetMasterVolume()
*/
int32_t sceScreamSetMasterVolumeDucker(int32_t which, const SceScreamDuckerDef *state);

/**
@ingroup groupFunctions

@brief
Retrieves the current number of active synthesizer voices in use by a Group.

This function returns the current number of active synthesizer voices in use by a specified Group.

@param which (Input)
One of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants.

@return
The function returns the number of active synthesizer voices in use by the specified Group.

@see
sceScreamGetActiveSoundCountByGroup(), sceScreamGetMaxPolyphony()

*/
uint32_t  sceScreamGetActiveVoiceCountByGroup(int32_t which);

/**
@ingroup groupFunctions

@brief
Retrieves the current number of active sounds in a Group.

This function returns the current number of active sounds in a specified Group.

@param which (Input)
One of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants.

@return
The function returns the number of active sounds in the specified Group.

@see
sceScreamGetActiveVoiceCountByGroup()

*/
uint32_t  sceScreamGetActiveSoundCountByGroup(int32_t which);

/**
@ingroup groupFunctions

@brief
Retrieves a group-specific script speed factor for variable speed replays.

This function retrieves a group-specific script speed factor. Script speed factors are used for variable speed replays.
A value of 1.0 indicates normal speed. Values greater than 1.0 indicate increasingly faster replays.
Values less than 1.0 indicate progressively slower replays.

@param group (Input)
Index of the target Group from which to retrieve a script speed factor.
Any of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants except #SCE_SCREAM_GROUP_MASTER_VOLUME, which is not valid as a script speed target.

@param outFlags (Output)
Pointer to a <c>uint32_t</c> variable in which to receive any script speed flag values applied to the target group.
By default, variable speed replay affects time domain scripting properties only and does not affect pitch domain or ADSR envelope durations.
The #SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_PITCH flag set means variable speed replay also affects the pitch domain.
The #SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_ADSR flag set indicates variable speed replay scales the durations of ADSR segments.
Set to <c>NULL</c> if flag values are not required.

@return
Returns the specified group's script speed factor and optionally, script speed flags.

@see
sceScreamSetGroupScriptSpeedFactor(), sceScreamGetScriptSpeedFactor(), sceScreamSetScriptSpeedFactor(), sceScreamGetRandomIndex(), sceScreamSetRandomIndex()
*/
float  sceScreamGetGroupScriptSpeedFactor(uint32_t group, uint32_t *outFlags);

/**
@ingroup groupFunctions

@brief
Sets a group-specific script speed factor for variable speed replays.

In Scream, you can set both global and volume group-specific script speed factors for variable-speed replays.
This function sets a group-specific script speed factor. Use the sceScreamSetScriptSpeedFactor() function to set the global script speed factor.

<c><i>speedFactor</i></c> functions similarly to the jog wheel on a video cassette player. It can either be at rest (where
playback is at normal speed), rotated clockwise (to speed up playback), or rotated counter-clockwise (to
slow down playback). A <c><i>speedFactor</i></c> value of 1.0 indicates normal speed. Values
greater than 1.0 increasingly speed up playback. Values less than 1.0 progressively slow down playback.

<c><i>speedFactor</i></c> must be greater than 0.0 (variable speed replay cannot stand still or play backwards).
While there are no other direct programmatic constraints on the <c><i>speedFactor</i></c> value, there are
some indirect and practical constraints.

At the upper extremes, pitch shift on the rendering synthesizer cannot exceed two octaves above the original pitch, so
the effective maximum <c><i>speedFactor</i></c> value for the pitch domain is 4.0. The time-based playback
parameters can be speeded up by factors in excess of 4&times;. Note however, that very high speeds with
many simultaneous Sounds rapidly consume processor cycles. A practical constraint at the high end of the time domain may
be to keep <c><i>speedFactor</i></c> value less than 20.0. Note also that envelope values (ADSR) are not affected
by variable speed replays, so long attacks, decays, and releases remain the same no matter what
the <c><i>speedFactor</i></c> is set to.

At the lower extremes, because <c><i>speedFactor</i></c> temporarily changes the Scream tick rate, very low <c><i>speedFactor</i></c>
values could cause a noticeable delay following the replay until the tick rate returns to 240
ticks-per-second. A practical constraint at the low end may be to keep the <c><i>speedFactor</i></c> value greater than
0.05. If you need a slower replay speed, use pause/continue functionality to affect frame-by-frame replays.

For more information, see &quot;Manipulating Group Script Speed&quot; in the &quot;Working with Groups&quot; chapter of the <i>Scream Library Overview</i>.

@param group (Input)
Index of the target Group for which to set a script speed factor.
Any of the \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink constants except #SCE_SCREAM_GROUP_MASTER_VOLUME, which is not valid as a script speed target.

@param speedFactor (Input)
A speed multiplier for variable speed replays. Must be greater than 0. A value of 1.0 indicates normal speed.

@param flags (Input)
By default, variable speed replay affects time domain scripting properties only and does not affect pitch domain or ADSR envelope durations.
Set the #SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_PITCH flag if you want variable speed replay to also affect the pitch domain.
Set the #SCE_SCREAM_SND_SCRIPTSPEED_AFFECT_ADSR flag if you want variable speed replay to scale the durations of ADSR segments.

@return
If the script speed factor was set correctly, returns the new factor. Otherwise returns the existing script speed factor if a new factor could not be set.

@see
sceScreamGetGroupScriptSpeedFactor(), sceScreamGetScriptSpeedFactor(), sceScreamSetScriptSpeedFactor(), sceScreamGetRandomIndex(), sceScreamSetRandomIndex()
*/
float  sceScreamSetGroupScriptSpeedFactor(uint32_t group, float speedFactor, uint32_t flags);

/**
@ingroup groupFunctions

@brief
Solos one or more Groups.

This function solos audio output from one or more Groups.
You specify the target Group(s) using the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink.
Use the bitwise <c>OR</c> operator to make multiple selections to create a bit field of Groups to solo.

@param groups (Input)
A bit field indicating the Group(s) to solo. One or more of the \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.

@param solo (Input)
A Boolean value expressing solo status. Set to <c>TRUE</c> to solo the specified group(s); set to <c>FALSE</c> to cancel solo of the specified group(s).

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamSetGroupMute()
*/
int32_t sceScreamSetGroupSolo(uint32_t groups, bool solo);

/**
@ingroup groupFunctions

@brief
Mutes one or more Groups.

This function mutes audio output from one or more Groups.
You specify the target Group(s) using the Group Flags; see \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink.
Use the bitwise <c>OR</c> operator to make multiple selections to create a bit field of Groups to mute.

@param groups (Input)
A bit field indicating the Group(s) to mute. One or more of the Group Flags; see \link #SCE_SCREAM_GROUP_FLAG_SFX Group Flags\endlink. Use the bitwise <c>OR</c> operator for multiple selections.

@param mute (Input)
A Boolean value expressing mute status. Set to <c>TRUE</c> to mute the specified group(s); set to <c>FALSE</c> to cancel mute of the specified group(s).

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamSetGroupSolo()
*/
int32_t sceScreamSetGroupMute(uint32_t groups, bool mute);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Group Mixer

/**
@defgroup groupMixFunctions Group Mix Functions
@brief
Group mix functions allow you to activate, deactivate, and query mix snapshots. And to set the mixer base level.
@{*/
/**
@brief
Activates a mix snapshot.

This function activates a mix snapshot.
You specify the name of a snapshot to activate, as defined in a loaded group mixer file.
You pre-load a group mixer file into memory, and then provide the corresponding memory pointer as a value for
the SceScreamPlatformInitEx2 structure's <c><i>pGroupMixerFile</i></c> member when initializing Scream.

The mix snapshots mechanism supports activation of multiple snapshots at the same time.
You can set an upper limit for the number of simultaneously active snapshots at initialization time using the SceScreamPlatformInitEx2 <c><i>maxActiveSnapshots</i></c> member.

Snapshots contain level settings for one or more Groups, which are applied using either of two modes: Adjustment or Absolute.
In Absolute mode, Group volume level is set by a single snapshot. If multiple snapshots contain Absolute settings for a Group, the snapshot with the highest priority prevails.
In Adjustment mode, Group volume level may be set by a combination of multiple snapshots.
If multiple snapshots contain Adjustment settings for a Group, their settings add together to produce a combined snapshot level for the Group.

For further details, see &quot;Understanding Mix Snapshots&quot; in the &quot;Working with Mix Snapshots&quot; of the <i>Scream Library Overview</i>.

@param name (Input)
Name of a snapshot to activate.

@param mixScalar (Input)
A normalized percentage of the snapshot to apply. Defaults to 1.0 (or 100%) to use the designer’s setting.
Setting this parameter to lower than 1.0 reduces the level-setting impact of a snapshot.

@param fadeTimeOverride (Input)
A programmer override on the transition-in time of any mix changes that occur as a result of activating a snapshot.
Expressed in seconds. Defaults to -1.0 (or no override), allowing the snapshot's transition-in time to be as defined by the designer.

@return
Returns <c>TRUE</c> if the snapshot is successfully activated, otherwise returns <c>FALSE</c>.

@see
sceScreamDeactivateMixSnapshot(), sceScreamDeactivateAllMixSnapshots(), SceScreamPlatformInitEx2.pGroupMixerFile, sceScreamSetMasterVolume()
*/
bool sceScreamActivateMixSnapshot(const char *name, float mixScalar, float fadeTimeOverride);
/**@}*/

/**
@ingroup groupMixFunctions

@brief
Deactivates a mix snapshot.

This function deactivates a mix snapshot, specified by name.

@param name (Input)
Name of a snapshot to deactivate.

@param fadeTimeOverride (Input)
A programmer override on the transition-out time of any mix changes that occur as a result of deactivating a snapshot.
Expressed in seconds. Defaults to -1.0 (or no override), allowing the snapshot's transition-out time to be as defined by the designer.

@return
Returns <c>TRUE</c> if the snapshot is successfully deactivated, otherwise returns <c>FALSE</c>.

@see
sceScreamActivateMixSnapshot(), sceScreamDeactivateAllMixSnapshots(), sceScreamSetMasterVolume()
*/
bool sceScreamDeactivateMixSnapshot(const char *name, float fadeTimeOverride);

/**
@ingroup groupMixFunctions

@brief
Deactivates all active mix snapshots.

This function deactivates all active mix snapshots.

@param fadeTimeSeconds (Input)
Transition-out time, over which all Group volumes return to foundation mix settings, that is, initial Group levels combined with the mixer base level.
Expressed in seconds.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamActivateMixSnapshot(), sceScreamDeactivateMixSnapshot(), sceScreamSetMasterVolume()
*/
int32_t sceScreamDeactivateAllMixSnapshots(float fadeTimeSeconds);

/**
@ingroup groupMixFunctions

@brief
Queries whether a mix snapshot is active.

This function queries whether a mix snapshot, specified by name, is active.

@param name (Input)
Name of a snapshot to query.

@return
Returns <c>TRUE</c> if the specified snapshot is active; returns <c>FALSE</c> if the snapshot is inactive.

@see
sceScreamGetActiveMixSnapshotCount(), sceScreamGetMixSnapshotPriority()
*/
bool sceScreamIsMixSnapshotActive(const char *name);

/**
@ingroup groupMixFunctions

@brief
Retrieves a count of the total number of mix snapshots.

This function retrieves a count of the total number of mix snapshots contained in a group mixer file with which Scream was initialized.

You can use the returned count value to determine the upper limit of snapshot indices when retrieving snapshot names using the sceScreamGetMixSnapshotName() function.

@return
Returns a count of the number of mix snapshots contained in your group mixer file.

@see
sceScreamGetMixSnapshotName(), SceScreamPlatformInitEx2.pGroupMixerFile, sceScreamGetActiveMixSnapshotCount()
*/
uint32_t sceScreamGetMixSnapshotCount(void);

/**
@ingroup groupMixFunctions

@brief
Retrieves the name of a mix snapshot, specified by index.

This function retrieves the name of a mix snapshot.
Mix snapshots are contained in a group mixer file, which must be loaded into Scream at initialization time.
You identify a mix snapshot to query by its index within your group mixer file.
You can use the sceScreamGetMixSnapshotCount() function to retrieve a count the number of mix snapshots contained in your group mixer file.
The <c><i>snapshotIndex</i></c> parameter takes a zero-based index.
So you must subtract 1 from the value returned by sceScreamGetMixSnapshotCount() to determine the index of the last snapshot.

@param snapshotIndex (Input)
The index of a snapshot for which to retrieve the name. Range 0 to (sceScreamGetMixSnapshotCount() &ndash; 1).

@param snapshotName (Output)
A <c>char</c> array into which the name of the specified mix snapshot is copied.

@param maxLength (Input)
Maximum number of characters to copy into the <c><i>snapshotName</i></c> array.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@see
sceScreamGetMixSnapshotCount(), SceScreamPlatformInitEx2.pGroupMixerFile, sceScreamGetActiveMixSnapshotNames()
*/
int32_t sceScreamGetMixSnapshotName(uint32_t snapshotIndex, char* snapshotName, uint32_t maxLength);

/**
@ingroup groupMixFunctions

@brief
Retrieves a count of the number of active mix snapshots.

This function retrieves a count of the number of active mix snapshots.

@return
Returns a count of the number of active mix snapshots. The returned value is in the range 0 to SceScreamPlatformInitEx2.maxActiveSnapshots.

@see
sceScreamIsMixSnapshotActive(), sceScreamGetMixSnapshotPriority()
*/
uint32_t sceScreamGetActiveMixSnapshotCount(void);

/**
@ingroup groupMixFunctions

@brief
Retrieves a priority ordered list of active mix snapshot names.

This function retrieves a priority ordered list of active mix snapshot names.

@param names (Output)
An array of <c>char</c> pointers in which to receive snapshot names.

@param maxCount (Input)
Maximum number of active snapshot names to retrieve. Range: 0 to SceScreamPlatformInitEx2.maxActiveSnapshots.

@return
Returns the number of active mix snapshot names retrieved. The returned value is in the range: 0 to <c><i>maxCount</i></c>.

@see
sceScreamGetActiveMixSnapshotCount()
*/
uint32_t sceScreamGetActiveMixSnapshotNames(char **names, uint32_t maxCount);

/**
@ingroup groupMixFunctions

@brief
Retrieves the priority setting for a mix snapshot.

This function retrieves the priority setting for a mix snapshot.

@param name (Input)
Name of a snapshot for which to retrieve the priority setting.

@param priority (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the snapshot's priority.

@return
Returns <c>TRUE</c> if the priority retrieval operation was successful; returns <c>FALSE</c> if not.

@see
sceScreamIsMixSnapshotActive(), sceScreamGetActiveMixSnapshotCount()
*/
bool sceScreamGetMixSnapshotPriority(const char *name, uint32_t *priority);

/**
@ingroup groupMixFunctions

@brief
Sets the group mixer base level.

This function sets the group mixer base level.
The group mixer base level provides an adjustment control on all Group volume levels, before further scaling by the Group Master level.
It is conceived as an additional headroom control, and is part of the foundation mix settings included in a group mixer file.
The initial base level setting is defined in a group mixer file, which can be loaded into Scream at initialization time.
See the SceScreamPlatformInitEx2 <c><i>pGroupMixerFile</i></c> member.

@note
Setting the group mixer base level from the API overrides the initial base level set by a group mixer file.
This essentially alters the foundation mix, and thus may offset the effects of activating mix snapshots in unpredictable ways.
When setting the mixer base level, it is prudent to store its initial value, so that you can reset to this value later, allowing your audio designer's foundation mix settings to remain intact.
For further details, see the &quot;Working with Mix Snapshots&quot; chapter in the <i>Scream Library Overview</i>.

@param dbLevel (Input)
Group mixer base level. Expressed in dB.

@param fadeTimeSeconds (Input)
Fade time for the group mixer to reach the target base level from its current level. Expressed in seconds.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
SceScreamPlatformInitEx2.pGroupMixerFile
*/
int32_t sceScreamSetGroupMixerBaseLevel(float dbLevel, float fadeTimeSeconds);

////////////////////////////////////////////////////////////////////////////////
// Banks
/**
@defgroup bankFunctions Bank Functions
@brief
Bank functions load and manipulate Banks, and retrieve Bank information.
@{*/
/**
@brief
Loads a Bank file from disk.

This function loads a Bank (BNK file) into main memory from the disk.

If a data management system is being used, in which BNK files are embedded into larger container files,
the <c><i>offset</i></c> parameter provides a way to reference an embedded BNK file by specifying the number of bytes
into the container file where the BNK file begins.

@param name (Input)
Name of the BNK file to load from disk.

@param offset (Input)
Offset number of bytes into a container file where the embedded BNK file begins.
Set to zero if the BNK file is not embedded in a container file.

@return
If the load operation is successful, the function returns a <c>SceScreamSFXBlock2</c> pointer to the loaded Bank.
If the load fails, the function returns <c>NULL</c>.

@note
Whenever memory is requested for a Bank, the system passes the constant #SCE_SCREAM_SND_MEM_USE_BANK
to your custom SceScreamExternSndMemAlloc() <c><i>use</i></c> parameter.

@note
If the Bank load operation fails, you can check the reason for the failure using the sceScreamGetLastLoadError()
function.

@note
Banks are platform-specific. Be sure that you are loading a Bank for the intended platform.

@see
sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), sceScreamUnloadBank(), sceScreamGetLastLoadError()
*/
SceScreamSFXBlock2*  sceScreamBankLoadEx(const char *name, int32_t offset);
/**@}*/

/**
@ingroup bankFunctions

@brief
Loads a Bank from memory.

This function loads a Bank that is already resident in main memory. This has the effect of registering the Bank
with Scream, enabling its Sounds to be played. It is important that the Bank remains resident in main memory
until it is unloaded, using the sceScreamUnloadBank() function.

This function is useful if you want to page a Scream Bank into memory while the game is in progress. When
the paging code has finished loading the Bank (from Blu-ray or HDD), you can register the memory-loaded Bank with
Scream using this function. This is generally the preferred method, as the sceScreamBankLoadEx() function
blocks the calling thread until the file has completed loading from disk. sceScreamBankLoadFromMemEx(), however, returns much more quickly.

@param loc (Input)
Pointer to a memory address where the Bank resides.

@return
If the load operation is successful, the function returns a <c>SceScreamSFXBlock2</c> pointer to the loaded Bank.
If the load fails, the function returns <c>NULL</c>.

@note
If the Bank load operation fails, the reason for the failure can be checked using the sceScreamGetLastLoadError()
function. If the failure is due to the <c><i>loc</i></c> parameter being passed an invalid memory pointer, the
sceScreamGetLastLoadError() function returns #SCE_SCREAM_SND_LOAD_ERROR_MEMORY.

@note
Banks are platform-specific. Be sure that you are loading a Bank for the intended platform.

@note
A small amount of memory (16 bytes or less) is required for Bank data management that is in addition to the actual Bank data.
When calling this function, the system passes the constant #SCE_SCREAM_SND_MEM_USE_BANK
to your custom SceScreamExternSndMemAlloc() <c><i>use</i></c> parameter in requesting the additional memory, even though the Bank data
itself is already in memory.

@see
sceScreamBankLoadEx(), sceScreamFindLoadedBankByName(), sceScreamUnloadBank(), sceScreamGetLastLoadError()
*/
SceScreamSFXBlock2*  sceScreamBankLoadFromMemEx(void *loc);

/**
@ingroup bankFunctions

@brief
Retrieves the pointer to a loaded Bank by reference to its name.

This function retrieves the pointer to a loaded Bank that you reference by name.
Because both functions for playing a Sound &ndash; sceScreamPlaySoundByIndexEx() and sceScreamPlaySoundByNameEx() &ndash;
require a <c>SceScreamSFXBlock2</c> pointer as the <c><i>bank</i></c> argument, this function is helpful in cases where a Bank's
name is known, but not its <c>SceScreamSFXBlock2</c> pointer.

@param bankName (Input)
Name of the Bank for which to retrieve the pointer.

@return
Returns the <c>SceScreamSFXBlock2</c> pointer for the specified Bank.

@see
sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamUnloadBank(), sceScreamFindLoadedBankNameByPointer(), sceScreamGetNextLoadedBank()
*/
SceScreamSFXBlock2*  sceScreamFindLoadedBankByName(const char *bankName);

/**
@ingroup bankFunctions

@brief
Retrieves the name of a loaded Bank by reference to its <c>SceScreamSFXBlock2</c> pointer.

This function retrieves the name of a loaded Bank by reference to its <c>SceScreamSFXBlock2</c> pointer.

@param bank (Input)
Pointer of a Bank for which to retrieve the name.

@param outBankName (Output)
Pointer to a variable in which to store the Bank name.

@return
Returns <c>TRUE</c> if the Bank name was found, otherwise returns <c>FALSE</c>.
If the referenced Bank is loaded but not named, the function returns <c>TRUE</c> &mdash; but the value stored in the <c><i>outBankName</i></c> variable is set to all zeros.

@see
sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), sceScreamGetNextLoadedBank()
*/
bool        sceScreamFindLoadedBankNameByPointer(SceScreamSFXBlock2 *bank, char outBankName[SCE_SCREAM_SND_MAX_BANK_NAME_LENGTH]);

/**
@ingroup bankFunctions

@brief
Retrieves the next loaded Bank in the linked list of loaded Banks.

This function retrieves the next Bank in the linked list of loaded Banks.
It can be used to iterate over all loaded Banks.

@param prevBank (Input)
<c>SceScreamSFXBlock2</c> pointer of the Bank that comes immediately before the <c>SceScreamSFXBlock2</c> pointer to retrieve.
Can be <c>NULL</c>, in which case the pointer to the head of the Bank linked list is returned.

@return
Returns the <c>SceScreamSFXBlock2</c> pointer immediately following the pointer passed in as <c><i>prevBank</i></c>. If there is no next Bank, the function returns <c>NULL</c>.

@see
sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), sceScreamFindLoadedBankNameByPointer()
*/
SceScreamSFXBlock2*  sceScreamGetNextLoadedBank(SceScreamSFXBlock2 *prevBank);

/**
@ingroup bankFunctions

@brief
Retrieves the last Bank load error condition.

This function retrieves the last error condition set in relation to a Bank load operation.
The resulting error condition will either be an OS-specific file system error code, or one of the following Scream-specific error codes:<br>
#SCE_SCREAM_SND_LOAD_ERROR_COULDNT_OPEN_FILE<br>
#SCE_SCREAM_SND_LOAD_ERROR_READING_FILE<br>
#SCE_SCREAM_SND_LOAD_ERROR_MEMORY<br>
#SCE_SCREAM_SND_LOAD_ERROR_ALIGNMENT<br>
#SCE_SCREAM_SND_LOAD_ERROR_INVALID_FORMAT<br>
#SCE_SCREAM_SND_LOAD_ERROR_ALREADY_LOADED

@return
Returns the error code generated during the last failed Bank load operation.

@see
sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamUnloadBank()
*/
int32_t     sceScreamGetLastLoadError(void);

/**
@ingroup bankFunctions

@brief
Stops all Sounds in a Bank.

This function stops all Sounds in a specified Bank.

The <c><i>behavior</i></c> parameter provides a choice of two stop behaviors:
<ul>
<li>#SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF: Performs a graceful stop, triggering any <i>On Stop Marker</i> grain events, and issuing key-off messages to active voices with ADSR Release settings.</li>
<li>#SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE: Performs an instantaneous stop.</li>
</ul>

@param bank (Input)
Handle of the Bank that you wish to stop, as returned by the sceScreamBankLoadEx() or
sceScreamBankLoadFromMemEx() functions.

@param behavior (Input)
A choice of two stop behaviors: #SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF or #SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE.

@note
sceScreamStopAllSoundsInBank() is called automatically by the sceScreamUnloadBank() function.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx(), sceScreamStopAllSounds(), sceScreamStopSound(), sceScreamStopAllSoundsInGroup()
*/
int32_t sceScreamStopAllSoundsInBank(const SceScreamSFXBlock2 *bank, int32_t behavior);

/**
@ingroup bankFunctions

@brief
Unloads a loaded Bank &ndash; synchronously or asynchronously.

This function unloads a loaded Bank. The <c><i>synchronous</i></c> parameter allows you to specify synchronous or asynchronous unloading.

If the Bank had been loaded using the sceScreamBankLoadEx() function, the memory it occupies is freed automatically
with an internal call to the registered memory free function (see sceScreamStartSoundSystemEx2()).

If the Bank had been loaded using the sceScreamBankLoadFromMemEx() function, it is
simply unregistered (rather than unloaded). <b>Note:</b> In this case, the application is
responsible for freeing the memory occupied by the unloaded Bank.

@param bank (Input)
Handle of the Bank you wish to unload, as returned by the sceScreamBankLoadEx() or
sceScreamBankLoadFromMemEx() functions.

@param synchronous (Input)
A Boolean specifying whether or not the function should execute synchronously.
Specify <c>TRUE</c> for synchronous (blocking) execution. With synchronous execution, it is safe to free (or overwrite) the Bank's allocated memory by the time the function returns.
Specify <c>FALSE</c> for asynchronous execution. With asynchronous execution, before freeing (or overwriting) the Bank's allocated memory, you must poll the Bank's status using the sceScreamBankIsSafeToDelete() function until that function returns <c>TRUE</c>, indicating it is safe to do so.
While the default value is <c>TRUE</c>, it is recommended to set this parameter to <c>FALSE</c>. See &quot;Notes&quot; below.

@return
Returns <c>TRUE</c> if successful, otherwise returns <c>FALSE</c>.

@note
In the interests of maintaining backwards compatibility, the <c><i>synchronous</i></c> parameter defaults to <c>TRUE</c>.
However, using synchronous unloading can sleep the calling thread for a significant time interval, and is not recommended.

@note
If a Bank was loaded directly from memory (using sceScreamBankLoadFromMemEx()), you must first unload
it &mdash; to unregister the Bank from Scream  &mdash; before freeing its allocated memory.

@note
This function fails if a Bank relocation operation is currently in progress.

@see
sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamBankIsSafeToDelete(), sceScreamGetLastLoadError()

*/
bool        sceScreamUnloadBank(const SceScreamSFXBlock2 *bank, bool synchronous /* = true */);

/**
@ingroup bankFunctions

@brief
Determines whether it is safe to delete memory allocated for a Bank.

This function determines whether memory allocated for a Bank can safely be deleted or otherwise overwritten.
This function applies only to Banks that were originally loaded using the sceScreamBankLoadFromMemEx() function.
If a Bank has been unloaded asynchronously using the sceScreamUnloadBank() function (that is, with the function's <c><i>synchronous</i></c> parameter set to <c>FALSE</c>),
you can poll the Bank's status using this function. Once the function returns <c>TRUE</c>, it is safe to free (or overwrite) the specified Bank's memory.
Before it returns <c>TRUE</c>, it must be assumed that the underlying synthesizer is still accessing the memory.

@param bank (Input)
Handle of the Bank for which to determine delete status, as returned by the sceScreamBankLoadFromMemEx() function.

@return
This function returns <c>TRUE</c> when it is safe to free (or overwrite) the specified Bank's memory. Otherwise, it returns <c>FALSE</c>.

@note
If the specified Bank was loaded using sceScreamBankLoadEx(), the function always returns <c>FALSE</c>.
The allocated memory for Banks loaded using the sceScreamBankLoadEx() function is automatically freed upon unloading the Bank with a call to sceScreamUnloadBank().

@see
sceScreamUnloadBank(), sceScreamBankLoadFromMemEx(), sceScreamBankLoadEx()
*/
bool        sceScreamBankIsSafeToDelete( const SceScreamSFXBlock2 *bank );

/**
@ingroup bankFunctions

@brief
Retrieves the number of Sounds in a Bank.

This function retrieves the number of Sounds resident in a specified Bank.

@param bank (Input)
Handle of the Bank for which you wish to obtain the number of Sounds.

@return
If successful, returns the number of Sounds in the specified Bank. If not successful, returns 0.

@see
sceScreamBankGetSoundNameByIndex(), sceScreamBankGetSoundIndexByName()
*/
uint32_t    sceScreamBankGetNumSoundsInBank(const SceScreamSFXBlock2 *bank);

/**
@ingroup bankFunctions

@brief
Retrieves the name of a Sound by reference to its index within a Bank.

This function retrieves the name of a Sound by reference to its index within a Bank.
It stores the name in a user-supplied character array.

@param bank (Input)
Handle of the Bank from which to retrieve the Sound name.

@param index (Input)
Zero-based index of a Sound from which to retrieve the name.

@param soundName (Output)
A character array in which to receive the name of the Sound. Minimum length: #SCE_SCREAM_SND_MAX_NAME_LENGTH.

@return
Returns <c>TRUE</c> if successful, otherwise returns <c>FALSE</c>.

@see
sceScreamBankGetNumSoundsInBank(), sceScreamBankGetSoundIndexByName()
*/
bool        sceScreamBankGetSoundNameByIndex(const SceScreamSFXBlock2 *bank, int16_t index, char soundName[SCE_SCREAM_SND_MAX_NAME_LENGTH]);

/**
@ingroup bankFunctions

@brief
Retrieves the index of a Sound by reference to its name.

This function retrieves the index of a Sound (and its containing Bank) by reference to its name.
You can optionally specify a <c>SceScreamSFXBlock2</c> pointer if you only wish to search a single Bank.

@param bank (Input)
Handle of a Bank to search for the specified Sound name. Set to <c>NULL</c> to search all loaded Banks.

@param soundName (Input)
Name of the Sound from which to retrieve the index.

@param outIndex (Output)
Pointer to an <c>int16_t</c> variable in which to receive the Sound index &ndash; if found.

@param outBank (Output)
Pointer to a <c>SceScreamSFXBlock2</c> pointer in which to receive the Bank pointer that contains the referenced Sound. Can be <c>NULL</c> if the Bank pointer is not desired.

@return
Returns <c>TRUE</c> if successful, otherwise returns <c>FALSE</c>.

@see
sceScreamBankGetNumSoundsInBank(), sceScreamBankGetSoundNameByIndex()
*/
bool        sceScreamBankGetSoundIndexByName(const SceScreamSFXBlock2 *bank, const char *soundName, int16_t *outIndex, SceScreamSFXBlock2 **outBank);

////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////
// Sound Instance

// Play, Stop, Pause
/**
@defgroup soundFunctions Sound Functions
@brief
Sound instance functions start and stop Sounds, dynamically manipulate their parameters, and set and retrieve Sound state information.
@{*/
/**
@brief
Continues a paused Sound.

This function continues a paused Sound and any Child Sounds it may contain.
If the Sound is not currently paused, this function will have no effect.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@return
Returns the specified handle if the Sound is continued.
Returns 0 if the specified Sound is no longer active.

@note
This function continues a Sound regardless of how it was originally paused, that is,
whether using sceScreamPauseSound(), sceScreamPauseAllSoundsInGroup(), and so on.

@see
sceScreamPauseSound(), sceScreamPauseAllSoundsInGroup(), sceScreamContinueAllSoundsInGroup(), sceScreamPauseGroup(), sceScreamContinueGroup(), sceScreamReverbPause(), sceScreamReverbContinue()
*/
uint32_t  sceScreamContinueSound(uint32_t handle);
/**@}*/

/**
@ingroup soundFunctions

@brief
Verifies whether a Sound instance is still playing.

This status function verifies whether a Sound is still playing.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@return
Returns the passed in Sound handle if the Sound is still playing.
Returns 0 if the Sound has stopped.

@see
sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx()
*/
uint32_t  sceScreamSoundIsStillPlaying(uint32_t handle);

/**
@ingroup soundFunctions

@brief
Pauses a Sound.

This function pauses the specified Sound and any Child Sounds it contains. If the Sound is
already paused, this function has no effect. Pausing a Sound does not free the voice(s) it is using.
If you start the same Sound from a new call, any instance limits still apply &ndash; just as if the paused Sound is still playing and using voices.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@return
Returns the specified handle if the Sound is paused.
Returns 0 if the specified Sound is no longer active.

@see
sceScreamContinueSound(), sceScreamPauseAllSoundsInGroup(), sceScreamContinueAllSoundsInGroup(), sceScreamPauseGroup(), sceScreamContinueGroup(), sceScreamReverbPause(), sceScreamReverbContinue(), sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx()
*/
uint32_t  sceScreamPauseSound(uint32_t handle);

/**
@ingroup soundFunctions

@brief
Plays a Sound by reference to its index within a Bank.

This function plays a Sound by reference to its index within a specified Bank.

The <c><i>params</i></c> argument takes a pointer to a SceScreamSoundParams structure, in which you can store initial parameter values to set on the Sound.

@param bank (Input)
Pointer to a Bank that contains the Sound you wish to play, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param index (Input)
Zero-based index of the requested Sound within the specified <c><i>bank</i></c>.

@param params (Input)
Pointer to an initialized SceScreamSoundParams structure containing any Sound parameter values to set from the API. See &quot;Notes&quot; below.

@param outputDest (Input)
Index of an output destination.
Defaults to #SCE_SCREAM_SND_OUTPUT_DEST_MASTER for master output.
To inherit an output destination from the Group to which the Sound is assigned, use #SCE_SCREAM_SND_OUTPUT_DEST_BY_GROUP.
To specify an allocated pre-master submix buss, use the number of the desired submix, indexing from zero, and within the range: #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 to (#SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES &ndash; 1).
*/

/**
@return
Returns the handle of the requested Sound. Returns 0 if the specified <c><i>index</i></c> is out of range or if SceScreamSoundParams.size specified in the <c><i>params</i></c> member is invalid.

@note
Setting Sound parameter values from the API overrides any corresponding settings arising from Bank contents.
For further details, see &quot;Scream Tool and API Parameter Settings&quot; in the &quot;System Overview&quot; chapter of the <i>Scream Library Overview</i>.

@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the SceScreamSystemParams structure.
Make sure that you do not set a pre-master submix output destination in <c><i>outputDest</i></c> that has not been allocated.

*/
/**

@see
sceScreamPlaySoundByNameEx(), sceScreamStopSound(), sceScreamSetGroupVoiceOutputDest()
*/
uint32_t  sceScreamPlaySoundByIndexEx(const SceScreamSFXBlock2 *bank, int16_t index, const SceScreamSoundParams *params, int32_t outputDest /* = SCE_SCREAM_SND_OUTPUT_DEST_MASTER*/);

/**
@ingroup soundFunctions

@brief
Plays a Sound by reference to its name within a Bank.

This function plays a Sound by reference to its name within a specified Bank.

The <c><i>params</i></c> argument takes a pointer to a SceScreamSoundParams structure, in which you can store initial parameter values to set on the Sound.

@param bank (Input)
Pointer to a Bank that contains the Sound you wish to play, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().
Can also be <c>NULL</c>. See &quot;Notes&quot; below.

@param name (Input)
Name of the requested Sound within the specified <c><i>bank</i></c>.

@param params (Input)
Pointer to an initialized SceScreamSoundParams structure containing any Sound parameter values to set from the API. See &quot;Notes&quot; below.

@param outputDest (Input)
Index of an output destination.
Defaults to #SCE_SCREAM_SND_OUTPUT_DEST_MASTER for master output.
To inherit an output destination from the Group to which the Sound is assigned, use #SCE_SCREAM_SND_OUTPUT_DEST_BY_GROUP.
To specify an allocated pre-master submix buss, use the number of the desired submix, indexing from zero, and within the range: #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 to (#SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES &ndash; 1).
*/
/**

@return
Returns the handle of the requested Sound. Returns 0 if the specified <c><i>name</i></c> is not valid or if SceScreamSoundParams.size specified in the <c><i>params</i></c> member is invalid.

@note
If <c><i>bank</i></c> is <c>NULL</c>, this function searches through all registered Banks, then plays the first Sound it finds having the specified <c><i>name</i></c>.
If no Sound with that name is found, the function returns 0.

@note
Setting Sound parameter values from the API overrides any corresponding settings arising from Bank contents.
For further details, see &quot;Scream Tool and API Parameter Settings&quot; in the &quot;System Overview&quot; chapter of the <i>Scream Library Overview</i>.

@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the SceScreamSystemParams structure.
Make sure that you do not set a pre-master submix output destination in <c><i>outputDest</i></c> that has not been allocated.

*/
/**

@see
sceScreamPlaySoundByIndexEx(), sceScreamStopSound(), sceScreamSetGroupVoiceOutputDest()
*/
uint32_t  sceScreamPlaySoundByNameEx(const SceScreamSFXBlock2 *bank, const char *name, const SceScreamSoundParams *params, int32_t outputDest /* = SCE_SCREAM_SND_OUTPUT_DEST_MASTER */);

/**
@ingroup soundFunctions

@brief
Stops a Sound.

This function stops the specified Sound.

The <c><i>behavior</i></c> parameter provides a choice of two stop behaviors:
<ul>
<li>#SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF: Performs a graceful stop, triggering any <i>On Stop Marker</i> grain events, and issuing key-off messages to active voices with ADSR Release settings.</li>
<li>#SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE: Performs an instantaneous stop.</li>
</ul>

This function is primarily used for looping Sounds; one-shot Sounds stop themselves.

@param handle (Input)
Handle of the Sound to stop, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@param behavior (Input)
A choice of two stop behaviors: #SCE_SCREAM_SND_STOP_BEHAVIOR_KEYOFF or #SCE_SCREAM_SND_STOP_BEHAVIOR_SILENCE.

@return
Returns the specified handle if the Sound is stopped.
Returns 0 if the specified Sound is no longer active.

@see
sceScreamStopAllSounds(), sceScreamStopAllSoundsInGroup(), sceScreamStopAllSoundsInBank(), sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx()
*/
uint32_t  sceScreamStopSound(uint32_t handle, int32_t behavior);

// All Parameters
/**
@ingroup soundFunctions

@brief
Retrieves an active Sound's parameter values.

This function retrieves parameter values for an actively playing Sound. The retrieved values are stored in
the SceScreamSoundParams instance pointed to in the <c><i>params</i></c> argument.

@param handle (Input)
Handle of the Sound for which to retrieve parameter values.

@param params (Output)
Pointer to a SceScreamSoundParams data structure, into which the retrieved parameter values are stored.
The SceScreamSynthParams structure in the SceScreamSoundParams's <c><i>synthParams</i></c> member may also be filled; see &quot;Notes&quot; below.
Do not provide a pointer to a SceScreamSynthParams structure in <c><i>synthParams</i></c>; that can also be filled by the function.

@return
Returns the handle of the specified Sound. Returns 0 if the Sound is no longer active or if SceScreamSoundParams.size specified in the <c><i>params</i></c> member is invalid.
Even though the supplied SceScreamSoundParams structure is filled by this function, you must set its <c><i>size</i></c> member appropriately to indicate that the properly size structure is provided.

@note
If the #SCE_SCREAM_SND_MASK_SYNTH_PARAMS bit is set in the SceScreamSoundParams <c><i>mask</i></c>
member, this indicates that one or more synthesizer-specific parameters have been set from the Scream API &mdash; overriding those settings
in Bank contents &mdash; and that the SceScreamSynthParams structure in the <c><i>synthParams</i></c> parameter has the changed values.
To see which synthesizer-specific parameters have been set from the Scream API, examine the value of the SceScreamSynthParams <c><i>mask</i></c> member.

@note
If the #SCE_SCREAM_SND_MASK_SYNTH_PARAMS bit is <i>not</i> set, then the synthesizer parameters are as specified in Bank contents
and have not been changed by the Scream API.
In this case, the corresponding SceScreamSoundParams <c><i>synthParams</i></c> member does not contain data.
A Sound can contain multiple Grains, but synthesizer parameter settings
in Bank contents are on a per-Grain basis, and therefore Sound settings cannot be represented in single SceScreamSynthParams data structure.
For more information, see &quot;Parent and Child Sounds&quot; and &quot;Scream Tool and API Parameter Settings&quot; in the &quot;System Overview&quot; chapter of the <i>Scream Library Overview</i>.

@see
sceScreamSetSoundParamsEx()
*/
uint32_t sceScreamGetSoundParamsEx(uint32_t handle, SceScreamSoundParams *params);

/**
@ingroup soundFunctions

@brief
Sets an active Sound's parameter values.

This function sets the parameters of an actively playing Sound. Sound parameter settings
made from the Scream API override any settings in Bank contents. For
further details, see &quot;Notes&quot; below.

@note
If the pointed to SceScreamSoundParams data structure includes SceScreamSynthParams settings, these
will override all synthesizer-specific parameter settings in Bank contents, which may include
settings in multiple Grains and in Child Sounds. Therefore, it is generally good practice to coordinate synthesizer parameter
settings with your audio design team.

@note
For more information on how setting these parameters interacts with the original Bank contentsScream Tool settings, see &quot;Setting Parameter Values&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.

@param handle (Input)
Handle of the Sound for which to set parameter values.

@param params (Input)
Pointer to a SceScreamSoundParams data structure containing the parameter values to set.

@return
If successful, returns the handle of the specified Sound. Returns 0 if not successful or if SceScreamSoundParams.size specified in the <c><i>params</i></c> member is invalid.

@see
sceScreamGetSoundParamsEx(), sceScreamGetSoundGainComponents()
*/
uint32_t sceScreamSetSoundParamsEx(uint32_t handle, const SceScreamSoundParams *params);

// Gain and Pitch Components
/**
@ingroup soundFunctions

@brief
Retrieves the gain components that comprise a Sound's aggregate gain level.

A Sound's aggregate gain level is comprised of a number of components.
This function retrieves all of a Sound's gain components and stores them in a SceScreamGainComponents structure.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@param components (Output)
Pointer to a SceScreamGainComponents structure in which to receive the Sound's gain components.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@note
You can determine the Sound's aggregate gain level by multiplying together the values of its constituent gain components.

@note
You may still hear a Sound's output even if its aggregate gain components calculation comes to zero.
In such a case, the Sound's auxiliary send(s) may be non-zero, causing signal to feed into an auxiliary buss, and subsequently through an effect and back into the master buss.

@see
SceScreamGainComponents, sceScreamGetSoundPanAzimuthComponents(), sceScreamGetSoundPitchTransposeComponents(), sceScreamGetSoundPitchBendFactorComponents(), sceScreamGetSoundParamsEx()
*/
uint32_t sceScreamGetSoundGainComponents(uint32_t handle, SceScreamGainComponents *components);

/**
@ingroup soundFunctions

@brief
Retrieves the pan components that comprise a Sound's aggregate panning azimuth.

A Sound's aggregate panning azimuth is comprised of a number of components.
This function retrieves all of a Sound's pan components and stores them in a SceScreamPanAzimuthComponents structure.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@param components (Output)
Pointer to a SceScreamPanAzimuthComponents structure in which to receive the Sound's pan components.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@note
You can determine a Sound's aggregate panning azimuth by adding together the values of its constituent pan components modulo 360.

@see
SceScreamPanAzimuthComponents, sceScreamGetSoundPitchTransposeComponents(), sceScreamGetSoundPitchBendFactorComponents(), sceScreamGetSoundGainComponents(), sceScreamGetSoundParamsEx()
*/
uint32_t sceScreamGetSoundPanAzimuthComponents(uint32_t handle, SceScreamPanAzimuthComponents *components);

/**
@ingroup soundFunctions

@brief
Retrieves the pitch transposition components that comprise a Sound's aggregate pitch transposition.

A Sound's aggregate pitch transposition is comprised of a number of components.
This function retrieves all of a Sound's pitch transposition components and stores them in a
SceScreamPitchTransposeComponents structure.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@param components (Output)
Pointer to a SceScreamPitchTransposeComponents structure in which to receive the Sound's pitch transposition components.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@note
You can determine a Sound's aggregate pitch transposition by adding together the values of its constituent pitch transposition components and clamping to &plusmn;#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE, relative to the original pitch.

@see
SceScreamPitchTransposeComponents, sceScreamGetSoundPitchBendFactorComponents(), sceScreamGetSoundGainComponents(), sceScreamGetSoundPanAzimuthComponents(), sceScreamGetSoundParamsEx()
*/
uint32_t sceScreamGetSoundPitchTransposeComponents(uint32_t handle, SceScreamPitchTransposeComponents *components);

/**
@ingroup soundFunctions

@brief
Retrieves the pitchbend factor components that comprise a Sound's aggregate pitchbend factor.

A Sound's aggregate pitchbend factor is comprised of a number of components.
This function retrieves all of a Sound's pitchbend factor components and stores them in a
SceScreamPitchBendFactorComponents structure.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@param components (Output)
Pointer to a SceScreamPitchBendFactorComponents structure in which to receive the Sound's pitchbend factor components.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@note
You can determine a Sound's pitchbend factor amount by adding together the values of its constituent pitchbend
components and clamping between #SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR to #SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR.

@see
SceScreamPitchBendFactorComponents, sceScreamGetSoundPitchTransposeComponents(), sceScreamGetSoundGainComponents(), sceScreamGetSoundPanAzimuthComponents(), sceScreamGetSoundParamsEx()
*/
uint32_t sceScreamGetSoundPitchBendFactorComponents (uint32_t handle, SceScreamPitchBendFactorComponents *components);

// Looping
/**
@ingroup soundFunctions

@brief
Verifies whether an indexed Sound contains looping waveforms.

This function verifies whether a Sound &ndash; referenced by its Bank index &ndash; contains any looping waveforms and is therefore considered a <i>looper</i>.
It returns 1 or 0 to indicate looping status.

@param bank (Input)
Pointer to a Bank that contains the referenced Sound, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param index (Input)
Index of the Sound to obtain looping status for.

@return
Returns 0 if the Sound has no looping waveforms. Returns 1 if the Sound has one or more looping waveforms.

@note
This function only tests for looping <i>Waveform</i> Grains. It does not detect the loop-oriented
scripting Grains: <i>Loop Start</i>, <i>Loop Continue</i>, or <i>Loop End</i>.

@see
sceScreamIsSoundNameALooper(), sceScreamIsSoundInstanceALooper()
*/
int32_t sceScreamIsSoundIndexALooper(const SceScreamSFXBlock2 *bank, int16_t index);

/**
@ingroup soundFunctions

@brief
Verifies whether a named Sound contains looping waveforms.

This function verifies whether a Sound &ndash; referenced by name within its Bank &ndash; contains any looping waveforms and is therefore considered a <i>looper</i>.
It returns 1 or 0 to indicate looping status.

@param bank (Input)
Pointer to a Bank that contains the referenced Sound, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param name (Input)
Name of the Sound for which to obtain looping status.

@return
Returns 0 if the Sound has no looping waveforms. Returns 1 if the Sound has one or more looping waveforms.

@note
This function only tests for looping <i>Waveform</i> Grains. It does not detect the loop-oriented
scripting Grains: <i>Loop Start</i>, <i>Loop Continue</i>, or <i>Loop End</i>.

@see
sceScreamIsSoundIndexALooper(), sceScreamIsSoundInstanceALooper()
*/
int32_t sceScreamIsSoundNameALooper(const SceScreamSFXBlock2 *bank, const char *name);

/**
@ingroup soundFunctions

@brief
Verifies whether a Sound instance is looping.

This function verifies whether a Sound instance is looping. It returns 1 or 0 to indicate looping status.

@param handle (Input)
Handle of the Sound for which to obtain looping status.

@return
Returns 0 if the Sound is not looping. Returns 1 if the Sound is looping.

@note
Unlike sceScreamIsSoundIndexALooper() and sceScreamIsSoundNameALooper(), which operate on a Sound as stored in Bank contents, this function operates on
a running instance of a Sound.

@see
sceScreamIsSoundIndexALooper(), sceScreamIsSoundNameALooper()
*/
int32_t sceScreamIsSoundInstanceALooper(uint32_t handle);

// 3D
/**

@ingroup soundFunctions

@brief
Retrieves asset Grain 3D parameter data by reference to a Sound index.

This function retrieves 3D parameter data from scripted Sounds and CCSounds, as referenced by an index within a Bank.
Technically, 3D parameter data is not the property of a Sound, but actually belongs to asset Grains (<i>Waveform</i> and <i>Stream</i> Grains) contained in a Sound's script.
For CCSounds, the function retrieves 3D parameter data from asset Grains contained in the scripts of Sounds controlled by a CCSound.

The function retrieves 3D parameter data from a maximum of <c><i>outNum3dGrains</i></c> associated asset Grains.
If the output value of <c><i>outNum3dGrains</i></c> is less than the value you specified for <c><i>maxCount</i></c>, you can be sure that data was retrieved from all associated asset Grains.
However, if <c><i>outNum3dGrains</i></c> is equal to the value you specified for <c><i>maxCount</i></c>, the retrieved 3D data may or may not represent all associated asset Grains.

@param bank (Input)
Pointer to a Bank containing a Sound to query, as returned by the sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank() functions.

@param index (Input)
Index of a Sound within the specified <c><i>bank</i></c> to query for 3D parameter data.

@param maxCount (Input)
The maximum number of asset Grains to query for 3D parameter data.
Constrains the number of SceScreamSnd3DGrainData structures to store in the <c><i>out3DGrainData</i></c> array.

@param outNum3dGrains (Output)
A pointer to a <c>uint32_t</c> variable in which to hold the actual number of SceScreamSnd3DGrainData structures stored in the <c><i>out3DGrainData</i></c> array.
Can be less than <c><i>maxCount</i></c> if there are fewer asset Grains associated with a referenced Sound.

@param out3dGrainData (Output)
A pointer to an array of SceScreamSnd3DGrainData structures, large enough to store at least <c><i>maxCount</i></c> records.

@note
Using this function, you can also determine whether a Sound can be designated as a <i>3D Sound</i>.
That is, whether a Sound has an assigned distance model (or inherits a distance model from its assigned Group).
The function only queries asset Grains that possess 3D settings.
So if you set <c><i>maxCount</i></c> to 1, and the output value of <c><i>outNum3dGrains</i></c> is 1, it is safe to assume that at least one Grain contained 3D settings, and therefore that the Sound can be considered a 3D Sound.
Conversely, if the output value of <c><i>outNum3dGrains</i></c> is zero, you can assume the Sound is not a 3D Sound.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@see
sceScreamSoundNameGet3DDesignerParams(), sceScreamSoundInstanceGet3DDesignerParams(), SceScreamSnd3DGrainData, sceScreamSoundInstanceGet3DComponents()
*/
int32_t sceScreamSoundIndexGet3DDesignerParams(SceScreamSFXBlock2 *bank, int16_t index, uint32_t maxCount, uint32_t *outNum3dGrains, SceScreamSnd3DGrainData out3dGrainData[]);

/**

@ingroup soundFunctions

@brief
Retrieves asset Grain 3D parameter data by reference to a Sound name.

This function retrieves 3D parameter data from scripted Sounds and CCSounds, as referenced by a name within a Bank.
Technically, 3D parameter data is not the property of a Sound, but actually belongs to asset Grains (<i>Waveform</i> and <i>Stream</i> Grains) contained in a Sound's script.
For CCSounds, the function retrieves 3D parameter data from asset Grains contained in the scripts of Sounds controlled by a CCSound.

The function retrieves 3D parameter data from a maximum of <c><i>outNum3dGrains</i></c> associated asset Grains.
If the output value of <c><i>outNum3dGrains</i></c> is less than the value you specified for <c><i>maxCount</i></c>, you can be sure that data was retrieved from all associated asset Grains.
However, if <c><i>outNum3dGrains</i></c> is equal to the value you specified for <c><i>maxCount</i></c>, the retrieved 3D data may or may not represent all associated asset Grains.

@param bank (Input)
Pointer to a Bank containing a Sound to query, as returned by the sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank() functions.

@param name (Input)
Name of a Sound within the specified <c><i>bank</i></c> to query for 3D parameter data.

@param maxCount (Input)
The maximum number of asset Grains to query for 3D parameter data.
Constrains the number of SceScreamSnd3DGrainData structures to store in the <c><i>out3DGrainData</i></c> array.

@param outNum3dGrains (Output)
A pointer to a <c>uint32_t</c> variable in which to hold the actual number of SceScreamSnd3DGrainData structures stored in the <c><i>out3DGrainData</i></c> array.
Can be less than <c><i>maxCount</i></c> if there are fewer asset Grains associated with a referenced Sound.

@param out3dGrainData (Output)
A pointer to an array of SceScreamSnd3DGrainData structures, large enough to store at least <c><i>maxCount</i></c> records.

@note
Using this function, you can also determine whether a Sound can be designated as <i>3D Sound</i>.
That is, whether a Sound has an assigned distance model (or inherits a distance model from its assigned Group).
The function only queries asset Grains that possess 3D settings.
So if you set <c><i>maxCount</i></c> to 1, and the output value of <c><i>outNum3dGrains</i></c> is 1, it is safe to assume that at least one Grain contained 3D settings, and therefore that the Sound can be considered a 3D Sound.
Conversely, if the output value of <c><i>outNum3dGrains</i></c> is zero, you can assume the Sound is not a 3D Sound.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@see
sceScreamSoundIndexGet3DDesignerParams(), sceScreamSoundInstanceGet3DDesignerParams(), SceScreamSnd3DGrainData, sceScreamSoundInstanceGet3DComponents()
*/
int32_t sceScreamSoundNameGet3DDesignerParams(SceScreamSFXBlock2 *bank, const char *name, uint32_t maxCount, uint32_t *outNum3dGrains, SceScreamSnd3DGrainData out3dGrainData[]);

/**

@ingroup soundFunctions

@brief
Retrieves asset Grain 3D parameter data by reference to a Sound instance handle.

This function retrieves 3D parameter data from active scripted Sounds and CCSounds, as referenced by an instance handle.
Technically, 3D parameter data is not the property of a Sound, but actually belongs to asset Grains (<i>Waveform</i> and <i>Stream</i> Grains) contained in a Sound's script.
For CCSounds, the function retrieves 3D parameter data from asset Grains contained in the scripts of Sounds controlled by a CCSound.

The function retrieves 3D parameter data from a maximum of <c><i>outNum3dGrains</i></c> associated asset Grains.
If the output value of <c><i>outNum3dGrains</i></c> is less than the value you specified for <c><i>maxCount</i></c>, you can be sure that data was retrieved from all associated asset Grains.
However, if <c><i>outNum3dGrains</i></c> is equal to the value you specified for <c><i>maxCount</i></c>, the retrieved 3D data may or may not represent all associated asset Grains.

@param handle (Input)
Handle of an active Sound instance to query.

@param maxCount (Input)
The maximum number of asset Grains to query for 3D parameter data.
Constrains the number of SceScreamSnd3DGrainData structures to store in the <c><i>out3DGrainData</i></c> array.

@param outNum3dGrains (Output)
A pointer to a <c>uint32_t</c> variable in which to hold the actual number of SceScreamSnd3DGrainData structures stored in the <c><i>out3DGrainData</i></c> array.
Can be less than <c><i>maxCount</i></c> if there are fewer asset Grains associated with a referenced Sound.

@param out3dGrainData (Output)
A pointer to an array of SceScreamSnd3DGrainData structures, large enough to store at least <c><i>maxCount</i></c> records.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@note
Using this function, you can also determine whether a Sound can be designated as <i>3D Sound</i>.
That is, whether a Sound has an assigned distance model (or inherits a distance model from its assigned Group).
The function only queries asset Grains that possess 3D settings.
So if you set <c><i>maxCount</i></c> to 1, and the output value of <c><i>outNum3dGrains</i></c> is 1, it is safe to assume that at least one Grain contained 3D settings, and therefore that the Sound can be considered a 3D Sound.
Conversely, if the output value of <c><i>outNum3dGrains</i></c> is zero, you can assume the Sound is not a 3D Sound.

@note
Unlike sceScreamSoundIndexGet3DDesignerParams() and sceScreamSoundNameGet3DDesignerParams(), which
operate on a Sound as stored in Bank contents, this function operates on a running instance of a Sound.

@see
sceScreamSoundIndexGet3DDesignerParams(), sceScreamSoundNameGet3DDesignerParams(), SceScreamSnd3DGrainData, sceScreamSoundInstanceGet3DComponents()
*/
int32_t sceScreamSoundInstanceGet3DDesignerParams(uint32_t handle, uint32_t maxCount, uint32_t *outNum3dGrains, SceScreamSnd3DGrainData out3dGrainData[]);

/**
@ingroup soundFunctions

@brief
Retrieves dynamic 3D components for Grains associated with a Sound instance.

This function retrieves dynamic 3D attenuation components resulting from an active distance model on a Sound instance.
The function stores its results in an array of SceScreamSnd3DComponents structures, specified in the <c><i>out3dComponents</i></c> parameter, one structure per Grain queried.

Technically, 3D attenuation components are not the properties of a Sound, but actually belong to asset Grains (<i>Waveform</i> and <i>Stream</i> Grains) contained in a Sound's script.
For CCSounds, the function retrieves 3D components from asset Grains contained in the scripts of Sounds controlled by a CCSound.

The function retrieves 3D attenuation components from a maximum of <c><i>maxCount</i></c> associated asset Grains.
If the actual number of Grains from which 3D components were retrieved (that is, the output value of <c><i>outNum3dComponents</i></c>) is less than the value you specified for <c><i>maxCount</i></c>, you can be sure that data was retrieved from all associated asset Grains.
However, if <c><i>outNum3dGrains</i></c> is equal to the value you specified for <c><i>maxCount</i></c>, the retrieved 3D data may or may not represent all associated asset Grains.

@param handle (Input)
Handle of an active Sound instance to query.

@param maxCount (Input)
The maximum number of asset Grains to query for 3D component data.
Constrains the number of SceScreamSnd3DComponents structures to store in the <c><i>out3dComponents</i></c> array.

@param outNum3dComponents (Output)
A pointer to a <c>uint32_t</c> variable in which to hold the actual number of SceScreamSnd3DComponents structures stored in the <c><i>out3dComponents</i></c> array.
Can be less than <c><i>maxCount</i></c> if there are fewer asset Grains associated with a referenced Sound instance.

@param out3dComponents (Output)
A pointer to an array of SceScreamSnd3DComponents structures, large enough to store at least <c><i>maxCount</i></c> records.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@see
SceScreamSnd3DComponents, sceScreamSoundIndexGet3DDesignerParams(), sceScreamSoundNameGet3DDesignerParams(), sceScreamSoundInstanceGet3DDesignerParams(), SceScreamSnd3DGrainData
*/
int32_t sceScreamSoundInstanceGet3DComponents(uint32_t handle, uint32_t maxCount, uint32_t *outNum3dComponents, SceScreamSnd3DComponents out3dComponents[]);

// Streaming
/**
@ingroup soundFunctions

@brief
Retrieves the number of active stream handles associated with a Sound instance.

This function returns the number of active stream handles associated with a specified Sound instance.

@param handle (Input)
Handle of the Sound from which to obtain a stream handle count.

@return
Returns the number of active stream handles.

@see
sceScreamGetActiveStreamHandle()
*/
uint32_t sceScreamGetNumActiveStreamHandles(uint32_t handle);

/**
@ingroup soundFunctions

@brief
Retrieves an active stream handle associated with a Sound instance.

This function returns an active stream handle associated with a specified Sound instance.

For details on working with Streams, see <i>Sndstream Library Overview</i> and <i>Sndstream Library Reference</i>.

@param handle (Input)
Handle of the Sound from which to obtain a stream handle.

@param index (Input)
Zero-based index of the stream handle to retrieve.

@return
Returns the indexed stream handle if it exists, otherwise <c>NULL</c>.

@see
sceScreamGetNumActiveStreamHandles()
*/
uint32_t sceScreamGetActiveStreamHandle(uint32_t handle, int16_t index);

/**
@ingroup soundFunctions

@brief
Verifies whether an indexed Sound contains streaming content.

This function verifies whether a Sound &ndash; referenced by index within its Bank &ndash; contains any streaming content.
Returns 1 or 0 to indicate streaming content status.

@param bank (Input)
Pointer to a Bank that contains the referenced Sound, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param index (Input)
Index of the Sound from which to obtain streaming status.

@return
Returns 1 if the Sound has streaming content. Returns 0 if the Sound has no streaming content.

@see
sceScreamIsSoundNameAStreamer(), sceScreamIsSoundInstanceAStreamer()
*/
int32_t sceScreamIsSoundIndexAStreamer(const SceScreamSFXBlock2 *bank, int16_t index);

/**
@ingroup soundFunctions

@brief
Verifies whether a named Sound contains streaming content.

This function verifies whether a Sound &ndash; referenced by name within its Bank &ndash; contains any streaming content.
It returns 1 or 0 to indicate streaming status.

@param bank (Input)
Pointer to a Bank that contains the referenced Sound, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param name (Input)
Name of the Sound from which to obtain streaming status.

@return
Returns 1 if the Sound has streaming content. Returns 0 if the Sound has no streaming content.

@see
sceScreamIsSoundIndexAStreamer(), sceScreamIsSoundInstanceAStreamer()
*/
int32_t sceScreamIsSoundNameAStreamer(const SceScreamSFXBlock2 *bank, const char *name);

/**
@ingroup soundFunctions

@brief
Verifies whether a Sound instance contains streaming content.

This function verifies whether a Sound instance contains streaming content. Returns 1 or 0 to indicate streaming status.

@param handle (Input)
Handle of the Sound from which to obtain streaming status.

@return
Returns 1 if the Sound contains streaming content. Returns 0 if the Sound does not contain streaming content.

@note
Unlike sceScreamIsSoundIndexAStreamer() and sceScreamIsSoundNameAStreamer(), which operate on a Sound as stored in Bank contents, this function operates on
a running instance of a Sound.

@see
sceScreamIsSoundIndexAStreamer(), sceScreamIsSoundNameAStreamer()
*/
int32_t sceScreamIsSoundInstanceAStreamer(uint32_t handle);

// On Stop
/**

@ingroup soundFunctions

@brief
Verifies whether an indexed Sound contains an <i>On Stop Marker</i> Grain.

This function verifies whether a Sound &ndash; referenced by its Bank index &ndash; contains an <i>On Stop Marker</i> Grain in its script.
It returns 1 or 0 to indicate the presence of the marker.

@param bank (Input)
Pointer to a Bank that contains the referenced Sound, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param index (Input)
Index of the Sound to examine for an <i>On Stop Marker</i> Grain.

@return
Returns 1 if the Sound has an <i>On Stop Marker</i> Grain. Returns 0 otherwise.

@see
sceScreamSoundNameHasOnStopMarker(), sceScreamSoundInstanceHasOnStopMarker()

*/
int32_t sceScreamSoundIndexHasOnStopMarker(const SceScreamSFXBlock2 *bank, int16_t index);

/**
@ingroup soundFunctions

@brief
Verifies whether a named Sound contains an <i>On Stop Marker</i> Grain.

This function verifies whether a Sound &ndash; referenced by name within its Bank &ndash; contains an <i>On Stop Marker</i> Grain.
It returns 1 or 0 to indicate the presence of the marker.

@param bank (Input)
Pointer to a Bank that contains the referenced Sound, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param name (Input)
Name of the Sound to examine for an <i>On Stop Marker</i> Grain.

@return
Returns 1 if the Sound contains an <i>On Stop Marker</i> Grain. Returns 0 otherwise.

@see
sceScreamSoundIndexHasOnStopMarker(), sceScreamSoundInstanceHasOnStopMarker()
*/
int32_t sceScreamSoundNameHasOnStopMarker(const SceScreamSFXBlock2 *bank, const char *name);

/**
@ingroup soundFunctions

@brief
Verifies whether a Sound instance contains an <i>On Stop Marker</i> Grain.

This function verifies whether a Sound instance contains an <i>On Stop Marker</i> Grain. It returns 1 or 0 to indicate the presence of the marker.

@param handle (Input)
Handle of the Sound to examine for an <i>On Stop Marker</i> Grain.

@return
Returns 1 if the Sound contains an <i>On Stop Marker</i> Grain. Returns 0 otherwise.

@note
Unlike sceScreamSoundIndexHasOnStopMarker() and sceScreamSoundNameHasOnStopMarker(), which operate on a Sound as stored in Bank contents, this function operates on
a running instance of a Sound.

@see
sceScreamSoundIndexHasOnStopMarker(), sceScreamSoundNameHasOnStopMarker()
*/
int32_t sceScreamSoundInstanceHasOnStopMarker(uint32_t handle);

// Volume Group
/**
@ingroup soundFunctions

@brief
Retrieves the volume group to which a Sound is assigned by reference to its index.

This function retrieves the volume group to which a Sound is assigned by reference to the Sound's index within a loaded Bank.

@param bank (Input)
Pointer to a loaded Bank, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param index (Input)
Index of the Sound within the specified Bank.

@return
If successful, returns the volume group to which the Sound is assigned (see \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink).
If not successful, returns -1.

@see
sceScreamGetSoundNameVolumeGroup(), sceScreamGetSoundInstanceVolumeGroup()
*/
int32_t sceScreamGetSoundIndexVolumeGroup(const SceScreamSFXBlock2 *bank, int16_t index);

/**
@ingroup soundFunctions

@brief
Retrieves the volume group to which a Sound is assigned by reference to its name.

This function retrieves the volume group to which a Sound is assigned by reference to the Sound's name within a loaded Bank.

@param bank (Input)
Pointer to a loaded Bank, as returned by sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param name (Input)
Name of the Sound within the specified Bank.

@return
If successful, returns the volume group to which the Sound is assigned (see \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink).
If not successful, returns -1.

@see
sceScreamGetSoundIndexVolumeGroup(), sceScreamGetSoundInstanceVolumeGroup()
*/
int32_t sceScreamGetSoundNameVolumeGroup(const SceScreamSFXBlock2 *bank, const char *name);

/**
@ingroup soundFunctions

@brief
Retrieves the volume group to which a Sound is assigned by reference to its instance handle.

This function retrieves the volume group to which a Sound is assigned by reference to the Sound's instance handle.

@param handle (Input)
Handle of the Sound instance for which to retrieve the assigned volume Group.

@return
If successful, returns the volume group to which the Sound is assigned (see \link #SCE_SCREAM_GROUP_VOLUME_SFX Volume Groups\endlink).
If not successful, returns -1.

@note
Unlike sceScreamGetSoundIndexVolumeGroup() and sceScreamGetSoundNameVolumeGroup(), which operate on a Sound as stored in Bank contents, this function operates on
a running instance of a Sound.

@see
sceScreamGetSoundIndexVolumeGroup(), sceScreamGetSoundNameVolumeGroup()
*/
int32_t sceScreamGetSoundInstanceVolumeGroup(uint32_t handle);

// User Data
/**
@ingroup soundFunctions

@brief
Retrieves a Sound's associated user data values by reference to its index.

User data values are (up to) twelve values associated with a Sound that can optionally be entered by audio designers using the Scream Tool Sound Properties panel.
This function retrieves the user data values associated with a Sound, by reference to its index within a Bank.
For more information, see &quot;User Data?&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.

@param bank (Input)
Pointer to a loaded Bank, as returned from sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param index (Input)
Index of the Sound within the Bank for which to obtain associated user data.

@return
If successful, returns a pointer to an array of twelve <c>uint32_t</c> values representing the Sound's associated user data.
If not successful, returns <c>NULL</c>.

@see
sceScreamGetSoundNameUserDataPtr(), sceScreamGetSoundInstanceUserDataPtr()
*/
const uint32_t* sceScreamGetSoundIndexUserDataPtr(const SceScreamSFXBlock2 *bank, int16_t index);

/**
@ingroup soundFunctions

@brief
Retrieves a Sound's associated user data values by reference to its name.

User data values are (up to) twelve values associated with a Sound that can optionally be entered by audio designers using the Scream Tool Sound Properties panel.
This function retrieves the user data values associated with a Sound, by reference to its name within a Bank.
For more information, see &quot;User Data?&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.

@note
If <c><i>bank</i></c> is <c>NULL</c>, this function searches through all registered Banks, and returns user data for the first Sound it finds matching the specified <c><i>name</i></c>.
If <c><i>name</i></c> is not found in any Bank, the function returns <c>NULL</c>.

@param bank (Input)
Pointer to a loaded Bank, as returned from sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank(). Can be <c>NULL</c>. See &quot;Notes&quot; below.

@param name (Input)
Name of the Sound within the Bank for which to obtain associated user data.

@return
If successful, returns a pointer to an array of twelve <c>uint32_t</c> values representing the Sound's associated user data.
If not successful, returns <c>NULL</c>.

@see
sceScreamGetSoundIndexUserDataPtr(), sceScreamGetSoundInstanceUserDataPtr()
*/
const uint32_t* sceScreamGetSoundNameUserDataPtr(const SceScreamSFXBlock2 *bank, const char *name);

/**
@ingroup soundFunctions

@brief
Retrieves a Sound's associated user data values by reference to its instance handle.

User data values are (up to) twelve values associated with a Sound that can optionally be entered by audio designers using the Scream Tool Sound Properties panel.
This function retrieves the user data values associated with a Sound, by reference to its handle.
For more information, see &quot;User Data?&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.

@param handle (Input)
Handle of the Sound for which to obtain associated user data.

@note
Unlike sceScreamGetSoundIndexUserDataPtr() and sceScreamGetSoundNameUserDataPtr(), which operate on a Sound as stored in Bank contents, this function operates on
a running instance of a Sound.

@return
If successful, returns a pointer to an array of twelve <c>uint32_t</c> values representing the Sound's associated user data.
If not successful, returns <c>NULL</c>.

@see
sceScreamGetSoundIndexUserDataPtr(), sceScreamGetSoundNameUserDataPtr()
*/
const uint32_t* sceScreamGetSoundInstanceUserDataPtr(uint32_t handle);

// Designer Parameters
/**
@ingroup soundFunctions

@brief
Retrieves a Sound's associated designer parameters by reference to its index.

This function retrieves the designer parameter values associated with a Sound, by reference to its index within a Bank.

@param bank (Input)
Pointer to a loaded Bank, as returned from sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank().

@param index (Input)
Index of the Sound within the specified <c><i>bank</i></c> for which to obtain associated designer parameters.

@param designerParams (Output)
A pointer to a SceScreamDesignerParams structure to be filled out by this function.

@return
If successful, returns <c>TRUE</c>.
If not successful, returns <c>FALSE</c>.

@see
sceScreamGetSoundNameDesignerParams(), sceScreamGetSoundInstanceDesignerParams(), SceScreamDesignerParams
*/
bool sceScreamGetSoundIndexDesignerParams(const SceScreamSFXBlock2 *bank, int16_t index, SceScreamDesignerParams* designerParams);

/**
@ingroup soundFunctions

@brief
Retrieves a Sound's associated designer parameters by reference to its name.

This function retrieves the designer parameter values associated with a Sound, by reference to its name within a Bank.

@note
If <c><i>bank</i></c> is <c>NULL</c>, this function searches through all registered Banks, and returns designer parameters for the first Sound it finds matching the specified <c><i>name</i></c>.
If <c><i>name</i></c> is not found in any Bank, the function returns <c>FALSE</c>.

@param bank (Input)
Pointer to a loaded Bank, as returned from sceScreamBankLoadEx(), sceScreamBankLoadFromMemEx(), sceScreamFindLoadedBankByName(), or sceScreamGetNextLoadedBank(). Can be <c>NULL</c>. See &quot;Notes&quot; below.

@param name (Input)
Name of the Sound within the specified <c><i>bank</i></c> for which to obtain associated designer parameters.

@param designerParams (Output)
A pointer to a SceScreamDesignerParams structure to be filled out by this function.

@return
If successful, returns <c>TRUE</c>.
If not successful, returns <c>FALSE</c>.

@see
sceScreamGetSoundIndexDesignerParams(), sceScreamGetSoundInstanceDesignerParams(), SceScreamDesignerParams
*/
bool sceScreamGetSoundNameDesignerParams(const SceScreamSFXBlock2 *bank, const char *name, SceScreamDesignerParams* designerParams);

/**
@ingroup soundFunctions

@brief
Retrieves a Sound's associated designer parameters by reference to its instance handle.

This function retrieves associated designer parameter values from a Sound instance, by reference to its handle.

@param handle (Input)
Handle of the Sound for which to obtain associated designer parameters.

@param designerParams (Output)
A pointer to a SceScreamDesignerParams structure to be filled out by this function.

@return
Returns the specified handle if the query is successful.
Returns 0 if the specified Sound is no longer active.

@note
Unlike sceScreamGetSoundIndexDesignerParams() and sceScreamGetSoundNameDesignerParams(), which operate on a Sound as stored in Bank contents, this function operates on
a running instance of a Sound.

@see
sceScreamGetSoundIndexDesignerParams(), sceScreamGetSoundNameDesignerParams(), SceScreamDesignerParams
*/
uint32_t  sceScreamGetSoundInstanceDesignerParams(uint32_t handle, SceScreamDesignerParams* designerParams);

// Registers
/**
@ingroup soundFunctions

@brief
Retrieves the value of a local register.

This function retrieves the current value of a local (Sound-specific) register.

@param handle (Input)
Handle of the Sound from which to get the register value.

@param which (Input)
One-based index of the register to access. Range: 1 to #SCE_SCREAM_SND_MAX_REGISTERS.

@param val (Output)
Pointer to a variable in which to store the register value. Range: -128 to 127.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@see
sceScreamSetSoundReg(), sceScreamGetAllSoundReg(), sceScreamSetAllSoundReg()
*/
uint32_t sceScreamGetSoundReg(uint32_t handle, int32_t which, int8_t *val);

/**
@ingroup soundFunctions

@brief
Sets the value of a local register.

This function sets the value of a local (Sound-specific) register.

@param handle (Input)
Handle of the Sound on which to set a register value.

@param which (Input)
One-based index of the register to set. Range: 1 to #SCE_SCREAM_SND_MAX_REGISTERS.

@param val (Input)
Value to set the register to. Range: -128 to 127.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@see
sceScreamGetSoundReg(), sceScreamGetAllSoundReg(), sceScreamSetAllSoundReg()
*/
uint32_t sceScreamSetSoundReg(uint32_t handle, int32_t which, int8_t val);

/**
@ingroup soundFunctions

@brief
Gets the values of all local registers specific to a Sound.

This function gets the values of all local registers specific to a Sound.

@param handle (Input)
Handle of the Sound for which to get all registers.

@param vals (Output)
An array (of length #SCE_SCREAM_SND_MAX_REGISTERS) in which to store the register values. Range for each value: -128 to 127.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@note
To perform atomic read/modify/write operations on a Sound's local registers (that is, without interference from running scripts),
use sceScreamLockAllSoundReg() and sceScreamUnlockAllSoundReg().

@see
sceScreamSetAllSoundReg(), sceScreamSetSoundReg(), sceScreamGetSoundReg(), sceScreamLockAllSoundReg(), sceScreamUnlockAllSoundReg()
*/
uint32_t sceScreamGetAllSoundReg(uint32_t handle, int8_t *vals);

/**
@ingroup soundFunctions

@brief
Sets the values of all local registers specific to a Sound.

This function sets the values of all local registers specific to a Sound.

@param handle (Input)
Handle of the Sound for which to set all registers.

@param vals (Input)
An array of register values. Range of each value: -128 to 127. Length: #SCE_SCREAM_SND_MAX_REGISTERS.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@note
To perform atomic read/modify/write operations on a Sound's local registers (that is, without interference from running scripts),
use sceScreamLockAllSoundReg() and sceScreamUnlockAllSoundReg().

@see
sceScreamGetAllSoundReg(), sceScreamGetSoundReg(), sceScreamSetSoundReg(), sceScreamLockAllSoundReg(), sceScreamUnlockAllSoundReg()
*/
uint32_t sceScreamSetAllSoundReg(uint32_t handle, const int8_t *vals);

/**
@ingroup soundFunctions

@brief
Locks a Sound's local registers and retrieves their current values.

This function locks a Sound's local registers, and retrieves their current values. You can then process the register values
with the knowledge that a script cannot modify them during processing time.

<b>Note:</b> In order to lock a Sound's local registers, the function effectively locks the entire underlying rendering synthesizer.
See warning in &quot;Notes&quot; below.

@param handle (Input)
Handle of the Sound from which to lock and retrieve all local register values.

@param vals (Output)
An array (of size #SCE_SCREAM_SND_MAX_REGISTERS) in which to store the local register values. Range of each value: -128 to 127.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@note
<b>WARNING</b>: Because this function locks the underlying rendering synthesizer, it is critical that calls to it
are followed by a matching call to sceScreamUnlockAllSoundReg(). Processing performed between these
two calls should be kept to an absolute minimum!

@note
If you do not need an atomic read/modify/write capability on a Sound's local registers (that is, without interference from running scripts),
use sceScreamGetAllSoundReg() and sceScreamSetAllSoundReg() instead.

@see
sceScreamUnlockAllSoundReg(), sceScreamGetAllSoundReg(), sceScreamSetAllSoundReg(), sceScreamGetSoundReg()
*/
uint32_t sceScreamLockAllSoundReg(uint32_t handle, int8_t *vals);

/**
@ingroup soundFunctions

@brief
Sets a Sound's local register values and unlocks them.

This function sets new values for a Sound's local registers after they have been locked with a call to sceScreamLockAllSoundReg().
After setting the local register values, the function unlocks them, re-exposing them to script modification.

@param handle (Input)
Handle of the Sound for which to set all local register values.

@param vals (Input)
An array (of size #SCE_SCREAM_SND_MAX_REGISTERS) containing the local register values to set. Range of each value: -128 to 127.

@return
Returns the specified handle if the Sound is still active. Returns 0 if the specified Sound is no longer active.

@note
<b>WARNING</b>: This function must be used in conjunction with a preceding call to sceScreamLockAllSoundReg().
Because sceScreamLockAllSoundReg() effectively locks the entire underlying rendering synthesizer, it is critical that
it is followed by a matching call to this function to unlock the rendering synthesizer.
Processing performed between these two calls should be kept to an absolute minimum!

@note
If you do not need an atomic read/modify/write capability on a Sound's local registers (that is, without interference from running scripts),
use sceScreamGetAllSoundReg() and sceScreamSetAllSoundReg() instead.

@see
sceScreamLockAllSoundReg(), sceScreamGetAllSoundReg(), sceScreamSetAllSoundReg(), sceScreamSetSoundReg()
*/
uint32_t sceScreamUnlockAllSoundReg(uint32_t handle, const int8_t *vals);

// Local Variables
/**
@ingroup soundFunctions

@brief
Sets the value of a local variable.

This function sets the value of a local variable associated with a Sound.
You reference a local variable by its hash.
You can obtain a hash for a variable name using the sceScreamGetHashFromName() function.

The maximum number of local variables per Sound instance is defined by the constant #SCE_SCREAM_SND_MAX_LOCAL_VARIABLES.

You can set all a Sound’s local variables at the same time by placing their values in a SceScreamSndLocalVarData structure and point to it
as the <c><i>localVariableData</i></c> member of a SceScreamSoundParams structure.
Call sceScreamSetSoundParamsEx() using this SceScreamSoundParams to write the variables' values.

@param handle (Input)
Handle of a Sound upon which to set a local variable.

@param nameHash (Input)
32-bit hash of a named local variable to set.

@param val (Input)
A floating-point value to set the specified local variable to.

@return
Returns <c>TRUE</c> if the specified Sound is active and the specified local variable exists.  Returns <c>FALSE</c> otherwise.

@see
sceScreamGetHashFromName(), sceScreamGetLocalVariableByHash(), SceScreamSndLocalVarData, SceScreamSoundParams, sceScreamSetSoundParamsEx()
*/
bool sceScreamSetLocalVariableByHash(uint32_t handle, uint32_t nameHash, float val);

/**
@ingroup soundFunctions

@brief
Retrieves the value of a local variable.

This function retrieves the value of a local variable associated with a Sound.

The maximum number of local variables per Sound instance is defined by the constant #SCE_SCREAM_SND_MAX_LOCAL_VARIABLES.

You can read all a Sound’s local variables at the same time by calling sceScreamGetSoundParamsEx() with a SceScreamSoundParams structure.
The local variables' values are in the SceScreamSndLocalVarData structure, the <c><i>localVariableData</i></c> member of the SceScreamSoundParams structure.

@param handle (Input)
Handle of a Sound from which to retrieve a local variable value.

@param nameHash (Input)
32-bit hash of a named local variable from which to retrieve the value.

@param val (Output)
A pointer to a floating variable in which to store the retrieved value.

@return
Returns <c>TRUE</c> if the specified Sound is active and the specified local variable exists.  Returns <c>FALSE</c> otherwise.

@see
sceScreamGetHashFromName(), sceScreamSetLocalVariableByHash(), SceScreamSndLocalVarData, SceScreamSoundParams, sceScreamGetSoundParamsEx()
*/
bool sceScreamGetLocalVariableByHash(uint32_t handle, uint32_t nameHash, float* val);

// Automated parameter change
/**
@ingroup soundFunctions

@brief
Changes the panning azimuth of a Sound over a specified time.

This function performs an automated change to the panning azimuth of a Sound.
It incrementally changes the azimuth setting from its current value to a target value over a specified time.

@param handle (Input)
Handle of the Sound to which to apply a panning azimuth change.

@param targetPanAzimuth (Input)
The target panning azimuth in degrees. Range: 0 to 359.

@param timeToTarget (Input)
The time taken to reach the target panning azimuth in seconds.

@param behaviorFlags (Input)
Zero or more of the Automated Parameter Change constants (bitwise <c>OR</c> multiple
selections). See \link #SCE_SCREAM_SND_AUTO_STOP_AT_DESTINATION Automated Parameter Change Flags\endlink.

@return
Returns the specified Sound handle if the automated pan change is successful.
Returns 0 if the specified Sound is no longer active.

@note
For a counter-clockwise panning motion, bitwise OR the #SCE_SCREAM_SND_AUTO_COUNTER_CLOCKWISE constant with the <c><i>behaviorFlags</i></c> member.

@note
By default, sceScreamAutoPan() targets the <c><i>apiPanAzimuth</i></c> component of the SceScreamPanAzimuthComponents structure filled by
sceScreamGetSoundPanAzimuthComponents(). However, if you set the #SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR <c><i>behavior</i></c> flag when calling sceScreamAutoPan(),
the function instead targets the <c><i>autoPanAzimuth</i></c> component. For more information, see &quot;Use Separate Factor&quot; in the &quot;Working with Sounds&quot; chapter of <i>Scream Library Overview</i>.

@note
The #SCE_SCREAM_SND_AUTO_COUNTER_CLOCKWISE and the #SCE_SCREAM_SND_AUTO_TAKE_SHORTEST_PATH constants are mutually exclusive.

@see
sceScreamAutoPitchTranspose(), sceScreamAutoPitchBend(), sceScreamAutoGain(), SceScreamPanAzimuthComponents, sceScreamGetSoundPanAzimuthComponents()
*/
uint32_t sceScreamAutoPan(uint32_t handle, uint32_t targetPanAzimuth, float timeToTarget, uint32_t behaviorFlags);

/**
@ingroup soundFunctions

@brief
Changes the pitch transposition of a Sound over a specified time.

This function performs an automated change to the pitch transposition of a Sound.
It incrementally changes the pitch transposition setting from its current value to a target value over a specified time.

@param handle (Input)
Handle of the Sound to which to apply a pitch transposition change.

@param targetPitchTranspose (Input)
The target pitch transposition in fines. Range: &ndash;#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE to +#SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE. See &quot;Notes&quot; below.

@param timeToTarget (Input)
The time taken to reach the target pitch transposition in seconds.

@param behaviorFlags (Input)
Zero or more of the Automated Parameter Change constants (bitwise <c>OR</c> multiple
selections). See \link #SCE_SCREAM_SND_AUTO_STOP_AT_DESTINATION Automated Parameter Change Flags\endlink.

@return
Returns the specified Sound handle if the automated pitch transpose change is successful.
Returns 0 if the specified Sound is no longer active.

@note
You specify pitch transposition units in fines. A fine is a 128<sup>th</sup> microtonal subdivision of a semitone.
There are 128 &times; 12 = 1536 fines per octave, expressed in the constant #SCE_SCREAM_SND_FINES_PER_OCTAVE. The maximum
pitch transposition amount, up or down, is 5 octaves, expressed in the constant #SCE_SCREAM_SND_MAX_PITCH_TRANSPOSE. Some pitch transposition examples:
- To transpose down one octave, set <c><i>targetPitchTranspose</i></c> to -1536.
- To transpose up one octave, set <c><i>targetPitchTranspose</i></c> to 1536.
- To transpose up 2 semitones, set <c><i>targetPitchTranspose</i></c> to 256.

@note
By default, sceScreamAutoPitchTranspose() targets the <c><i>apiPitchTranspose</i></c> component of the SceScreamPitchTransposeComponents structure filled by
sceScreamGetSoundPitchTransposeComponents(). However, if you set the #SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR <c><i>behavior</i></c> flag when calling sceScreamAutoPitchTranspose(),
the function instead targets the <c><i>autoPitchTranspose</i></c> component. For more information, see &quot;Use Separate Factor&quot; in the &quot;Working with Sounds&quot; chapter of <i>Scream Library Overview</i>.

@see
sceScreamAutoPan(), sceScreamAutoPitchBend(), sceScreamAutoGain(), SceScreamPitchTransposeComponents, sceScreamGetSoundPitchTransposeComponents(), sceScreamGetDopplerPitchTranspose()
*/
uint32_t sceScreamAutoPitchTranspose(uint32_t handle, int32_t targetPitchTranspose, float timeToTarget, uint32_t behaviorFlags);

/**
@ingroup soundFunctions

@brief
Changes the pitchbend factor of a Sound over a specified time.

This function performs an automated change to the pitchbend factor of a Sound.
It incrementally changes the pitchbend factor setting from its current value to a target value over a specified time.

@param handle (Input)
Handle of the Sound to which to apply a pitchbend factor change.

@param targetPitchBend (Input)
The target pitchbend factor. Range: #SCE_SCREAM_SND_MIN_PITCH_BEND_FACTOR to #SCE_SCREAM_SND_MAX_PITCH_BEND_FACTOR.

@param timeToTarget (Input)
The time taken to reach the target pitchbend factor in seconds.

@param behaviorFlags (Input)
Zero or more of the Automated Parameter Change constants (bitwise <c>OR</c> multiple
selections). See \link #SCE_SCREAM_SND_AUTO_STOP_AT_DESTINATION Automated Parameter Change Flags\endlink.

@return
Returns the specified Sound handle if the automated pitchbend change is successful.
Returns 0 if the specified Sound is no longer active.

@note
The limits, within which a Sound will bend up or down from its original pitch, are set in Bank contents.
If the specified <c><i>targetPitchBend</i></c> value is positive, it is multiplied by the pitchbend upper limit.
If the specified <c><i>targetPitchBend</i></c> value is negative, it is multiplied by the pitchbend lower limit.
For example, suppose a Sound's pitchbend settings in Bank contents are 2 semitones on the upper limit, and 4 semitones on the lower limit.
If <c><i>targetPitchBend</i></c> is 0.5, the pitchbend factor change stops at 1 semitone above the original pitch.
If <c><i>targetPitchBend</i></c> is -0.5, the pitchbend factor change stops at 2 semitones below the original pitch.

@note
By default, sceScreamAutoPitchBend() targets the <c><i>apiPitchBendFactor</i></c> component of the SceScreamPitchBendFactorComponents structure filled by sceScreamGetSoundPitchBendFactorComponents().
However, if you set the #SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR <c><i>behavior</i></c> flag when calling sceScreamAutoPitchBend(),
the function instead targets the <c><i>autoPitchBendFactor</i></c> component. For more information, see &quot;Use Separate Factor&quot; in the &quot;Working with Sounds&quot; chapter of <i>Scream Library Overview</i>.

@see
sceScreamAutoPan(), sceScreamAutoPitchTranspose(), sceScreamAutoGain(), SceScreamPitchBendFactorComponents, sceScreamGetSoundPitchBendFactorComponents()
*/
uint32_t sceScreamAutoPitchBend(uint32_t handle, float targetPitchBend, float timeToTarget, uint32_t behaviorFlags);

/**
@ingroup soundFunctions

@brief
Changes the gain of a Sound over a specified time.

This function performs an automated change to the gain (volume) of a Sound.
It incrementally changes the gain setting from its current value to a target value over a specified time.

@param handle (Input)
Handle of the Sound to which to apply a volume change.

@param targetGain (Input)
Target gain. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.

@param timeToTarget (Input)
Time taken to reach the target volume in seconds.

@param behaviorFlags (Input)
Zero or more of the Automated Parameter Change constants (bitwise <c>OR</c> multiple
selections). See \link #SCE_SCREAM_SND_AUTO_STOP_AT_DESTINATION Automated Parameter Change Flags\endlink.

@return
Returns the specified Sound handle if the automated gain change is successful.
Returns 0 if the specified Sound is no longer active.

@note
By default, sceScreamAutoGain() targets the <c><i>apiGain</i></c> component of the SceScreamGainComponents structure filled by sceScreamGetSoundGainComponents().
However, if you set the #SCE_SCREAM_SND_AUTO_USE_SEPARATE_FACTOR <c><i>behavior</i></c> flag when calling sceScreamAutoGain(),
the function instead targets the <c><i>autoGain</i></c> component. For more information, see &quot;Use Separate Factor&quot; in the &quot;Working with Sounds&quot; chapter of <i>Scream Library Overview</i>.
@see
sceScreamAutoPan(), sceScreamAutoPitchTranspose(), sceScreamAutoPitchBend(), SceScreamGainComponents, sceScreamGetSoundGainComponents()
*/
uint32_t sceScreamAutoGain(uint32_t handle, float targetGain, float timeToTarget, uint32_t behaviorFlags);

// LFO
/**

@ingroup soundFunctions

@brief
Initializes an LFO or updates parameters on a running LFO.

This function either initializes a new LFO on a Sound instance or, if the specified LFO already exists, updates its parameters.

For more information on setting up an LFO, see &quot;Initializing and Controlling Sound LFOs&quot; in the &quot;Working with Sounds&quot; chapter of the <i>Scream Library Overview</i>.

@param handle (Input)
Handle of a Sound upon which to apply LFO settings.

@param params (Input)
A SceScreamLFOParameters structure, appropriately initialized with LFO parameter values.

@return
Returns the specified Sound handle if the Sound is still active and LFO parameters were successfully applied.
Returns 0 if the specified Sound is no longer active or if there was an error.

@note
When modifying the parameters of a running LFO (whether set up from Bank contents or from the Scream API), only changes to rate and depth can be performed seamlessly.
Changes to all other parameters (for example, <c><i>shape</i></c>, <c><i>targetParam</i></c>, <c><i>startOffset</i></c>, and so on) cause the LFO to restart from the beginning of its shape.

@note
When initializing an LFO on a Sound, you must specify the full set of LFO parameters, setting the SceScreamLFOParameters <c><i>paramMask</i></c> member to: (#SCE_SCREAM_SND_LFO_MASK_TARGET_PARAM | #SCE_SCREAM_SND_LFO_MASK_SHAPE | #SCE_SCREAM_SND_LFO_MASK_RATE | #SCE_SCREAM_SND_LFO_MASK_DEPTH).

@see
SceScreamLFOParameters
*/
uint32_t sceScreamSetSoundInstanceLFO(uint32_t handle, const SceScreamLFOParameters* params);

// Information and debugging
/**
@ingroup soundFunctions

@brief
Retrieves the number of voices being used by a Sound.

This function retrieves the number of voices currently being used by the specified Sound instance.
It stores the value in the variable referenced in the <c><i>outVoiceCount</i></c> parameter.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@param outVoiceCount (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the voice count.

@return
Returns the specified handle if the Sound is still active.
Returns 0 if the specified Sound is no longer active.

@see
sceScreamGetMaxPolyphony(), sceScreamSetGroupVoiceRange()
*/
uint32_t sceScreamGetSoundVoiceCount(uint32_t handle, uint32_t *outVoiceCount);

/**
@ingroup soundFunctions

@brief
Outputs information about an active Sound instance to the TTY.

This function outputs information about an active Sound instance to the TTY.

@param handle (Input)
Sound handle, as returned by sceScreamPlaySoundByIndexEx() or sceScreamPlaySoundByNameEx().

@param flags (Input)
Any combination of \link #SCE_SCREAM_SND_OUTPUT_TTY_FLAGS TTY Output Flags\endlink.

@return
Returns the specified handle if the Sound is still active.
Returns 0 if the specified Sound is no longer active.

@see
sceScreamOutputAllPlayingSoundInfoToTTY(), SceScreamSndDebugHandler(), sceScreamSetDebugHandler(), sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx()
*/
uint32_t  sceScreamOutputHandlerInfoToTTY(uint32_t handle, uint32_t flags);

/**
@ingroup soundFunctions

@brief
Outputs information about all active Sound instances to the TTY.

This function outputs information about all active Sound instances to the TTY.

@param flags (Input)
Any combination of \link #SCE_SCREAM_SND_OUTPUT_TTY_FLAGS TTY Output Flags\endlink.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful.

@see
sceScreamOutputHandlerInfoToTTY(), SceScreamSndDebugHandler(), sceScreamSetDebugHandler(), sceScreamPlaySoundByIndexEx(), sceScreamPlaySoundByNameEx()
*/
int32_t sceScreamOutputAllPlayingSoundInfoToTTY(uint32_t flags);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Reverb API
/**
@defgroup generalReverbFunctions Reverb Functions
@brief
Reverb functions set stock and custom presets, set properties, and pause/continue I3DL2 reverb instances.
@{*/
/**
@brief
Returns the handle of a reverb instance currently assigned to a specified buss.

This function returns the handle of a reverb instance currently assigned to a specified auxiliary send buss.

@return
Returns the handle of a reverb instance assigned to the specified buss. If the specified buss is unoccupied, the function returns zero.

@param buss (Input)
Zero-based index of an auxiliary send buss from which to retrieve the reverb instance handle. Range: 0 to (#SCE_SCREAM_NUM_AUX_BUSSES &ndash; 1).

@note
To route an external voice to a Scream-managed reverb instance, with respect to synthesizer, cast the return value from a SceScreamReverbHandle to a <c>SceNgsHVoice</c> type.
*/

SceScreamReverbHandle sceScreamReverbGetHandleByBuss(uint32_t buss);
/**@}*/

/**
@ingroup generalReverbFunctions

@brief
Sets a stock preset on a specified reverb instance.

This function sets one of the stock presets on a specified reverb instance.
For a description of the reverb stock presets, see \link #SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_DEFAULT SceScreamI3DL2StockPresets\endlink.

@param handle (Input)
Handle of a reverb instance upon which to set the stock preset.

@param presetIndex (Input)
Index of the desired stock preset. One of the \link #SCE_SCREAM_SND_I3DL2_ENVIRONMENT_PRESET_DEFAULT SceScreamI3DL2StockPresets\endlink constants.
*/

/**
@see
sceScreamReverbSetCustomPresetByName(), sceScreamReverbSetCustomPreset()
*/

/**
@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
*/
int32_t sceScreamReverbSetStockPreset(SceScreamReverbHandle handle, uint32_t presetIndex);

/**
@ingroup generalReverbFunctions

@brief
Sets a custom preset, referenced by index, on a specified reverb instance.

This function sets a custom preset on a specified reverb instance.
You load custom presets files (in INI format) into Scream using the sceScreamPresetFileLoad() function, which returns a SceScreamIniHandle.
You specify the desired preset by its index within the presets file.

@param handle (Input)
Handle of a reverb instance upon which to set a custom preset.

@param iniFile (Input)
Handle of a presets file that contains the desired custom preset.

@param presetIndex (Input)
Zero-based index of the desired custom preset within the specified presets file.
Range: 0 to (<i>numPresets</i> &ndash; 1), where <i>numPresets</i> represents the number of presets in the specified presets file,
and can be determined by calling sceScreamPresetFileGetPresetCount(), passing the appropriate SceScreamIniHandle.

@note
To set a preset by name, use the sceScreamReverbSetCustomPresetByName() function.
*/

/**
@see
sceScreamReverbSetCustomPresetByName(), sceScreamReverbSetStockPreset(), sceScreamPresetFileLoad(), sceScreamPresetFileGetPresetCount()
*/

/**
@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
*/
int32_t sceScreamReverbSetCustomPreset(SceScreamReverbHandle handle, SceScreamIniHandle iniFile, uint32_t presetIndex);

/**
@ingroup generalReverbFunctions

@brief
Sets a custom preset, referenced by name, on a specified reverb instance.

This function sets a custom preset on a specified reverb instance.
You load custom presets files (in INI format) into Scream using the sceScreamPresetFileLoad() function.
The sceScreamReverbSetCustomPresetByName() function allows you specify the desired preset by name &ndash; rather than by its index &ndash; within the presets file.

@param handle (Input)
Handle of a reverb instance upon which to set the custom preset.

@param iniFile (Input)
Handle of a presets file that contains the desired custom preset.

@param presetName (Input)
A string matching one of the preset names within the specified presets file.

@note
To specify a preset by its index within the file, use the sceScreamReverbSetCustomPreset() function.
*/

/**
@see
sceScreamReverbSetCustomPreset(), sceScreamReverbSetStockPreset(), sceScreamPresetFileLoad(), sceScreamPresetFileGetPresetCount(), sceScreamPremasterSubmixSetCustomPresetByName()
*/

/**
@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
*/
int32_t sceScreamReverbSetCustomPresetByName(SceScreamReverbHandle handle, SceScreamIniHandle iniFile, const char *presetName);

/**
@ingroup generalReverbFunctions

@brief
Sets the properties of a reverb instance.

This function sets the properties (that is, parameter values) of a reverb instance.
You store the desired reverb property values in a SceScreamSndReverbProps structure, and reference it in
the <c><i>properties</i></c> parameter.

A simpler way to set reverb properties is to set a stock or custom preset using the
sceScreamReverbSetStockPreset() or sceScreamReverbSetCustomPreset() functions respectively.

This function may be useful if you are working with a custom data format for storing reverb settings
or programmatically generating reverb parameter values based on game geometries.

@param handle (Input)
Handle of a reverb instance upon which to set properties.

@param properties (Input)
A SceScreamSndReverbProps structure, storing reverb property values.
*/

/**
@see
SceScreamSndReverbProps, sceScreamReverbSetStockPreset(), sceScreamReverbSetCustomPreset()
*/

/**
@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
 */
int32_t sceScreamReverbSetAllProperties(SceScreamReverbHandle handle, const SceScreamSndReverbProps *properties);

/**
@ingroup generalReverbFunctions

@brief
Sets reverb instance volume and pan properties.

This function sets output volume and panning properties collectively for all channels of a reverb instance.

For further information about reverb azimuth and focus, see the &quot;Setting Reverb Instance Output Gain and Panning&quot; in the &quot;Working with the I3DL2 Reverb&quot; chapter of the <i>Scream Library Overview</i>.

@param handle (Input)
Handle of the reverb instance for which to set volume and pan properties.

@param gain (Input)
Overall output gain level of the reverb instance. This parameter scales all output channels except the LFE channel. Range: #SCE_SCREAM_SND_MIN_GAIN to #SCE_SCREAM_SND_MAX_GAIN.

@param lfeGain (Input)
Gain on the LFE channel. <b>Note</b>: this parameter is ignored when running Scream on the NGS synthesizer.

@param azimuth (Input)
Panning azimuth of reverb instance, expressed in degrees clockwise. Range: 0 to 359.
A value of 0 specifies that reverb is straight ahead; 90 specifies directly to the right; 180 specifies behind, and so on.

@param focus (Input)
Width of panning focus of reverb instance, expressed in degrees. Range: 0 to 360. A value of 0 specifies a point source; 360 specifies reverb coming from all directions.
<b>Note:</b> Setting <c><i>focus</i></c> to 360 makes <c><i>azimuth</i></c> irrelevant.
*/

/**
@param mode (Input)
<b>Note</b>: This parameter is ignored when running Scream on the NGS synthesizer.

@param excludeTargets (Input)
<b>Note</b>: This parameter is ignored when running Scream on the NGS synthesizer.
*/

/**
@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
*/
int32_t sceScreamReverbSetVolumePolar(SceScreamReverbHandle handle, float gain, float lfeGain, uint32_t azimuth, uint32_t focus, uint32_t mode, uint32_t excludeTargets);

/**
@ingroup generalReverbFunctions

@brief
Sets the output destination of a reverb instance.

This function sets the output destination of a reverb instance.
Without calling this function, reverb instance output destination defaults to the master buss.
However, using this function you can optionally route reverb output to one of the pre-master submix busses.

@param handle (Input)
Handle of a reverb instance for which to set the output destination.
*/
/**
@param outputDest (Input)
Index of an output destination.
To specify an allocated pre-master submix buss, use the number of the desired submix, indexing from zero, and within the range: #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 to (#SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES &ndash; 1).
To specify the master buss, use #SCE_SCREAM_SND_OUTPUT_DEST_MASTER.
See &quot;Notes&quot; below.
*/

/**
@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the SceScreamSystemParams structure.
Make sure that you do not set a pre-master submix output destination in <c><i>outputDest</i></c> that has not been allocated.
For further details, see &quot;Setting NGS/NGS2 Pre-Master Submix Indices&quot; in the &quot;Working with Pre-Master and Master Signal Processors&quot; chapter of the <i>Scream Library Overview</i>.
*/
/**
@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamSetGroupVoiceOutputDest()
*/
int32_t sceScreamReverbSetDirectPathOutputDest(SceScreamReverbHandle handle, int32_t outputDest);

/**
@ingroup generalReverbFunctions

@brief
Pauses a reverb instance.

This function suspends processing of a reverb instance. This means that active reverb tails are preserved, and are resumed immediately upon calling sceScreamReverbContinue().

@param handle (Input)
Handle of the reverb instance to pause.

@note
Pausing a reverb instance that is already paused has no effect.
*/
/**
@see
sceScreamReverbContinue(), sceScreamPauseGroup(), sceScreamContinueGroup(), sceScreamPauseAllSoundsInGroup(), sceScreamContinueAllSoundsInGroup(), sceScreamPauseSound(), sceScreamContinueSound()
*/

/**
@return
Returns #SCE_SCREAM_SS_ERROR_OK.
*/
int32_t sceScreamReverbPause(SceScreamReverbHandle handle);

/**
@ingroup generalReverbFunctions

@brief
Continues a (paused) reverb instance.

This function continues a reverb instance that has been paused using the sceScreamReverbPause() function.

@param handle (Input)
Handle of the reverb instance to continue.

@note
Continuing an instance that is not paused has no effect.
*/

/**
@see
sceScreamReverbPause(), sceScreamPauseGroup(), sceScreamContinueGroup(), sceScreamPauseAllSoundsInGroup(), sceScreamContinueAllSoundsInGroup(), sceScreamPauseSound(), sceScreamContinueSound()
*/

/**
@return
Returns #SCE_SCREAM_SS_ERROR_OK.
*/
int32_t sceScreamReverbContinue(SceScreamReverbHandle handle);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Submix Preset API

/**
@ingroup preMasterSubmixFunctions

@brief
Sets a custom effects preset, referenced by index, on a specified pre-master submix buss.

This function sets a custom effects preset on a specified pre-master submix buss.
You load custom presets files (in INI format) into Scream using the sceScreamPresetFileLoad() function.
The sceScreamPremasterSubmixSetCustomPreset() function allows you specify the desired preset by index &ndash; rather than by its name &ndash; within the presets file.

@param premasterSubmixID (Input)
Zero-based index of the target pre-master submix upon which to set a custom effect preset.

@param iniFile (Input)
Handle of a presets file that contains the desired custom preset.

@param presetIndex (Input)
Zero-based index of the desired custom preset within the specified INI file.
Range: 0 to (<i>numPresets</i> &ndash; 1), where <i>numPresets</i> represents the number of presets in the specified presets file,
and can be determined by calling sceScreamPresetFileGetPresetCount(), passing the appropriate SceScreamIniHandle.

@note
To specify a preset by its name within the file, use the sceScreamPremasterSubmixSetCustomPresetByName() function.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamPremasterSubmixSetCustomPresetByName(), sceScreamPremasterSubmixSetAllProperties()
*/
int32_t sceScreamPremasterSubmixSetCustomPreset(uint32_t premasterSubmixID, SceScreamIniHandle iniFile, uint32_t presetIndex);

/**
@ingroup preMasterSubmixFunctions

@brief
Sets a custom effects preset, referenced by name, on a specified pre-master submix buss.

This function sets a custom effects preset on a specified pre-master submix buss.
You load custom presets files (in INI format) into Scream using the sceScreamPresetFileLoad() function.
The sceScreamPremasterSubmixSetCustomPresetByName() function allows you specify the desired preset by name &ndash; rather than by its index &ndash; within the presets file.

@param premasterSubmixID (Input)
Zero-based index of the target pre-master submix upon which to set a custom effects preset.

@param iniFile (Input)
Handle of a presets file that contains the desired custom preset.

@param presetName (Input)
A string matching one of the preset names within the specified presets file.

@note
To specify a preset by its index within the file, use the sceScreamPremasterSubmixSetCustomPreset() function.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamPremasterSubmixSetCustomPreset(), sceScreamPremasterSubmixSetAllProperties()
*/
int32_t sceScreamPremasterSubmixSetCustomPresetByName(uint32_t premasterSubmixID, SceScreamIniHandle iniFile, const char *presetName);

/**
@ingroup preMasterSubmixFunctions

@brief
Sets the properties of all effects on a specified pre-master submix buss.

This function sets the properties of all effects on a specified pre-master submix buss.

@param premasterSubmixID (Input)
Zero-based index of the target pre-master submix upon which to set all effect properties.

@param properties (Input)
Pointer to a SceScreamSndPremasterSubmixProps structure, appropriately initialized with effect property values.

@note
To set properties for individual pre-master submix effects, you can use the sceScreamSynthPremasterSubmixSetupCompressor() function.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
SceScreamSndPremasterSubmixProps, sceScreamPremasterSubmixSetCustomPreset(), sceScreamPremasterSubmixSetCustomPresetByName(), sceScreamSynthPremasterSubmixSetupCompressor()
*/
int32_t sceScreamPremasterSubmixSetAllProperties(uint32_t premasterSubmixID, const SceScreamSndPremasterSubmixProps *properties);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Preset (.ini) Files

/**
@defgroup presetFileINIFunctions Presets File (INI) Functions
@brief
Preset file functions load and unload presets (INI) files, and retrieve information from them.
@{*/
/**

@brief
Loads a presets file from disk.

This function loads a presets file in INI format from disk, and returns a handle to it.

@param name (Input)
Path to a presets file to load from disk.

@return
Returns a SceScreamIniHandle presets file handle.

@note
Whenever memory is requested for a presets file, the system passes the constant #SCE_SCREAM_SND_MEM_USE_PRESETS to your custom SceScreamExternSndMemAlloc() <c><i>use</i></c> parameter.

@see
sceScreamPresetFileLoadFromMem(), sceScreamPresetFileUnload()
*/
SceScreamIniHandle sceScreamPresetFileLoad(const char* name);
/**@}*/

/**
@ingroup presetFileINIFunctions

@brief
Loads a presets file from memory.

This function loads a presets file in INI format from memory, and returns a handle to it.

@param loc (Input)
Location of a presets file in memory.

@param size (Input)
Size, in bytes, of the memory-resident presets file pointed to in <c><i>loc</i></c>.

@return
Returns a SceScreamIniHandle presets file handle.

@note
The preset file must remain resident in memory until released with a call to the sceScreamPresetFileUnload() function.

@see
sceScreamPresetFileLoad(), sceScreamPresetFileUnload()
*/
SceScreamIniHandle sceScreamPresetFileLoadFromMem(const void* loc, uint32_t size);

/**
@ingroup presetFileINIFunctions

@brief
Unloads a presets file.

This function unloads a presets file, freeing any associated memory.

@param handle (Input)
Handle of the presets file to unload.
Returned from the sceScreamPresetFileLoad() or sceScreamPresetFileLoadFromMem() functions.

@note
This function should be called regardless of the method used to load the presets file &ndash; from disk or from memory.
There is no asynchronous presets file unload function.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamPresetFileLoad(), sceScreamPresetFileLoadFromMem()
*/
int32_t sceScreamPresetFileUnload(SceScreamIniHandle handle);

/**
@ingroup presetFileINIFunctions

@brief
Retrieves the count of individual presets contained in a presets file.

This function retrieves the total count of presets contained in a presets INI file.

@param handle (Input)
Handle of the presets file from which to obtain a count of presets.
Returned by the sceScreamPresetFileLoad() or sceScreamPresetFileLoadFromMem() functions.

@return
Returns the total count of presets contained in the specified presets file.

@note
Use this function to determine the maximum value plus one for the <c><i>presetIndex</i></c> parameter in the sceScreamReverbSetCustomPreset() and sceScreamPremasterSubmixSetCustomPreset() functions.
Because these functions' <c><i>presetIndex</i></c> parameter expects a zero-based index of presets, subtract one (1) from the value returned by this function to get the maximum index.

@see
sceScreamReverbSetCustomPreset(), sceScreamPremasterSubmixSetCustomPreset()
*/
uint32_t sceScreamPresetFileGetPresetCount(SceScreamIniHandle handle);

/**
@ingroup presetFileINIFunctions

@brief
Retrieves the name of a preset contained in a presets file.

This function retrieves the name of a preset, specified by its index within a presets file.

@param handle (Input)
Handle of the presets file from which to retrieve the name of a preset.
Returned by the sceScreamPresetFileLoad() or sceScreamPresetFileLoadFromMem() functions.

@param presetIndex (Input)
Zero-based index of a preset from which to retrieve the name.

@param buffer (Input)
Pointer to a character buffer in which to store the preset name.
Must be at least the size specified in <c><i>bufferLength</i></c>.

@param bufferLength (Input)
Size, in bytes, of the buffer pointed to by <c><i>buffer</i></c>.

@return
Returns #SCE_SCREAM_SS_ERROR_OK if the operation was successful, otherwise returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.

@see
sceScreamReverbSetCustomPresetByName(), sceScreamPremasterSubmixSetCustomPresetByName(), sceScreamPresetFileGetPresetCount()
*/
int32_t sceScreamPresetFileGetPresetName(SceScreamIniHandle handle, uint32_t presetIndex, char* buffer, uint32_t bufferLength);

////////////////////////////////////////////////////////////////////////////////
// Aux Buss API
/**
@defgroup auxBussFunctions Auxiliary Buss Functions
@brief
Auxiliary buss functions allow you to manipulate auxiliary busses.
@{*/

/**
@brief
Sets an auxiliary buss output destination.

This function sets the output destination for an auxiliary buss.
Without calling this function, auxiliary buss output destination defaults to the master buss.
However, using this function you can optionally route auxiliary buss output to one of the pre-master submix busses.

@param auxBuss (Input)
Zero-based index of an auxiliary buss for which to set the output destination.

@param outputDest (Input)
Index of an output destination to set. For the master output, use #SCE_SCREAM_SND_OUTPUT_DEST_MASTER.
To specify an allocated pre-master submix buss, use the number of the desired submix, indexing from zero.
Range: #SCE_SCREAM_SND_OUTPUT_DEST_PREMASTER_0 to (#SCE_SCREAM_SND_MAX_PREMASTER_SUBMIXES &ndash; 1). See &quot;Notes&quot; below.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the SceScreamSystemParams structure.
Make sure that you do not set a pre-master submix output destination that has not been allocated.

@see
sceScreamSetGroupVoiceOutputDest
*/

int32_t sceScreamSetAuxBussOutputDest(uint32_t auxBuss, int32_t outputDest);
/**@}*/

////////////////////////////////////////////////////////////////////////////////
// Buss Configuration (.bus) Files

/**
@defgroup bussConfigurationFunctions Buss Configuration Functions
@brief
Buss configuration functions allow you to set and query buss presets.
@{*/
/**
@brief
Applies a preset to a buss effect.

This function applies a preset to an effect. The preset, specified by name, must be contained in a buss configuration file,
loaded into Scream at initialization time, specified in the SceScreamPlatformInitEx2.pBussConfigFile member.
The index of the target buss upon which to apply the preset can be specified either by preset data or by the programmer.

@param name (Input)
Name of a preset to apply.

@param bussIndex (Input)
Index of a premaster submix buss or auxiliary buss upon which to apply the preset.
Defaults to -1, in which case the buss index value is specified by the preset itself.
Not applicable to presets for which there is only one corresponding buss, such as the master buss.
See &quot;Notes&quot; below.

@return
Returns <c>TRUE</c> if the preset was successfully applied, otherwise returns <c>FALSE</c>.

@note
The buss index specified in the <c><i>bussIndex</i></c> parameter, if other than the default, overrides any preset data-specified buss index.
*/
/**
@note
On the NGS synthesizer, the number of auxiliary busses is #SCE_SCREAM_NUM_AUX_BUSSES (3), and auxiliary buss indices range from 0 to 2.

@see
SceScreamPlatformInitEx2.pBussConfigFile
*/

/**
@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the SceScreamSystemParams structure.
Make sure that you do not apply a buss preset to a premaster submix buss that has not been allocated.
*/
bool sceScreamApplyBussPreset(const char* name, int32_t bussIndex);
/**@}*/


/**
@defgroup effectPresetFunctions Effect Preset Functions
@brief
Effect preset functions allow you to apply and query effect presets.
<b>Note</b>: To use these functions you must set the #SCE_SCREAM_SND_SYNTH_INIT_FLAG_ENABLE_EFFECT_API flag in the SceScreamSystemParams <c><i>initFlags</i></c> member when initializing Scream.
@{*/
/**
@brief
Applies a preset to an effect.

This function applies a preset to an effect.
The preset, specified by name, must be contained in a buss configuration file, loaded into Scream at initialization time, specified in the SceScreamPlatformInitEx2.pBussConfigFile member.
You identify an effect instance upon which to apply a preset by its SceScreamEffectHandle.
The index of the target buss upon which to apply the preset can be specified either by preset data or by the programmer.

@param name (Input)
Name of a preset to apply.

@param handle (Input)
Optional SceScreamEffectHandle of an effect instance upon which to apply a named preset.
Defaults to 0, in which case the specified <c><i>bussIndex</i></c> or a buss index value specified in preset data is used to determine the target effect instance.
If a buss index is not included in preset data, and neither a valid SceScreamEffectHandle nor a valid <c><i>bussIndex</i></c> is specified, this function fails.
See &quot;Notes&quot; below.

@param bussIndex (Input)
Index of a premaster submix buss or auxiliary buss upon which to apply the preset.
Defaults to -1, in which case the buss index value is specified by the preset itself.
Not applicable to presets for which there is only one corresponding buss, such as the master buss.
See &quot;Notes&quot; below.

@return
Returns <c>TRUE</c> if the preset was successfully applied, otherwise returns <c>FALSE</c>.

@note
The buss index specified in the <c><i>bussIndex</i></c> parameter, if other than the default, overrides any preset data-specified buss index.

@note
On the NGS2 synthesizer, the number of auxiliary busses is determined by the value set for SceScreamSystemParams.numAuxBusses when initializing Scream. Auxiliary buss indices are zero-based.

@note
Pre-master submix busses must be allocated at initialization time using the <c><i>numPremasterCompSubmixes</i></c> and <c><i>numPremasterScCompSubmixes</i></c> members of the SceScreamSystemParams structure.
Make sure that you do not apply a buss preset to a premaster submix buss that has not been allocated.

@note
To use this function you must set the #SCE_SCREAM_SND_SYNTH_INIT_FLAG_ENABLE_EFFECT_API flag in the SceScreamSystemParams <c><i>initFlags</i></c> member when initializing Scream.

@see
SceScreamPlatformInitEx2.pBussConfigFile
*/
bool sceScreamApplyEffectPreset(const char* name, SceScreamEffectHandle handle, int32_t bussIndex);
/**@}*/


/**
@ingroup bussConfigurationFunctions

@brief
Retrieves the buss type associated with a named buss preset.

This function retrieves the buss type associated with a named effect preset.
The preset, specified by name, must be contained in a buss presets file, loaded into Scream at initialization time, specified in the SceScreamPlatformInitEx2.pBussConfigFile member.

@param name (Input)
Name of a preset to query for its buss type.
*/

/**
@see
SceScreamPlatformInitEx2.pBussConfigFile
*/

/**
@return
Returns one of the \link #SCE_SCREAM_SND_BUSS_TYPE_UNKNOWN Buss Types\endlink.
*/
int32_t sceScreamGetBussPresetType(const char* name);

/**
@ingroup effectPresetFunctions

@brief
Retrieves the buss type associated with a named effect preset.

This function retrieves the buss type associated with a named effect preset.
The preset, specified by name, must be contained in a buss presets file, loaded into Scream at initialization time,
specified in the SceScreamPlatformInitEx2.pBussConfigFile member.

@param name (Input)
Name of a preset to query for its effect type.

@note
To use this function you must set the #SCE_SCREAM_SND_SYNTH_INIT_FLAG_ENABLE_EFFECT_API flag in the SceScreamSystemParams <c><i>initFlags</i></c> member when initializing Scream.

@return
For auxiliary effects, returns one of the \link #SCE_SCREAM_SND_EFFECT_TYPE_NONE SceScreamSndEffectTypes\endlink enumerations.
For non-auxiliary effects, returns one of the \link #SCE_SCREAM_SND_BUSS_TYPE_UNKNOWN Buss Types\endlink.

@see
SceScreamPlatformInitEx2.pBussConfigFile, sceScreamApplyEffectPreset(), sceScreamGetEffectPresetCount()
*/
int32_t sceScreamGetEffectPresetType(const char *name);


/**
@ingroup bussConfigurationFunctions

@brief
Retrieves the total count of buss presets.

This function retrieves the total count of loaded effect presets.
Presets must be contained in a buss presets file, loaded into Scream at initialization time, specified in the SceScreamPlatformInitEx2.pBussConfigFile member.

@param count (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the buss preset count.
*/

/**
@see
SceScreamPlatformInitEx2.pBussConfigFile
*/

/**
@return
Returns <c>TRUE</c> if successful, otherwise returns <c>FALSE</c>.
*/
bool sceScreamGetBussPresetCount(uint32_t *count);

/**
@ingroup effectPresetFunctions

@brief
Retrieves the total count of effect presets.

This function retrieves the total count of loaded effect presets.
Presets must be contained in a buss presets file, loaded into Scream at initialization time, specified in the SceScreamPlatformInitEx2.pBussConfigFile member.

@param count (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the effect preset count.

@note
To use this function you must set the #SCE_SCREAM_SND_SYNTH_INIT_FLAG_ENABLE_EFFECT_API flag in the SceScreamSystemParams <c><i>initFlags</i></c> member when initializing Scream.

@return
Returns <c>TRUE</c> if successful, otherwise returns <c>FALSE</c>.

@see
SceScreamPlatformInitEx2.pBussConfigFile, sceScreamGetEffectPresetName(), sceScreamGetEffectPresetType()
*/
bool sceScreamGetEffectPresetCount(uint32_t *count);

/**
@ingroup bussConfigurationFunctions

@brief
Retrieves the name of a buss preset.

This function retrieves the name of an effect preset specified by index.
Presets must be contained in an effect presets file, loaded into Scream at initialization time, specified in the SceScreamPlatformInitEx2.pBussConfigFile member.

@param presetIndex (Input)
Index of a preset for which to retrieve the name.

@param presetName (Output)
Pointer to a <c>const char</c> pointer in which to receive the name of the specified preset.
*/

/**
@see
SceScreamPlatformInitEx2.pBussConfigFile
*/

/**
@return
Returns <c>TRUE</c> if successful, otherwise returns <c>FALSE</c>.
*/
bool sceScreamGetBussPresetName(uint32_t presetIndex, const char **presetName);

/**
@ingroup effectPresetFunctions

@brief
Retrieves the name of an effect preset.

This function retrieves the name of an effect preset specified by index.
Presets must be contained in an effect presets file, loaded into Scream at initialization time, specified in the SceScreamPlatformInitEx2.pBussConfigFile member.

@param presetIndex (Input)
Index of a preset for which to retrieve the name.

@param presetName (Output)
Pointer to a <c>const char</c> pointer in which to receive the name of the specified preset.

@note
To use this function you must set the #SCE_SCREAM_SND_SYNTH_INIT_FLAG_ENABLE_EFFECT_API flag in the SceScreamSystemParams <c><i>initFlags</i></c> member when initializing Scream.

@return
Returns <c>TRUE</c> if successful, otherwise returns <c>FALSE</c>.

@see
SceScreamPlatformInitEx2.pBussConfigFile, sceScreamGetEffectPresetCount(), sceScreamGetEffectPresetType()
*/
bool sceScreamGetEffectPresetName(uint32_t presetIndex, const char **presetName);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 3D Utility Functions.

/**
@defgroup utilityFunctions Utility Functions
@brief
Utility functions calculate Doppler pitch transpose and 3D sound spatialization parameters. For more information on spatialization, see &quot;Sound Spatialization&quot; in the &quot;Working with Distance Models, Doppler, and Spatialization&quot; chapter of the <i>Scream Library Overview</i>.
@{*/
/**
@brief
Calculates a pitch transposition amount used for the Doppler effect.

This function calculates pitch transposition amounts used for the Doppler pitch shift effect.
Return values are expressed in fines, and can be applied directly to the SceScreamSoundParams.pitchTranspose member.

Doppler is the name given to the phenomenon of pitch
shifting that occurs with a moving sound source (or a moving
listener). An everyday example would be an ambulance or fire truck
siren that moves towards and then away from a stationary listener. The
pitch of the sound source appears to increase as the sound becomes
closer; and to decrease as the sound gets further
away. The effect of moving sound sources is sometimes exaggerated in
games for dramatic effect.

For further discussion, see &quot;Doppler Pitch Shifting&quot; in the &quot;Working with Distance Models, Doppler, and Spatialization&quot; chapter of the <i>Scream Library Overview</i>.

@param
approachingMps (Input)
Speed of an approaching sound-producing object in meters per second. Use negative amounts for
objects that are moving away from the listener.

@return
Returns a pitch transposition value expressed in fines. See #SCE_SCREAM_SND_FINES_PER_OCTAVE.

@see
SceScreamSoundParams, sceScreamAutoPitchTranspose()
*/
int32_t sceScreamGetDopplerPitchTranspose(float32_t approachingMps);
/**@}*/

/**
@ingroup utilityFunctions

@brief
Creates a three-dimensional (3D) sound spatialization listener.

This function creates a listener used for 3D sound spatialization.
Along with sceScreamSetListener() and sceScreamCalcSoundAngles(), it is used to calculate
the polar coordinates of sound-emitting object(s) relative to a listener, based on game world Cartesian coordinates.

A listener is a proxy for a listening point in game world space.
For example, this might be a game character's ears, or in a sports game, the location of a camera.

The function finds an available listener (from a pool of #SCE_SCREAM_SND_MAXLISTENERS), and allocates it.

For more information on using listeners, see the &quot;Working with Distance Models, Doppler, and Spatialization&quot; chapter of the <i>Scream Library Overview</i>.

@return
If successful, returns a <c>uint32_t</c> representing the listener handle. Otherwise returns zero.

@see
sceScreamDeleteListener(), sceScreamSetListener(), sceScreamGetListener(), sceScreamCalcSoundAngles()
*/
uint32_t sceScreamCreateListener(void);

/**
@ingroup utilityFunctions

@brief
Deletes a 3D sound spatialization listener.

This function deallocates a 3D sound spatialization listener and returns it to a pool of #SCE_SCREAM_SND_MAXLISTENERS.

@param handle (Input)
The handle of the listener you wish to delete, a value returned by sceScreamCreateListener().

@return
Returns 0 if successful.
Returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
Returns #SCE_SCREAM_SS_ERROR_SYSTEM_NOT_STARTED if Scream is not currently running.

@see
sceScreamCreateListener(), sceScreamSetListener(), sceScreamGetListener(), sceScreamCalcSoundAngles()
*/
int32_t sceScreamDeleteListener(uint32_t handle);

/**
@ingroup utilityFunctions

@brief
Sets the location and orientation of a 3D sound spatialization listener.

This function sets the location and orientation of a 3D sound spatialization listener.
The <c><i>location</i></c>, <c><i>front</i></c>, and <c><i>top</i></c> parameters specify, respectively,
the location, front, and top orientation vectors of the listener.

@param handle (Input)
The handle of the listener you wish to set, a value returned by sceScreamCreateListener().

@param location (Input)
Pointer to a SceScreamSnd3DVector structure containing the location of the listener in game world space.

@param front (Input)
Pointer to a SceScreamSnd3DVector structure containing the front orientation vector relative to the location of the listener.

@param top (Input)
Pointer to a SceScreamSnd3DVector structure containing the top orientation vector relative to the location of the listener.

@param cameraCut (Input)
A Boolean value indicating, for purpose of Doppler pitch shift calculation, whether there is a discontinuity in listener location.
Set to <c>TRUE</c> if a camera cut is occurring this frame. Otherwise, set to <c>FALSE</c>.
See &quot;Notes&quot; below.

@return
Returns 0 if successful.
Returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
Returns #SCE_SCREAM_SS_ERROR_SYSTEM_NOT_STARTED if Scream is not currently running.

@note
When using Scream's Doppler effect, you can set the <c><i>cameraCut</i></c> parameter to <c>TRUE</c> to indicate a discontinuity in listener (or camera) location.
This avoids the potential for large instantaneous Doppler pitch shifts that might otherwise result.
A discontinuity in listener position is the more common camera cut scenario.
You can also specify a camera cut when there has been a discontinuity in emitter location.
For further details, see the #SCE_SCREAM_SND_FLAG_DOPPLER_CAMERA_CUT Sound flag.
Specification of both listener <i>and</i> emitter camera cuts within the same frame is unnecessary.

@see
sceScreamCreateListener(), sceScreamDeleteListener(), sceScreamGetListener(), sceScreamCalcSoundAngles(), SceScreamSnd3DVector, #SCE_SCREAM_SND_FLAG_DOPPLER_CAMERA_CUT
*/
int32_t sceScreamSetListener(uint32_t handle, const SceScreamSnd3DVector *location, const SceScreamSnd3DVector *front, const SceScreamSnd3DVector *top, bool cameraCut);

/**
@ingroup utilityFunctions

@brief
Gets the location and orientation of a 3D sound spatialization listener.

This function retrieves the location and orientation of a 3D sound spatialization listener.
Values for the listener's location, front orientation vector, and top orientation vector are stored, respectively,
in SceScreamSnd3DVector structures pointed by the <c><i>location</i></c>, <c><i>front</i></c>, and <c><i>top</i></c> parameters.

@param handle (Input)
The handle of the listener for which to retrieve location/orientation data, a value returned by sceScreamCreateListener().

@param location (Output)
Pointer to a SceScreamSnd3DVector structure in which to receive the location of the listener in game world space.
Set to <c>NULL</c> if this information is not required.

@param front (Output)
Pointer to a SceScreamSnd3DVector structure in which to receive the listener's front orientation vector.
Set to <c>NULL</c> if this information is not required.

@param top (Output)
Pointer to a SceScreamSnd3DVector structure in which to receive the listener's top orientation vector.
Set to <c>NULL</c> if this information is not required.

@return
Returns 0 if successful.
Returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
Returns #SCE_SCREAM_SS_ERROR_SYSTEM_NOT_STARTED if Scream is not currently running.

@see
sceScreamCreateListener(), sceScreamDeleteListener(), sceScreamSetListener(), sceScreamCalcSoundAngles(), SceScreamSnd3DVector
*/
int32_t sceScreamGetListener(uint32_t handle, SceScreamSnd3DVector *location, SceScreamSnd3DVector *front, SceScreamSnd3DVector *top);

/**
@ingroup utilityFunctions

@brief
Calculates azimuth and elevation angles for 3D sound spatialization.

This function calculates the azimuth and elevation angles between a specified listener and sound-emitting object.
You specify the location of the sound-emitting object as a SceScreamSnd3DVector structure in the <c><i>location</i></c> parameter.

The output <c><i>azimuth</i></c> and <c><i>elevation</i></c> values from this function can be utilized for 3D sound spatialization.
The azimuth value is expressed in degrees, 0 being directly in front of, and 180 being directly behind the listener.
You can apply the <c><i>azimuth</i></c> value directly to the SceScreamSoundParams <c><i>azimuth</i></c> member.

The <c><i>elevation</i></c> value is also expressed in degrees, 0 being at listener height, 90 directly above, and -90 directly below the listener.
The SceScreamSoundParams structure, however, does not include an <c><i>elevation</i></c> member.
Instead, Scream provides a way to manage distance cues through panning focus.
Closer sounds &ndash; which tend to be more dispersed &ndash; are given wider focus.
Conversely, more distant sounds are given narrower focus.
Developers are free to choose from a variety of potential approaches for mapping <c><i>elevation</i></c> to focus, or even to ignore this value.
One approach, for example, could be a simple linear calculation such as:<br>
<c>focus = ( abs(<i>elevation</i>) / 90 ) * 360 )</c>

For an example of using this function, see &quot;Sound Spatialization&quot; in the &quot;Working with Distance Models, Doppler, and Spatialization&quot; chapter of the <i>Scream Library Overview</i>.

@param handle (Input)
The handle of the listener for which to calculate azimuth/elevation data, a value returned by sceScreamCreateListener().

@param location (Input)
Pointer to a SceScreamSnd3DVector structure containing the location of the sound-emitting object in game world space.

@param azimuth (Output)
Pointer to a <c>uint32_t</c> variable in which to receive the azimuth angle for the sound-emitting object.

@param elevation (Output)
Pointer to an <c>int32_t</c> variable in which to receive the elevation angle for the sound-emitting object.

@return
Returns 0 if successful.
Returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER if an invalid parameter value was detected.
Returns #SCE_SCREAM_SS_ERROR_SYSTEM_NOT_STARTED if Scream is not currently running.

@see
SceScreamSoundParams, sceScreamCreateListener(), sceScreamDeleteListener(), sceScreamGetListener(), sceScreamSetListener(), SceScreamSnd3DVector
*/
int32_t sceScreamCalcSoundAngles(uint32_t handle, const SceScreamSnd3DVector *location, uint32_t *azimuth, int32_t *elevation);

/**
@ingroup utilityFunctions

@brief
Sets the number of game-world units per meter.

This function sets the number of game-world units per meter.
Scream uses meters as its unit of distance.
Distance calculations for distance model input, and velocity calculations for Scream's Doppler effect, are based on values specified for Sound and listener 3D positional coordinates.
These values are assumed to be expressed in meters.
In your game, if distance is expressed in units other than meters, you can use this function to instruct Scream to convert your distance units to meters.
Thereafter, you can specify Sound and listener positions in your game-world units, and Scream adjusts its calculations accordingly.
For example, if your game uses feet as its unit measure of distance, you should set this value to approximately 3.281, which is the number of feet in a meter.

@param unitsPerMeter (Input)
The number of game-world units per meter.

@return
If successful, returns #SCE_SCREAM_SS_ERROR_OK. Otherwise, returns #SCE_SCREAM_SS_ERROR_INVALID_PARAMETER.

@see
sceScreamGetWorldUnitsPerMeter(), sceScreamGetDopplerPitchTranspose(), SceScreamSnd3DVector, sceScreamSetListener(), SceScreamSoundParams.position
*/
int32_t sceScreamSetWorldUnitsPerMeter(float unitsPerMeter);

/**
@ingroup utilityFunctions

@brief
Retrieves the currently assigned number of game-world units per meter.

This function retrieves the currently assigned number of game-world units per meter.
Without setting the units by calling sceScreamSetWorldUnitsPerMeter(), game-world units per meter defaults to 1.0.

@return
The current number of game-world units per meter.

@see
sceScreamSetWorldUnitsPerMeter(), sceScreamGetDopplerPitchTranspose(), SceScreamSnd3DGrainData
*/
float sceScreamGetWorldUnitsPerMeter(void);

////////////////////////////////////////////////////////////////////////////////

#if (defined(_cplusplus) || defined(__cplusplus))
}  //extern "C"
#endif

#endif // _DOLCESDK_PSP2_SCREAM_SCE_SCREAM_H_
