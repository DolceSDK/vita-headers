/**
 * \usergroup{SceUlt}
 */

#ifndef _DOLCESDK_PSP2_ULT_COMMON_H_
#define _DOLCESDK_PSP2_ULT_COMMON_H_

#ifdef __psp2__
#include <psp2/sdk_version.h>
#define _SCE_ULT_VERSION (SCE_PSP2_SDK_VERSION & 0xffff0000)
#else
#define _SCE_ULT_VERSION 0x00930000
#endif

#ifndef SCE_ULT_MAX_NAME_LENGTH
#define SCE_ULT_MAX_NAME_LENGTH 31
#endif

#include <psp2/scebase_common.h>

typedef struct _SceUltOptParamHeader {
	int64_t __reserved__[2];
} _SceUltOptParamHeader;

#define SCE_ULT_THREAD_TYPE_KERNEL_THREAD             0x1
#define SCE_ULT_THREAD_TYPE_ULTHREAD                  0x2

#define SCE_ULT_THREAD_OPERATION_READER_LOCK          0x1
#define SCE_ULT_THREAD_OPERATION_WRITER_LOCK          0x2
#define SCE_ULT_THREAD_OPERATION_QUEUE_PUSH           0x3
#define SCE_ULT_THREAD_OPERATION_QUEUE_POP            0x4

#define SCE_ULT_READER_WRITER_LOCK_STATUS_UNLOCK      0x0
#define SCE_ULT_READER_WRITER_LOCK_STATUS_READER_LOCK 0x1
#define SCE_ULT_READER_WRITER_LOCK_STATUS_WRITER_LOCK 0x2

#define _SCE_ULT_WAIT_THREAD_INFO_SIZE                32
#define SCE_ULT_WAIT_THREAD_INFO_ALIGNMENT            8

typedef _SCE_ALIGN_BEG(SCE_ULT_WAIT_THREAD_INFO_ALIGNMENT) struct SceUltWaitThreadInfo {
	uint32_t size;
	int32_t threadType;
	uint32_t threadId;
	int32_t operation;
	uint64_t __reserved__[ (_SCE_ULT_WAIT_THREAD_INFO_SIZE - sizeof(uint32_t)*2 - sizeof(int32_t)*2)/ sizeof(uint64_t) ];
} _SCE_ALIGN_END(SCE_ULT_WAIT_THREAD_INFO_ALIGNMENT) SceUltWaitThreadInfo;

#endif /* _DOLCESDK_PSP2_ULT_COMMON_H_ */
