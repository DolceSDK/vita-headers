#ifndef _DOLCESDK_PSP2_AVCDEC_H_
#define _DOLCESDK_PSP2_AVCDEC_H_

#include <psp2/types.h>
#include <psp2/videodec.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#define SCE_AVCDEC_ERROR_INVALID_TYPE				(-2141061119) /* 0x80620001 */
#define SCE_AVCDEC_ERROR_INVALID_PARAM				(-2141061118) /* 0x80620002 */
#define SCE_AVCDEC_ERROR_OUT_OF_MEMORY				(-2141061117) /* 0x80620003 */
#define SCE_AVCDEC_ERROR_INVALID_STATE				(-2141061116) /* 0x80620004 */
#define SCE_AVCDEC_ERROR_UNSUPPORT_IMAGE_SIZE		(-2141061115) /* 0x80620005 */
#define SCE_AVCDEC_ERROR_INVALID_COLOR_FORMAT		(-2141061114) /* 0x80620006 */
#define SCE_AVCDEC_ERROR_NOT_PHY_CONTINUOUS_MEMORY	(-2141061113) /* 0x80620007 */
#define SCE_AVCDEC_ERROR_ALREADY_USED				(-2141061112) /* 0x80620008 */
#define SCE_AVCDEC_ERROR_INVALID_POINTER			(-2141061111) /* 0x80620009 */
#define SCE_AVCDEC_ERROR_ES_BUFFER_FULL				(-2141061110) /* 0x8062000A */
#define SCE_AVCDEC_ERROR_INITIALIZE					(-2141061109) /* 0x8062000B */
#define SCE_AVCDEC_ERROR_NOT_INITIALIZE				(-2141061108) /* 0x8062000C */
#define SCE_AVCDEC_ERROR_INVALID_STREAM				(-2141061107) /* 0x8062000D */
#define SCE_AVCDEC_ERROR_INVALID_ARGUMENT_SIZE		(-2141061106) /* 0x8062000E */
#define SCE_AVCDEC_ERROR_GREATER_THAN_1200_AT_LV30	(-2141061105) /* 0x8062000F */
#define SCE_AVCDEC_ERROR_INTERLACED					(-2141061104) /* 0x80620010 */
#define SCE_AVCDEC_ERROR_INVALID_PICTURE			(-2141061055) /* 0x80620041 */


typedef struct SceAvcdecQueryDecoderInfo {
	SceUInt32	horizontal;
	SceUInt32	vertical;
	SceUInt32	numOfRefFrames;

} SceAvcdecQueryDecoderInfo;

typedef struct SceAvcdecDecoderInfo {
	SceUInt32	frameMemSize;

} SceAvcdecDecoderInfo;


typedef struct SceAvcdecBuf {
	void		*pBuf;
	SceUInt32	size;
} SceAvcdecBuf;

typedef	struct SceAvcdecCtrl {
	SceUInt32		handle;
	SceAvcdecBuf	frameBuf;
} SceAvcdecCtrl;

typedef struct SceAvcdecAu {
	SceVideodecTimeStamp	pts;
	SceVideodecTimeStamp	dts;
	SceAvcdecBuf			es;
} SceAvcdecAu;


#define SCE_AVCDEC_PIXEL_RGBA8888				(0x0U)		/* A:B:G:R=8:8:8:8    32bit   U8U8U8U8_ABGR	*/
#define SCE_AVCDEC_PIXEL_RGB565					(0x1U)
#define SCE_AVCDEC_PIXEL_RGBA5551				(0x2U)
#define SCE_AVCDEC_PIXEL_BGRA8888				(0x8U)		/* A:R:G:B=8:8:8:8    32bit   U8U8U8U8_ARGB	*/
#define SCE_AVCDEC_PIXEL_YUV420_RASTER			(0x10U)		/*                            YUV420P3		*/
#define SCE_AVCDEC_PIXEL_YUV420_PACKED_RASTER	(0x20U)		/*                            YVU420P2		*/

#define SCE_AVCDEC_CSC_COEFFICIENT_DEFAULT			(0)
#define SCE_AVCDEC_CSC_COEFFICIENT_ITU601			(1)
#define SCE_AVCDEC_CSC_COEFFICIENT_ITU709			(2)
#define SCE_AVCDEC_CSC_COEFFICIENT_ITU601_FULL		(3)
#define SCE_AVCDEC_CSC_COEFFICIENT_ITU709_FULL		(4)

#define SCE_AVCDEC_OPTION_ENABLE				(1<<31)

