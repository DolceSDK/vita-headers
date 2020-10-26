#ifndef _DOLCESDK_PSP2_LIBHTTP_COOKIE_H_
#define _DOLCESDK_PSP2_LIBHTTP_COOKIE_H_

#include <psp2/types.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

typedef SceInt32 (*SceHttpCookieRecvCallback)(
	SceInt32 request,
	const char *url,
	const char *cookieHeader,
	SceSize headerLen,
	void *userArg);
typedef SceInt32 (*SceHttpCookieSendCallback)(
	SceInt32 request,
	const char *url,
	const char *cookieHeader,
	void *userArg);

typedef struct SceHttpCookieStats{
	SceSize		currentInuseSize;
	SceUInt32	currentInuseNum;
	SceSize		maxInuseSize;
	SceUInt32	maxInuseNum;
	SceUInt32	removedNum;
	SceInt32	reserved;
} SceHttpCookieStats;

SceInt32 sceHttpSetCookieEnabled(SceInt32 id, SceBool enable);
SceInt32 sceHttpGetCookieEnabled(SceInt32 id, SceBool *enable);
SceInt32 sceHttpGetCookie(const char *url, char *cookie, SceSize *required, SceSize prepared, SceBool secure);
SceInt32 sceHttpAddCookie(const char *url, const char *cookie, SceSize cookieLength);
SceInt32 sceHttpSetCookieRecvCallback(SceInt32 id, SceHttpCookieRecvCallback cbfunc, void *userArg);
SceInt32 sceHttpSetCookieSendCallback(SceInt32 id, SceHttpCookieSendCallback cbfunc, void *userArg);
SceInt32 sceHttpCookieExport(void *buffer, SceSize bufferSize, SceSize *exportSize);
SceInt32 sceHttpCookieImport(const void *buffer, SceSize bufferSize);
SceInt32 sceHttpCookieFlush(void);
SceInt32 sceHttpSetCookieTotalMaxSize(SceUInt32 size);
SceInt32 sceHttpSetCookieMaxSize(SceUInt32 size);
SceInt32 sceHttpSetCookieMaxNum(SceUInt32 num);
SceInt32 sceHttpSetCookieMaxNumPerDomain(SceUInt32 num);
SceInt32 sceHttpGetCookieStats(SceHttpCookieStats* stats);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif	/* _DOLCESDK_PSP2_LIBHTTP_COOKIE_H_ */
