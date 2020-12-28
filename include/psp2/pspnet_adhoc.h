#ifndef _DOLCESDK_PSP2_PSPNET_ADHOC_H_
#define _DOLCESDK_PSP2_PSPNET_ADHOC_H_

#include <psp2/pspnet_adhoc/pspnet_adhocctl.h>


#define SCE_ERROR_NET_ADHOC_INVALID_SOCKET_ID		0x80410701
	/* Invalid socket id was specified. */
#define SCE_ERROR_NET_ADHOC_INVALID_ADDR			0x80410702
	/* Invalid address was specified.  */
#define SCE_ERROR_NET_ADHOC_INVALID_PORT			0x80410703
	/* Invalid port was specified. */
#define SCE_ERROR_NET_ADHOC_INVALID_BUFLEN			0x80410704
	/* Invalid buffer length was specified. */
#define SCE_ERROR_NET_ADHOC_INVALID_DATALEN			0x80410705
	/* Invalid data length was specified. */
#define SCE_ERROR_NET_ADHOC_NOT_ENOUGH_SPACE		0x80410706
	/* Specified buffer space is not enough. */
#define SCE_ERROR_NET_ADHOC_SOCKET_DELETED			0x80410707
	/* Socket has been deleted. */
#define SCE_ERROR_NET_ADHOC_SOCKET_ALERTED			0x80410708
	/* Socket alert has been set. */
#define SCE_ERROR_NET_ADHOC_WOULD_BLOCK				0x80410709
	/* Fall iin block state in non-blocking mode. */
#define SCE_ERROR_NET_ADHOC_PORT_IN_USE				0x8041070a
	/* Specified port is in use. */
#define SCE_ERROR_NET_ADHOC_NOT_CONNECTED			0x8041070b
	/* Socket is not connected. */
#define SCE_ERROR_NET_ADHOC_DISCONNECTED			0x8041070c
	/* Socket is disconnected. */
#define SCE_ERROR_NET_ADHOC_NOT_OPENED				0x8041070d
	/* Socket is not opened. */
#define SCE_ERROR_NET_ADHOC_NOT_LISTENED			0x8041070e
	/* Socket is not listened. */
#define SCE_ERROR_NET_ADHOC_SOCKET_ID_NOT_AVAIL		0x8041070f
	/* Any socket id is not available. */
#define SCE_ERROR_NET_ADHOC_PORT_NOT_AVAIL			0x80410710
	/* Any port is not available. */
#define SCE_ERROR_NET_ADHOC_INVALID_ARG				0x80410711
	/* Invalid argument was specified. */
#define SCE_ERROR_NET_ADHOC_NOT_INITIALIZED			0x80410712
	/* Library module is not initialized. */
#define SCE_ERROR_NET_ADHOC_ALREADY_INITIALIZED		0x80410713
	/* Library module is already initialized. */
#define SCE_ERROR_NET_ADHOC_BUSY					0x80410714
	/* Library module is busy. */
#define SCE_ERROR_NET_ADHOC_TIMEOUT					0x80410715
	/* API call was timeout. */
#define SCE_ERROR_NET_ADHOC_NO_ENTRY				0x80410716
	/* No entry was found. */
#define SCE_ERROR_NET_ADHOC_EXCEPTION_EVENT			0x80410717
	/* Exception event was occured. */
#define SCE_ERROR_NET_ADHOC_CONNECTION_REFUSED		0x80410718
	/* Connection was refused by peer. */
#define SCE_ERROR_NET_ADHOC_THREAD_ABORTED			0x80410719
	/* Caller was aborted by sceNetThreadAbort(). */
#define SCE_ERROR_NET_ADHOC_ALREADY_CREATED			0x8041071a
	/* GameMode handle is already created */
#define SCE_ERROR_NET_ADHOC_NOT_IN_GAMEMODE			0x8041071b
	/* State is not in gamemode */
#define SCE_ERROR_NET_ADHOC_NOT_CREATED				0x8041071c
	/* GameMode handle is not created */
#define SCE_ERROR_NET_ADHOC_INVALID_ALIGNMENT		0x8041071d
	/* Alignment of the argument is not acceptable */



#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */


/* socket descriptor for sceNetAdhocPoll() */
struct SceNetAdhocPollSd {
	int id;
	int events;
	int revents;
};

#define SCE_NET_ADHOC_EV_SEND		0x0001
#define SCE_NET_ADHOC_EV_RECV		0x0002
#define SCE_NET_ADHOC_EV_CONNECT	0x0004
#define SCE_NET_ADHOC_EV_ACCEPT		0x0008
#define SCE_NET_ADHOC_EV_FLUSH		0x0010
#define SCE_NET_ADHOC_EV_INVALID	0x0100
#define SCE_NET_ADHOC_EV_DELETE		0x0200
#define SCE_NET_ADHOC_EV_ALERT		0x0400
#define SCE_NET_ADHOC_EV_DISCONNECT	0x0800

