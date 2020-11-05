#ifndef _DOLCESDK_PSP2_GXM_MEMORY_INTERNAL_H_
#define _DOLCESDK_PSP2_GXM_MEMORY_INTERNAL_H_

/** @file

  	Memory mapping API for the GPU.
*/

#include <psp2/gxm/memory.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** Checks if memory is mapped for GPU usage. If mapped, pointers within the region of
	memory described by <c><i>base</i></c> and <c><i>size</i></c> may be used with libgxm
	functions directly.

	@param[in]	base		The base address of the region to check.
	@param[in]	size		The size in bytes of the region to check.
	@param[in]	attribs		Bitwise combined attributes from #SceGxmMemoryAttribFlags.

	@retval
	SCE_OK	The memory region is mapped with <c><i>attribs</i></c>.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.
	@retval
	SCE_GXM_ERROR_INVALID_MAPPING The memory region is not mapped with <c><i>attribs</i></c>.

	@ingroup render
*/
SceGxmErrorCode sceGxmCheckMappedMemory(void *base, uint32_t size, uint32_t attribs);

/** Maps memory for vertex USSE code usage.  If successful, this mapping
	operation returns a USSE offset to address the memory as vertex USSE code.

	@param[in]	base	A 4K-aligned base address of the region to map.
	@param[in]	size	A 4K-aligned size in bytes of the region to map. This
						cannot be greater than 8MB.
	@param[in]	offset	A pointer to a 32-bit value to hold the USSE offset.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a parameter was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmMapVertexUsseMemoryInternal(void *base, uint32_t size, uint32_t *offset);

/** Unmaps memory that was previously mapped as vertex USSE code.  It is the
	responsibility of the caller to ensure that the GPU no longer needs this
	memory for rendering.  This could be accomplished by calling #sceGxmFinish()
	before unmapping.

	@param[in]	base	The base address of the region to unmap.  This must match
						the base address that was used when mapping the memory
						using #sceGxmMapVertexUsseMemory().

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmUnmapVertexUsseMemoryInternal(void *base);

/** Maps memory for fragment USSE code usage.  If successful, this mapping
	operation returns a USSE offset to address the memory as fragment USSE code.

	@param[in]	base	A 4K-aligned base address of the region to map.
	@param[in]	size	A 4K-aligned size in bytes of the region to map. This
						cannot be greater than 8MB.
	@param[in]	offset	A pointer to a 32-bit value to hold the USSE offset.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a parameter was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmMapFragmentUsseMemoryInternal(void *base, uint32_t size, uint32_t *offset);

/** Unmaps memory that was previously mapped as fragment USSE code.  It is the
	responsibility of the caller to ensure that the GPU no longer needs this
	memory for rendering.  This could be accomplished by calling #sceGxmFinish()
	before unmapping.

	@param[in]	base	The base address of the region to unmap.  This must match
						the base address that was used when mapping the memory
						using #sceGxmMapFragmentUsseMemory().

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_UNINITIALIZED The operation failed because the library was not initialized.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_DRIVER The operation failed due to a driver error.

	@ingroup render
*/
SceGxmErrorCode sceGxmUnmapFragmentUsseMemoryInternal(void *base);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_MEMORY_INTERNAL_H_ */
