#ifndef _DOLCESDK_PSP2_AUDIODEC_H_
#define _DOLCESDK_PSP2_AUDIODEC_H_

#include <psp2/types.h>

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif /* defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus) */

/* Error definition */
#define SCE_AUDIODEC_ERROR_API_FAIL                     (-2139160576) /* 0x807F0000 */
#define SCE_AUDIODEC_ERROR_INVALID_TYPE                 (-2139160575) /* 0x807F0001 */
#define SCE_AUDIODEC_ERROR_INVALID_INIT_PARAM           (-2139160574) /* 0x807F0002 */
#define SCE_AUDIODEC_ERROR_ALREADY_INITIALIZED          (-2139160573) /* 0x807F0003 */
#define SCE_AUDIODEC_ERROR_OUT_OF_MEMORY                (-2139160572) /* 0x807F0004 */
#define SCE_AUDIODEC_ERROR_NOT_INITIALIZED              (-2139160571) /* 0x807F0005 */
#define SCE_AUDIODEC_ERROR_A_HANDLE_IN_USE              (-2139160570) /* 0x807F0006 */
#define SCE_AUDIODEC_ERROR_ALL_HANDLES_IN_USE           (-2139160569) /* 0x807F0007 */
#define SCE_AUDIODEC_ERROR_INVALID_PTR                  (-2139160568) /* 0x807F0008 */
#define SCE_AUDIODEC_ERROR_INVALID_HANDLE               (-2139160567) /* 0x807F0009 */
#define SCE_AUDIODEC_ERROR_NOT_HANDLE_IN_USE            (-2139160566) /* 0x807F000A */
#define SCE_AUDIODEC_ERROR_CH_SHORTAGE                  (-2139160565) /* 0x807F000B */
#define SCE_AUDIODEC_ERROR_INVALID_WORD_LENGTH          (-2139160564) /* 0x807F000C */
#define SCE_AUDIODEC_ERROR_INVALID_SIZE                 (-2139160563) /* 0x807F000D */
#define SCE_AUDIODEC_ERROR_UNSUPPORTED                  (-2139160562) /* 0x807F000E */
#define SCE_AUDIODEC_ERROR_INVALID_NFRAMES              (-2139160561) /* 0x807F000F */
#define SCE_AUDIODEC_ERROR_INVALID_NSTREAMS             (-2139160560) /* 0x807F0010 */
#define SCE_AUDIODEC_ERROR_DIFFERENT_TYPES              (-2139160559) /* 0x807F0011 */
#define SCE_AUDIODEC_ERROR_SAME_HANDLES                 (-2139160558) /* 0x807F0012 */
#define SCE_AUDIODEC_ERROR_BUSY                         (-2139160557) /* 0x807F0013 */

/* Error of ATRAC9 */
/* 0x807F2000 - 0x807F27FF */
#define SCE_AUDIODEC_AT9_ERROR_INVALID_CONFIG           (-2139152384) /* 0x807F2000 */
/* Error of MP3 */
/* 0x807F2800 - 0x807F2FFF */
#define SCE_AUDIODEC_MP3_ERROR_INVALID_CH               (-2139150336) /* 0x807F2800 */
#define SCE_AUDIODEC_MP3_ERROR_INVALID_MPEG_VERSION     (-2139150335) /* 0x807F2801 */
/* Error of AAC */
/* 0x807F3000 - 0x807F37FF */
#define SCE_AUDIODEC_AAC_ERROR_INVALID_CH               (-2139148288) /* 0x807F3000 */
/* Error of CELP */
/* 0x807F3800 - 0x807F3FFF */
#define SCE_AUDIODEC_CELP_ERROR_INVALID_CONFIG          (-2139146240) /* 0x807F3800 */

#define SCE_AUDIODEC_ALIGNMENT_SIZE (0x100U)
#define SCE_AUDIODEC_ROUND_UP(size) ((size + SCE_AUDIODEC_ALIGNMENT_SIZE - 1) & ~(SCE_AUDIODEC_ALIGNMENT_SIZE - 1))

/* The definiton of wordLength */
#define SCE_AUDIODEC_WORD_LENGTH_16BITS (16)

/* Audio decoder type */
#define SCE_AUDIODEC_TYPE_AT9  (0x1003U)
#define SCE_AUDIODEC_TYPE_MP3  (0x1004U)
#define SCE_AUDIODEC_TYPE_AAC  (0x1005U)
#define SCE_AUDIODEC_TYPE_CELP (0x1006U)

