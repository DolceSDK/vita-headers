#ifndef _DOLCESDK_PSP2_LIBNETCTL_H_
#define _DOLCESDK_PSP2_LIBNETCTL_H_

#include <psp2/net.h>
#include <psp2/np/np_npid.h>
#include <psp2/system_param.h>
#include <psp2/rtc.h>

#define SCE_NET_CTL_ERROR_NOT_INITIALIZED                           0x80412101
	/* An API is called but library is not initialized yet. */
#define SCE_NET_CTL_ERROR_NOT_TERMINATED                            0x80412102
	/* init function is called before terminating library. */
#define SCE_NET_CTL_ERROR_CALLBACK_MAX                              0x80412103
	/* there is no space for new callback */
#define SCE_NET_CTL_ERROR_ID_NOT_FOUND                              0x80412104
	/* specified ID is not found */
#define SCE_NET_CTL_ERROR_INVALID_ID                                0x80412105
	/* specified ID is invalid */
#define SCE_NET_CTL_ERROR_INVALID_CODE                              0x80412106
	/* specified code is invalid */
#define SCE_NET_CTL_ERROR_INVALID_ADDR                              0x80412107
	/* specified addr is invalid */
#define SCE_NET_CTL_ERROR_NOT_CONNECTED                             0x80412108
	/* Not connected */
#define SCE_NET_CTL_ERROR_NOT_AVAIL                                 0x80412109
	/* Not available */
#define SCE_NET_CTL_ERROR_AUTO_CONNECT_DISABLED                     0x8041210a
	/* Auto connect functionality is disabled at this timing. */
#define SCE_NET_CTL_ERROR_AUTO_CONNECT_FAILED                       0x8041210b
	/* libnetctl tried Auto Connect but it failed. */
#define SCE_NET_CTL_ERROR_NO_SUITABLE_SETTING_FOR_AUTO_CONNECT      0x8041210c
	/* libnetctl tried Auto Connect but suitable setting did not exist. */
#define SCE_NET_CTL_ERROR_DISCONNECTED_FOR_ADHOC_USE                0x8041210d
	/* inet connection is disconnected for adhoc use */
#define SCE_NET_CTL_ERROR_DISCONNECT_REQ                            0x8041210e
	/* disconnect event occured by Disconnect API */
#define SCE_NET_CTL_ERROR_INVALID_TYPE                              0x8041210f
	/* specified type is invalid */
#define SCE_NET_CTL_ERROR_AUTO_DISCONNECT                           0x80412110
	/* disconnect event occured by Auto Disconnect */
#define SCE_NET_CTL_ERROR_INVALID_SIZE                              0x80412111
	/* specified size is invalid */
#define SCE_NET_CTL_ERROR_FLIGHT_MODE_ENABLED                       0x80412112
	/* flight mode is enabled at this timing. */
#define SCE_NET_CTL_ERROR_WIFI_DISABLED                             0x80412113
	/* wifi is disabled at this timing. */
#define SCE_NET_CTL_ERROR_WIFI_IN_ADHOC_USE                         0x80412114
	/* wifi is used for adhoc use at this timing. */
#define SCE_NET_CTL_ERROR_ETHERNET_PLUGOUT                          0x80412115
	/*J Ethernet cable becomes disconnected. */
#define SCE_NET_CTL_ERROR_WIFI_DEAUTHED                             0x80412116
	/*J Deauthed from access point */
#define SCE_NET_CTL_ERROR_WIFI_BEACON_LOST                          0x80412117
	/*J could not receive beacon from access point */
#define SCE_NET_CTL_ERROR_DISCONNECTED_FOR_SUSPEND                  0x80412118
	/* inet connection is disconnected due to suspend */
#define SCE_NET_CTL_ERROR_COMMUNICATION_ID_NOT_EXIST				0x80412119
	/* adhoc connection needs SceNpCommunicationId */
#define SCE_NET_CTL_ERROR_ADHOC_ALREADY_CONNECTED					0x8041211a
	/* ad-hoc mod is already connected */
#define SCE_NET_CTL_ERROR_DHCP_TIMEOUT								0x8041211b
	/* timeout occurs during DHCP */
#define SCE_NET_CTL_ERROR_PPPOE_TIMEOUT								0x8041211c
	/* timeout occurs during PPPoE */
#define SCE_NET_CTL_ERROR_INSUFFICIENT_MEMORY						0x8041211d
	/* libnet memory is insufficient */
#define SCE_NET_CTL_ERROR_PSP_ADHOC_JOIN_TIMEOUT					0x8041211e
	/* timeout occurs during PSP Adhoc Join */
