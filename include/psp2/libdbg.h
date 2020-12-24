/**
 * \usergroup{SceDbg}
 * \usage{psp2/libdbg.h}
 */

#ifndef _DOLCESDK_PSP2_LIBDBG_H_
#define _DOLCESDK_PSP2_LIBDBG_H_

#include <stdbool.h>
#include <psp2/scebase_common.h>
#include <psp2/types.h>

#define SCE_DBG_SUBSTR_CONCATENATE(s1,s2) s1##s2
#define SCE_DBG_CONCATENATE(s1,s2)        SCE_DBG_SUBSTR_CONCATENATE(s1,s2)

#if defined(__GNUC__)
	#define _SCE_DBG_ATTRIBUTE_PRINTF(i) __attribute__ (( __format__(__printf__,i,i+1) ))
#else
	#define _SCE_DBG_ATTRIBUTE_PRINTF(i)
#endif

#ifndef SCE_BREAK
#define SCE_BREAK() _SCE_BREAK()
#endif

#ifndef SCE_STOP
#define SCE_STOP() _SCE_STOP()
#endif

#ifndef SCE_NORETURN_STOP
#define SCE_NORETURN_STOP() _SCE_NORETURN_STOP()
#endif

#ifndef SCE_DBG_ASSERTS_ENABLED
#define SCE_DBG_ASSERTS_ENABLED	0
#endif

#ifndef SCE_DBG_LOGGING_ENABLED
#define SCE_DBG_LOGGING_ENABLED	1
#endif

typedef enum SceDbgLogLevel {
	SCE_DBG_LOG_LEVEL_TRACE = 0,
	SCE_DBG_LOG_LEVEL_DEBUG,
	SCE_DBG_LOG_LEVEL_INFO,
	SCE_DBG_LOG_LEVEL_WARNING,
	SCE_DBG_LOG_LEVEL_ERROR,
	SCE_DBG_NUM_LOG_LEVELS
} SceDbgLogLevel;

typedef enum SceDbgBreakOnErrorState {
	SCE_DBG_DISABLE_BREAK_ON_ERROR = 0,
	SCE_DBG_ENABLE_BREAK_ON_ERROR
} SceDbgBreakOnErrorState;

typedef enum SceDbgBreakOnWarningState {
	SCE_DBG_DISABLE_BREAK_ON_WARNING = 0,
	SCE_DBG_ENABLE_BREAK_ON_WARNING
} SceDbgBreakOnWarningState;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

SceInt32 sceDbgSetMinimumLogLevel(SceInt32 minimumLogLevel);

SceInt32 sceDbgSetBreakOnErrorState(SceDbgBreakOnErrorState state);

SceInt32 sceDbgSetBreakOnWarningState(SceDbgBreakOnWarningState state);

/*----------------------------------------------------------------------------------------------------------------------*/

SceInt32 sceDbgAssertionHandler(
	const char *pFile,
	int line,
	bool stop,
	const char *pComponent,
	const char *pMessage, ...) _SCE_DBG_ATTRIBUTE_PRINTF(5);

SceInt32 sceDbgLoggingHandler(
	const char *pFile,
	int line,
	int severity,
	const char *pComponent,
	const char *pMessage, ...) _SCE_DBG_ATTRIBUTE_PRINTF(5);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

/*----------------------------------------------------------------------------------------------------------------------*/

#ifndef SCE_DBG_MINIMUM_LOG_LEVEL
#define SCE_DBG_MINIMUM_LOG_LEVEL SCE_DBG_LOG_LEVEL_TRACE
#endif

#ifndef SCE_DBG_LOG_PREFIX
#define SCE_DBG_LOG_PREFIX ""
#endif

#ifndef SCE_DBG_LOG_COMPONENT
#define SCE_DBG_LOG_COMPONENT ""
#endif