/* Maximum number of total channels */
#define SCE_AUDIODEC_AT9_MAX_CH_IN_LIBRARY (16)
/* Maximum number of streams */
#define SCE_AUDIODEC_MP3_MAX_STREAMS        (8)
#define SCE_AUDIODEC_AAC_MAX_STREAMS        (8)
#define SCE_AUDIODEC_CELP_MAX_STREAMS       (8)

/* Maximum number of channels per stream */
#define SCE_AUDIODEC_AT9_MAX_CH_IN_DECODER  (2)
#define SCE_AUDIODEC_MP3_MAX_CH_IN_DECODER  (2)
#define SCE_AUDIODEC_AAC_MAX_CH_IN_DECODER  (2)
#define SCE_AUDIODEC_CELP_MAX_CH_IN_DECODER (1)

/* Maximum number of samples */
#define SCE_AUDIODEC_AT9_MAX_SAMPLES   (256)
#define SCE_AUDIODEC_MP3_MAX_SAMPLES  (1152)
#define SCE_AUDIODEC_AAC_MAX_SAMPLES  (2048)
#define SCE_AUDIODEC_CELP_MAX_SAMPLES  (320)

/* Maximum elementary stream size */
#define SCE_AUDIODEC_AT9_MAX_ES_SIZE  (1024)
#define SCE_AUDIODEC_MP3_MAX_ES_SIZE  (1441)
#define SCE_AUDIODEC_AAC_MAX_ES_SIZE  (1792)
#define SCE_AUDIODEC_CELP_MAX_ES_SIZE   (27)

/* Extra access size of elementary stream buffer */
#define SCE_AUDIODEC_AT9_EXTRA_ACCESS_SIZE  (0)
#define SCE_AUDIODEC_MP3_EXTRA_ACCESS_SIZE  (0)
#define SCE_AUDIODEC_AAC_EXTRA_ACCESS_SIZE  (0)
#define SCE_AUDIODEC_CELP_EXTRA_ACCESS_SIZE (0)

/* Maximum number of frames to be decoded in sceAudiodecDecodeNFrames() */
#define SCE_AUDIODEC_AT9_MAX_NFRAMES  (8)
#define SCE_AUDIODEC_MP3_MAX_NFRAMES  (1)
#define SCE_AUDIODEC_AAC_MAX_NFRAMES  (1)
#define SCE_AUDIODEC_CELP_MAX_NFRAMES (1)

/* Maximum number of streams to be decoded in sceAudiodecDecodeNStreams() */
#define SCE_AUDIODEC_AT9_MAX_NSTREAMS  (6)
#define SCE_AUDIODEC_MP3_MAX_NSTREAMS  (6)
#define SCE_AUDIODEC_AAC_MAX_NSTREAMS  (6)
#define SCE_AUDIODEC_CELP_MAX_NSTREAMS (7)

/* MPEG version (MPEG specification compliant) */
#define SCE_AUDIODEC_MP3_MPEG_VERSION_2_5      (0) /* MPEG2.5 */
#define SCE_AUDIODEC_MP3_MPEG_VERSION_RESERVED (1) /* reserved */
#define SCE_AUDIODEC_MP3_MPEG_VERSION_2        (2) /* MPEG2 */
#define SCE_AUDIODEC_MP3_MPEG_VERSION_1        (3) /* MPEG1 */

/* CELP decoder default excitation mode */
#define SCE_AUDIODEC_CELP_MPE (0)
/* CELP decoder default sampling rate */
#define SCE_AUDIODEC_CELP_SAMPLING_RATE_8KHZ (8000)
/* CELP decoder bitrate definition */
#define SCE_AUDIODEC_CELP_BIT_RATE_3850BPS   (3850) /*  3850 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_4650BPS   (4650) /*  4650 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_5700BPS   (5700) /*  5700 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_6600BPS   (6600) /*  6600 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_7300BPS   (7300) /*  7300 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_8700BPS   (8700) /*  8700 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_9900BPS   (9900) /*  9900 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_10700BPS (10700) /* 10700 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_11800BPS (11800) /* 11800 bps */
#define SCE_AUDIODEC_CELP_BIT_RATE_12200BPS (12200) /* 12200 bps */

typedef struct SceAudiodecInitStreamParam {
	SceUInt32 size;         /* size of this structure */
	SceUInt32 totalStreams;
} SceAudiodecInitStreamParam;

typedef struct SceAudiodecInitChParam {
	SceUInt32 size;    /* size of this structure */
	SceUInt32 totalCh;
} SceAudiodecInitChParam;

typedef union SceAudiodecInitParam {
	SceUInt32                  size;
	SceAudiodecInitChParam     at9;
	SceAudiodecInitStreamParam mp3;
	SceAudiodecInitStreamParam aac;
	SceAudiodecInitStreamParam celp;
} SceAudiodecInitParam;