#define SCE_NET_CTL_ERROR_UNKNOWN_DEVICE                            0x80412188
	/* specified device type is invalid */


/* state */
#define SCE_NET_CTL_STATE_DISCONNECTED       0
#define SCE_NET_CTL_STATE_CONNECTING         1
#define SCE_NET_CTL_STATE_IPOBTAINING        2
#define SCE_NET_CTL_STATE_IPOBTAINED         3

/* event type */
#define SCE_NET_CTL_EVENT_TYPE_DISCONNECTED               1
#define SCE_NET_CTL_EVENT_TYPE_DISCONNECT_REQ_FINISHED    2
#define SCE_NET_CTL_EVENT_TYPE_IPOBTAINED                 3

/* info code */
#define SCE_NET_CTL_INFO_CNF_NAME          1
#define SCE_NET_CTL_INFO_DEVICE            2
#define SCE_NET_CTL_INFO_ETHER_ADDR        3
#define SCE_NET_CTL_INFO_MTU               4
#define SCE_NET_CTL_INFO_LINK              5
#define SCE_NET_CTL_INFO_BSSID             6
#define SCE_NET_CTL_INFO_SSID              7
#define SCE_NET_CTL_INFO_WIFI_SECURITY     8
#define SCE_NET_CTL_INFO_RSSI_DBM          9
#define SCE_NET_CTL_INFO_RSSI_PERCENTAGE   10
#define SCE_NET_CTL_INFO_CHANNEL           11
#define SCE_NET_CTL_INFO_IP_CONFIG         12
#define SCE_NET_CTL_INFO_DHCP_HOSTNAME     13
#define SCE_NET_CTL_INFO_PPPOE_AUTH_NAME   14
#define SCE_NET_CTL_INFO_IP_ADDRESS        15
#define SCE_NET_CTL_INFO_NETMASK           16
#define SCE_NET_CTL_INFO_DEFAULT_ROUTE     17
#define SCE_NET_CTL_INFO_PRIMARY_DNS       18
#define SCE_NET_CTL_INFO_SECONDARY_DNS     19
#define SCE_NET_CTL_INFO_HTTP_PROXY_CONFIG 20
#define SCE_NET_CTL_INFO_HTTP_PROXY_SERVER 21
#define SCE_NET_CTL_INFO_HTTP_PROXY_PORT   22
#define SCE_NET_CTL_INFO_RESERVED1         23
#define SCE_NET_CTL_INFO_RESERVED2         24

/* device */
#define SCE_NET_CTL_DEVICE_WIRELESS  0
#define SCE_NET_CTL_DEVICE_WIRED     1
#define SCE_NET_CTL_DEVICE_PHONE     2

/* link */
#define SCE_NET_CTL_LINK_DISCONNECTED   0
#define SCE_NET_CTL_LINK_CONNECTED      1

/* wifi_security */
#define SCE_NET_CTL_WIFI_SECURITY_NOAUTH          0
#define SCE_NET_CTL_WIFI_SECURITY_WEP             1
#define SCE_NET_CTL_WIFI_SECURITY_WPAPSK_WPA2PSK  2
#define SCE_NET_CTL_WIFI_SECURITY_WPAPSK_TKIP     3
#define SCE_NET_CTL_WIFI_SECURITY_WPAPSK_AES      4
#define SCE_NET_CTL_WIFI_SECURITY_WPA2PSK_TKIP    5
#define SCE_NET_CTL_WIFI_SECURITY_WPA2PSK_AES     6
#define SCE_NET_CTL_WIFI_SECURITY_UNSUPPORTED     7

/* ip_config */
#define SCE_NET_CTL_IP_DHCP      0
#define SCE_NET_CTL_IP_STATIC    1
#define SCE_NET_CTL_IP_PPPOE     2

/* http_proxy_config */
#define SCE_NET_CTL_HTTP_PROXY_OFF  0
#define SCE_NET_CTL_HTTP_PROXY_ON   1

#define SCE_NET_CTL_CNF_NAME_LEN            (64 + 1)
#define SCE_NET_CTL_SSID_LEN                (32 + 1)
#define SCE_NET_CTL_WIFI_SECURITY_KEY_LEN   (64 + 1)
#define SCE_NET_CTL_AUTH_NAME_LEN           (127 + 1)
#define SCE_NET_CTL_AUTH_KEY_LEN            (127 + 1)
#define SCE_NET_CTL_HOSTNAME_LEN            (255 + 1)
#define SCE_NET_CTL_IPV4_ADDR_STR_LEN       16

