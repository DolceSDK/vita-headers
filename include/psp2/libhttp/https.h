#ifndef _DOLCESDK_PSP2_LIBHTTP_HTTPS_H_
#define _DOLCESDK_PSP2_LIBHTTP_HTTPS_H_

#include <psp2/libssl.h>

typedef enum {
	SCE_HTTPS_SSLV23,
	SCE_HTTPS_SSLV2,
	SCE_HTTPS_SSLV3,
	SCE_HTTPS_TLSV1
} SceHttpSslVersion;

typedef struct SceHttpsData {
	char *ptr;
	SceSize size;
} SceHttpsData;

typedef struct SceHttpsCaList {
	SceSslCert **caCerts;
	SceInt32 caNum;
} SceHttpsCaList;

typedef SceInt32 (*SceHttpsCallback)(
	unsigned int verifyEsrr,
	SceSslCert * const sslCert[],
	int certNum,
	void *userArg);

#define SCE_HTTPS_FLAG_SERVER_VERIFY		(0x01U)
#define SCE_HTTPS_FLAG_CLIENT_VERIFY		(0x02U)
#define SCE_HTTPS_FLAG_CN_CHECK				(0x04U)
#define SCE_HTTPS_FLAG_NOT_AFTER_CHECK		(0x08U)
#define SCE_HTTPS_FLAG_NOT_BEFORE_CHECK		(0x10U)
#define SCE_HTTPS_FLAG_KNOWN_CA_CHECK		(0x20U)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

SceInt32 sceHttpsLoadCert(SceInt32 caCertNum,
					 const SceHttpsData **caList,
					 const SceHttpsData	*cert,
					 const SceHttpsData *privKey);
SceInt32 sceHttpsUnloadCert(void);
SceInt32 sceHttpsEnableOption(SceUInt32 sslFlags);
SceInt32 sceHttpsDisableOption(SceUInt32 sslFlags);
SceInt32 sceHttpsEnableOption2(SceInt32 id, SceUInt32 sslFlags);
SceInt32 sceHttpsDisableOption2(SceInt32 id, SceUInt32 sslFlags);
SceInt32 sceHttpsGetSslError(SceInt32 id, SceInt32 *errNum, SceUInt32 *detail);
SceInt32 sceHttpsSetSslCallback(SceInt32 id, SceHttpsCallback cbfunc, void *userArg);
SceInt32 sceHttpsGetCaList(SceHttpsCaList* caList);
SceInt32 sceHttpsFreeCaList(SceHttpsCaList* caList);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */


#endif	/* _DOLCESDK_PSP2_LIBHTTP_HTTPS_H_ */
