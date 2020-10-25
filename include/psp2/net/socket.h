#ifndef _DOLCESDK_PSP2_NET_SOCKET_H_
#define _DOLCESDK_PSP2_NET_SOCKET_H_

#include <psp2/net/nettypes.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* protocol */
#define SCE_NET_IPPROTO_IP            0
#define SCE_NET_IPPROTO_ICMP          1
#define SCE_NET_IPPROTO_IGMP          2
#define SCE_NET_IPPROTO_TCP           6
#define SCE_NET_IPPROTO_UDP           17
#define SCE_NET_SOL_SOCKET            0xffff

/* socket option (IP) */
#define SCE_NET_IP_HDRINCL            2
#define SCE_NET_IP_TOS                3
#define SCE_NET_IP_TTL                4
#define SCE_NET_IP_MULTICAST_IF       9
#define SCE_NET_IP_MULTICAST_TTL      10
#define SCE_NET_IP_MULTICAST_LOOP     11
#define SCE_NET_IP_ADD_MEMBERSHIP     12
#define SCE_NET_IP_DROP_MEMBERSHIP    13
#define SCE_NET_IP_TTLCHK             23
#define SCE_NET_IP_MAXTTL             24
#define SCE_NET_IP_DONTFRAG           26

/* socket option (TCP) */
#define SCE_NET_TCP_NODELAY           1
#define SCE_NET_TCP_MAXSEG            2
#define SCE_NET_TCP_MSS_TO_ADVERTISE  3

/* socket option (SOCKET) */
#define SCE_NET_SO_REUSEADDR          0x00000004
#define SCE_NET_SO_KEEPALIVE          0x00000008
#define SCE_NET_SO_BROADCAST          0x00000020
#define SCE_NET_SO_LINGER             0x00000080
#define SCE_NET_SO_OOBINLINE          0x00000100
#define SCE_NET_SO_REUSEPORT          0x00000200
#define SCE_NET_SO_ONESBCAST          0x00000800
#define SCE_NET_SO_USECRYPTO          0x00001000
#define SCE_NET_SO_USESIGNATURE       0x00002000
#define SCE_NET_SO_SNDBUF             0x1001
#define SCE_NET_SO_RCVBUF             0x1002
#define SCE_NET_SO_SNDLOWAT           0x1003
#define SCE_NET_SO_RCVLOWAT           0x1004
#define SCE_NET_SO_SNDTIMEO           0x1005
#define SCE_NET_SO_RCVTIMEO           0x1006
#define SCE_NET_SO_ERROR              0x1007
#define SCE_NET_SO_TYPE               0x1008
#define SCE_NET_SO_NBIO               0x1100
#define SCE_NET_SO_TPPOLICY           0x1101
#define SCE_NET_SO_NAME               0x1102
#define SCE_NET_SO_ERROR_EX           0x1104

/* socket types */
#define SCE_NET_SOCK_STREAM           1
#define SCE_NET_SOCK_DGRAM            2
#define SCE_NET_SOCK_RAW              3
#define SCE_NET_SOCK_DGRAM_P2P        6
#define SCE_NET_SOCK_STREAM_P2P       10

/* port numbers */
#define SCE_NET_ADHOC_PORT            3658

/* address families */
#define SCE_NET_AF_INET               2

typedef struct SceNetLinger {
	int l_onoff;	/* on/off */
	int l_linger;	/* linger time [sec] */
} SceNetLinger;

typedef struct SceNetSockaddr {
	SceUChar8 sa_len;
	SceNetSaFamily_t sa_family;
	SceChar8 sa_data[14];
} SceNetSockaddr;

#if defined(__cplusplus) || defined(__INTELLISENSE__)
#define SceNetSockaddrArg			SceNetSockaddr *
#define SceNetSockaddrConstArg		const SceNetSockaddr *
#else	/* defined(__cplusplus) || defined(__INTELLISENSE__) */
typedef union SceNetSockaddrArg {
	struct SceNetSockaddr   *sockaddr;
	struct SceNetSockaddrIn *sockaddr_in;
} SceNetSockaddrArg __attribute__((__transparent_union__));

typedef union SceNetSockaddrConstArg {
	const struct SceNetSockaddr   *sockaddr;
	const struct SceNetSockaddrIn *sockaddr_in;
} SceNetSockaddrConstArg __attribute__((__transparent_union__));
#endif	/* defined(__cplusplus) || defined(__INTELLISENSE__) */

typedef struct SceNetIovec {
	void *iov_base;
	SceSize iov_len;
} SceNetIovec;

typedef struct SceNetMsghdr {
	void *msg_name;
	SceNetSocklen_t msg_namelen;
	SceNetIovec *msg_iov;
	int msg_iovlen;
	void *msg_control;
	SceNetSocklen_t msg_controllen;
	int msg_flags;
} SceNetMsghdr;

/* flags */
#define SCE_NET_MSG_PEEK            0x00000002
#define SCE_NET_MSG_WAITALL         0x00000040
#define SCE_NET_MSG_DONTWAIT        0x00000080
#define SCE_NET_MSG_USECRYPTO       0x00000400
#define SCE_NET_MSG_USESIGNATURE    0x00000800
#define SCE_NET_MSG_PEEKLEN        (0x00001000 | SCE_NET_MSG_PEEK)

/* flags for sceNetShutdown */
#define SCE_NET_SHUT_RD             0
#define SCE_NET_SHUT_WR             1
#define SCE_NET_SHUT_RDWR           2

