#ifndef _DOLCESDK_PSP2_LIBHTTP_LIBHTTP_URL_H_
#define _DOLCESDK_PSP2_LIBHTTP_LIBHTTP_URL_H_

#include <psp2/types.h>

#define SCE_HTTP_URI_BUILD_WITH_SCHEME		0x01
#define SCE_HTTP_URI_BUILD_WITH_HOSTNAME	0x02
#define SCE_HTTP_URI_BUILD_WITH_PORT		0x04
#define SCE_HTTP_URI_BUILD_WITH_PATH		0x08
#define SCE_HTTP_URI_BUILD_WITH_USERNAME	0x10
#define SCE_HTTP_URI_BUILD_WITH_PASSWORD	0x20
#define SCE_HTTP_URI_BUILD_WITH_QUERY		0x40
#define SCE_HTTP_URI_BUILD_WITH_FRAGMENT	0x80
#define SCE_HTTP_URI_BUILD_WITH_ALL			0xFFFF


/* example "https://user:pass@foo.com:1443/var/test.cgi?test#hoge" */
typedef struct SceHttpUriElement{
	SceBool		opaque;		/* SceFalse */
	char		*scheme	;	/* "https" */
	char		*username;	/* "user" */
	char		*password;	/* "pass" */
	char		*hostname;	/* "foo.com" */
	char		*path;		/* "/var/test.cgi" */
	char		*query;		/* "?test" */
	char		*fragment;	/* "#hoge" */
	SceUShort16	port;		/*  1443 */
	SceUChar8	reserved[10];
} SceHttpUriElement;


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int sceHttpUriEscape(char *out, SceSize *require, SceSize prepare,
				 const char *in);
int sceHttpUriUnescape(char *out, SceSize *require, SceSize prepare,
				   const char *in);
int sceHttpUriParse(SceHttpUriElement *out, const char *srcUrl, void *pool,
				SceSize *require, SceSize prepare);
int sceHttpUriBuild(char *out, SceSize *require, SceSize prepare,
				const SceHttpUriElement *srcElement, SceUInt32 option);
int sceHttpUriMerge(char *mergedUrl, const char *url, const char *relativeUrl,
				SceSize *require, SceSize prepare, SceUInt32 option);
int sceHttpUriSweepPath(char *dst, const char *src, SceSize srcSize);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif	/* _DOLCESDK_PSP2_LIBHTTP_LIBHTTP_URL_H_ */

