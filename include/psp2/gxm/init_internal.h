#ifndef _DOLCESDK_PSP2_GXM_INIT_INTERNAL_H_
#define _DOLCESDK_PSP2_GXM_INIT_INTERNAL_H_

/** @file
*/

#include <psp2/gxm/init.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Flags for libgxm initialization.

	@ingroup render
*/
typedef enum SceGxmInitializeFlagsInternal
{
	SCE_GXM_INITIALIZE_FLAG_PB_USE_USER_MEMORY			=	0x00000001U,	///< Use uncached main memory for the parameter buffer.
	SCE_GXM_INITIALIZE_FLAG_PBDESCFLAGS_ZLS_OVERRIDE	=	0x00000002U,
	SCE_GXM_INITIALIZE_FLAG_PBDESCFLAGS_SHARED			=	0x00000004U,	///< The parameter buffer can be shared between rendering contexts.
	SCE_GXM_INITIALIZE_FLAG_DRIVER_MEM_SHARE			=	0x00000008U		///< Use shared driver memory for the parameter buffer.
} SceGxmInitializeFlagsInternal;

/** Initializes the libgxm library for shared sync objects.

	Internally this function will prepare this process for rendering, creating
	the parameter buffer with the given size.

	This function must be called before any other libgxm object is created, such
	as a context, or sync object.

	@param[in]	params					A pointer to a populated SceGxmInitializeParams structure.

	@retval
	SCE_OK	The operation completed successfully.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER		The SceGxmInitializeParams pointer was <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE			One or more parameters were invalid.
	@retval
	SCE_GXM_ERROR_ALREADY_INITIALIZED	The operation failed because libgxm is already initialized.
	@retval
	SCE_GXM_ERROR_OUT_OF_MEMORY			There was no memory to perform the operation.
	@retval
	SCE_GXM_ERROR_DRIVER				The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmInitializeInternal(const SceGxmInitializeParams *params);

/** Checks if the libgxm library was initialized for shared sync objects.

	@return
	Returns <c>true</c> if the libgxm library was initialized for shared sync objects; otherwise <c>false</c> is returned.

	@ingroup render
*/
bool sceGxmIsInitializedInternal(void);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_INIT_INTERNAL_H_ */
