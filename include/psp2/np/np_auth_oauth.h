#ifndef _DOLCESDK_PSP2_NP_NP_AUTH_OAUTH_H_
#define _DOLCESDK_PSP2_NP_NP_AUTH_OAUTH_H_

#include <psp2/np/np_common.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

//
// Note:
// To use fuctions in this header, the application code has to link libSceNpManager_stub.a.
//

typedef struct SceNpAuthGetAuthorizationCodeParameter {
	SceSize size;
	const SceNpClientId *pClientId;
	const SceChar8 *pScope;
} SceNpAuthGetAuthorizationCodeParameter;

typedef int SceNpAuthOAuthRequestId;

SceNpAuthOAuthRequestId
sceNpAuthCreateOAuthRequest(
    void
	);

int
sceNpAuthDeleteOAuthRequest(
    SceNpAuthOAuthRequestId reqId
	);

int
sceNpAuthAbortOAuthRequest(
    SceNpAuthOAuthRequestId reqId
    );

int
sceNpAuthGetAuthorizationCode(
    SceNpAuthOAuthRequestId reqId,
	const SceNpAuthGetAuthorizationCodeParameter *param,
	SceNpAuthorizationCode *authCode,
	int *issuerId
    );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_AUTH_OAUTH_H_ */
