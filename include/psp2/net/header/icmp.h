#ifndef _DOLCESDK_PSP2_NET_HEADER_ICMP_H_
#define _DOLCESDK_PSP2_NET_HEADER_ICMP_H_

#include <psp2/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct SceNetIcmpHeaderEcho {
	SceUShort16 id;
	SceUShort16 sequence;
} SceNetIcmpHeaderEcho;

typedef struct SceNetIcmpHeaderFrag {
	SceUShort16 unused;
	SceUShort16 mtu;
} SceNetIcmpHeaderFrag;

typedef union SceNetIcmpHeaderUnion {
	SceNetIcmpHeaderEcho echo;
	unsigned int gateway;
	SceNetIcmpHeaderFrag frag;
} SceNetIcmpHeaderUnion;

typedef struct SceNetIcmpHeader {
	SceUChar8 type;
#define SCE_NET_ICMP_TYPE_ECHO_REPLY           0
#define SCE_NET_ICMP_TYPE_DEST_UNREACH         3
#define SCE_NET_ICMP_TYPE_SOURCE_QUENCH        4
#define SCE_NET_ICMP_TYPE_REDIRECT             5
#define SCE_NET_ICMP_TYPE_ECHO_REQUEST         8
#define SCE_NET_ICMP_TYPE_TIME_EXCEEDED        11
#define SCE_NET_ICMP_TYPE_PARAMETER_PROBLEM    12
#define SCE_NET_ICMP_TYPE_TIMESTAMP_REQUEST    13
#define SCE_NET_ICMP_TYPE_TIMESTAMP_REPLY      14
#define SCE_NET_ICMP_TYPE_INFORMATION_REQUEST  15
#define SCE_NET_ICMP_TYPE_INFORMATION_REPLY    16
#define SCE_NET_ICMP_TYPE_ADDRESS_MASK_REQUEST 17
#define SCE_NET_ICMP_TYPE_ADDRESS_MASK_REPLY   18
	SceUChar8 code;
	/* DEST_UNREACH */
#define SCE_NET_ICMP_CODE_DEST_UNREACH_NET_UNREACH          0
#define SCE_NET_ICMP_CODE_DEST_UNREACH_HOST_UNREACH         1
#define SCE_NET_ICMP_CODE_DEST_UNREACH_PROTO_UNREACH        2
#define SCE_NET_ICMP_CODE_DEST_UNREACH_PORT_UNREACH         3
#define SCE_NET_ICMP_CODE_DEST_UNREACH_FRAG_AND_DF          4
#define SCE_NET_ICMP_CODE_DEST_UNREACH_SRC_HOST_FAILED      5
#define SCE_NET_ICMP_CODE_DEST_UNREACH_DST_NET_UNKNOWN      6
#define SCE_NET_ICMP_CODE_DEST_UNREACH_DST_HOST_UNKNOWN     7
#define SCE_NET_ICMP_CODE_DEST_UNREACH_SRC_HOST_ISOLATED    8
#define SCE_NET_ICMP_CODE_DEST_UNREACH_NET_ADMIN_PROHIBITED 9
#define SCE_NET_ICMP_CODE_DEST_UNREACH_NET_HOST_PROHIBITED  10
#define SCE_NET_ICMP_CODE_DEST_UNREACH_NET_TOS              11
#define SCE_NET_ICMP_CODE_DEST_UNREACH_HOST_TOS             12
#define SCE_NET_ICMP_CODE_TIME_EXCEEDED_TTL_EXCEEDED        0
#define SCE_NET_ICMP_CODE_TIME_EXCEEDED_FRT_EXCEEDED        1
	SceUShort16 checksum;
	SceNetIcmpHeaderUnion un;
} SceNetIcmpHeader;

#ifdef __cplusplus
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_HEADER_ICMP_H_ */

