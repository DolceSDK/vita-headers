#ifndef _DOLCESDK_PSP2_COMMON_DIALOG_TYPES_H_
#define _DOLCESDK_PSP2_COMMON_DIALOG_TYPES_H_

#include <psp2/types.h>
#include <psp2/gxm/structs.h>
#include <psp2/appmgr.h>

typedef enum {
	SCE_COMMON_DIALOG_STATUS_NONE		= 0,
	SCE_COMMON_DIALOG_STATUS_RUNNING	= 1,
	SCE_COMMON_DIALOG_STATUS_FINISHED	= 2
}	SceCommonDialogStatus;

typedef enum {
	SCE_COMMON_DIALOG_RESULT_OK,
	SCE_COMMON_DIALOG_RESULT_USER_CANCELED,
	SCE_COMMON_DIALOG_RESULT_ABORTED
} SceCommonDialogResult;

typedef enum {
	SCE_COMMON_DIALOG_FOCUS_INVALID = 0,
	SCE_COMMON_DIALOG_FOCUS_VISIBLE,
	SCE_COMMON_DIALOG_FOCUS_INVISIBLE
} SceCommonDialogFocusStatus;

typedef struct SceCommonDialogRenderTargetInfo {
	ScePVoid depthSurfaceData;
	ScePVoid colorSurfaceData;
	SceGxmColorSurfaceType surfaceType;
	SceGxmColorFormat colorFormat;
	SceUInt32 width;
	SceUInt32 height;
	SceUInt32 strideInPixels;
	SceUInt8 reserved[32];
} SceCommonDialogRenderTargetInfo;

typedef struct SceCommonDialogUpdateParam {
	SceCommonDialogRenderTargetInfo renderTarget;
	SceGxmSyncObject *displaySyncObject;
	SceUInt8 reserved[32];
} SceCommonDialogUpdateParam;

typedef struct SceCommonDialogInfobarParam {
	SceInt32 visibility;
	SceInt32 color;
	SceInt32 transparency;
	SceUInt8 reserved[32];
} SceCommonDialogInfobarParam;

typedef struct SceCommonDialogColor {
	SceUInt8 r;
	SceUInt8 g;
	SceUInt8 b;
	SceUInt8 a;
} SceCommonDialogColor;

typedef SceCommonDialogColor SceCommonDialogBgColor;

typedef struct SceCommonDialogParam {
	SceCommonDialogInfobarParam* infobarParam;
	SceCommonDialogColor* bgColor;
	SceCommonDialogColor* dimmerColor;
	SceUInt8 reserved[60];
	SceUInt32 magic;
} SceCommonDialogParam;

#define SCE_COMMON_DIALOG_MAGIC_NUMBER 0xC0D1A109

#endif /* _DOLCESDK_PSP2_COMMON_DIALOG_TYPES_H_ */
