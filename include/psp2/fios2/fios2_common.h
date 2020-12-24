/**
 * \usergroup{SceFios2}
 * \usage{psp2/fios2.h,SceFios2_stub}
 */

#ifndef _DOLCESDK_PSP2_FIOS2_COMMON_H_
#define _DOLCESDK_PSP2_FIOS2_COMMON_H_

#include <psp2/scebase_common.h>

#ifndef SCE_FIOS_LINKAGE
#define SCE_FIOS_LINKAGE      _SCE_IMPORT
#endif

#define SCE_FIOS_THREAD_LOCAL_SUPPORTED   0
#undef  SCE_FIOS_THREAD_LOCAL

#define SCE_FIOS_ATTRIBUTE(attr)        __attribute__(attr)
#define SCE_FIOS_ATTRIBUTE_GCC(attr)
#define SCE_FIOS_ATTRIBUTE_SENTINEL
#define SCE_FIOS_ATTRIBUTE_NONNULL(x)
#define SCE_FIOS_LIKELY(expr)            _SCE_LIKELY(!!(expr))
#define SCE_FIOS_UNLIKELY(expr)          _SCE_UNLIKELY(expr)
#define SCE_FIOS_UNUSED(param)           (void)&param

#define SCE_FIOS_RESTRICT
#define SCE_FIOS_DISK_CACHE   0
#define SCE_FIOS_CACHE        0

#endif