/* PDP statistics */
struct SceNetAdhocPdpStat {
	struct SceNetAdhocPdpStat *next;
	int id;
	struct SceNetEtherAddr laddr;
	SceUShort16 lport;
	unsigned int rcv_sb_cc;
};

/* PTP statistics */
#define SCE_NET_ADHOC_PTP_STATE_CLOSED		0
#define SCE_NET_ADHOC_PTP_STATE_LISTEN		1
#define SCE_NET_ADHOC_PTP_STATE_SYN_SENT	2
#define SCE_NET_ADHOC_PTP_STATE_SYN_RCVD	3
#define SCE_NET_ADHOC_PTP_STATE_ESTABLISHED	4

struct SceNetAdhocPtpStat {
	struct SceNetAdhocPtpStat *next;
	int id;
	struct SceNetEtherAddr laddr;
	struct SceNetEtherAddr paddr;
	SceUShort16 lport;
	SceUShort16 pport;
	unsigned int snd_sb_cc;
	unsigned int rcv_sb_cc;
	int state;
};

/* flags for adhoc socket API */
#define SCE_NET_ADHOC_F_NONBLOCK		0x0001

#define SCE_NET_ADHOC_F_ALERTSEND		0x0010
#define SCE_NET_ADHOC_F_ALERTRECV		0x0020
#define SCE_NET_ADHOC_F_ALERTPOLL		0x0040
#define SCE_NET_ADHOC_F_ALERTCONNECT	0x0080
#define SCE_NET_ADHOC_F_ALERTACCEPT		0x0100
#define SCE_NET_ADHOC_F_ALERTFLUSH		0x0200
#define SCE_NET_ADHOC_F_ALERTALL \
	(SCE_NET_ADHOC_F_ALERTSEND \
		|SCE_NET_ADHOC_F_ALERTRECV \
		|SCE_NET_ADHOC_F_ALERTPOLL \
		|SCE_NET_ADHOC_F_ALERTCONNECT \
		|SCE_NET_ADHOC_F_ALERTACCEPT \
		|SCE_NET_ADHOC_F_ALERTFLUSH \
	)

/* PDP Maximum Fragment Size */
#define SCE_NET_ADHOC_PDP_MFS		1444

/* PDP Maximum Transfer Unit */
#define SCE_NET_ADHOC_PDP_MTU		65523

/* PTP Maximum Segment Size */
#define SCE_NET_ADHOC_PTP_MSS		1444

int sceNetAdhocInit(void);
int sceNetAdhocTerm(void);

int sceNetAdhocPollSocket( struct SceNetAdhocPollSd *sds, int nsds, unsigned int timeout, int flag );
int sceNetAdhocSetSocketAlert( int id, int flag );
int sceNetAdhocGetSocketAlert( int id, int *flag );

int sceNetAdhocPdpCreate( const struct SceNetEtherAddr *saddr, SceUShort16 sport, unsigned int bufsize, int flag );
int sceNetAdhocPdpSend( int id, const struct SceNetEtherAddr *daddr, SceUShort16 dport, const void *data, int len, unsigned int timeout, int flag );
int sceNetAdhocPdpRecv( int id, struct SceNetEtherAddr *saddr, SceUShort16 *sport, void *buf, int *len, unsigned   int timeout, int flag );
int sceNetAdhocPdpDelete( int id, int flag );
int sceNetAdhocGetPdpStat( int *buflen, void *buf );

int sceNetAdhocPtpOpen( const struct SceNetEtherAddr *saddr, SceUShort16 sport, const struct SceNetEtherAddr *daddr, SceUShort16 dport, unsigned int bufsize, unsigned int rexmt_int, int rexmt_cnt, int flag );
int sceNetAdhocPtpConnect( int id, unsigned int timeout, int flag );
int sceNetAdhocPtpListen( const struct SceNetEtherAddr *saddr, SceUShort16 sport, unsigned int bufsize, unsigned   int rexmt_int, int rexmt_cnt, int backlog, int flag );
int sceNetAdhocPtpAccept( int id, struct SceNetEtherAddr *addr, SceUShort16 *port, unsigned int timeout, int flag );
int sceNetAdhocPtpSend( int id, const void *data, int *len, unsigned int timeout, int flag );
int sceNetAdhocPtpRecv( int id, void *buf, int *len, unsigned int timeout, int flag );
int sceNetAdhocPtpFlush( int id, unsigned int timeout, int flag );
int sceNetAdhocPtpClose( int id, int flag) ;
int sceNetAdhocGetPtpStat( int *buflen, void *buf );


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */



#endif /* _DOLCESDK_PSP2_PSPNET_ADHOC_H_ */
