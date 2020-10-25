#ifndef _DOLCESDK_PSP2_NET_HEADER_IP_H_
#define _DOLCESDK_PSP2_NET_HEADER_IP_H_

#include <psp2/net/in.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct SceNetIpHeaderIpVerHl {
#if defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN
	SceUChar8 ver:4;
	SceUChar8 hl:4;
#else
	SceUChar8 hl:4;
	SceUChar8 ver:4;
#endif	/* BYTE_ORDER */
} SceNetIpHeaderIpVerHl;

typedef union SceNetIpHeaderUnion {
	SceNetIpHeaderIpVerHl ip_ver_hl;
	SceUChar8 ver_hl;
} SceNetIpHeaderUnion;

typedef struct SceNetIpHeader {
	SceNetIpHeaderUnion un;
#define SCE_NET_IPVERSION   4
	SceUChar8 ip_tos;
	SceUShort16 ip_len;
	SceUShort16 ip_id;
	SceUShort16 ip_off;
#define SCE_NET_IP_RF       0x8000
#define SCE_NET_IP_DF       0x4000
#define SCE_NET_IP_MF       0x2000
#define SCE_NET_IP_OFFMASK  0x1fff
	SceUChar8 ip_ttl;
	SceUChar8 ip_p;
	SceUShort16 ip_sum;
	SceNetInAddr ip_src;
	SceNetInAddr ip_dst;
} SceNetIpHeader;

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_HEADER_IP_H_ */