/* Information for ATRAC9(TM) */
typedef struct SceAudiodecInfoAt9 {
	SceUInt32 size;               /* size of this structure */
	SceUInt8  configData[4];      /* config data */
	SceUInt32 ch;                 /* number of channels */
	SceUInt32 bitRate;            /* bit rate */
	SceUInt32 samplingRate;       /* sampling rate */
	SceUInt32 superFrameSize;     /* super frame size */
	SceUInt32 framesInSuperFrame; /* number of frames in a super frame */
} SceAudiodecInfoAt9;

/* Information for MP3 */
typedef struct SceAudiodecInfoMp3 {
	SceUInt32 size;    /* size of this structure */
	SceUInt32 ch;      /* number of channels (mono: 1, stereo/joint stereo/two mono: 2) */
	SceUInt32 version; /* MPEG version (MPEG1: 3, MPEG2: 2, MPEG2.5: 0) */
} SceAudiodecInfoMp3;

/* Information for MPEG4 AAC-LC/HE-AAC */
typedef struct SceAudiodecInfoAac {
	SceUInt32 size;         /* size of this structure */
	SceUInt32 isAdts;       /* if ADTS, non-zero */
	SceUInt32 ch;           /* number of channels */
	SceUInt32 samplingRate; /* sampling rate */
	SceUInt32 isSbr;        /* if SBR, non-zero */
} SceAudiodecInfoAac;

/* Information for CELP */
typedef struct SceAudiodecInfoCelp {
	SceUInt32 size;           /* size of this structure */
	SceUInt32 excitationMode; /* excitation mode */
	SceUInt32 samplingRate;   /* sampling rate */
	SceUInt32 bitRate;        /* bit rate */
	SceUInt32 lostCount;      /* lost frame count */
} SceAudiodecInfoCelp;

/* Audio decoder information */
typedef union SceAudiodecInfo {
	SceUInt32           size;
	SceAudiodecInfoAt9  at9;
	SceAudiodecInfoMp3  mp3;
	SceAudiodecInfoAac  aac;
	SceAudiodecInfoCelp celp;
} SceAudiodecInfo;

/* Audio decoder control */
typedef struct SceAudiodecCtrl {
	SceUInt32       size;          /* size of this structure */
	SceInt32        handle;        /* decoder handle */
	SceUInt8        *pEs;          /* pointer to elementary stream */
	SceUInt32       inputEsSize;   /* size of elementary stream used actually (in byte) */
	SceUInt32       maxEsSize;     /* maximum size of elementary stream used (in byte) */
	void            *pPcm;         /* pointer to PCM */
	SceUInt32       outputPcmSize; /* size of PCM output actually (in byte) */
	SceUInt32       maxPcmSize;    /* maximum size of PCM output (in byte) */
	SceUInt32       wordLength;    /* PCM bit depth */
	SceAudiodecInfo *pInfo;        /* pointer to SceAudiodecInfo */
} SceAudiodecCtrl;

extern SceInt32 sceAudiodecInitLibrary(SceUInt32 codecType, SceAudiodecInitParam *pInitParam);
extern SceInt32 sceAudiodecTermLibrary(SceUInt32 codecType);
extern SceInt32 sceAudiodecCreateDecoder(SceAudiodecCtrl *pCtrl, SceUInt32 codecType);
extern SceInt32 sceAudiodecDeleteDecoder(SceAudiodecCtrl *pCtrl);
extern SceInt32 sceAudiodecDecode(SceAudiodecCtrl *pCtrl);
extern SceInt32 sceAudiodecDecodeNFrames(SceAudiodecCtrl *pCtrl, SceUInt32 nFrames);
extern SceInt32 sceAudiodecDecodeNStreams(SceAudiodecCtrl *pCtrls[], SceUInt32 nStreams);
extern SceInt32 sceAudiodecClearContext(SceAudiodecCtrl *pCtrl);
extern SceInt32 sceAudiodecGetInternalError(SceAudiodecCtrl *pCtrl, SceInt32 *pInternalError);

extern SceInt32 sceAudiodecGetContextSize(SceAudiodecCtrl *pCtrl, SceUInt32 codecType);
extern SceInt32 sceAudiodecCreateDecoderExternal(SceAudiodecCtrl *pCtrl, SceUInt32 codecType, SceUIntVAddr vaContext, SceUInt32 contextSize);
extern SceInt32 sceAudiodecDeleteDecoderExternal(SceAudiodecCtrl *pCtrl, SceUIntVAddr *pvaContext);

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
}
#endif /* defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_AUDIODEC_H_ */