/* flags for sceNetSocketAbort */
#define SCE_NET_SOCKET_ABORT_FLAG_RCV_PRESERVATION  0x00000001
#define SCE_NET_SOCKET_ABORT_FLAG_SND_PRESERVATION  0x00000002

SceNetId sceNetSocket(const char *name, int domain, int type, int protocol);
SceNetId sceNetAccept(SceNetId s, SceNetSockaddrArg addr,
	SceNetSocklen_t *addrlen);
int sceNetBind(SceNetId s, SceNetSockaddrConstArg addr,
	SceNetSocklen_t addrlen);
int sceNetConnect(SceNetId s, SceNetSockaddrConstArg name,
	SceNetSocklen_t namelen);
int sceNetGetpeername(SceNetId s, SceNetSockaddrArg name,
	SceNetSocklen_t *namelen);
int sceNetGetsockname(SceNetId s, SceNetSockaddrArg name,
	SceNetSocklen_t *namelen);
int sceNetGetsockopt(SceNetId s, int level, int optname, void *optval,
	SceNetSocklen_t *optlen);
int sceNetListen(SceNetId s, int backlog);
int sceNetRecv(SceNetId s, void *buf, SceSize len, int flags);
int sceNetRecvfrom(SceNetId s, void *buf, SceSize len, int flags,
	SceNetSockaddrArg from, SceNetSocklen_t *fromlen);
int sceNetRecvmsg(SceNetId s, SceNetMsghdr *msg, int flags);
int sceNetSend(SceNetId s, const void *msg, SceSize len, int flags);
int sceNetSendto(SceNetId s, const void *msg, SceSize len, int flags,
	SceNetSockaddrConstArg to, SceNetSocklen_t tolen);
int sceNetSendmsg(SceNetId s, const SceNetMsghdr *msg, int flags);
int sceNetSetsockopt(SceNetId s, int level, int optname, const void *optval,
	SceNetSocklen_t optlen);
int sceNetShutdown(SceNetId s, int how);
int sceNetSocketClose(SceNetId s);
int sceNetSocketAbort(SceNetId s, int flags);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

#if (defined(__GNUC__) || defined(__SNC__)) && !defined(__INTELLISENSE__)
static inline SceNetId sceNetAccept(SceNetId s, struct SceNetSockaddrIn *addr,
	SceNetSocklen_t *addrlen) __attribute__((__always_inline__));
static inline int sceNetBind(SceNetId s, const struct SceNetSockaddrIn *addr,
	SceNetSocklen_t addrlen) __attribute__((__always_inline__));
static inline int sceNetConnect(SceNetId s, const struct SceNetSockaddrIn *name,
	SceNetSocklen_t namelen) __attribute__((__always_inline__));
static inline int sceNetGetpeername(SceNetId s, struct SceNetSockaddrIn *name,
	SceNetSocklen_t *namelen) __attribute__((__always_inline__));
static inline int sceNetGetsockname(SceNetId s, struct SceNetSockaddrIn *name,
	SceNetSocklen_t *namelen) __attribute__((__always_inline__));
static inline int sceNetRecvfrom(SceNetId s, void *buf, SceSize len,
	int flags, struct SceNetSockaddrIn *from, SceNetSocklen_t *fromlen)
	__attribute__((__always_inline__));
static inline int sceNetSendto(SceNetId s, const void *msg, SceSize len,
	int flags, const struct SceNetSockaddrIn *to, SceNetSocklen_t tolen)
	__attribute__((__always_inline__));
#endif	/* (defined(__GNUC__) || defined(__SNC__)) && !defined(__INTELLISENSE__) */

static inline SceNetId sceNetAccept(SceNetId s, struct SceNetSockaddrIn *addr,
	SceNetSocklen_t *addrlen)
{
	return sceNetAccept(s,
				static_cast<SceNetSockaddr *>(
					static_cast<void *>(addr)),
				addrlen);
}

static inline int sceNetBind(SceNetId s, const struct SceNetSockaddrIn *addr,
	SceNetSocklen_t addrlen)
{
	return sceNetBind(s,
				static_cast<const SceNetSockaddr *>(
					static_cast<const void *>(addr)),
				addrlen);
}

static inline int sceNetConnect(SceNetId s, const struct SceNetSockaddrIn *name,
	SceNetSocklen_t namelen)
{
	return sceNetConnect(s,
				static_cast<const SceNetSockaddr *>(
					static_cast<const void *>(name)),
				namelen);
}

static inline int sceNetGetpeername(SceNetId s, struct SceNetSockaddrIn *name,
	SceNetSocklen_t *namelen)
{
	return sceNetGetpeername(s,
				static_cast<SceNetSockaddr *>(static_cast<void *>(name)),
				namelen);
}

static inline int sceNetGetsockname(SceNetId s, struct SceNetSockaddrIn *name,
	SceNetSocklen_t *namelen)
{
	return sceNetGetsockname(s,
				static_cast<SceNetSockaddr *>(static_cast<void *>(name)),
				namelen);
}

static inline int sceNetRecvfrom(SceNetId s, void *buf, SceSize len,
	int flags, struct SceNetSockaddrIn *from, SceNetSocklen_t *fromlen)
{
	return sceNetRecvfrom(s, buf, len, flags,
				static_cast<SceNetSockaddr *>(static_cast<void *>(from)),
				fromlen);
}

static inline int sceNetSendto(SceNetId s, const void *msg, SceSize len,
	int flags, const struct SceNetSockaddrIn *to, SceNetSocklen_t tolen)
{
	return sceNetSendto(s, msg, len, flags,
				static_cast<const SceNetSockaddr *>(
					static_cast<const void *>(to)),
				tolen);
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_SOCKET_H_ */

