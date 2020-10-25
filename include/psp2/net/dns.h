#ifndef _DOLCESDK_PSP2_NET_DNS_H_
#define _DOLCESDK_PSP2_NET_DNS_H_

#include <psp2/net/in.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define SCE_NET_DNS_ADDR_MAX  2

typedef struct SceNetDnsInfo {
	SceNetInAddr dns_addr[SCE_NET_DNS_ADDR_MAX];	/* network byte order */
} SceNetDnsInfo;

int sceNetSetDnsInfo(SceNetDnsInfo *info, int flags);
int sceNetClearDnsCache(int flags);

#if defined(__cplusplus)
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_DNS_H_ */