typedef union SceNetCtlInfo {
	char cnf_name[SCE_NET_CTL_CNF_NAME_LEN];
	SceUInt device;
	SceNetEtherAddr ether_addr;
	SceUInt mtu;
	SceUInt link;
	SceNetEtherAddr bssid;
	char ssid[SCE_NET_CTL_SSID_LEN];
	SceUInt wifi_security;
	SceUInt rssi_dbm;
	SceUInt rssi_percentage;
	SceUInt channel;
	SceUInt ip_config;
	char dhcp_hostname[SCE_NET_CTL_HOSTNAME_LEN];
	char pppoe_auth_name[SCE_NET_CTL_AUTH_NAME_LEN];
	char ip_address[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	char netmask[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	char default_route[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	char primary_dns[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	char secondary_dns[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	SceUInt http_proxy_config;
	char http_proxy_server[SCE_NET_CTL_HOSTNAME_LEN];
	SceUInt http_proxy_port;
} SceNetCtlInfo;

typedef struct SceNetCtlNatInfo {
	SceSize size;
	int stun_status;   /* SCE_NET_CTL_NATINFO_STUN_XXX */
	int nat_type;      /* SCE_NET_CTL_NATINFO_NAT_TYPE_XXX */
	SceNetInAddr mapped_addr;
} SceNetCtlNatInfo;

/* stun staus */
#define SCE_NET_CTL_NATINFO_STUN_UNCHECKED     0
#define SCE_NET_CTL_NATINFO_STUN_FAILED        1
#define SCE_NET_CTL_NATINFO_STUN_OK            2
/* nat type */
#define SCE_NET_CTL_NATINFO_NAT_TYPE_1         1
#define SCE_NET_CTL_NATINFO_NAT_TYPE_2         2
#define SCE_NET_CTL_NATINFO_NAT_TYPE_3         3

typedef struct SceNetCtlIfStat {
	SceSize size;
	SceUInt32 totalSec;
	SceUInt64 txBytes;
	SceUInt64 rxBytes;
	SceRtcTick resetTick;
	SceUInt32 reserved[8];
} SceNetCtlIfStat;

typedef struct SceNetCtlAdhocPeerInfo {
	struct SceNetInAddr inetAddr;
	SceNpId npId;
	SceUInt64 lastRecv;
	int appVer;
	SceBool isValidNpId;
	char username[SCE_SYSTEM_PARAM_USER_NAME_MAXSIZE];
	char padding[7];
} SceNetCtlAdhocPeerInfo;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */


int
sceNetCtlInit(
	void
	);

void
sceNetCtlTerm(
	void
	);

int
sceNetCtlCheckCallback(
	void
	);

int
sceNetCtlInetGetResult(
	int eventType,
	int *errorCode
	);

int
sceNetCtlAdhocGetResult(
	int eventType,
	int *errorCode
	);

int
sceNetCtlInetGetInfo(
	int code,
	SceNetCtlInfo *info
	);

int
sceNetCtlInetGetState(
	int *state
	);

int
sceNetCtlGetNatInfo(
	SceNetCtlNatInfo *natinfo
	);

int
sceNetCtlGetIfStat(
	int device,                      /* SCE_NET_CTL_DEVICE_XXX */
	SceNetCtlIfStat *ifstat
	);

typedef void (*SceNetCtlCallback)(
	int event_type,
	void *arg
	);

#define SCE_NET_CTL_CALLBACK_MAX 8
int
sceNetCtlInetRegisterCallback(
	SceNetCtlCallback func,
	void *arg,
	int *cid
	);

int
sceNetCtlInetUnregisterCallback(
	int cid
	);

int
sceNetCtlAdhocRegisterCallback(
	SceNetCtlCallback func,
	void *arg,
	int *cid
	);

int
sceNetCtlAdhocUnregisterCallback(
	int cid
	);

int
sceNetCtlAdhocGetState(
	int *state
	);

int
sceNetCtlAdhocDisconnect(
	void
	);

int
sceNetCtlAdhocGetPeerList(
	SceSize *peerInfoNum,
	SceNetCtlAdhocPeerInfo *peerInfo
	);

int
sceNetCtlAdhocGetInAddr(
	SceNetInAddr *inaddr
	);

#define SCE_NET_CTL_DOWNLOADABLE_SIZE_UNLIMITED	(0x7fffffffffffffffLL)
int
sceNetCtlGetPhoneMaxDownloadableSize(
	SceInt64 *maxDownloadableSize
	);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_LIBNETCTL_H_ */