/* For use in sceAvcdecSetDecodeMode() */
#define SCE_AVCDEC_MODE_EXTENDED				(0x80U)

/* For use in sceAvcdecSetLowDelayModeNongameapp() */
#define SCE_AVCDEC_DELAY_MODE_LOW					(0)
#define SCE_AVCDEC_DELAY_MODE_1						(2)
#define SCE_AVCDEC_DELAY_MODE_2						(4)
#define SCE_AVCDEC_DELAY_MODE_HIGH					(6)

typedef struct SceAvcdecInfo {
	SceUInt32	numUnitsInTick;
	SceUInt32	timeScale;
	SceUChar8	fixedFrameRateFlag;

	SceUChar8	aspectRatioIdc;
	SceUShort16	sarWidth;
	SceUShort16	sarHeight;

	SceUChar8	colourPrimaries;
	SceUChar8	transferCharacteristics;
	SceUChar8	matrixCoefficients;

	SceUChar8	videoFullRangeFlag;

	SceUChar8	reserved[3];

	SceUChar8	flag;
	SceUChar8	padding[2];
	SceVideodecTimeStamp	outputPts;
} SceAvcdecInfo;

typedef struct SceAvcdecFrameOptionRGBA {
	SceUInt8	alpha;
	SceUInt8	cscCoefficient;
	SceUInt8	reserved[14];
} SceAvcdecFrameOptionRGBA;

typedef union SceAvcdecFrameOption {
	SceUInt8					reserved[16];
	SceAvcdecFrameOptionRGBA	rgba;
} SceAvcdecFrameOption;


typedef struct SceAvcdecFrame {
	SceUInt32		pixelType;
	SceUInt32		framePitch;
	SceUInt32		frameWidth;
	SceUInt32		frameHeight;

	SceUInt32		horizontalSize;
	SceUInt32		verticalSize;

	SceUInt32		frameCropLeftOffset;
	SceUInt32		frameCropRightOffset;
	SceUInt32		frameCropTopOffset;
	SceUInt32		frameCropBottomOffset;

	SceAvcdecFrameOption opt;

	void			*pPicture[2];
} SceAvcdecFrame;


typedef struct SceAvcdecPicture {
	SceSize			size;
	SceAvcdecFrame	frame;
	SceAvcdecInfo	info;
} SceAvcdecPicture;

typedef struct SceAvcdecArrayPicture {
	SceUInt32				numOfOutput;
	SceUInt32				numOfElm;
	SceAvcdecPicture		**pPicture;
} SceAvcdecArrayPicture;


extern SceInt32 sceAvcdecSetDecodeMode(SceUInt32 codecType, SceInt32 mode);

extern SceInt32 sceAvcdecQueryDecoderMemSize(SceUInt32 codecType, const SceAvcdecQueryDecoderInfo *pDecoderInfo, SceAvcdecDecoderInfo *pMemInfo);
extern SceInt32 sceAvcdecCreateDecoder(SceUInt32 codecType, SceAvcdecCtrl *pCtrl, const SceAvcdecQueryDecoderInfo *pDecoderInfo);
extern SceInt32 sceAvcdecDeleteDecoder(SceAvcdecCtrl *pCtrl);

extern SceInt32 sceAvcdecDecodeAvailableSize(SceAvcdecCtrl *pCtrl);
extern SceInt32 sceAvcdecDecode(const SceAvcdecCtrl *pCtrl, const SceAvcdecAu *pAu, SceAvcdecArrayPicture *pArrayPicture);
extern SceInt32 sceAvcdecDecodeStop(const SceAvcdecCtrl *pCtrl, SceAvcdecArrayPicture *pArrayPicture );
extern SceInt32 sceAvcdecDecodeFlush(const SceAvcdecCtrl *pCtrl);

/* Internal */

extern SceInt32 sceAvcdecSetDecodeModeInternal(SceUInt32 codecType, SceInt32 mode);
extern SceInt32 sceAvcdecRegisterCallbackInternal(SceAvcdecCtrl *pCtrl, SceUID cbId, int unk);
extern SceInt32 sceAvcdecUnregisterCallbackInternal(SceAvcdecCtrl *pCtrl);
extern SceInt32 sceAvcdecUnregisterCallbackWithCbidInternal(SceAvcdecCtrl *pCtrl, SceUID cbId);

