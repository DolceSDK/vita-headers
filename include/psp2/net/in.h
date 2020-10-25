#ifndef _DOLCESDK_PSP2_NET_IN_H_
#define _DOLCESDK_PSP2_NET_IN_H_

#include <psp2/net/nettypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct SceNetInAddr {
	SceNetInAddr_t s_addr;
} SceNetInAddr;

typedef struct SceNetSockaddrIn {
	SceUChar8 sin_len;
	SceNetSaFamily_t sin_family;
	SceNetInPort_t sin_port;
	SceNetInAddr sin_addr;
	SceNetInPort_t sin_vport;
	SceChar8 sin_zero[6];
} SceNetSockaddrIn;

typedef struct SceNetIpMreq {
	SceNetInAddr imr_multiaddr;
	SceNetInAddr imr_interface;
} SceNetIpMreq;

/* address & mask */
#define SCE_NET_INADDR_ANY           ((SceUInt32)0x00000000)
#define SCE_NET_INADDR_LOOPBACK      ((SceUInt32)0x7f000001) /* 127.0.0.1 */
#define SCE_NET_INADDR_BROADCAST     ((SceUInt32)0xffffffff)
#define SCE_NET_INADDR_UNSPEC_GROUP  ((SceUInt32)0xe0000000) /* 224.0.0.0 */
#define SCE_NET_INADDR_AUTOIP        ((SceUInt32)0xa9fe0000) /* 169.254.0.0 */

#define SCE_NET_IN_CLASSD_NET        ((SceUInt32)0xf0000000)
#define SCE_NET_IN_AUTOIP_NET        ((SceUInt32)0xffff0000)

#define SCE_NET_INET_ADDRSTRLEN     16

/* multicast */
#define SCE_NET_IP_DEFAULT_MULTICAST_TTL   1
#define SCE_NET_IP_DEFAULT_MULTICAST_LOOP  1

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_IN_H_ */

