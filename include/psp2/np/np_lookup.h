#ifndef _DOLCESDK_PSP2_NP_NP_LOOKUP_H_
#define _DOLCESDK_PSP2_NP_NP_LOOKUP_H_

#include <psp2/np/np_common.h>

#define SCE_NP_LOOKUP_MAX_CTX_NUM	(32)
#define SCE_NP_LOOKUP_MAX_REQUEST_NUM	(32)
#define SCE_NP_LOOKUP_TIMEOUT_NO_EFFECT	(0)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int sceNpLookupInit(
	SceBool		usesAsync,
	SceInt32	threadPriority,
	SceInt32	cpuAffinityMask,
	void		*option);

int	sceNpLookupTerm(void);

int	sceNpLookupCreateTitleCtx(
	const SceNpCommunicationId  *titleId,
	const SceNpId  *selfNpId
);

int	sceNpLookupDeleteTitleCtx (
	SceInt32 titleCtxId
);
/* for compatibility */
#define sceNpLookupDestroyTitleCtx(id)			sceNpLookupDeleteTitleCtx(id)

int	sceNpLookupCreateRequest(
	SceInt32 titleCtxId
);
/* for compatibility */
#define sceNpLookupCreateTransactionCtx(id)		sceNpLookupCreateRequest(id)

int	sceNpLookupDeleteRequest (
	SceInt32 reqId
);
/* for compatibility */
#define sceNpLookupDestroyTransactionCtx(id)	sceNpLookupDeleteRequest(id)

int sceNpLookupAbortRequest (
	SceInt32 reqId
);
/* for compatibility */
#define sceNpLookupAbortTransaction(id)			sceNpLookupAbortRequest(id)

int sceNpLookupSetTimeout(
	SceInt32  id,
	SceInt32  resolveRetry,
	SceUInt32 resolveTimeout,
	SceUInt32 connTimeout,
	SceUInt32 sendTimeout,
	SceUInt32 recvTimeout
);

int	sceNpLookupWaitAsync (
	SceInt32 reqId,
	SceInt32 *result
);

int	sceNpLookupPollAsync (
	SceInt32 reqId,
	SceInt32 *result
);

int	sceNpLookupNpId(
	SceInt32			reqId,
	const SceNpOnlineId	*onlineId,
	SceNpId				*npId,
	void				*option
);

int	sceNpLookupNpIdAsync(
	SceInt32			reqId,
	const SceNpOnlineId	*onlineId,
	SceNpId				*npId,
	void				*option
);

int	sceNpLookupUserProfile(
	SceInt32				reqId,
	SceInt32				avatarSizeType,
	const SceNpId			*npId,
	SceNpUserInformation	*userInfo,
	SceNpAboutMe			*aboutMe,
	SceNpMyLanguages		*languages,
	SceNpCountryCode		*countryCode,
	void					*avatarImageData,
	SceSize					avatarImageDataMaxSize,
	SceSize					*avatarImageDataSize,
	void					*option
);

int	sceNpLookupUserProfileAsync(
	SceInt32				reqId,
	SceInt32				avatarSizeType,
	const SceNpId			*npId,
	SceNpUserInformation	*userInfo,
	SceNpAboutMe			*aboutMe,
	SceNpMyLanguages		*languages,
	SceNpCountryCode		*countryCode,
	void					*avatarImageData,
	SceSize					avatarImageDataMaxSize,
	SceSize					*avatarImageDataSize,
	void					*option
);

int	sceNpLookupAvatarImage(
	SceInt32				reqId,
	const SceNpAvatarUrl	*avatarUrl,
	SceNpAvatarImage		*avatarImage,
	void					*option
);

int	sceNpLookupAvatarImageAsync(
	SceInt32				reqId,
	const SceNpAvatarUrl	*avatarUrl,
	SceNpAvatarImage		*avatarImage,
	void					*option
);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_LOOKUP_H_ */
