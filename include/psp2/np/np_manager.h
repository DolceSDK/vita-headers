#ifndef _DOLCESDK_PSP2_NP_NP_MANAGER_H_
#define _DOLCESDK_PSP2_NP_NP_MANAGER_H_

#include <psp2/np/np_common.h>


typedef struct SceNpManagerCacheParam {
	SceNpId npId;
	SceNpAvatarUrl avatarUrl;
} SceNpManagerCacheParam;


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int
sceNpManagerGetNpId(
	SceNpId *npId
	);

int
sceNpManagerGetAccountRegion(
	SceNpCountryCode *countryCode,
	int *languageCode
	);

int
sceNpManagerGetContentRatingFlag(
	int *isRestricted,
	int *age
	);

int
sceNpManagerGetChatRestrictionFlag(
	int *isRestricted
	);

int
sceNpManagerGetCachedParam(
	SceNpManagerCacheParam *param
	);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_MANAGER_H_ */
