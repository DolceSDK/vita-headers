#ifndef _DOLCESDK_PSP2_AUDIOENC_H_
#define _DOLCESDK_PSP2_AUDIOENC_H_

#include <psp2/types.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/* Error definition */
#define SCE_AUDIOENC_ERROR_API_FAIL                     (-2138701824) /* 0x80860000 */
#define SCE_AUDIOENC_ERROR_INVALID_TYPE                 (-2138701823) /* 0x80860001 */
#define SCE_AUDIOENC_ERROR_INVALID_INIT_PARAM           (-2138701822) /* 0x80860002 */
#define SCE_AUDIOENC_ERROR_ALREADY_INITIALIZED          (-2138701821) /* 0x80860003 */
#define SCE_AUDIOENC_ERROR_OUT_OF_MEMORY                (-2138701820) /* 0x80860004 */
#define SCE_AUDIOENC_ERROR_NOT_INITIALIZED              (-2138701819) /* 0x80860005 */
#define SCE_AUDIOENC_ERROR_A_HANDLE_IN_USE              (-2138701818) /* 0x80860006 */
#define SCE_AUDIOENC_ERROR_ALL_HANDLES_IN_USE           (-2138701817) /* 0x80860007 */
#define SCE_AUDIOENC_ERROR_INVALID_PTR                  (-2138701816) /* 0x80860008 */
#define SCE_AUDIOENC_ERROR_INVALID_HANDLE               (-2138701815) /* 0x80860009 */
#define SCE_AUDIOENC_ERROR_NOT_HANDLE_IN_USE            (-2138701814) /* 0x8086000A */
#define SCE_AUDIOENC_ERROR_CH_SHORTAGE                  (-2138701813) /* 0x8086000B */
#define SCE_AUDIOENC_ERROR_INVALID_WORD_LENGTH          (-2138701812) /* 0x8086000C */
#define SCE_AUDIOENC_ERROR_INVALID_SIZE                 (-2138701811) /* 0x8086000D */
#define SCE_AUDIOENC_ERROR_INVALID_ALIGNMENT            (-2138701810) /* 0x8086000E */
#define SCE_AUDIOENC_ERROR_UNSUPPORTED                  (-2138701809) /* 0x8086000F */

/* Error of CELP */
/* 0x80861000 - 0x808617FF */
#define SCE_AUDIOENC_CELP_ERROR_INVALID_CONFIG          (-2138697727) /* 0x80861001 */

#define SCE_AUDIOENC_ALIGNMENT_SIZE (0x100U)

#define SCE_AUDIOENC_ROUND_UP(size) ((size + SCE_AUDIOENC_ALIGNMENT_SIZE - 1) & ~(SCE_AUDIOENC_ALIGNMENT_SIZE - 1))

/* The definiton of wordLength */
#define SCE_AUDIOENC_WORD_LENGTH_16BITS (16)

/* Audio encoder type */
#define SCE_AUDIOENC_TYPE_CELP (0x2006U)
#define SCE_AUDIOENC_TYPE_SILK (0x2007U) /* Only use with sceAudioencCreateEncoderResident() */

/* Maximum number of streams */
#define SCE_AUDIOENC_CELP_MAX_STREAMS (1)

/* Maximum number of samples */
#define SCE_AUDIOENC_CELP_MAX_SAMPLES (320)

/* Maximum elementary stream size */
#define SCE_AUDIOENC_CELP_MAX_ES_SIZE (27)

/* CELP encoder default excitation mode */
#define SCE_AUDIOENC_CELP_MPE (0)
/* CELP encoder default sampling rate */
#define SCE_AUDIOENC_CELP_SAMPLING_RATE_8KHZ (8000)
/* CELP encoder bitrate definition */
#define SCE_AUDIOENC_CELP_BIT_RATE_3850BPS   (3850) /*  3850 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_4650BPS   (4650) /*  4650 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_5700BPS   (5700) /*  5700 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_6600BPS   (6600) /*  6600 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_7300BPS   (7300) /*  7300 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_8700BPS   (8700) /*  8700 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_9900BPS   (9900) /*  9900 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_10700BPS (10700) /* 10700 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_11800BPS (11800) /* 11800 bps */
#define SCE_AUDIOENC_CELP_BIT_RATE_12200BPS (12200) /* 12200 bps */

typedef struct SceAudioencInitStreamParam {
	SceUInt32 size;         /* size of this structure */
	SceUInt32 totalStreams;
} SceAudioencInitStreamParam;

typedef union SceAudioencInitParam {
	SceUInt32                  size;
	SceAudioencInitStreamParam celp;
} SceAudioencInitParam;

/* Information for CELP */
typedef struct SceAudioencInfoCelp {
	SceUInt32 size;           /* size of this structure */
	SceUInt32 excitationMode; /* excitation mode */
	SceUInt32 samplingRate;   /* sampling rate */
	SceUInt32 bitRate;        /* bit rate */
} SceAudioencInfoCelp;

/* Optional information for CELP */
typedef struct SceAudioencOptInfoCelp {
	SceUInt32 size;            /* size of this structure */
	SceUInt8  header[32];      /* header buffer */
	SceUInt32 headerSize;      /* header size */
	SceUInt32 encoderVersion;
} SceAudioencOptInfoCelp;

/* Audio encoder information */
typedef union SceAudioencInfo {
	SceUInt32           size;
	SceAudioencInfoCelp celp;
} SceAudioencInfo;

/* Audio encoder optional information */
typedef union SceAudioencOptInfo {
	SceUInt32              size;
	SceAudioencOptInfoCelp celp;
} SceAudioencOptInfo;

/* Audio encoder control */
typedef struct SceAudioencCtrl {
	SceUInt32          size;         /* size of this structure */
	SceInt32           handle;       /* encoder handle */
	SceUInt8           *pInputPcm;   /* pointer to elementary stream */
	SceUInt32          inputPcmSize; /* size of elementary stream used actually (in byte) */
	SceUInt32          maxPcmSize;   /* maximum size of elementary stream used (in byte) */
	void               *pOutputEs;   /* pointer to PCM */
	SceUInt32          outputEsSize; /* size of PCM output actually (in byte) */
	SceUInt32          maxEsSize;    /* maximum size of PCM output (in byte) */
	SceUInt32          wordLength;   /* PCM bit depth */
	SceAudioencInfo    *pInfo;       /* pointer to SceAudioencInfo */
	SceAudioencOptInfo *pOptInfo;    /* pointer to SceAudioencOptInfo */
} SceAudioencCtrl;

extern SceInt32 sceAudioencInitLibrary(SceUInt32 codecType, SceAudioencInitParam *pInitParam);
extern SceInt32 sceAudioencTermLibrary(SceUInt32 codecType);
extern SceInt32 sceAudioencCreateEncoder(SceAudioencCtrl *pCtrl, SceUInt32 codecType);
extern SceInt32 sceAudioencDeleteEncoder(SceAudioencCtrl *pCtrl);
extern SceInt32 sceAudioencEncode(SceAudioencCtrl *pCtrl);
extern SceInt32 sceAudioencClearContext(SceAudioencCtrl *pCtrl);
extern SceInt32 sceAudioencGetOptInfo(SceAudioencCtrl *pCtrl);
extern SceInt32 sceAudioencGetInternalError(SceAudioencCtrl *pCtrl, SceInt32 *pInternalError);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_AUDIOENC_H_ */
