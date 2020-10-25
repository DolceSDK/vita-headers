#ifndef _DOLCESDK_PSP2_NET_NETTYPES_H_
#define _DOLCESDK_PSP2_NET_NETTYPES_H_

#include <psp2/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef SceUInt32 SceNetInAddr_t;
typedef SceUShort16 SceNetInPort_t;
typedef SceUChar8 SceNetSaFamily_t;
typedef SceUInt32 SceNetSocklen_t;

typedef int SceNetId;

#define SCE_NET_DEBUG_NAME_LEN_MAX 31   /* non null terminated */

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_NETTYPES_H_ */

