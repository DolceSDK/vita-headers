#ifndef _DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_TARGET_H_
#define _DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_TARGET_H_


#if defined(__ORBIS__)
	#define _SCE_MACRO_BEGIN				do {
	#define _SCE_MACRO_END					} while(0)

	#define _SCE_ALIGN_BEG(x)
	#define _SCE_ALIGN_END(x)						__attribute__((__aligned__(x)))

	#define _SCE_EXPECT(expr, val)					__builtin_expect((expr),(val))

	#define _SCE_TARGET_CPU_X86				1
	#define _SCE_TARGET_CPU_X86_X64			1

    #define _SCE_BREAK()         			_SCE_MACRO_BEGIN { __asm volatile ("int $0x41"); } _SCE_MACRO_END
    #define _SCE_STOP()          			_SCE_MACRO_BEGIN { __asm volatile ("int $0x42"); } _SCE_MACRO_END
    #define _SCE_NORETURN_STOP() 			_SCE_MACRO_BEGIN { __builtin_trap(); } _SCE_MACRO_END

	#define _SCE_TARGET_OS_ORBIS			1
#endif

#if defined(__SNC__)
	#define _SCE_HOST_COMPILER_SNC					1
#endif

#if defined(__GNUC__)
	#define _SCE_HOST_COMPILER_GCC					1
#endif

#if defined(__psp2__)
	#define _SCE_MACRO_BEGIN						do {
	#define _SCE_MACRO_END							} while(0)

	#define _SCE_ALIGN_BEG(x)
	#define _SCE_ALIGN_END(x)						__attribute__((__aligned__(x)))

	#define _SCE_EXPECT(expr, val)					__builtin_expect((expr),(val))

	#ifndef __SNC__
		#define _SCE_BREAK()						_SCE_MACRO_BEGIN { __asm__ volatile("bkpt 0x0000"); } _SCE_MACRO_END
		#define _SCE_STOP()							_SCE_MACRO_BEGIN { __asm__ volatile("bkpt 0x0002"); } _SCE_MACRO_END
		#define _SCE_NORETURN_STOP()				_SCE_MACRO_BEGIN { __asm__ volatile("bkpt 0x0001"); } _SCE_MACRO_END
	#else
		#define _SCE_BREAK()						_SCE_MACRO_BEGIN { __breakpoint(0); }_SCE_MACRO_END
		#define _SCE_STOP()							_SCE_MACRO_BEGIN { __breakpoint(2); }_SCE_MACRO_END
		#define _SCE_NORETURN_STOP()				_SCE_MACRO_BEGIN { __breakpoint(1); }_SCE_MACRO_END
	#endif

	#if defined(__ARMEL__)
		#define _SCE_TARGET_CPU_ARM					1


		/* assume these for now until SNC has predefines to be more specific */
		#define _SCE_TARGET_CPU_ARM_ARCH_V7			1
		#define _SCE_TARGET_CPU_ARM_CORTEX_A9_MPCORE 1

		#define _SCE_TARGET_CAPS_INT64				1
		#define _SCE_TARGET_CAPS_INT64_SW			1

		/* assume __fp16 for now until SNC has a predefine */
		#define _SCE_TARGET_CAPS_F16				1
		#define _SCE_TARGET_CAPS_F16_HW				1

		#define _SCE_TARGET_CAPS_F32				1
		#define _SCE_TARGET_CAPS_F32_HW				1
		#define _SCE_TARGET_CAPS_F64				1
		#define _SCE_TARGET_CAPS_F64_SW				1
	#endif

	#define _SCE_TARGET_OS_PSP2						1
#endif

