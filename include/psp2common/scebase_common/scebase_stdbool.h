#ifndef _DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_STDBOOL_H_
#define _DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_STDBOOL_H_

#include <psp2common/scebase_common/scebase_target.h>

#if !defined(SCE_SCEBASE_NO_STDBOOL_DEFS) && !defined(_SCE_SCEBASE_STDBOOL_DEFINED)

	#ifndef __cplusplus
		#if _SCE_HOST_COMPILER_MSVC

            #define _SCE_SCEBASE_STDBOOL_DEFINED

			#if !defined(__BOOL_DEFINED) || !__BOOL_DEFINED
                #if _MSC_VER < 1800
				  typedef unsigned __int8    _Bool;
                #endif

				#define bool   _Bool
				#define false  0
				#define true   1

			#endif


		#else /* #if !SCE_HOST_COMPILER_MSVC */

			#include    <stdbool.h>

		#endif /* #if SCE_HOST_COMPILER_MSVC */
	#endif /* #ifndef __cplusplus */

#endif /* !defined(SCE_SCEBASE_NO_STDBOOL_DEFS) && !defined(_SCE_SCEBASE_STDBOOL_DEFINED) */

#endif  /*	_DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_STDBOOL_H_ */
