#ifndef _DOLCESDK_PSP2_NET_NETEMU_H_
#define _DOLCESDK_PSP2_NET_NETEMU_H_

#include <psp2/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct SceNetEmulationData {
	SceUShort16 drop_rate;           /* index:+0   0-100 % (1%) */
	SceUShort16 drop_duration;       /* index:+2   0-8000 ms (1ms) */
	SceUShort16 pass_duration;       /* index:+4   0-8000 ms (1ms) */
	SceUShort16 delay_time;          /* index:+6   0-8000 ms (1ms) */
	SceUShort16 delay_jitter;        /* index:+8   0-delay_time ms (1ms) */
	SceUShort16 order_rate;          /* index:+10  0-100 % (1%) */
	SceUShort16 order_delay_time;    /* index:+12  0-8000 ms (1ms) */
	SceUShort16 duplication_rate;    /* index:+14  0-100 % (1%) */
	SceUInt32 bps_limit;             /* index:+16  0, 1024-1G bps (1bps) */
	SceUShort16 lower_size_limit;    /* index:+20  0-upper_size_limit bytes */
	SceUShort16 upper_size_limit;    /* index:+22  lower_size_limit-1500 */
	SceUInt32 system_policy_pattern; /* index:+24  system */
	SceUInt32 game_policy_pattern;   /* index:+28  game */
	SceUShort16 policy_flags[64];    /* index:+32  each policy */
	SceUChar8 reserved[64];          /* index:+128 */
} SceNetEmulationData;	/* sizeof(SceNetEmulationData) = 224 */

typedef struct SceNetEmulationParam {
	SceUShort16 version;             /* index:0   IN, 0 means the latest */
	SceUShort16 option_number;       /* index:2   IN  */
	SceUShort16 current_version;     /*           OUT */
	SceUShort16 result;              /*           OUT */
	SceUInt32 flags;                 /* index:8   IN/OUT */
#define SCE_NET_EMULATION_PARAM_FLAGS_BPS_LIMIT_SHORT_TIME        (0x00000001)
#define SCE_NET_EMULATION_PARAM_FLAGS_API                         (0x00000100)
#define SCE_NET_EMULATION_PARAM_FLAGS_DEBUG                       (0x00000200)
#define SCE_NET_EMULATION_PARAM_FLAGS_HOSTTOOL                    (0x00000400)
	SceUInt32 reserved1;
	SceNetEmulationData send;        /* index:16  IN */
	SceNetEmulationData recv;        /* index:240 IN */
	SceUInt32 seed;                  /* index:464 IN */
	SceUChar8 reserved[44];          /* index:468 */
} SceNetEmulationParam;	/* sizeof(SceNetEmulationParam) = 512 */

/* flags for sceNetEmulation{Set,Get}() */
#define SCE_NET_EMULATION_FLAG_ETH0        0x00000001
#define SCE_NET_EMULATION_FLAG_WLAN0       0x00000002

int sceNetEmulationSet(SceNetEmulationParam *param, int flags);
int sceNetEmulationGet(SceNetEmulationParam *param, int flags);

#if defined(__cplusplus)
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_NETEMU_H_ */

