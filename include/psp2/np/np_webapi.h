#ifndef _DOLCESDK_PSP2_NP_NP_WEBAPI_H_
#define _DOLCESDK_PSP2_NP_NP_WEBAPI_H_

#include <stdint.h>
#include <stddef.h>
#include <psp2/np/np_common.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#define SCE_NP_WEBAPI_CONTENT_TYPE_APPLICATION_JSON_UTF8 "application/json; charset=utf-8"

typedef enum SceNpWebApiHttpMethod {
	SCE_NP_WEBAPI_HTTP_METHOD_GET,
	SCE_NP_WEBAPI_HTTP_METHOD_POST,
	SCE_NP_WEBAPI_HTTP_METHOD_PUT,
	SCE_NP_WEBAPI_HTTP_METHOD_DELETE
} SceNpWebApiHttpMethod;

typedef struct SceNpWebApiContentParameter {
	size_t contentLength;
	const char *pContentType;
	uint8_t reserved[16];
} SceNpWebApiContentParameter;

typedef struct SceNpWebApiHttpHeader {
	char *pName;
	char *pValue;
} SceNpWebApiHttpHeader;

typedef struct SceNpWebApiMultipartPartParameter {
	SceNpWebApiHttpHeader *pHeaders;
	size_t headerNum;
	size_t contentLength;
} SceNpWebApiMultipartPartParameter;

#define SCE_NP_WEBAPI_PUSH_EVENT_DATA_TYPE_LEN_MAX 64
typedef struct SceNpWebApiPushEventDataType {
	char val[SCE_NP_WEBAPI_PUSH_EVENT_DATA_TYPE_LEN_MAX + 1];
} SceNpWebApiPushEventDataType;

#define SCE_NP_WEBAPI_EXTD_PUSH_EVENT_EXTD_DATA_KEY_LEN_MAX 32
typedef struct SceNpWebApiExtdPushEventExtdDataKey {
	char val[SCE_NP_WEBAPI_EXTD_PUSH_EVENT_EXTD_DATA_KEY_LEN_MAX + 1];
} SceNpWebApiExtdPushEventExtdDataKey;

typedef struct SceNpWebApiExtdPushEventFilterParameter {
	SceNpWebApiPushEventDataType dataType;
	char padding[3];
	SceNpWebApiExtdPushEventExtdDataKey *pExtdDataKey;
	size_t extdDataKeyNum;
} SceNpWebApiExtdPushEventFilterParameter;

typedef struct SceNpWebApiExtdPushEventExtdData {
	SceNpWebApiExtdPushEventExtdDataKey extdDataKey;
	char padding[3];
	char *pData;
	size_t dataLen;
} SceNpWebApiExtdPushEventExtdData;

#define SCE_NP_WEBAPI_NP_SERVICE_NAME_NONE NULL

typedef void (*SceNpWebApiExtdPushEventCallback)(
	int32_t callbackId,
	const char *pNpServiceName,
	SceNpServiceLabel npServiceLabel,
	const SceNpPeerAddress *pTo,
	const SceNpPeerAddress *pFrom,
	const SceNpWebApiPushEventDataType *pDataType,
	const char *pData,
	size_t dataLen,
	const SceNpWebApiExtdPushEventExtdData *pExtdData,
	size_t extdDataNum,
	void *pUserArg
	);

typedef struct SceNpWebApiMemoryPoolStats {
	size_t poolSize;
	size_t maxInuseSize;
	size_t currentInuseSize;
	int32_t reserved;
} SceNpWebApiMemoryPoolStats;

typedef struct SceNpWebApiResponseInformationOption {
	int32_t httpStatus;
	char *pErrorObject;
	size_t errorObjectSize;
	size_t responseDataSize;
} SceNpWebApiResponseInformationOption;

/* -----------------------------------------------
 * Initialize/Terminate
 * ----------------------------------------------- */
int32_t sceNpWebApiInitialize(
	size_t poolSize
	);

int32_t
sceNpWebApiTerminate(
	void
	);

/* -----------------------------------------------
 * Request
 * ----------------------------------------------- */
int32_t
sceNpWebApiCreateRequest(
	const char *pApiGroup,
	const char *pPath,
	SceNpWebApiHttpMethod method,
	const SceNpWebApiContentParameter *pContentParameter,
	int64_t *pRequestId
	);

int32_t
sceNpWebApiDeleteRequest(
	int64_t requestId
	);

int32_t
sceNpWebApiAbortRequest(
	int64_t requestId
	);

int32_t
sceNpWebApiSendRequest2(
	int64_t requestId,
	const void *pData,
	size_t dataSize,
	SceNpWebApiResponseInformationOption *pRespInfoOption
	);

int32_t sceNpWebApiReadData(
	int64_t requestId,
	void *pData,
	size_t size
	);

int32_t
sceNpWebApiAddHttpRequestHeader(
	int64_t requestId,
	const char *pFieldName,
	const char *pValue
	);

int32_t
sceNpWebApiGetHttpResponseHeaderValueLength(
	int64_t requestId,
	const char *pFieldName,
	size_t *pValueLength
	);

