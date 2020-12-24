#ifndef _DOLCESDK_PSP2_COMMON_DIALOG_COMMON_API_H_
#define _DOLCESDK_PSP2_COMMON_DIALOG_COMMON_API_H_

#include <psp2/common_dialog/error.h>
#include <psp2/common_dialog/types.h>
#include <psp2/sdk_version.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

SceInt32 sceCommonDialogUpdate(const SceCommonDialogUpdateParam *updateParam);

SceBool sceCommonDialogIsRunning();

SceUID sceCommonDialogGetWorkerThreadId();

static inline
void _sceCommonDialogSetMagicNumber(SceCommonDialogParam *param)
{
	param->magic = SCE_COMMON_DIALOG_MAGIC_NUMBER + (SceUInt32)param;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_COMMON_DIALOG_COMMON_API_H_ */
