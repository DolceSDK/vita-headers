#ifndef _DOLCESDK_PSP2_NET_SOCKINFO_H_
#define _DOLCESDK_PSP2_NET_SOCKINFO_H_

#include <psp2/net/id.h>
#include <psp2/net/in.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct SceNetSockInfo {
	char name[SCE_NET_DEBUG_NAME_LEN_MAX + 1];
	SceUID pid;
	SceNetId s;
	SceInt8 socket_type;
	SceInt8 policy;
	SceInt16 reserved16;
	int recv_queue_length;
	int send_queue_length;
	SceNetInAddr local_adr;
	SceNetInAddr remote_adr;
	SceNetInPort_t local_port;
	SceNetInPort_t remote_port;
	SceNetInPort_t local_vport;
	SceNetInPort_t remote_vport;
	int state;
#define SCE_NET_SOCKINFO_STATE_UNKNOWN      0
#define SCE_NET_SOCKINFO_STATE_CLOSED       1
#define SCE_NET_SOCKINFO_STATE_OPENED       2
#define SCE_NET_SOCKINFO_STATE_LISTEN       3
#define SCE_NET_SOCKINFO_STATE_SYN_SENT     4
#define SCE_NET_SOCKINFO_STATE_SYN_RECEIVED 5
#define SCE_NET_SOCKINFO_STATE_ESTABLISHED  6
#define SCE_NET_SOCKINFO_STATE_FIN_WAIT_1   7
#define SCE_NET_SOCKINFO_STATE_FIN_WAIT_2   8
#define SCE_NET_SOCKINFO_STATE_CLOSE_WAIT   9
#define SCE_NET_SOCKINFO_STATE_CLOSING      10
#define SCE_NET_SOCKINFO_STATE_LAST_ACK     11
#define SCE_NET_SOCKINFO_STATE_TIME_WAIT    12
	int flags;
#define SCE_NET_SOCKINFO_F_SELF             0x00000001
#define SCE_NET_SOCKINFO_F_KERNEL           0x00000002
#define SCE_NET_SOCKINFO_F_OTHERS           0x00000004
#define SCE_NET_SOCKINFO_F_RECV_WAIT        0x00010000
#define SCE_NET_SOCKINFO_F_SEND_WAIT        0x00020000
#define SCE_NET_SOCKINFO_F_RECV_EWAIT       0x00040000
#define SCE_NET_SOCKINFO_F_SEND_EWAIT       0x00080000
#define SCE_NET_SOCKINFO_F_WAKEUP_SIGNAL    0x00100000
#define SCE_NET_SOCKINFO_F_ALL              0x001F0007
	int reserved[8];
} SceNetSockInfo;

/* flags for sceNetGetSockInfo */

int sceNetGetSockInfo(SceNetId s, SceNetSockInfo *info, int n, int flags);
int sceNetGetSockIdInfo(SceNetFdSet *fds, int sockinfoflags, int flags);

#if defined(__cplusplus)
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_SOCKINFO_H_ */