int32_t
sceNpWebApiGetHttpResponseHeaderValue(
	int64_t requestId,
	const char *pFieldName,
	char *pValue,
	size_t valueSize
	);

/* -----------------------------------------------
 * Utilities
 * ----------------------------------------------- */
int32_t
sceNpWebApiUtilityParseNpId(
	const char *pJsonNpId,
	SceNpId *pNpId
	);

/* -----------------------------------------------
 * Memory
 * ----------------------------------------------- */
int32_t
sceNpWebApiGetMemoryPoolStats(
	SceNpWebApiMemoryPoolStats *pCurrentStat
	);

/* -----------------------------------------------
 * Handle
 * ----------------------------------------------- */
int32_t
sceNpWebApiCreateHandle(
	);

int32_t
sceNpWebApiDeleteHandle(
	int32_t handleId
	);

int32_t
sceNpWebApiAbortHandle(
	int32_t handleId
	);

/* -----------------------------------------------
 * Check Callback
 * ----------------------------------------------- */
int32_t
sceNpWebApiCheckCallback(
    void
	);

/* -----------------------------------------------
 * NP Title ID
 * ----------------------------------------------- */
int
sceNpWebApiSetNpTitleId(
	const SceNpTitleId *pTitleId,
	const SceNpTitleSecret *pTitleSecret
	);

int
sceNpWebApiGetNpTitleId(
	SceNpTitleId *pTitleId,
	SceNpTitleSecret *pTitleSecret
	);

/* -----------------------------------------------
 * Multi Part
 * ----------------------------------------------- */
int32_t
sceNpWebApiCreateMultipartRequest(
	const char *pApiGroup,
	const char *pPath,
	SceNpWebApiHttpMethod method,
	int64_t *pRequestId
	);

int32_t
sceNpWebApiSendMultipartRequest2(
	int64_t requestId,
	int32_t partIndex,
	const void *pData,
	size_t dataSize,
	SceNpWebApiResponseInformationOption *pRespInfoOption
	);

int32_t
sceNpWebApiSetMultipartContentType(
	int64_t requestId,
	const char *pTypeName,
	const char *pBoundary
	);

int32_t
sceNpWebApiAddMultipartPart(
	int64_t requestId,
	const SceNpWebApiMultipartPartParameter *pParam,
	int32_t *pIndex
	);

/* -----------------------------------------------
 * Extd Push Event
 * ----------------------------------------------- */
int32_t
sceNpWebApiCreateExtdPushEventFilter(
	int32_t handleId,
	const char *pNpServiceName,
	SceNpServiceLabel npServiceLabel,
	const SceNpWebApiExtdPushEventFilterParameter *pFilterParam,
	size_t filterParamNum
	);

int32_t
sceNpWebApiDeleteExtdPushEventFilter(
	int32_t filterId
	);

int32_t
sceNpWebApiRegisterExtdPushEventCallback(
	int32_t filterId,
	SceNpWebApiExtdPushEventCallback cbFunc,
	void *pUserArg
	);

int32_t
sceNpWebApiUnregisterExtdPushEventCallback(
	int32_t callbackId
	);

/* -----------------------------------------------
 * Push Event
 * ----------------------------------------------- */
typedef void (*SceNpWebApiPushEventCallback)(
	int32_t callbackId,
	const SceNpPeerAddress *pTo,
	const SceNpPeerAddress *pFrom,
	const SceNpWebApiPushEventDataType *pDataType,
	const char *pData,
	size_t dataLen,
	void *pUserArg
	);

int32_t
sceNpWebApiCreatePushEventFilter(
	const SceNpWebApiPushEventDataType *pDataType,
	size_t dataTypeNum
	);

int32_t
sceNpWebApiDeletePushEventFilter(
	int32_t filterId
	);

int32_t
sceNpWebApiRegisterPushEventCallback(
	int32_t filterId,
	SceNpWebApiPushEventCallback cbFunc,
	void *pUserArg
	);

int32_t
sceNpWebApiUnregisterPushEventCallback(
	int32_t callbackId
	);

/* -----------------------------------------------
 * Service Push Event
 * ----------------------------------------------- */
typedef void (*SceNpWebApiServicePushEventCallback)(
	int32_t callbackId,
	const char *pNpServiceName,
	SceNpServiceLabel npServiceLabel,
	const SceNpPeerAddress *pTo,
	const SceNpPeerAddress *pFrom,
	const SceNpWebApiPushEventDataType *pDataType,
	const char *pData,
	size_t dataLen,
	void *pUserArg
	);

int32_t
sceNpWebApiCreateServicePushEventFilter(
	int32_t handleId,
	const char *pNpServiceName,
	SceNpServiceLabel npServiceLabel,
	const SceNpWebApiPushEventDataType *pDataType,
	size_t dataTypeNum
	);

int32_t
sceNpWebApiDeleteServicePushEventFilter(
	int32_t filterId
	);

int32_t
sceNpWebApiRegisterServicePushEventCallback(
	int32_t filterId,
	SceNpWebApiServicePushEventCallback cbFunc,
	void *pUserArg
	);

int32_t
sceNpWebApiUnregisterServicePushEventCallback(
	int32_t callbackId
	);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_WEBAPI_H_ */
