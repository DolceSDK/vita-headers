#ifndef _DOLCESDK_PSP2_NET_NET_H_
#define _DOLCESDK_PSP2_NET_NET_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct SceNetInitParam {
	void *memory;
	int size;
	int flags;
} SceNetInitParam;

int sceNetInit(SceNetInitParam *param);
int sceNetTerm(void);

int sceNetShowIfconfig(void);
int sceNetShowRoute(void);
int sceNetShowNetstat(void);

#if defined(__cplusplus)
}
#endif

/* This is for backward compatibility with Vitasdk */
#if !defined(_DOLCESDK_PSP2_NET_H_)
#pragma message "<psp2/net/net.h> has been split into multiple files. Please include <psp2/net.h>."
#include <psp2/net.h>
#endif

#endif	/* _DOLCESDK_PSP2_NET_NET_H_ */

