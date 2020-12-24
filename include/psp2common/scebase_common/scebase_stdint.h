#ifndef _DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_STDINT_H_
#define _DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_STDINT_H_

#include <psp2common/scebase_common/scebase_target.h>

#if !defined(SCE_SCEBASE_NO_STDINT_DEFS) && !defined(_SCE_SCEBASE_STDINT_DEFINED)

   #if _SCE_HOST_COMPILER_MSVC

      #if (_MSC_VER < 1600)
        #define _SCE_SCEBASE_STDINT_DEFINED

		typedef signed char			int8_t;
		typedef signed short		int16_t;
		typedef signed int			int32_t;
		typedef signed long long	int64_t;
		typedef unsigned char		uint8_t;
		typedef unsigned short		uint16_t;
		typedef unsigned int		uint32_t;
		typedef unsigned long long	uint64_t;

	    #ifndef _INTPTR_T_DEFINED
	    #if _SCE_TARGET_RT_PTR_SIZE_64
	    typedef __int64             intptr_t;
	    #else
	    typedef __w64 int            intptr_t;
	    #endif
	    #define _INTPTR_T_DEFINED
	    #endif

	    #ifndef _UINTPTR_T_DEFINED
	    #if _SCE_TARGET_RT_PTR_SIZE_64
	    typedef unsigned __int64    uintptr_t;
	    #else
	    typedef __w64 unsigned int   uintptr_t;
	    #endif
	    #define _UINTPTR_T_DEFINED
	    #endif
      #else /* (_MSC_VER < 1600)  */
		#include    <stdint.h>
	  #endif /* (_MSC_VER < 1600)  */

  #else /* #if !SCE_HOST_COMPILER_MSVC */

	#include    <stdint.h>

  #endif /* #if SCE_HOST_COMPILER_MSVC */

#endif /* !defined(SCE_SCEBASE_NO_STDINT_DEFS) && !defined(_SCE_SCEBASE_STDINT_DEFINED) */

#endif  /*	_DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_STDINT_H_ */