#if defined(_MSC_VER)
	#define _SCE_HOST_COMPILER_MSVC					1
	#define _SCE_HOST_COMPILER_MSVC71				(_MSC_VER <= 1310)
	#define _SCE_HOST_COMPILER_MSVC80				(_MSC_VER >= 1400 && _MSC_VER < 1500)
	#define _SCE_HOST_COMPILER_MSVC90				(_MSC_VER >= 1500 && _MSC_VER < 1600)
	#define _SCE_HOST_COMPILER_MSVC100				(_MSC_VER >= 1600 && _MSC_VER < 1700)
	#define _SCE_HOST_COMPILER_MSVC110				(_MSC_VER >= 1700 && _MSC_VER < 1800)
	#define _SCE_HOST_COMPILER_MSVC120				(_MSC_VER >= 1800)

	#define _SCE_ALIGN_BEG(x)						__declspec( align(x) )
	#define _SCE_ALIGN_END(x)
	#define _SCE_EXPECT(expr, val)					(expr)


	#define _SCE_BREAK()							__debugbreak()
	#define _SCE_STOP()								__debugbreak()
	#define _SCE_NORETURN_STOP()					__debugbreak()


	#define _SCE_MACRO_BEGIN						do {
	#define _SCE_MACRO_END							\
		__pragma(warning(push))						\
		__pragma(warning(disable: 4127))			\
		} while (0)									\
		__pragma(warning(pop))

	#if defined(_M_IX86) || defined(_M_X64)
		#define _SCE_TARGET_CPU_X86					1
		#if defined(_M_IX86)
			#define _SCE_TARGET_CPU_X86_IA32		1
			#define _SCE_TARGET_CAPS_INT64_SW		1
		#elif defined(_M_X64)
			#define _SCE_TARGET_CPU_X86_X64			1
			#define _SCE_TARGET_CAPS_INT64_HW		1
		#endif

		#define _SCE_TARGET_CAPS_INT64				1
		#define _SCE_TARGET_CAPS_F32				1
		#define _SCE_TARGET_CAPS_F32_HW				1
		#define _SCE_TARGET_CAPS_F64				1
		#define _SCE_TARGET_CAPS_F64_HW				1
		#define _SCE_TARGET_CAPS_F80				1
		#define _SCE_TARGET_CAPS_F80_HW				1
	#else
		#error "Microsoft Visual C++ with unknown target cpu"
	#endif

	#if defined(_WIN32) || defined(_WIN64)
		#define _SCE_TARGET_OS_WINDOWS				1
		#if defined(_WIN32)
			#define _SCE_TARGET_OS_WIN32			1
		#endif
		#if defined(_WIN64)
			#define _SCE_TARGET_OS_WIN64			1
		#endif

	#else
		#error "Microsoft Visual C++ with unknown target runtime"
	#endif

#endif

/*
 * workaround for IntelliSense
 */

#if defined(__SNC__) && defined(__INTELLISENSE__)
#undef _SCE_ALIGN_BEG
#define _SCE_ALIGN_BEG(x)
#undef _SCE_ALIGN_END
#define _SCE_ALIGN_END(x)
#undef _SCE_EXPECT
#define _SCE_EXPECT(expr, val)						(expr)
#undef _SCE_BREAK
#define _SCE_BREAK()
#undef _SCE_STOP
#define _SCE_STOP()
#undef _SCE_NORETURN_STOP
#define _SCE_NORETURN_STOP()
#endif	/* defined(__SNC__) && defined(__INTELLISENSE__) */

/*
 * defined always
 */

#define _SCE_UNLIKELY(expr)							_SCE_EXPECT(expr,0)
#define _SCE_LIKELY(expr)							_SCE_EXPECT(expr,1)

/*
 * define the remaining settings to 0 so they may be used in runtime logic
 */

#if !defined(_SCE_HOST_COMPILER_MSVC)
	#define _SCE_HOST_COMPILER_MSVC					0
#endif
#if !defined(_SCE_HOST_COMPILER_MSVC71)
	#define _SCE_HOST_COMPILER_MSVC71				0
#endif
#if !defined(_SCE_HOST_COMPILER_MSVC80)
	#define _SCE_HOST_COMPILER_MSVC80				0
#endif
#if !defined(_SCE_HOST_COMPILER_MSVC90)
	#define _SCE_HOST_COMPILER_MSVC90				0
#endif
#if !defined(_SCE_HOST_COMPILER_MSVC100)
	#define _SCE_HOST_COMPILER_MSVC100				0
#endif
#if !defined(_SCE_HOST_COMPILER_MSVC110)
	#define _SCE_HOST_COMPILER_MSVC110				0
#endif
#if !defined(_SCE_HOST_COMPILER_MSVC120)
	#define _SCE_HOST_COMPILER_MSVC120				0
#endif
#if !defined(_SCE_HOST_COMPILER_GCC)
	#define _SCE_HOST_COMPILER_GCC					0
#endif
#if !defined(_SCE_HOST_COMPILER_GCC_SN)
	#define _SCE_HOST_COMPILER_GCC_SN				0
#endif
#if !defined(_SCE_HOST_COMPILER_SNC)
	#define _SCE_HOST_COMPILER_SNC					0
#endif

#if !defined(_SCE_TARGET_CPU_X86)
	#define _SCE_TARGET_CPU_X86						0
#endif
#if !defined(_SCE_TARGET_CPU_X86_IA32)
	#define _SCE_TARGET_CPU_X86_IA32				0
#endif
#if !defined(_SCE_TARGET_CPU_X86_X64)
	#define _SCE_TARGET_CPU_X86_X64					0
