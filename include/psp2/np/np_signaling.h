#ifndef _DOLCESDK_PSP2_NP_NP_SIGNALING_H_
#define _DOLCESDK_PSP2_NP_NP_SIGNALING_H_

#include <psp2/net.h>
#include <psp2/np/np_common.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/*
 * Np Signaling Context
 */
#define SCE_NP_SIGNALING_CTX_MAX						8

/*
 * Np Signaling Event
 */
#define SCE_NP_SIGNALING_EVENT_DEAD						0
#define SCE_NP_SIGNALING_EVENT_ESTABLISHED				1
#define SCE_NP_SIGNALING_EVENT_NETINFO_ERROR			2
#define SCE_NP_SIGNALING_EVENT_NETINFO_RESULT			3
#define SCE_NP_SIGNALING_EVENT_PEER_ACTIVATED			10
#define SCE_NP_SIGNALING_EVENT_PEER_DEACTIVATED			11
#define SCE_NP_SIGNALING_EVENT_MUTUAL_ACTIVATED			12

/* for compatibility with PS3 */
#define SCE_NP_SIGNALING_EVENT_EXT_PEER_ACTIVATED		SCE_NP_SIGNALING_EVENT_PEER_ACTIVATED
#define SCE_NP_SIGNALING_EVENT_EXT_PEER_DEACTIVATED		SCE_NP_SIGNALING_EVENT_PEER_DEACTIVATED
#define SCE_NP_SIGNALING_EVENT_EXT_MUTUAL_ACTIVATED		SCE_NP_SIGNALING_EVENT_MUTUAL_ACTIVATED

/*
 * Np Connection Status
 */
#define SCE_NP_SIGNALING_CONN_STATUS_INACTIVE			0
#define SCE_NP_SIGNALING_CONN_STATUS_PENDING			1
#define SCE_NP_SIGNALING_CONN_STATUS_ACTIVE				2

/*
 * Np Connection Info
 */
#define SCE_NP_SIGNALING_CONN_INFO_RTT					1
#define SCE_NP_SIGNALING_CONN_INFO_BANDWIDTH			2
#define SCE_NP_SIGNALING_CONN_INFO_PEER_NPID			3
#define SCE_NP_SIGNALING_CONN_INFO_PEER_ADDRESS			4
#define SCE_NP_SIGNALING_CONN_INFO_MAPPED_ADDRESS		5
#define SCE_NP_SIGNALING_CONN_INFO_PACKET_LOSS			6

/*
 * Np Signaling Context Option
 */
#define SCE_NP_SIGNALING_CTX_OPT_BANDWIDTH_PROBE		1

#define SCE_NP_SIGNALING_CTX_OPT_BANDWIDTH_PROBE_ENABLE		1
#define SCE_NP_SIGNALING_CTX_OPT_BANDWIDTH_PROBE_DISABLE	0

typedef union SceNpSignalingConnectionInfo {
	SceUInt32 rtt;
	SceUInt32 bandwidth;
	SceNpId npId;
	struct {
		SceNetInAddr addr;
		SceNetInPort_t port;
		SceUChar8 padding[2];
	} address;
	SceUInt32 packet_loss;
} SceNpSignalingConnectionInfo;

/*
 * Np Signaling Handler
 */
typedef void (*SceNpSignalingHandler)(
	SceUInt32 ctxId,
	SceUInt32 subjectId,
	int event,
	int errorCode,
	void *arg
	);

/*
 * Np Signaling API
 */
#define SCE_NP_SIGNALING_POOLSIZE_DEFAULT (128 * 1024) // 128 KiB
#define SCE_NP_SIGNALING_THREAD_PRIORITY_DEFAULT SCE_KERNEL_DEFAULT_PRIORITY_USER
#define SCE_NP_SIGNALING_THREAD_STACK_SIZE_DEFAULT (16 * 1024) // 16 KiB

int
sceNpSignalingInit(
	SceSize poolSize,
	SceInt32 threadPriority,
	SceInt32 cpuAffinityMask,
	SceSize threadStackSize
	);

int
sceNpSignalingTerm(
	void
	);

int
sceNpSignalingCreateCtx(
	const SceNpId *npId,
	SceNpSignalingHandler handler,
	void *arg,
	SceUInt32 *ctxId
	);

int
sceNpSignalingDestroyCtx(
	SceUInt32 ctxId
	);

int
sceNpSignalingActivateConnection(
	SceUInt32 ctxId,
	const SceNpId *npId,
	SceUInt32 *connId
	);

int
sceNpSignalingDeactivateConnection(
	SceUInt32 ctxId,
	SceUInt32 connId
	);

int
sceNpSignalingTerminateConnection(
	SceUInt32 ctxId,
	SceUInt32 connId
	);

int
sceNpSignalingGetConnectionStatus(
	SceUInt32 ctxId,
	SceUInt32 connId,
	int *connStatus,
	SceNetInAddr *peerAddr,
	SceNetInPort_t *peerPort
	);

int
sceNpSignalingGetConnectionInfo(
	SceUInt32 ctxId,
	SceUInt32 connId,
	int code,
	SceNpSignalingConnectionInfo *info
	);

int
sceNpSignalingGetConnectionFromNpId(
	SceUInt32 ctxId,
	const SceNpId *npId,
	SceUInt32 *connId
	);

int
sceNpSignalingGetConnectionFromPeerAddress(
	SceUInt32 ctxId,
	SceNetInAddr peerAddr,
	SceNetInPort_t peerPort,
	SceUInt32 *connId
	);

int
sceNpSignalingSetCtxOpt(
	SceUInt32 ctxId,
	int optname,
	int optval
	);

int
sceNpSignalingGetCtxOpt(
	SceUInt32 ctxId,
	int optname,
	int *optval
	);

/*
 * Np Signaling NetInfo
 */

typedef struct SceNpSignalingNetInfo {
	size_t size;
	SceNetInAddr local_addr;
	SceNetInAddr mapped_addr;
	int nat_status;
} SceNpSignalingNetInfo;

/* nat staus */
#define SCE_NP_SIGNALING_NETINFO_NAT_STATUS_UNKNOWN		0
#define SCE_NP_SIGNALING_NETINFO_NAT_STATUS_TYPE1		1
#define SCE_NP_SIGNALING_NETINFO_NAT_STATUS_TYPE2		2
#define SCE_NP_SIGNALING_NETINFO_NAT_STATUS_TYPE3		3

/*
 * Np Signaling NetInfo API
 */

int
sceNpSignalingGetLocalNetInfo(
	SceUInt32 ctxId,
	SceNpSignalingNetInfo *netinfo
	);

int
sceNpSignalingGetPeerNetInfo(
	SceUInt32 ctxId,
	const SceNpId *npId,
	SceUInt32 *reqId
	);

int
sceNpSignalingCancelPeerNetInfo(
	SceUInt32 ctxId,
	SceUInt32 reqId
	);

int
sceNpSignalingGetPeerNetInfoResult(
	SceUInt32 ctxId,
	SceUInt32 reqId,
	SceNpSignalingNetInfo *netinfo
	);

/*
 * Memory Info
 */
typedef struct SceNpSignalingMemoryInfo {
	SceSize totalMemSize;		/* Total memory size */
	SceSize curMemUsage;		/* Current memory usage */
	SceSize maxMemUsage;		/* Max memory usage */
	SceUChar8 reserved[12];
} SceNpSignalingMemoryInfo;

/*
 * Np Signaling Memory Info API
 */

int
sceNpSignalingGetMemoryInfo(
	SceNpSignalingMemoryInfo *memInfo
	);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_NP_NP_SIGNALING_H_ */
