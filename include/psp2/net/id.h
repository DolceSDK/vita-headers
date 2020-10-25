#ifndef _DOLCESDK_PSP2_NET_ID_H_
#define _DOLCESDK_PSP2_NET_ID_H_

#include <psp2/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define SCE_NET_ID_SOCKET_MIN      0
#define SCE_NET_ID_SOCKET_MAX      1023

typedef SceUInt32 SceNetIdMask;
#define SCE_NET_NBITS       (sizeof(SceNetIdMask) * 8)
#define SCE_NET_NBITS_SHIFT 5
#define SCE_NET_NBITS_MASK	(SCE_NET_NBITS - 1)

#define SCE_NET_ID_SET(n, p, min_id, max_id) \
	if ((n) >= (min_id) && (n) <= (max_id)) { \
		((p)->bits[(SceUInt32)((n) - (min_id)) >> SCE_NET_NBITS_SHIFT] \
		    |= (SceUInt32)(1 << ((SceUInt32)((n) - (min_id)) & \
		    SCE_NET_NBITS_MASK))); \
	}
#define SCE_NET_ID_CLR(n, p, min_id, max_id) \
	if ((n) >= (min_id) && (n) <= (max_id)) { \
		((p)->bits[(SceUInt32)((n) - (min_id)) >> SCE_NET_NBITS_SHIFT] \
		    &= (SceUInt32)~(1 << ((SceUInt32)((n) - (min_id)) & \
		    SCE_NET_NBITS_MASK))); \
	}
#define SCE_NET_ID_ISSET(n, p, min_id, max_id) \
	((p)->bits[(SceUInt32)((n) - (min_id)) >> SCE_NET_NBITS_SHIFT] \
	    & (SceUInt32)(1 << ((SceUInt32)((n) - (min_id)) & SCE_NET_NBITS_MASK)))
#define SCE_NET_ID_ZERO(p, id_size) do { \
	SceNetIdMask *__bits = (p)->bits; \
	unsigned int __i; \
	for (__i = 0; __i < ((id_size) >> SCE_NET_NBITS_SHIFT); __i++) { \
		__bits[__i] = 0; \
	} \
} while (0)

/* socket */
#define SCE_NET_FD_SETSIZE \
	(SCE_NET_ID_SOCKET_MAX - SCE_NET_ID_SOCKET_MIN + 1)

typedef struct SceNetFdSet {
	SceNetIdMask bits[SCE_NET_FD_SETSIZE >> SCE_NET_NBITS_SHIFT];
} SceNetFdSet;

#define SCE_NET_FD_SET(n, p) \
	SCE_NET_ID_SET(n, p, \
	    (SceNetId)SCE_NET_ID_SOCKET_MIN, (SceNetId)SCE_NET_ID_SOCKET_MAX)
#define SCE_NET_FD_CLR(n, p) \
	SCE_NET_ID_CLR(n, p, \
	    (SceNetId)SCE_NET_ID_SOCKET_MIN, (SceNetId)SCE_NET_ID_SOCKET_MAX)
#define SCE_NET_FD_ISSET(n, p) \
	SCE_NET_ID_ISSET(n, p, \
	    (SceNetId)SCE_NET_ID_SOCKET_MIN, (SceNetId)SCE_NET_ID_SOCKET_MAX)
#define SCE_NET_FD_ZERO(p) \
	SCE_NET_ID_ZERO(p, SCE_NET_FD_SETSIZE)

#if defined(__cplusplus)
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_ID_H_ */

