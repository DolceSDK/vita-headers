#ifndef _DOLCESDK_PSP2_NP_NP_WORD_FILTER_H_
#define _DOLCESDK_PSP2_NP_NP_WORD_FILTER_H_

#include <psp2/np/np_common.h>

#define SCE_NP_WORD_FILTER_MAX_CTX_NUM	(32)
#define SCE_NP_WORD_FILTER_MAX_REQUEST_NUM	(32)
#define SCE_NP_WORD_FILTER_CENSOR_COMMENT_MAXLEN		(1024)
#define SCE_NP_WORD_FILTER_SANITIZE_COMMENT_MAXLEN	(1024)
#define SCE_NP_WORD_FILTER_TIMEOUT_NO_EFFECT	(0)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int sceNpWordFilterInit(
	SceBool		usesAsync,
	SceInt32	threadPriority,
	SceInt32	cpuAffinityMask,
	void		*option);

int	sceNpWordFilterTerm(void);

int	sceNpWordFilterCreateTitleCtx(
	const SceNpCommunicationId  *titleId,
	const SceNpId  *selfNpId
);

int	sceNpWordFilterDeleteTitleCtx (
	SceInt32 titleCtxId
);

int	sceNpWordFilterCreateRequest(
	SceInt32 titleCtxId
);

int	sceNpWordFilterDeleteRequest (
	SceInt32 reqId
);

int sceNpWordFilterAbortRequest (
	SceInt32 reqId
);
int sceNpWordFilterSetTimeout(
	SceInt32  id,
	SceInt32  resolveRetry,
	SceUInt32 resolveTimeout,
	SceUInt32 connTimeout,
	SceUInt32 sendTimeout,
	SceUInt32 recvTimeout
);

int	sceNpWordFilterWaitAsync (
	SceInt32 reqId,
	SceInt32 *result
);

int	sceNpWordFilterPollAsync (
	SceInt32 reqId,
	SceInt32 *result
);

SceInt32 sceNpWordFilterCensorComment (
	SceInt32	reqId,
	const char *comment,
	void *option
);

SceInt32 sceNpWordFilterCensorCommentAsync (
	SceInt32	reqId,
	const char *comment,
	void *option
);

SceInt32 sceNpWordFilterSanitizeComment (
	SceInt32	reqId,
	const char *comment,
	char *sanitizedComment,
	void *option
);

SceInt32 sceNpWordFilterSanitizeCommentAsync (
	SceInt32	reqId,
	const char *comment,
	char *sanitizedComment,
	void *option
);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_WORD_FILTER_H_ */
