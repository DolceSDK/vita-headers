#ifndef _DOLCESDK_PSP2_LIBHTTP_LIBHTTP_COMPAT_H_
#define _DOLCESDK_PSP2_LIBHTTP_LIBHTTP_COMPAT_H_

#include <psp2/libhttp.h>

#define sceHttpEnd()									sceHttpTerm()
#define sceHttpAddExtraHeader(id, name, value, mode)	sceHttpAddRequestHeader(id, name, value, mode)
#define sceHttpDeleteHeader(id, name)					sceHttpRemoveRequestHeader(id, name)
#define sceHttpSetContentLength(id, contentLength)		sceHttpSetRequestContentLength(id, contentLength)
#define sceHttpGetAllHeader(reqId, header, headerSize)	sceHttpGetAllResponseHeaders(reqId, header, headerSize)
#define sceHttpGetContentLength(reqId, contentLength)	sceHttpGetResponseContentLength(reqId, contentLength)
#define sceHttpSetResHeaderMaxSize(id, headerSize)		sceHttpSetResponseHeaderMaxSize(id, headerSize)
#define sceHttpEnableRedirect(id)						sceHttpSetAutoRedirect(id, SCE_TRUE)
#define sceHttpDisableRedirect(id)						sceHttpSetAutoRedirect(id, SCE_FALSE)
#define sceHttpEnableCookie(id)							sceHttpSetCookieEnabled(id, SCE_TRUE)
#define sceHttpDisableCookie(id)						sceHttpSetCookieEnabled(id, SCE_FALSE)
#define sceHttpEnableAuth(id)							sceHttpSetAuthEnabled(id, SCE_TRUE)
#define sceHttpDisableAuth(id)							sceHttpSetAuthEnabled(id, SCE_FALSE)
#define sceHttpsInit(caCertNum, caList, cert, privKey)	sceHttpsLoadCert(caCertNum, caList, cert, privKey)
#define sceHttpsEnd()									sceHttpsUnloadCert()

#define sceHttpInsertRequestHeader(id, name, value)		sceHttpAddRequestHeader(id, name, value, SCE_HTTP_HEADER_ADD)

#define SCE_HTTPS_ERR_INTERNAL			SCE_HTTPS_ERROR_SSL_INTERNAL
#define SCE_HTTPS_ERR_INVALID_CERT		SCE_HTTPS_ERROR_SSL_INVALID_CERT
#define SCE_HTTPS_ERR_CN_CHECK			SCE_HTTPS_ERROR_SSL_CN_CHECK
#define SCE_HTTPS_ERR_NOT_AFTER_CHECK	SCE_HTTPS_ERROR_SSL_NOT_AFTER_CHECK
#define SCE_HTTPS_ERR_NOT_BEFORE_CHECK	SCE_HTTPS_ERROR_SSL_NOT_BEFORE_CHECK
#define SCE_HTTPS_ERR_UNKNOWN_CA		SCE_HTTPS_ERROR_SSL_UNKNOWN_CA

#define SCE_HTTP_ERROR_UNKOWN_AUTH_TYPE SCE_HTTP_ERROR_UNKNOWN_AUTH_TYPE

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

typedef SceHttpMethods SceHTTPMethods;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif	/* _DOLCESDK_PSP2_LIBHTTP_LIBHTTP_COMPAT_H_ */

