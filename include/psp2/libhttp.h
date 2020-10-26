#ifndef _DOLCESDK_PSP2_LIBHTTP_H_
#define _DOLCESDK_PSP2_LIBHTTP_H_

#include <psp2/types.h>

#include <psp2/libhttp/libhttp_common.h>
#include <psp2/libhttp/libhttp_error.h>
#include <psp2/libhttp/methods.h>
#include <psp2/libhttp/status_code.h>
#include <psp2/libhttp/https.h>
#include <psp2/libhttp/libhttp_url.h>
#include <psp2/libhttp/libhttp_compat.h>
#include <psp2/libhttp/cookie.h>

#define SCE_HTTP_DEFAULT_RESOLVER_TIMEOUT		(1 * 1000 * 1000U)
#define SCE_HTTP_DEFAULT_RESOLVER_RETRY			(5U)
#define SCE_HTTP_DEFAULT_CONNECT_TIMEOUT		(30* 1000 * 1000U)
#define SCE_HTTP_DEFAULT_SEND_TIMEOUT			(120* 1000 * 1000U)
#define SCE_HTTP_DEFAULT_RECV_TIMEOUT			(120* 1000 * 1000U)
#define SCE_HTTP_DEFAULT_RECV_BLOCK_SIZE		(1500U)
#define SCE_HTTP_DEFAULT_RESPONSE_HEADER_MAX	(5000U)
#define SCE_HTTP_DEFAULT_REDIRECT_MAX			(6U)
#define SCE_HTTP_DEFAULT_TRY_AUTH_MAX			(6U)

#define SCE_HTTP_INVALID_ID						0

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

typedef SceInt32 (*SceHttpAuthInfoCallback)(
	SceInt32 request,
	SceHttpAuthType authType,
	const char *realm,
	char *username,
	char *password,
	SceBool needEntity,
	SceUChar8 **entityBody,
	SceSize *entitySize,
	SceBool *save,
	void *userArg);
typedef SceInt32 (*SceHttpRedirectCallback)(
	SceInt32 request,
	SceInt32 statusCode,
	SceInt32 *method,
	const char *location,
	void *userArg);

typedef struct SceHttpMemoryPoolStats{
	SceSize		poolSize;
	SceSize		maxInuseSize;
	SceSize		currentInuseSize;
	SceInt32	reserved;
} SceHttpMemoryPoolStats;

SceInt32 sceHttpInit(SceSize	poolSize);
SceInt32 sceHttpTerm(void);
SceInt32 sceHttpGetMemoryPoolStats(SceHttpMemoryPoolStats* currentStat);

SceInt32 sceHttpCreateTemplate(const char *userAgent, SceInt32 httpVer, SceBool autoProxyConf);
SceInt32 sceHttpDeleteTemplate(SceInt32 tmplId);
SceInt32 sceHttpCreateConnection(SceInt32 tmplId, const char *serverName, const char *scheme, SceUShort16 port, SceBool enableKeepalive);
SceInt32 sceHttpCreateConnectionWithURL(SceInt32 tmplId, const char *url, SceBool enableKeepalive);
SceInt32 sceHttpDeleteConnection(SceInt32 connId);
SceInt32 sceHttpCreateRequest(SceInt32 connId, SceInt32 method, const char *path, SceULong64	contentLength);
SceInt32 sceHttpCreateRequest2(SceInt32 connId, const char* method, const char *path, SceULong64 contentLength);
SceInt32 sceHttpCreateRequestWithURL(SceInt32 connId, SceInt32 method, const char *url, SceULong64 contentLength);
SceInt32 sceHttpCreateRequestWithURL2(SceInt32 connId, const char* method, const char *url, SceULong64 contentLength);
SceInt32 sceHttpDeleteRequest(SceInt32 reqId);
SceInt32 sceHttpSetResponseHeaderMaxSize(SceInt32 id, SceSize headerSize);
/* SceInt32 sceHttpSetRecvBlockSize(SceInt32 id, SceSize blockSize); */
SceInt32 sceHttpSetRequestContentLength(SceInt32 id, SceULong64 contentLength);
SceInt32 sceHttpSetInflateGZIPEnabled(SceInt32 id, SceBool isEnable);