#endif
#if !defined(_SCE_TARGET_CPU_ARM)
	#define _SCE_TARGET_CPU_ARM						0
#endif
#if !defined(_SCE_TARGET_CPU_ARM_ARCH_V7)
	#define _SCE_TARGET_CPU_ARM_ARCH_V7				0
#endif
#if !defined(_SCE_TARGET_CPU_ARM_CORTEX_A8)
	#define _SCE_TARGET_CPU_ARM_CORTEX_A8			0
#endif
#if !defined(_SCE_TARGET_CPU_ARM_CORTEX_A9_MPCORE)
	#define _SCE_TARGET_CPU_ARM_CORTEX_A9_MPCORE	0
#endif



#if !defined(_SCE_TARGET_CAPS_INT64)
	#define _SCE_TARGET_CAPS_INT64					0
#endif
	#if !defined(_SCE_TARGET_CAPS_INT64_HW)
		#define _SCE_TARGET_CAPS_INT64_HW			0
	#endif
	#if !defined(_SCE_TARGET_CAPS_INT64_SW)
		#define _SCE_TARGET_CAPS_INT64_SW			0
	#endif
#if !defined(_SCE_TARGET_CAPS_INT128)
	#define _SCE_TARGET_CAPS_INT128					0
#endif
	#if !defined(_SCE_TARGET_CAPS_INT128_HW)
		#define _SCE_TARGET_CAPS_INT128_HW			0
	#endif
	#if !defined(_SCE_TARGET_CAPS_INT128_SW)
		#define _SCE_TARGET_CAPS_INT128_SW			0
	#endif
#if !defined(_SCE_TARGET_CAPS_F16)
	#define _SCE_TARGET_CAPS_F16					0
#endif
	#if !defined(_SCE_TARGET_CAPS_F16_HW)
		#define _SCE_TARGET_CAPS_F16_HW				0
	#endif
	#if !defined(_SCE_TARGET_CAPS_F16_SW)
		#define _SCE_TARGET_CAPS_F16_SW				0
	#endif
#if !defined(_SCE_TARGET_CAPS_F32)
	#define _SCE_TARGET_CAPS_F32					0
#endif
	#if !defined(_SCE_TARGET_CAPS_F32_HW)
		#define _SCE_TARGET_CAPS_F32_HW				0
	#endif
	#if !defined(_SCE_TARGET_CAPS_F32_SW)
		#define _SCE_TARGET_CAPS_F32_SW				0
	#endif
#if !defined(_SCE_TARGET_CAPS_F64)
	#define _SCE_TARGET_CAPS_F64					0
#endif
	#if !defined(_SCE_TARGET_CAPS_F64_HW)
		#define _SCE_TARGET_CAPS_F64_HW				0
	#endif
	#if !defined(_SCE_TARGET_CAPS_F64_SW)
		#define _SCE_TARGET_CAPS_F64_SW				0
	#endif
#if !defined(_SCE_TARGET_CAPS_F80)
	#define _SCE_TARGET_CAPS_F80					0
#endif
	#if !defined(_SCE_TARGET_CAPS_F80_HW)
		#define _SCE_TARGET_CAPS_F80_HW				0
	#endif
	#if !defined(_SCE_TARGET_CAPS_F80_SW)
		#define _SCE_TARGET_CAPS_F80_SW				0
	#endif


#if !defined(_SCE_IMPORT)
	#define _SCE_IMPORT
#endif
#if !defined(_SCE_EXPORT)
	#define _SCE_EXPORT
#endif



#if !defined(_SCE_TARGET_OS_ORBIS)
	#define _SCE_TARGET_OS_ORBIS					0
#endif
#if !defined(_SCE_TARGET_OS_PSP2)
	#define _SCE_TARGET_OS_PSP2						0
#endif
#if !defined(_SCE_TARGET_OS_WINDOWS)
	#define _SCE_TARGET_OS_WINDOWS					0
#endif
#if !defined(_SCE_TARGET_OS_WIN32)
	#define _SCE_TARGET_OS_WIN32					0
#endif
#if !defined(_SCE_TARGET_OS_WIN64)
	#define _SCE_TARGET_OS_WIN64					0
#endif

#if defined(__LP64__) || defined(_WIN64) || defined(_LP64)
	#define _SCE_TARGET_RT_PTR_SIZE_64				1
#else
	#define _SCE_TARGET_RT_PTR_SIZE_64				0
#endif
#define _SCE_TARGET_RT_PTR_SIZE_32					(!_SCE_TARGET_RT_PTR_SIZE_64)

#endif	/* _DOLCESDK_PSP2COMMON_SCEBASE_COMMON_SCEBASE_TARGET_H_ */
