#ifndef _DOLCESDK_PSP2_NET_EPOLL_H_
#define _DOLCESDK_PSP2_NET_EPOLL_H_

#include <psp2/net/nettypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct SceNetEpollDataExt {
	SceNetId id;
	SceUInt32 u32;
} SceNetEpollDataExt;

typedef union SceNetEpollData {
	void *ptr;
	int fd;
	SceUInt32 u32;
	SceUInt64 u64;
	SceNetEpollDataExt ext;
} SceNetEpollData;

typedef struct SceNetEpollSystemData {
	SceUInt32 system[4];
} SceNetEpollSystemData;

typedef struct SceNetEpollEvent {
	SceUInt32 events;
#define SCE_NET_EPOLLIN         0x00000001	/* IN/OUT */
#define SCE_NET_EPOLLOUT        0x00000002	/* IN/OUT */
#define SCE_NET_EPOLLERR        0x00000008	/* OUT */
#define SCE_NET_EPOLLHUP        0x00000010	/* OUT */
#define SCE_NET_EPOLLDESCID     0x00010000	/* OUT, descriptor (resolver...) */
	SceUInt32 reserved;
	SceNetEpollSystemData system;	/* system use */
	SceNetEpollData data;
} SceNetEpollEvent;

/* flags for sceNetEpollControl */
#define SCE_NET_EPOLL_CTL_ADD   1
#define SCE_NET_EPOLL_CTL_MOD   2
#define SCE_NET_EPOLL_CTL_DEL   3

/* flags for sceNetEpollAbort */
#define SCE_NET_EPOLL_ABORT_FLAG_PRESERVATION  0x00000001

SceNetId sceNetEpollCreate(const char *name, int flags);
int sceNetEpollControl(SceNetId eid, int op, SceNetId id,
	SceNetEpollEvent *event);
int sceNetEpollWait(SceNetId eid, SceNetEpollEvent *events,
	int maxevents, int timeout);
int sceNetEpollWaitCB(SceNetId eid, SceNetEpollEvent *events,
	int maxevents, int timeout);
int sceNetEpollDestroy(SceNetId eid);
int sceNetEpollAbort(SceNetId eid, int flags);

#if defined(__cplusplus)
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_EPOLL_H_ */

