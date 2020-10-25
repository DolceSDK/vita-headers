#ifndef _DOLCESDK_PSP2_NET_INET_H_
#define _DOLCESDK_PSP2_NET_INET_H_

#include <psp2/net/nettypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

const char *sceNetInetNtop(int af, const void *src, char *dst,
	SceNetSocklen_t size);
int sceNetInetPton(int af, const char *src, void *dst);

SceUInt64 sceNetHtonll(SceUInt64 host64);
SceUInt32 sceNetHtonl(SceUInt32 host32);
SceUShort16 sceNetHtons(SceUShort16 host16);
SceUInt64 sceNetNtohll(SceUInt64 net64);
SceUInt32 sceNetNtohl(SceUInt32 net32);
SceUShort16 sceNetNtohs(SceUShort16 net16);

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_INET_H_ */

