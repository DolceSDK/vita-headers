#ifndef _DOLCESDK_PSP2_NP_NP_BANDWIDTH_TEST_H_
#define _DOLCESDK_PSP2_NP_NP_BANDWIDTH_TEST_H_

#include <psp2/types.h>

#define SCE_NP_BANDWIDTH_TEST_THREAD_STACK_SIZE (32 * 1024)
#define SCE_NP_BANDWIDTH_TEST_LEAST_HTTP_POOL_SIZE (16 * 1024)

typedef struct SceNpBandwidthTestResult {
	double uploadBps;
	double downloadBps;
	int result;
	char padding[4];
} SceNpBandwidthTestResult;

#define SCE_NP_BANDWIDTH_TEST_STATUS_NONE      0
#define SCE_NP_BANDWIDTH_TEST_STATUS_RUNNING   1
#define SCE_NP_BANDWIDTH_TEST_STATUS_FINISHED  2

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int sceNpBandwidthTestInitStart(SceInt32 initPriority, SceInt32 cpuAffinityMask);
int sceNpBandwidthTestGetStatus(void);
int sceNpBandwidthTestShutdown(SceNpBandwidthTestResult *result);
int sceNpBandwidthTestAbort(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_BANDWIDTH_TEST_H_ */
