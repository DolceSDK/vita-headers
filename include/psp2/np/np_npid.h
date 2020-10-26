#ifndef _DOLCESDK_NP_NP_NPID_H_
#define _DOLCESDK_NP_NP_NPID_H_

#include <psp2/types.h>

#define SCE_NP_ONLINEID_MIN_LENGTH			3
#define SCE_NP_ONLINEID_MAX_LENGTH			16

/* Online ID */
typedef struct SceNpOnlineId {
	char data[SCE_NP_ONLINEID_MAX_LENGTH];
	char term;
	char dummy[3];
} SceNpOnlineId;


/* NP ID */
typedef struct SceNpId {
	SceNpOnlineId handle;
	SceUChar8 opt[8];
	SceUChar8 reserved[8];
} SceNpId;

#endif /* _DOLCESDK_NP_NP_NPID_H_ */
