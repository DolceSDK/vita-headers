#ifndef _DOLCESDK_PSP2_NET_ERRNO_H_
#define _DOLCESDK_PSP2_NET_ERRNO_H_

#if defined(__cplusplus)
extern "C" {
#endif

#define SCE_NET_ECAST(x)   ((SceInt32)(x))
#define SCE_NET_MAKE_ERROR(status) \
	SCE_NET_ECAST(SCE_ERROR_MAKE_ERROR( \
	    SCE_ERROR_FACILITY_NETWORK, (0x0100 | (SceUInt32)(status))))

/*
 * Error number definition
 */

/**
 */
#define SCE_NET_ERROR_EPERM						-2143223551	/* 0x80410101 */

/**
 */
#define SCE_NET_ERROR_ENOENT					-2143223550	/* 0x80410102 */

/**
 */
#define SCE_NET_ERROR_ESRCH						-2143223549	/* 0x80410103 */

/**
 */
#define SCE_NET_ERROR_EINTR						-2143223548	/* 0x80410104 */

/**
 */
#define SCE_NET_ERROR_EIO						-2143223547	/* 0x80410105 */

/**
 */
#define SCE_NET_ERROR_ENXIO						-2143223546	/* 0x80410106 */

/**
 */
#define SCE_NET_ERROR_E2BIG						-2143223545	/* 0x80410107 */

/**
 */
#define SCE_NET_ERROR_ENOEXEC					-2143223544	/* 0x80410108 */

/**
 */
#define SCE_NET_ERROR_EBADF						-2143223543	/* 0x80410109 */

/**
 */
#define SCE_NET_ERROR_ECHILD					-2143223542	/* 0x8041010A */

/**
 */
#define SCE_NET_ERROR_EDEADLK					-2143223541	/* 0x8041010B */

/**
 */
#define SCE_NET_ERROR_ENOMEM					-2143223540	/* 0x8041010C */

/**
 */
#define SCE_NET_ERROR_EACCES					-2143223539	/* 0x8041010D */

/**
 */
#define SCE_NET_ERROR_EFAULT					-2143223538	/* 0x8041010E */

/**
 */
#define SCE_NET_ERROR_ENOTBLK					-2143223537	/* 0x8041010F */

/**
 */
#define SCE_NET_ERROR_EBUSY						-2143223536	/* 0x80410110 */

/**
 */
#define SCE_NET_ERROR_EEXIST					-2143223535	/* 0x80410111 */

/**
 */
#define SCE_NET_ERROR_EXDEV						-2143223534	/* 0x80410112 */

/**
 */
#define SCE_NET_ERROR_ENODEV					-2143223533	/* 0x80410113 */

/**
 */
#define SCE_NET_ERROR_ENOTDIR					-2143223532	/* 0x80410114 */

/**
 */
#define SCE_NET_ERROR_EISDIR					-2143223531	/* 0x80410115 */

/**
 */
#define SCE_NET_ERROR_EINVAL					-2143223530	/* 0x80410116 */

/**
 */
#define SCE_NET_ERROR_ENFILE					-2143223529	/* 0x80410117 */

/**
 */
#define SCE_NET_ERROR_EMFILE					-2143223528	/* 0x80410118 */

/**
 */
#define SCE_NET_ERROR_ENOTTY					-2143223527	/* 0x80410119 */

/**
 */
#define SCE_NET_ERROR_ETXTBSY					-2143223526	/* 0x8041011A */

/**
 */
#define SCE_NET_ERROR_EFBIG						-2143223525	/* 0x8041011B */

/**
 */
#define SCE_NET_ERROR_ENOSPC					-2143223524	/* 0x8041011C */

/**
 */
#define SCE_NET_ERROR_ESPIPE					-2143223523	/* 0x8041011D */

/**
 */
#define SCE_NET_ERROR_EROFS						-2143223522	/* 0x8041011E */

/**
 */
#define SCE_NET_ERROR_EMLINK					-2143223521	/* 0x8041011F */

/**
 */
#define SCE_NET_ERROR_EPIPE						-2143223520	/* 0x80410120 */

/**
 */
#define SCE_NET_ERROR_EDOM						-2143223519	/* 0x80410121 */

/**
 */
#define SCE_NET_ERROR_ERANGE					-2143223518	/* 0x80410122 */

/**
 */
#define SCE_NET_ERROR_EAGAIN					-2143223517	/* 0x80410123 */

/**
 */
#define SCE_NET_ERROR_EWOULDBLOCK				-2143223517	/* 0x80410123 */

/**
 */
#define SCE_NET_ERROR_EINPROGRESS				-2143223516	/* 0x80410124 */

/**
 */
#define SCE_NET_ERROR_EALREADY					-2143223515	/* 0x80410125 */

/**
 */
#define SCE_NET_ERROR_ENOTSOCK					-2143223514	/* 0x80410126 */

/**
 */
#define SCE_NET_ERROR_EDESTADDRREQ				-2143223513	/* 0x80410127 */

/**
 */
#define SCE_NET_ERROR_EMSGSIZE					-2143223512	/* 0x80410128 */

/**
 */
#define SCE_NET_ERROR_EPROTOTYPE				-2143223511	/* 0x80410129 */

/**
 */
#define SCE_NET_ERROR_ENOPROTOOPT				-2143223510	/* 0x8041012A */

/**
 */
#define SCE_NET_ERROR_EPROTONOSUPPORT			-2143223509	/* 0x8041012B */

/**
 */
#define SCE_NET_ERROR_ESOCKTNOSUPPORT			-2143223508	/* 0x8041012C */

/**
 */
#define SCE_NET_ERROR_EOPNOTSUPP				-2143223507	/* 0x8041012D */

/**
 */
#define SCE_NET_ERROR_EPFNOSUPPORT				-2143223506	/* 0x8041012E */

/**
 */
#define SCE_NET_ERROR_EAFNOSUPPORT				-2143223505	/* 0x8041012F */

/**
 */
#define SCE_NET_ERROR_EADDRINUSE				-2143223504	/* 0x80410130 */

/**
 */
#define SCE_NET_ERROR_EADDRNOTAVAIL				-2143223503	/* 0x80410131 */

/**
 */
#define SCE_NET_ERROR_ENETDOWN					-2143223502	/* 0x80410132 */

/**
 */
#define SCE_NET_ERROR_ENETUNREACH				-2143223501	/* 0x80410133 */

/**
 */
#define SCE_NET_ERROR_ENETRESET					-2143223500	/* 0x80410134 */

/**
 */
#define SCE_NET_ERROR_ECONNABORTED				-2143223499	/* 0x80410135 */

/**
 */
#define SCE_NET_ERROR_ECONNRESET				-2143223498	/* 0x80410136 */

/**
 */
#define SCE_NET_ERROR_ENOBUFS					-2143223497	/* 0x80410137 */

/**
 */
#define SCE_NET_ERROR_EISCONN					-2143223496	/* 0x80410138 */

/**
 */
#define SCE_NET_ERROR_ENOTCONN					-2143223495	/* 0x80410139 */

/**
 */
#define SCE_NET_ERROR_ESHUTDOWN					-2143223494	/* 0x8041013A */

/**
 */
#define SCE_NET_ERROR_ETOOMANYREFS				-2143223493	/* 0x8041013B */

/**
 */
#define SCE_NET_ERROR_ETIMEDOUT					-2143223492	/* 0x8041013C */

/**
 */
#define SCE_NET_ERROR_ECONNREFUSED				-2143223491	/* 0x8041013D */

/**
 */
#define SCE_NET_ERROR_ELOOP						-2143223490	/* 0x8041013E */

/**
 */
#define SCE_NET_ERROR_ENAMETOOLONG				-2143223489	/* 0x8041013F */

/**
 */
#define SCE_NET_ERROR_EHOSTDOWN					-2143223488	/* 0x80410140 */

/**
 */
#define SCE_NET_ERROR_EHOSTUNREACH				-2143223487	/* 0x80410141 */

/**
 */
#define SCE_NET_ERROR_ENOTEMPTY					-2143223486	/* 0x80410142 */

/**
 */
#define SCE_NET_ERROR_EPROCLIM					-2143223485	/* 0x80410143 */

/**
 */
#define SCE_NET_ERROR_EUSERS					-2143223484	/* 0x80410144 */

/**
 */
#define SCE_NET_ERROR_EDQUOT					-2143223483	/* 0x80410145 */

/**
 */
#define SCE_NET_ERROR_ESTALE					-2143223482	/* 0x80410146 */

/**
 */
#define SCE_NET_ERROR_EREMOTE					-2143223481	/* 0x80410147 */

/**
 */
#define SCE_NET_ERROR_EBADRPC					-2143223480	/* 0x80410148 */

/**
 */
#define SCE_NET_ERROR_ERPCMISMATCH				-2143223479	/* 0x80410149 */

/**
 */
#define SCE_NET_ERROR_EPROGUNAVAIL				-2143223478	/* 0x8041014A */

/**
 */
#define SCE_NET_ERROR_EPROGMISMATCH				-2143223477	/* 0x8041014B */

/**
 */
#define SCE_NET_ERROR_EPROCUNAVAIL				-2143223476	/* 0x8041014C */

/**
 */
#define SCE_NET_ERROR_ENOLCK					-2143223475	/* 0x8041014D */

/**
 */
#define SCE_NET_ERROR_ENOSYS					-2143223474	/* 0x8041014E */

/**
 */
#define SCE_NET_ERROR_EFTYPE					-2143223473	/* 0x8041014F */

/**
 */
#define SCE_NET_ERROR_EAUTH						-2143223472	/* 0x80410150 */

/**
 */
#define SCE_NET_ERROR_ENEEDAUTH					-2143223471	/* 0x80410151 */

/**
 */
#define SCE_NET_ERROR_EIDRM						-2143223470	/* 0x80410152 */

/**
 */
#define SCE_NET_ERROR_ENOMS						-2143223469	/* 0x80410153 */

/**
 */
#define SCE_NET_ERROR_EOVERFLOW					-2143223468	/* 0x80410154 */

/**
 */
#define SCE_NET_ERROR_EILSEQ					-2143223467	/* 0x80410155 */

/**
 */
#define SCE_NET_ERROR_ENOTSUP					-2143223466	/* 0x80410156 */

/**
 */
#define SCE_NET_ERROR_ECANCELED					-2143223465	/* 0x80410157 */

/**
 */
#define SCE_NET_ERROR_EBADMSG					-2143223464	/* 0x80410158 */

/**
 */
#define SCE_NET_ERROR_ENODATA					-2143223463	/* 0x80410159 */

/**
 */
#define SCE_NET_ERROR_ENOSR						-2143223462	/* 0x8041015A */

/**
 */
#define SCE_NET_ERROR_ENOSTR					-2143223461	/* 0x8041015B */

/**
 */
#define SCE_NET_ERROR_ETIME						-2143223460	/* 0x8041015C */

/**
 */
#define SCE_NET_ERROR_EADHOC					-2143223392	/* 0x804101A0 */

/**
 */
#define SCE_NET_ERROR_EDISABLEDIF				-2143223391	/* 0x804101A1 */

/**
 */
#define SCE_NET_ERROR_ERESUME					-2143223390	/* 0x804101A2 */

/**
 */
#define SCE_NET_ERROR_EIPADDRCHANGED			-2143223389	/* 0x804101A3 */

/**
 */
#define SCE_NET_ERROR_EINACTIVEDISABLED			-2143223389	/* 0x804101A3 */

/**
 */
#define SCE_NET_ERROR_ENOTINIT					-2143223352	/* 0x804101C8 */

/**
 */
#define SCE_NET_ERROR_ENOLIBMEM					-2143223351	/* 0x804101C9 */

/**
 */
#define SCE_NET_ERROR_ERESERVED202				-2143223350	/* 0x804101CA */

/**
 */
#define SCE_NET_ERROR_ECALLBACK					-2143223349	/* 0x804101CB */

/**
 */
#define SCE_NET_ERROR_EINTERNAL					-2143223348	/* 0x804101CC */

/**
 */
#define SCE_NET_ERROR_ERETURN					-2143223347	/* 0x804101CD */

/**
 */
#define SCE_NET_ERROR_RESOLVER_EINTERNAL		-2143223332	/* 0x804101DC */

/**
 */
#define SCE_NET_ERROR_RESOLVER_EBUSY			-2143223331	/* 0x804101DD */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ENOSPACE			-2143223330	/* 0x804101DE */

/**
 */
#define SCE_NET_ERROR_RESOLVER_EPACKET			-2143223329	/* 0x804101DF */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ERESERVED224		-2143223328	/* 0x804101E0 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ENODNS			-2143223327	/* 0x804101E1 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ETIMEDOUT		-2143223326	/* 0x804101E2 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ENOSUPPORT		-2143223325	/* 0x804101E3 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_EFORMAT			-2143223324	/* 0x804101E4 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ESERVERFAILURE	-2143223323	/* 0x804101E5 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ENOHOST			-2143223322	/* 0x804101E6 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ENOTIMPLEMENTED	-2143223321	/* 0x804101E7 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ESERVERREFUSED	-2143223320	/* 0x804101E8 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_ENORECORD		-2143223319	/* 0x804101E9 */

/**
 */
#define SCE_NET_ERROR_RESOLVER_EALIGNMENT		-2143223318	/* 0x804101EA */


/* kernel and libnet */
#define SCE_NET_EPERM           1
#define SCE_NET_ENOENT          2
#define SCE_NET_ESRCH           3
#define SCE_NET_EINTR           4
#define SCE_NET_EIO             5
#define SCE_NET_ENXIO           6
#define SCE_NET_E2BIG           7
#define SCE_NET_ENOEXEC         8
#define SCE_NET_EBADF           9
#define SCE_NET_ECHILD          10
#define SCE_NET_EDEADLK         11
#define SCE_NET_ENOMEM          12
#define SCE_NET_EACCES          13
#define SCE_NET_EFAULT          14
#define SCE_NET_ENOTBLK         15
#define SCE_NET_EBUSY           16
#define SCE_NET_EEXIST          17
#define SCE_NET_EXDEV           18
#define SCE_NET_ENODEV          19
#define SCE_NET_ENOTDIR         20
#define SCE_NET_EISDIR          21
#define SCE_NET_EINVAL          22
#define SCE_NET_ENFILE          23
#define SCE_NET_EMFILE          24
#define SCE_NET_ENOTTY          25
#define SCE_NET_ETXTBSY         26
#define SCE_NET_EFBIG           27
#define SCE_NET_ENOSPC          28
#define SCE_NET_ESPIPE          29
#define SCE_NET_EROFS           30
#define SCE_NET_EMLINK          31
#define SCE_NET_EPIPE           32
#define SCE_NET_EDOM            33
#define SCE_NET_ERANGE          34
#define SCE_NET_EAGAIN          35
#define SCE_NET_EWOULDBLOCK     SCE_NET_EAGAIN
#define SCE_NET_EINPROGRESS     36
#define SCE_NET_EALREADY        37
#define SCE_NET_ENOTSOCK        38
#define SCE_NET_EDESTADDRREQ    39
#define SCE_NET_EMSGSIZE        40
#define SCE_NET_EPROTOTYPE      41
#define SCE_NET_ENOPROTOOPT     42
#define SCE_NET_EPROTONOSUPPORT 43
#define SCE_NET_ESOCKTNOSUPPORT 44
#define SCE_NET_EOPNOTSUPP      45
#define SCE_NET_EPFNOSUPPORT    46
#define SCE_NET_EAFNOSUPPORT    47
#define SCE_NET_EADDRINUSE      48
#define SCE_NET_EADDRNOTAVAIL   49
#define SCE_NET_ENETDOWN        50
#define SCE_NET_ENETUNREACH     51
#define SCE_NET_ENETRESET       52
#define SCE_NET_ECONNABORTED    53
#define SCE_NET_ECONNRESET      54
#define SCE_NET_ENOBUFS         55
#define SCE_NET_EISCONN         56
#define SCE_NET_ENOTCONN        57
#define SCE_NET_ESHUTDOWN       58
#define SCE_NET_ETOOMANYREFS    59
#define SCE_NET_ETIMEDOUT       60
#define SCE_NET_ECONNREFUSED    61
#define SCE_NET_ELOOP           62
#define SCE_NET_ENAMETOOLONG    63
#define SCE_NET_EHOSTDOWN       64
#define SCE_NET_EHOSTUNREACH    65
#define SCE_NET_ENOTEMPTY       66
#define SCE_NET_EPROCLIM        67
#define SCE_NET_EUSERS          68
#define SCE_NET_EDQUOT          69
#define SCE_NET_ESTALE          70
#define SCE_NET_EREMOTE         71
#define SCE_NET_EBADRPC         72
#define SCE_NET_ERPCMISMATCH    73
#define SCE_NET_EPROGUNAVAIL    74
#define SCE_NET_EPROGMISMATCH   75
#define SCE_NET_EPROCUNAVAIL    76
#define SCE_NET_ENOLCK          77
#define SCE_NET_ENOSYS          78
#define SCE_NET_EFTYPE          79
#define SCE_NET_EAUTH           80
#define SCE_NET_ENEEDAUTH       81
#define SCE_NET_EIDRM           82
#define SCE_NET_ENOMSG          83
#define SCE_NET_EOVERFLOW       84
#define SCE_NET_EILSEQ          85
#define SCE_NET_ENOTSUP         86
#define SCE_NET_ECANCELED       87
#define SCE_NET_EBADMSG         88
#define SCE_NET_ENODATA         89
#define SCE_NET_ENOSR           90
#define SCE_NET_ENOSTR          91
#define SCE_NET_ETIME           92
#define SCE_NET_EADHOC          160
#define SCE_NET_EDISABLEDIF     161
#define SCE_NET_ERESUME         162
#define SCE_NET_EIPADDRCHANGED  163
#define SCE_NET_EINACTIVEDISABLED  SCE_NET_EIPADDRCHANGED

/* libnet */
#define SCE_NET_ENOTINIT                           200
#define SCE_NET_ENOLIBMEM                          201
#define SCE_NET_ETLS                               202
#define SCE_NET_ECALLBACK                          203
#define SCE_NET_EINTERNAL                          204
#define SCE_NET_ERETURN                            205

/* resolver */
#define SCE_NET_RESOLVER_EINTERNAL                 220
#define SCE_NET_RESOLVER_EBUSY                     221
#define SCE_NET_RESOLVER_ENOSPACE                  222
#define SCE_NET_RESOLVER_EPACKET                   223
#define SCE_NET_RESOLVER_ERESERVED224              224
#define SCE_NET_RESOLVER_ENODNS                    225
#define SCE_NET_RESOLVER_ETIMEDOUT                 226
#define SCE_NET_RESOLVER_ENOSUPPORT                227
#define SCE_NET_RESOLVER_EFORMAT                   228
#define SCE_NET_RESOLVER_ESERVERFAILURE            229
#define SCE_NET_RESOLVER_ENOHOST                   230
#define SCE_NET_RESOLVER_ENOTIMPLEMENTED           231
#define SCE_NET_RESOLVER_ESERVERREFUSED            232
#define SCE_NET_RESOLVER_ENORECORD                 233
#define SCE_NET_RESOLVER_EALIGNMENT                234

int *sceNetErrnoLoc(void);
#define sce_net_errno (*sceNetErrnoLoc())

#if defined(__cplusplus)
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_ERRNO_H_ */

