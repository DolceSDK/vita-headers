#ifndef _DOLCESDK_PSP2_GXM_CONTEXT_INTERNAL_H_
#define _DOLCESDK_PSP2_GXM_CONTEXT_INTERNAL_H_

/** @file
*/

#include <psp2/gxm/context.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Updates a YUV color profile. The visibility buffers will be used for all fragment jobs
	started after this function returns.

	This function is only supported on the immediate context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using a deferred context.

	The <c><i>cscIndex</i></c> parameter defines whether the profile being set will be active for
	textures that use YUV swizzles referencing CSC0 or CSC1.

	The default profile for CSC0 is #SCE_GXM_YUV_PROFILE_BT601_STANDARD, and the default profile for
	CSC1 is #SCE_GXM_YUV_PROFILE_BT709_STANDARD.

	@param[in,out]	immediateContext	A pointer to the immediate context.
	@param[in]		cscIndex		The CSC index (0 or 1).
	@param[in]		profile			The YUV color profile.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed due to an invalid input parameter, or because
	the context is not an immediate context.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetFragmentJobYuvProfile(
	SceGxmContext *immediateContext,
	uint32_t cscIndex,
	SceGxmYuvProfile profile);

/** Updates the visibility buffers. The visibility buffers will be used for all fragment jobs
	started after this function returns.

	This function is only supported on the immediate context, and it will return the
	#SCE_GXM_ERROR_INVALID_VALUE error code if called using a deferred context.

	The visibility buffer must be mapped with read/write access for the GPU, or page faults will
	occur.  The mapped region must extend from <c><i>bufferBase</i></c> for #SCE_GXM_GPU_CORE_COUNT times
	<c><i>stridePerCore</i></c> bytes.  In addition, the visibility slot index must be no more than
	<c><i>stridePerCore</i></c>/4 to ensure that the per-core buffers do not overlap.  Both the base
	address and stride must be aligned to #SCE_GXM_VISIBILITY_ALIGNMENT bytes.

	@param[in,out]	immediateContext	A pointer to the immediate context.
	@param[in]		bufferBase		The base address of the visibility buffer. The address must
									persist until fragment processing for the current scene has completed.
	@param[in]		stridePerCore	The stride between cores through the visibility buffer.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a parameter was unexpectedly <c>NULL</c>.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because the context is not an immediate context.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to either the base address or
	stride per core not being aligned to #SCE_GXM_VISIBILITY_ALIGNMENT bytes.

	@ingroup render
*/
SceGxmErrorCode sceGxmSetFragmentJobVisibilityBuffer(
	SceGxmContext *immediateContext,
	void *bufferBase,
	uint32_t stridePerCore);

/** Allocates a VDM buffer for Razor GPU Capture.

	@param[in]		context			A pointer to the rendering context.
	@param[in]		size			The size to allocate.
	@param[out]		mem				Receives the buffer address.

	@retval
	SCE_OK The operation was successful.
	@retval
	SCE_GXM_ERROR_RESERVE_FAILED The operation failed due to the VDM buffer callback
	function failing to provide sufficient memory.

	@ingroup render
*/
SceGxmErrorCode sceGxmRazorReplayReserveVdm(
	SceGxmContext *context,
	uint32_t size,
	void **mem);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_CONTEXT_INTERNAL_H_ */
