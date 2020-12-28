#ifndef _DOLCESDK_PSP2_PSPNET_ADHOC_PSPNET_ADHOCCTL_H_
#define _DOLCESDK_PSP2_PSPNET_ADHOC_PSPNET_ADHOCCTL_H_

#include <psp2/types.h>
#include <psp2/net.h>


#define SCE_ERROR_NET_ADHOCCTL_INVALID_ARG				0x80410b04
	/* Invalid argument was specified. */
#define SCE_ERROR_NET_ADHOCCTL_ALREADY_INITIALIZED		0x80410b07
	/* Service is already started. */
#define SCE_ERROR_NET_ADHOCCTL_NOT_INITIALIZED			0x80410b08
	/* Service is not ready. */




/* Adhoc ID */
#define SCE_NET_ADHOCCTL_ADHOCID_LEN			9
#define SCE_NET_ADHOCCTL_ADHOCTYPE_PRODUCT_ID	0
#define SCE_NET_ADHOCCTL_ADHOCTYPE_RESERVED		1
#define SCE_NET_ADHOCCTL_ADHOCTYPE_SYSTEM		2

typedef struct SceNetAdhocctlAdhocId {
	int type;
	SceChar8 data[SCE_NET_ADHOCCTL_ADHOCID_LEN];
	SceUChar8 padding[3];
} SceNetAdhocctlAdhocId;

/* Group Name */
#define SCE_NET_ADHOCCTL_GROUPNAME_LEN		8
typedef struct SceNetAdhocctlGroupName {
	SceChar8 data[SCE_NET_ADHOCCTL_GROUPNAME_LEN];
} SceNetAdhocctlGroupName;

/* Nickname */
#define SCE_NET_ADHOCCTL_NICKNAME_LEN 128
typedef struct SceNetAdhocctlNickname {
	SceChar8 data[SCE_NET_ADHOCCTL_NICKNAME_LEN];
} SceNetAdhocctlNickname;

/* Peer Info */
typedef struct SceNetAdhocctlPeerInfo {
	struct SceNetAdhocctlPeerInfo *next;
	struct SceNetAdhocctlNickname nickname;
	struct SceNetEtherAddr macAddr;
	SceUChar8 padding[6];
	SceUInt64 lastRecv;
} SceNetAdhocctlPeerInfo;

/* SSID */
#define SCE_NET_ADHOCCTL_BSSID_LEN  6
typedef struct SceNetAdhocctlBSSId {
	SceUChar8 data[SCE_NET_ADHOCCTL_BSSID_LEN];
	SceUChar8 padding[2];
} SceNetAdhocctlBSSId;

/* IBSS Parameter */
typedef struct SceNetAdhocctlParameter {
	int channel;
	struct SceNetAdhocctlGroupName groupName;
	struct SceNetAdhocctlNickname nickname;
	struct SceNetAdhocctlBSSId bssid;
} SceNetAdhocctlParameter;



#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int
sceNetAdhocctlInit(
	const struct SceNetAdhocctlAdhocId *adhocId
	);

int
sceNetAdhocctlTerm(
	void
	);


int
sceNetAdhocctlGetAdhocId(
	struct SceNetAdhocctlAdhocId *adhocId
	);

int
sceNetAdhocctlGetPeerList(
	int *buflen,
	void *buf
	);

int
sceNetAdhocctlGetPeerInfo(
	const struct SceNetEtherAddr *addr,
	int size,
	struct SceNetAdhocctlPeerInfo *peerInfo
	);

int
sceNetAdhocctlGetAddrByName(
	const struct SceNetAdhocctlNickname *nickname,
	int *buflen,
	void *buf
	);

int
sceNetAdhocctlGetNameByAddr(
	const struct SceNetEtherAddr *addr,
	struct SceNetAdhocctlNickname *nickname
	);

int
sceNetAdhocctlGetParameter(
	struct SceNetAdhocctlParameter *parameter
	);

int
sceNetAdhocctlGetEtherAddr(
	struct SceNetEtherAddr *addr
	);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_PSPNET_ADHOC_PSPNET_ADHOCCTL_H_ */
