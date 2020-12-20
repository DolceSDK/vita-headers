#ifndef _DOLCESDK_PSP2_NP_H_
#define _DOLCESDK_PSP2_NP_H_

#include <psp2/np/np_auth.h>
#include <psp2/np/np_common.h>
#include <psp2/np/np_error.h>
#include <psp2/np/np_manager.h>
#include <psp2/np/np_basic.h>
#include <psp2/np/np_bandwidth_test.h>
#include <psp2/np/np_lookup.h>
#include <psp2/np/np_ranking.h>
#include <psp2/np/np_matching2.h>
#include <psp2/np/np_activity.h>
#include <psp2/np/np_trophy.h>
#include <psp2/np/np_commerce2.h>
#include <psp2/np/np_message.h>
#include <psp2/np/np_tus.h>
#include <psp2/np/np_tss.h>
#include <psp2/np/np_word_filter.h>
#include <psp2/np/np_party.h>
#include <psp2/np/np_signaling.h>
#include <psp2/np/np_webapi.h>
#include <psp2/np/np_auth_oauth.h>

typedef struct SceNpOptParam {
	SceSize optParamSize;
} SceNpOptParam;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int
sceNpInit(
	const SceNpCommunicationConfig *commConf,
	SceNpOptParam *opt
	);

int
sceNpTerm(
	void
	);

int sceNpCheckCallback(
	void
	);

typedef enum {
	SCE_NP_SERVICE_STATE_UNKNOWN = 0,
	SCE_NP_SERVICE_STATE_SIGNED_OUT,
	SCE_NP_SERVICE_STATE_SIGNED_IN,
	SCE_NP_SERVICE_STATE_ONLINE
} SceNpServiceState;

int sceNpGetServiceState(
	SceNpServiceState *state
	);

typedef void(*SceNpServiceStateCallback)(
	SceNpServiceState state,
	int retCode,
	void *userdata
	);

int sceNpRegisterServiceStateCallback(
	SceNpServiceStateCallback callback,
	void *userdata
	);

int sceNpUnregisterServiceStateCallback(
	void
	);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */



#endif /* _DOLCESDK_PSP2_NP_H_ */
