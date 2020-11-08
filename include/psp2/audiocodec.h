#ifndef _DOLCESDK_PSP2_AUDIOCODEC_H_
#define _DOLCESDK_PSP2_AUDIOCODEC_H_

#include <psp2/audiodec.h>

/* Error definition */
#define SCE_AUDIOCODEC_ERROR_API_FAIL                     (0x8000 + SCE_AUDIODEC_ERROR_API_FAIL)
#define SCE_AUDIOCODEC_ERROR_INVALID_TYPE                 (0x8000 + SCE_AUDIODEC_ERROR_INVALID_TYPE)
#define SCE_AUDIOCODEC_ERROR_INVALID_INIT_PARAM           (0x8000 + SCE_AUDIODEC_ERROR_INVALID_INIT_PARAM)
#define SCE_AUDIOCODEC_ERROR_ALREADY_INITIALIZED          (0x8000 + SCE_AUDIODEC_ERROR_ALREADY_INITIALIZED)
#define SCE_AUDIOCODEC_ERROR_OUT_OF_MEMORY                (0x8000 + SCE_AUDIODEC_ERROR_OUT_OF_MEMORY)
#define SCE_AUDIOCODEC_ERROR_NOT_INITIALIZED              (0x8000 + SCE_AUDIODEC_ERROR_NOT_INITIALIZED)
#define SCE_AUDIOCODEC_ERROR_A_HANDLE_IN_USE              (0x8000 + SCE_AUDIODEC_ERROR_A_HANDLE_IN_USE)
#define SCE_AUDIOCODEC_ERROR_ALL_HANDLES_IN_USE           (0x8000 + SCE_AUDIODEC_ERROR_ALL_HANDLES_IN_USE)
#define SCE_AUDIOCODEC_ERROR_INVALID_PTR                  (0x8000 + SCE_AUDIODEC_ERROR_INVALID_PTR)
#define SCE_AUDIOCODEC_ERROR_INVALID_HANDLE               (0x8000 + SCE_AUDIODEC_ERROR_INVALID_HANDLE)
#define SCE_AUDIOCODEC_ERROR_NOT_HANDLE_IN_USE            (0x8000 + SCE_AUDIODEC_ERROR_NOT_HANDLE_IN_USE)
#define SCE_AUDIOCODEC_ERROR_CH_SHORTAGE                  (0x8000 + SCE_AUDIODEC_ERROR_CH_SHORTAGE)
#define SCE_AUDIOCODEC_ERROR_INVALID_WORD_LENGTH          (0x8000 + SCE_AUDIODEC_ERROR_INVALID_WORD_LENGTH)
#define SCE_AUDIOCODEC_ERROR_INVALID_SIZE                 (0x8000 + SCE_AUDIODEC_ERROR_INVALID_SIZE)
#define SCE_AUDIOCODEC_ERROR_UNSUPPORTED                  (0x8000 + SCE_AUDIODEC_ERROR_UNSUPPORTED)
#define SCE_AUDIOCODEC_ERROR_INVALID_NFRAMES              (0x8000 + SCE_AUDIODEC_ERROR_INVALID_NFRAMES)
#define SCE_AUDIOCODEC_ERROR_INVALID_NSTREAMS             (0x8000 + SCE_AUDIODEC_ERROR_INVALID_NSTREAMS)
#define SCE_AUDIOCODEC_ERROR_DIFFERENT_TYPES              (0x8000 + SCE_AUDIODEC_ERROR_DIFFERENT_TYPES)
#define SCE_AUDIOCODEC_ERROR_SAME_HANDLES                 (0x8000 + SCE_AUDIODEC_ERROR_SAME_HANDLES)
#define SCE_AUDIOCODEC_ERROR_BUSY                         (0x8000 + SCE_AUDIODEC_ERROR_BUSY)

/* Error of ATRAC9 */
/* 0x807F2000 - 0x807F27FF */
#define SCE_AUDIOCODEC_AT9_ERROR_INVALID_CONFIG           (0x8000 + SCE_AUDIODEC_AT9_ERROR_INVALID_CONFIG)
/* Error of MP3 */
/* 0x807F2800 - 0x807F2FFF */
#define SCE_AUDIOCODEC_MP3_ERROR_INVALID_CH               (0x8000 + SCE_AUDIODEC_MP3_ERROR_INVALID_CH)
#define SCE_AUDIOCODEC_MP3_ERROR_INVALID_MPEG_VERSION     (0x8000 + SCE_AUDIODEC_MP3_ERROR_INVALID_MPEG_VERSION)
/* Error of AAC */
/* 0x807F3000 - 0x807F37FF */
#define SCE_AUDIOCODEC_AAC_ERROR_INVALID_CH               (0x8000 + SCE_AUDIODEC_AAC_ERROR_INVALID_CH)
/* Error of CELP */
/* 0x807F3800 - 0x807F3FFF */
#define SCE_AUDIOCODEC_CELP_ERROR_INVALID_CONFIG          (0x8000 + SCE_AUDIODEC_CELP_ERROR_INVALID_CONFIG)

#define SCE_AUDIOCODEC_ATX        (0x00001000) // AT3PLUS/ATRAC-X
#define SCE_AUDIOCODEC_AT3        (0x00001001)
#define SCE_AUDIOCODEC_MP3        (0x00001002)
#define SCE_AUDIOCODEC_AAC        (0x00001003)
#define SCE_AUDIOCODEC_AT9        (0x00001004)

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum SceAudiocodecAacFormat {
	SCE_AUDIOCODEC_AAC_FORMAT_MPEG4,
	SCE_AUDIOCODEC_AAC_FORMAT_ADIF,
	SCE_AUDIOCODEC_AAC_FORMAT_ADTS
} SceAudiocodecAacFormat;

