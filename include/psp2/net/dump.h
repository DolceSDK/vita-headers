#ifndef _DOLCESDK_PSP2_NET_DUMP_H_
#define _DOLCESDK_PSP2_NET_DUMP_H_

#include <psp2/net/nettypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* flags for sceNetDumpRead */
#define SCE_NET_DUMP_PEEK      0x00000010	/* read(set) */
#define SCE_NET_DUMP_DONTWAIT  0x00000020	/* read(set) */
#define SCE_NET_DUMP_OVERFLOW  0x00000040	/* read(get) */

/* flags for sceNetSocketAbort */
#define SCE_NET_DUMP_ABORT_FLAG_PRESERVATION  0x00000001

SceNetId sceNetDumpCreate(const char *name, int len, int flags);
int sceNetDumpRead(SceNetId id, void *buf, int len, int *pflags);
int sceNetDumpDestroy(SceNetId id);
int sceNetDumpAbort(SceNetId id, int flags);

#if defined(__cplusplus)
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_DUMP_H_ */

