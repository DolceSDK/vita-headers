#ifndef _DOLCESDK_PSP2_NP_NP_TSS_H
#define _DOLCESDK_PSP2_NP_NP_TSS_H

#include <psp2/types.h>
#include <psp2/np/np_tus.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#if ! defined(__LANGUAGE_ASSEMBLY)

/* type definition */
#define SCE_NP_TSS_MAX_SIZE				(64  * 1024U)
#define SCE_NET_NP_TSS_MAX_SIZE			SCE_NP_TSS_MAX_SIZE
#define SCE_NP_TSS_EXTRA_SLOT_MAX_SIZE	(4 * 1024 * 1024U)

#define sceNpTssCreateTitleCtx(_commId, _passphrase, _selfNpId) sceNpTusCreateTitleCtx(_commId, _passphrase, _selfNpId)
#define sceNpTssCreateRequest(_titleCtxId) sceNpTusCreateRequest(_titleCtxId)
#define sceNpTssDeleteTitleCtx(_titleCtxId) sceNpTusDeleteTitleCtx(_titleCtxId)
#define sceNpTssDeleteRequest(_reqId) sceNpTusDeleteRequest(_reqId)

typedef SceInt32 SceNpTssSlotId;

typedef enum{
	SCE_NP_TSS_IFTYPE_IF_MODIFIED_SINCE,
	SCE_NP_TSS_IFTYPE_IF_RANGE
} SceNpTssIfType;

typedef enum {
	SCE_NP_TSS_STATUS_TYPE_OK,
	SCE_NP_TSS_STATUS_TYPE_PARTIAL,
	SCE_NP_TSS_STATUS_TYPE_NOT_MODIFIED
} SceNpTssStatusCodeType;

typedef struct SceNpTssIfModifiedSinceParam{
	SceInt32 ifType;
	SceUInt8 padding[4];
	SceRtcTick lastModified;
} SceNpTssIfModifiedSinceParam;

typedef struct SceNpTssGetDataOptParam{
	SceSize size;
	SceOff *offset;
	SceOff *lastByte;
	SceNpTssIfModifiedSinceParam *ifParam;
} SceNpTssGetDataOptParam;

typedef struct SceNpTssDataStatus{
	SceRtcTick lastModified;
	SceInt32 statusCodeType;
	SceSize contentLength;
} SceNpTssDataStatus;


/* prototype */

SceInt32	sceNpTssGetSmallStorage(
	SceInt32					reqId,
	void					*data,
	SceSize					maxSize,
	SceSize					*contentLength,
	void *option
);

SceInt32	sceNpTssGetSmallStorageAsync(
	SceInt32					reqId,
	void					*data,
	SceSize					maxSize,
	SceSize					*contentLength,
	void *option
);

SceInt32 sceNpTssGetData (
	SceInt32 reqId,
	SceNpTssSlotId slotId,
	SceNpTssDataStatus *dataStatus,
	SceSize dataStatusSize,
	void *data,
	SceSize recvSize,
	SceNpTssGetDataOptParam *option
);

SceInt32 sceNpTssGetDataAsync(
	SceInt32 reqId,
	SceNpTssSlotId slotId,
	SceNpTssDataStatus *dataStatus,
	SceSize dataStatusSize,
	void *data,
	SceSize recvSize,
	SceNpTssGetDataOptParam *option
);


#endif	/* !defined(__LANGUAGE_ASSEMBLY) */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */


#endif	/* _DOLCESDK_PSP2_NP_NP_TSS_H */