typedef struct SceAudiocodecInfoAac
{
	SceAudiocodecAacFormat format;
	SceUInt32 unk_24; //only used if format = 2, otherwise ignored
	SceUInt32 samplingRate;
	SceUInt32 isSbr;
	char unk[0x30]; //[out] more used here
} SceAudiocodecInfoAac;

typedef struct SceAudiocodecInfoMp3
{
	SceUInt32 frameSize; //for VBR - avg frame size
	SceUInt32 unk_24; //0, 1 or 9999, for decode can be 0
	SceUInt32 unk_28; //usually 3, for decode can be 0
	SceUInt32 unk_2C; //usually 0
	SceUInt32 bitrateIndex; //maybe, for decode can be 0
	char res[0x34];
} SceAudiocodecInfoMp3;

typedef struct SceAudiocodecInfoAt9
{
	SceUInt32 dwVersionInfo; //located at offset 0x30 in AT9 header
	char res[0x44]; //[out] more used here;
} SceAudiocodecInfoAt9;

typedef struct SceAudiocodecInfoAtx
{
	SceUInt8 codecParam1; //located at offset 0x22 in EA3 header (.oma and .aa3) and at offset 0x2 of format-specific part (AT3 header) of files with RIFF header (.at3)
	SceUInt8 codecParam2; //located at offset 0x23 in EA3 header (.oma and .aa3) and at offset 0x3 of format-specific part (AT3 header) of files with RIFF header (.at3)
	SceUInt16 reserved; //not used
	int unk_24;
	int unk_28;
	int unk_2C;
	int unk_30;
	int unk_34;
	SceUInt32 inputEsSize;
	char res[0x2C]; //[out] more used here;
} SceAudiocodecInfoAtx;

typedef struct SceAudiocodecInfoAt3
{
	SceUInt32 codecParam; //return value of sceAudiocodecGetAt3Config()
	char res[0x44]; //[out] more used here;
} SceAudiocodecInfoAt3;

typedef struct SceAudiocodecOutputAt9 {
	void* pPcmL;
	void* pPcmR;
	int chNum;
} SceAudiocodecOutputAt9;

typedef struct SceAudiocodecCtrl
{
	SceInt32 reserved_00; //not used
	void* pWorkMem;
	SceSize neededWorkMem;
	SceInt32 unk_atx_0C; //only used for atx, usually 1
	void* pEs;
	SceUInt32 inputEsSize;

	union {
		void* pPcm;
		SceAudiocodecOutputAt9* pPcmAt9; //only used for at9
	};

	SceUInt32 outputPcmSize; //not used for atx and at3

	union {
		SceAudiocodecInfoAt9 at9;
		SceAudiocodecInfoMp3 mp3;
		SceAudiocodecInfoAac aac;
		SceAudiocodecInfoAtx atx;
		SceAudiocodecInfoAt3 at3;
	};
} SceAudiocodecCtrl;

SceInt32 sceAudiocodecQueryMemSize(SceAudiocodecCtrl* pCtrl, SceUInt32 codecType);
SceInt32 sceAudiocodecInit(SceAudiocodecCtrl* pCtrl, SceUInt32 codecType);
SceInt32 sceAudiocodecDecode(SceAudiocodecCtrl* pCtrl, SceUInt32 codecType);

SceInt32 sceAudiocodecQueryPcmSize(SceAudiocodecCtrl* pCtrl, SceUInt32 codecType, SceSize* pSize);
SceInt32 sceAudiocodecQueryMaxPcmSize(SceAudiocodecCtrl* pCtrl, SceUInt32 codecType, SceSize* pSize);
SceInt32 sceAudiocodecValidate(SceAudiocodecCtrl* pCtrl, SceUInt32 codecType);

/**
 * Get configuration for ATRAC3 decoder. For PSP2 only 4, 6, 0xB, 0xE, 0xF return values are valid
 *
 * @param[out] cmode - probably channel configuration (mono/stereo/joint stereo)
 * @param[out] nbytes - unknown
 *
 * @return configuration value on success, < 0 on error.
*/
static inline
SceInt32 sceAudiocodecGetAt3Config(SceUInt32 cmode, SceUInt32 nbytes)
{
	if ((cmode == 0) && (nbytes == 0x100)) {
		return 0;
	}
	if ((cmode == 1) && (nbytes == 0x100)) {
		return 1;
	}
	if ((cmode == 0) && (nbytes == 0xd4)) {
		return 2;
	}
	if ((cmode == 1) && (nbytes == 0xd4)) {
		return 3;
	}
	if ((cmode == 0) && (nbytes == 0xc0)) {
		return 4;
	}
	if ((cmode == 1) && (nbytes == 0xc0)) {
		return 5;
	}
	if ((cmode == 0) && (nbytes == 0x98)) {
		return 6;
	}
	if ((cmode == 1) && (nbytes == 0x98)) {
		return 7;
	}
	if ((cmode == 0) && (nbytes == 0x88)) {
		return 8;
	}
	if ((cmode == 1) && (nbytes == 0x88)) {
		return 9;
	}
	if ((cmode == 0) && (nbytes == 0x60)) {
		return 10;
	}
	if ((cmode == 1) && (nbytes == 0x60)) {
		return 0xb;
	}
	if ((cmode == 1) && (nbytes == 0x44)) {
		return 0xc;
	}
	if ((cmode == 1) && (nbytes == 0x30)) {
		return 0xd;
	}
	if ((cmode == 2) && (nbytes == 0xc0)) {
		return 0xe;
	}
	if ((cmode == 2) && (nbytes == 0x98)) {
		return 0xf;
	}
	return -1;
}

#ifdef	__cplusplus
}
#endif

#endif /* _DOLCESDK_PSP2_AUDIOCODEC_H_ */
