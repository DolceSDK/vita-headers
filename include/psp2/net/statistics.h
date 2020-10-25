#ifndef _DOLCESDK_PSP2_NET_STATISTICS_H_
#define _DOLCESDK_PSP2_NET_STATISTICS_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct SceNetStatisticsInfo {
	/* kernel */
	int kernel_mem_free_size;
	int kernel_mem_free_min;
	int packet_count;
	int packet_qos_count;
	/* libnet */
	int libnet_mem_free_size;
	int libnet_mem_free_min;
} SceNetStatisticsInfo;

int sceNetGetStatisticsInfo(SceNetStatisticsInfo *info, int flags);

#if defined(__cplusplus)
}
#endif

#endif	/* _DOLCESDK_PSP2_NET_STATISTICS_H_ */