extern SceInt32 sceAvcdecQueryDecoderMemSizeInternal(SceUInt32 codecType, const SceAvcdecQueryDecoderInfo *pDecoderInfo, SceAvcdecDecoderInfo *pMemInfo);
extern SceInt32 sceAvcdecCreateDecoderInternal(SceUInt32 codecType, SceAvcdecCtrl *pCtrl, const SceAvcdecQueryDecoderInfo *pDecoderInfo);

extern SceInt32 sceAvcdecDecodeAuInternal(SceAvcdecCtrl *pCtrl, const SceAvcdecAu *pAu, int *pTimeout);
extern SceInt32 sceAvcdecDecodeGetPictureInternal(SceAvcdecCtrl *pCtrl, SceAvcdecArrayPicture *pArrayPicture, int* pTimeout);
extern SceInt32 sceAvcdecDecodeGetPictureWithWorkPictureInternal(SceAvcdecCtrl *pCtrl, SceAvcdecArrayPicture *pArrayPicture, SceAvcdecArrayPicture *pArrayWorkPicture, int* pTimeout);

/* Nongame and SceVideodecAsyncUser */

extern SceInt32 sceAvcdecSetRecoveryPointSEIMode(SceUInt32 codecType, SceInt32 mode);

extern SceInt32 sceAvcdecDecodeSetTrickModeNongameapp(SceUInt32 codecType, SceInt32 mode);
extern SceInt32 sceAvcdecSetLowDelayModeNongameapp(SceUInt32 codecType, SceInt32 mode);
extern SceInt32 sceAvcdecRegisterCallbackNongameapp(SceAvcdecCtrl *pCtrl, SceUID cbId, int unk);
extern SceInt32 sceAvcdecUnregisterCallbackNongameapp(SceAvcdecCtrl *pCtrl);
extern SceInt32 sceAvcdecUnregisterCallbackWithCbidNongameapp(SceAvcdecCtrl *pCtrl, SceUID cbId);

extern SceInt32 sceAvcdecCreateDecoderNongameapp(SceUInt32 codecType, SceAvcdecCtrl *pCtrl, const SceAvcdecQueryDecoderInfo *pDecoderInfo);
extern SceInt32 sceAvcdecQueryDecoderMemSizeNongameapp(SceUInt32 codecType, const SceAvcdecQueryDecoderInfo *pDecoderInfo, SceAvcdecDecoderInfo *pMemInfo);

extern SceInt32 sceAvcdecDecodeAuNongameapp(SceAvcdecCtrl *pCtrl, const SceAvcdecAu *pAu, int *pTimeout);
extern SceInt32 sceAvcdecDecodeGetPictureNongameapp(SceAvcdecCtrl *pCtrl, SceAvcdecArrayPicture *pArrayPicture, int* pTimeout);


#define SCE_AVCDEC_INTERLACED_STREAM_MODE_ENABLE			(0x00000001u)


#define SCE_AVCDEC_CT_TYPE_BIT_ENABLE_PIC_STRUCT		(0x80)
#define SCE_AVCDEC_CT_TYPE_BIT_ENABLE_CT_TYPE			(0x40)
#define SCE_AVCDEC_CT_TYPE_BIT_FIELD_PAIR				(0x20)
#define SCE_AVCDEC_CT_TYPE_BIT_TOP_FIELD_FIRST			(0x10)
#define SCE_AVCDEC_CT_TYPE_BIT_IDR_I_P_B_PIC_TYPE_FIELD	(0x0c)
#define SCE_AVCDEC_CT_TYPE_BIT_CT_TYPE_FIELD			(0x03)

typedef struct SceAvcdecInfoForInterlaced {
	SceUInt32	numUnitsInTick;
	SceUInt32	timeScale;
	SceUChar8	fixedFrameRateFlag;

	SceUChar8	aspectRatioIdc;
	SceUShort16	sarWidth;
	SceUShort16	sarHeight;

	SceUChar8	colourPrimaries;
	SceUChar8	transferCharacteristics;
	SceUChar8	matrixCoefficients;

	SceUChar8	videoFullRangeFlag;

	SceUChar8	picStruct[2];
	SceUChar8	ctType;

	SceUChar8	flag;
	SceUChar8	padding[2];
	SceVideodecTimeStamp	outputPts;
} SceAvcdecInfoForInterlaced;


typedef struct SceAvcdecPictureForInterlaced {
	SceSize						size;
	SceAvcdecFrame				frame;
	SceAvcdecInfoForInterlaced	info;
} SceAvcdecPictureForInterlaced;

extern SceInt32 sceAvcdecSetInterlacedStreamMode(SceUInt32 codecType, SceUInt32 flag);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_AVCDEC_H_ */