SceInt32 sceHttpSendRequest(SceInt32 reqId, const void *postData, SceSize size);
SceInt32 sceHttpAbortRequest(SceInt32 reqId);
SceInt32 sceHttpGetResponseContentLength(SceInt32 reqId, SceULong64 *contentLength);
SceInt32 sceHttpGetStatusCode(SceInt32 reqId, SceInt32 *statusCode);
SceInt32 sceHttpGetAllResponseHeaders(SceInt32 reqId, char **header, SceSize *headerSize);
SceInt32 sceHttpReadData(SceInt32 reqId, void *data, SceSize size);
SceInt32 sceHttpAddRequestHeader(SceInt32 id, const char *name, const char *value, SceUInt32 mode);
SceInt32 sceHttpRemoveRequestHeader(SceInt32 id, const char *name);

SceInt32 sceHttpParseResponseHeader(const char *header, SceSize headerLen, const char *fieldStr, const char **fieldValue, SceSize *valueLen);
SceInt32 sceHttpParseStatusLine(const char *statusLine, SceSize lineLen, SceInt32 *httpMajorVer, SceInt32 *httpMinorVer, SceInt32 *responseCode, const char **reasonPhrase, SceSize *phraseLen);

SceInt32 sceHttpSetAuthInfoCallback(SceInt32 id, SceHttpAuthInfoCallback cbfunc, void *userArg);
SceInt32 sceHttpSetAuthEnabled(SceInt32 id, SceBool enable);
SceInt32 sceHttpGetAuthEnabled(SceInt32 id, SceBool *enable);
SceInt32 sceHttpAuthCacheFlush(void);
SceInt32 sceHttpSetRedirectCallback(SceInt32 id, SceHttpRedirectCallback cbfunc, void *userArg);
SceInt32 sceHttpSetAutoRedirect(SceInt32 id, SceBool enable);
SceInt32 sceHttpGetAutoRedirect(SceInt32 id, SceBool *enable);
SceInt32 sceHttpRedirectCacheFlush(void);
SceInt32 sceHttpSetResolveTimeOut(SceInt32 id, SceUInt32 usec);
SceInt32 sceHttpSetResolveRetry(SceInt32 id, SceInt32 retry);
SceInt32 sceHttpSetConnectTimeOut(SceInt32 id, SceUInt32 usec);
SceInt32 sceHttpSetSendTimeOut(SceInt32 id, SceUInt32 usec);
SceInt32 sceHttpSetRecvTimeOut(SceInt32 id, SceUInt32 usec);

SceInt32 sceHttpGetLastErrno(SceInt32 reqId, SceInt32* errNum);

typedef void* SceHttpEpollHandle;

#define SCE_HTTP_NB_EVENT_IN			0x00000001
#define SCE_HTTP_NB_EVENT_OUT			0x00000002
#define SCE_HTTP_NB_EVENT_SOCK_ERR		0x00000008
#define SCE_HTTP_NB_EVENT_HUP			0x00000010
#define SCE_HTTP_NB_EVENT_ICM			0x00000020
#define SCE_HTTP_NB_EVENT_RESOLVED		0x00010000
#define SCE_HTTP_NB_EVENT_RESOLVER_ERR	0x00020000

typedef struct SceHttpNBEvent {
	SceUInt32	events;
	SceUInt32	eventDetail;
	SceInt32	id;
	void*		userArg;
} SceHttpNBEvent;

SceInt32 sceHttpSetNonblock(SceInt32 id, SceBool enable);
SceInt32 sceHttpGetNonblock(SceInt32 id, SceBool *enable);
SceInt32 sceHttpCreateEpoll(SceHttpEpollHandle* eh);
SceInt32 sceHttpSetEpoll(SceInt32 id, SceHttpEpollHandle eh, void *userArg);
SceInt32 sceHttpUnsetEpoll(SceInt32 id);
SceInt32 sceHttpGetEpoll(SceInt32 id, SceHttpEpollHandle* eh, void **userArg);
SceInt32 sceHttpDestroyEpoll(SceHttpEpollHandle eh);
SceInt32 sceHttpWaitRequest(SceHttpEpollHandle eh, SceHttpNBEvent* nbev, int maxevents, int timeout);
SceInt32 sceHttpWaitRequestCB(SceHttpEpollHandle eh, SceHttpNBEvent* nbev, int maxevents, int timeout);
SceInt32 sceHttpAbortWaitRequest(SceHttpEpollHandle eh);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */


#endif	/* _DOLCESDK_PSP2_LIBHTTP_H_ */
