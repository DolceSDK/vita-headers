#ifndef _DOLCESDK_PSP2_NET_ETHER_H_
#define _DOLCESDK_PSP2_NET_ETHER_H_

#include <psp2/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define SCE_NET_ETHER_ADDR_LEN	6
#define SCE_NET_ETHER_ADDRSTRLEN	18

typedef struct SceNetEtherAddr {
	SceUChar8 data[SCE_NET_ETHER_ADDR_LEN];
} SceNetEtherAddr;

int sceNetEtherStrton(const char *str, SceNetEtherAddr *n);
int sceNetEtherNtostr(const SceNetEtherAddr *n, char *str, SceSize len);
int sceNetGetMacAddress(SceNetEtherAddr *addr, int flags);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_ETHER_H_ */

