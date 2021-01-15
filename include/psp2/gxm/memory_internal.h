#ifndef _DOLCESDK_PSP2_GXM_MEMORY_INTERNAL_H_
#define _DOLCESDK_PSP2_GXM_MEMORY_INTERNAL_H_

/** @file

  	Memory mapping API for the GPU.
*/

#include <psp2/gxm/memory.h>

#ifdef	__cplusplus
extern "C" {
#endif	// def __cplusplus

/** The device heap ID when allocating memory using #sceGxmAllocDeviceMemLinux().

	@ingroup render
*/
typedef enum SceGxmDeviceHeapId {
	SCE_GXM_DEVICE_HEAP_ID_USER_NC,
	SCE_GXM_DEVICE_HEAP_ID_CDRAM,
	SCE_GXM_DEVICE_HEAP_ID_VERTEX_USSE,
	SCE_GXM_DEVICE_HEAP_ID_FRAGMENT_USSE
} SceGxmDeviceHeapId;

/** Memory info for memory allocated and mapped using #sceGxmAllocDeviceMemLinux().

	@ingroup render
*/
typedef struct SceGxmDeviceMemInfo {
	SceUID memBlockId;		///< The UID of the allocated memory block.
	void *mappedBase;		///< Base address of the allocated memory block.
	uint32_t offset;		///< USSE offset for vertex and fragment USSE memory.
	uint32_t size;			///< The size passed to #sceGxmAllocDeviceMemLinux().
	uint32_t heapId;		///< The device heap ID from #SceGxmDeviceHeapId.
} SceGxmDeviceMemInfo;

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

/** Allocates and maps memory for GPU usage.  The storage for the memory info is
	allocated by libgxm.

	@param[in]	heapId		Device memory heap ID from #SceGxmDeviceHeapId.
	@param[in]	flags		Bitwise combined attributes from #SceGxmMemoryAttribFlags.
	@param[in]	size		Size in bytes of the memory to allocate.
	@param[in]	alignment	This parameter is unused. Specify 0 or a power of 2.
	@param[out]	memInfo		Memory info of the allocated memory.

	@retval
	SCE_OK	The operation was completed successfully.
	@retval
	SCE_GXM_ERROR_OUT_OF_MEMORY There was no memory to perform the operation.
	@retval
	SCE_GXM_ERROR_INVALID_VALUE The operation failed because a parameter was invalid.
	@retval
	SCE_GXM_ERROR_INVALID_POINTER The operation failed because a pointer was invalid.
	@retval
	SCE_GXM_ERROR_INVALID_ALIGNMENT The operation failed due to invalid alignment.

	@ingroup render
*/
SceGxmErrorCode sceGxmAllocDeviceMemLinux(uint32_t heapId, uint32_t flags, uint32_t size, uint32_t alignment, SceGxmDeviceMemInfo **memInfo);

/** Unmaps and frees memory allocated with #sceGxmAllocDeviceMemLinux().  The
	storage for the memory info is freed by libgxm.

	@param[in]	memInfo		Memory info of the allocated memory.

	@retval
	SCE_OK	The operation was completed successfully.

	@ingroup render
*/
SceGxmErrorCode sceGxmFreeDeviceMemLinux(SceGxmDeviceMemInfo* memInfo);

#ifdef	__cplusplus
}
#endif	// def __cplusplus

#endif /* _DOLCESDK_PSP2_GXM_MEMORY_INTERNAL_H_ */