#define SCE_DBG_LOG_BASE(level, component, format, ...) \
	_SCE_MACRO_BEGIN \
		if (level >= SCE_DBG_MINIMUM_LOG_LEVEL) { \
			sceDbgLoggingHandler(__FILE__, __LINE__, level, component, SCE_DBG_LOG_PREFIX format, ##__VA_ARGS__); \
		} \
	_SCE_MACRO_END

#if SCE_DBG_LOGGING_ENABLED

#define SCE_DBG_LOG_TRACE(format, ...)   SCE_DBG_LOG_BASE(SCE_DBG_LOG_LEVEL_TRACE, SCE_DBG_LOG_COMPONENT, format, ##__VA_ARGS__)
#define SCE_DBG_LOG_DEBUG(format, ...)   SCE_DBG_LOG_BASE(SCE_DBG_LOG_LEVEL_DEBUG, SCE_DBG_LOG_COMPONENT, format, ##__VA_ARGS__)
#define SCE_DBG_LOG_INFO(format, ...)    SCE_DBG_LOG_BASE(SCE_DBG_LOG_LEVEL_INFO, SCE_DBG_LOG_COMPONENT, format, ##__VA_ARGS__)
#define SCE_DBG_LOG_WARNING(format, ...) SCE_DBG_LOG_BASE(SCE_DBG_LOG_LEVEL_WARNING, SCE_DBG_LOG_COMPONENT, format, ##__VA_ARGS__)
#define SCE_DBG_LOG_ERROR(format, ...)   SCE_DBG_LOG_BASE(SCE_DBG_LOG_LEVEL_ERROR, SCE_DBG_LOG_COMPONENT, format, ##__VA_ARGS__)

#else // SCE_DBG_LOGGING_ENABLED

#define SCE_DBG_LOG_TRACE(format, ...)
#define SCE_DBG_LOG_DEBUG(format, ...)
#define SCE_DBG_LOG_INFO(format, ...)
#define SCE_DBG_LOG_WARNING(format, ...)
#define SCE_DBG_LOG_ERROR(format, ...)

#endif // SCE_DBG_LOGGING_ENABLED

/*----------------------------------------------------------------------------------------------------------------------*/

#define SCE_DBG_ASSERT_PRIVATE(test,stop,stopaction,format,...) \
	_SCE_MACRO_BEGIN \
		if (SCE_UNLIKELY(!(test))) { \
			if (stop && sceDbgAssertionHandler(__FILE__,__LINE__,stop, \
			SCE_DBG_ASSERT_COMPONENT, format,##__VA_ARGS__)){ stopaction;	} \
	} \
	_SCE_MACRO_END

#ifndef SCE_DBG_ASSERT_COMPONENT
#define SCE_DBG_ASSERT_COMPONENT ""
#endif

#define SCE_DBG_ALWAYS_ASSERT(test)                  SCE_DBG_ASSERT_PRIVATE(test, true, SCE_BREAK(), "Assertion failed: %s\n",#test)
#define SCE_DBG_ALWAYS_ASSERT_MSG(test, msg, ...)    SCE_DBG_ASSERT_PRIVATE(test, true, SCE_BREAK(), msg, ##__VA_ARGS__)
#define SCE_DBG_ALWAYS_ASSERT_EQUAL(value, expected) SCE_DBG_ASSERT_PRIVATE((value == expected), true, SCE_BREAK(), "Assertion failed, values not equal\n")

#if SCE_DBG_ASSERTS_ENABLED

#define SCE_DBG_SIMPLE_ASSERT(test) \
	_SCE_MACRO_BEGIN \
		if (SCE_UNLIKELY(!(test))) { \
			SCE_BREAK(); \
		} \
	_SCE_MACRO_END

#define SCE_DBG_ASSERT(test)                  SCE_DBG_ASSERT_PRIVATE(test, true, SCE_BREAK(), "Assertion failed: %s\n", #test)
#define SCE_DBG_STOP_ASSERT(test)             SCE_DBG_ASSERT_PRIVATE(test, true, SCE_STOP(), "Assertion failed: %s\n", #test)
#define SCE_DBG_WARN_ASSERT(test)             SCE_DBG_ASSERT_PRIVATE(test, false, (void)0, "Warning - Assertion failed: %s\n", #test)
#define SCE_DBG_ASSERT_MSG(test, msg, ...)    SCE_DBG_ASSERT_PRIVATE(test, true, SCE_BREAK(), msg, ##__VA_ARGS__)
#define SCE_DBG_ASSERT_EQUAL(value, expected) SCE_DBG_ASSERT_PRIVATE(((value) == (expected)), true, SCE_BREAK(), "Assertion failed, values not equal\n")

#else // SCE_DBG_ASSERTS_ENABLED

#define SCE_DBG_SIMPLE_ASSERT(test)           _SCE_MACRO_BEGIN { (void)sizeof((test)); } _SCE_MACRO_END

#define SCE_DBG_ASSERT(test)                  _SCE_MACRO_BEGIN { (void)sizeof((test)); } _SCE_MACRO_END
#define SCE_DBG_STOP_ASSERT(test)             _SCE_MACRO_BEGIN { (void)sizeof((test)); } _SCE_MACRO_END
#define SCE_DBG_WARN_ASSERT(test)             _SCE_MACRO_BEGIN { (void)sizeof((test)); } _SCE_MACRO_END
#define SCE_DBG_ASSERT_MSG(test, msg, ...)    _SCE_MACRO_BEGIN { (void)sizeof((test)); } _SCE_MACRO_END
#define SCE_DBG_ASSERT_EQUAL(value, expected) _SCE_MACRO_BEGIN { (void)sizeof((value)); (void)sizeof(expected); } _SCE_MACRO_END

#endif // SCE_DBG_ASSERTS_ENABLED

#if SCE_DBG_ASSERTS_ENABLED

#define SCE_DBG_VERIFY(test)               SCE_DBG_ASSERT_PRIVATE(test, true, SCE_BREAK(), "Assertion failed: %s\n",#test)
#define SCE_DBG_VERIFY_MSG(test, msg, ...) SCE_DBG_ASSERT_PRIVATE(test, true, SCE_BREAK(), msg, ##__VA_ARGS__)

#else // SCE_DBG_ASSERTS_ENABLED

#define SCE_DBG_VERIFY(test)               ((void)(test))
#define SCE_DBG_VERIFY_MSG(test, msg, ...) ((void)(test))

#endif // SCE_DBG_ASSERTS_ENABLED

#ifndef SCE_UNLIKELY
#define SCE_UNLIKELY(expr) _SCE_UNLIKELY(expr)
#endif

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)

#if defined(__GNUC__)

#define SCE_DBG_STATIC_ASSERT(expr) static_assert(expr, #expr)

#else // defined(__GNUC__)

template <bool B> struct SCE_DBG_STATIC_ASSERT_FAILED;
template<> struct SCE_DBG_STATIC_ASSERT_FAILED<true> { };

#define SCE_DBG_STATIC_ASSERT(condition) \
	enum { \
		SCE_DBG_CONCATENATE(SCE_DBG_STATIC_ASSERT_ENUM_, __LINE__) \
		= sizeof(SCE_DBG_STATIC_ASSERT_FAILED< (bool)(condition) >) \
	}

#endif // defined(__GNUC__)

#else // defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)

#if defined(__GNUC__)

#define SCE_DBG_STATIC_ASSERT(expr) _Static_assert(expr, #expr)

#else // defined(__GNUC__)

#define SCE_DBG_STATIC_ASSERT(expr) \
	enum { SCE_DBG_CONCATENATE( SCE_DBG_STATIC_ASSERT_AT__LINE__, __LINE__) = 1/(expr) };

#endif // defined(__GNUC__)

#endif // defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)

#endif // _DOLCESDK_PSP2_LIBDBG_H_
