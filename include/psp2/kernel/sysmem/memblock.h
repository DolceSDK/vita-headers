#ifndef _DOLCESDK_PSP2_KERNEL_SYSMEM_MEMBLOCK_H_
#define _DOLCESDK_PSP2_KERNEL_SYSMEM_MEMBLOCK_H_

#include <psp2/cdefs.h>
#include <psp2/kernel/types.h>

/** @name sceKernelAllocMemBlockで指定可能なメモリタイプ
 */
/*@{*/

/**
 * memory block type for read write cache allocated on LPDDR2
 */
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_RW					0x0c20d060U

#define SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA				SCE_KERNEL_MEMBLOCK_TYPE_USER_RW

/**
 * memory block type for read execute cache allocated on LPDDR2
 */
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_RX					0x0c20d050U

/**
 * memory block type for read write uncache allocated on LPDDR2
 */
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_NC_RW					0x0c208060U

/**
 * alias of SCE_KERNEL_MEMBLOCK_TYPE_USER_NC_RW
 */
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE			SCE_KERNEL_MEMBLOCK_TYPE_USER_NC_RW

/**
 * alias of SCE_KERNEL_MEMBLOCK_TYPE_USER_NC_RW
 */
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE		SCE_KERNEL_MEMBLOCK_TYPE_USER_RW_UNCACHE

/**
 * memory block type for read write cache allocated on LPDDR2 physical continuous area
 */
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_RW		0x0c80d060U

/**
 * memory block type for read write uncache allocated on LPDDR2 physical continuous area
 */
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_MAIN_PHYCONT_NC_RW	0x0d808060U

/**
 * memory block type for read write uncache allocated on CDRAM
 */
#define SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW				0x09408060U

#define SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RWDATA			SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RW

/*@}*/

SCE_CDECL_BEGIN

#if !defined(_LANGUAGE_ASSEMBLY)

typedef struct SceKernelAllocMemBlockOpt0940 {
	SceSize		size;
	SceUInt32	attr;
	SceSize		alignment;
	SceUID		uidBaseBlock;
	const char	*strBaseBlockName;
} SceKernelAllocMemBlockOpt0940;

/**
 * Option parameter for sceKernelAllocMemBlock
 */
 typedef struct SceKernelAllocMemBlockOpt {
	/**
	 * size of this
	 */
	SceSize		size;

	/**
	 * attributes field
	 */
	SceUInt32	attr;

	/**
	 * alignment option
	 * must set SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_ALIGNMENT to 'attr'
	 */
	SceSize		alignment;

	/**
	 * reserved
	 */
	 SceUInt32	reserved;

	/**
	 * reserved2
	 */
	const char	*strBaseBlockName;

#if 0
	/**
	 * mapped base address [out]
	 */
	void		*mappedBase;

	/**
	 * mapped size [out]
	 */
	SceSize		mappedSize;

	/**
	 * memory type [out]
	 */
	SceKernelMemoryType	memoryType;

	SceUInt32	access;
#endif
} SceKernelAllocMemBlockOpt;

typedef struct SceKernelAllocMemBlockOptInternal {
	SceSize		size;
	SceUInt32	attr;
	SceSize		alignment;
	SceUID		uidBaseBlock;
	const char	*strBaseBlockName;
	SceUInt32	flags;					//! Unknown flags 0x10 or 0x30 for ::sceKernelOpenMemBlock
	SceUInt32	reserved[10];
} SceKernelAllocMemBlockOptInternal;

/**
 * Enable 'alignment' member
 */
#define SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_HAS_ALIGNMENT		0x00000004U

#define SCE_KERNEL_ALLOC_MEMBLOCK_ATTR_PHYCONT				0x00200000U

/**
 * Allocating memory block
 *
 * @param[in]	name			memory block name
 * @param[in]	vsize			memory block virtual size
 * @param[in]	flags			options
 * @retval		id				UID of memory block
 * @retval		<SCE_OK			Error code
 *
 */
SceUID sceKernelAllocMemBlock(
	const char *name,
	SceKernelMemBlockType type,
	SceSize vsize,
	const struct SceKernelAllocMemBlockOpt *pOpt);

/**
 * free memory block
 * @param[in] uid		block uid
 */
int sceKernelFreeMemBlock(SceUID uid);

/**
 * Get base address of memory block.
 * @param[in]  uid		block id
 * @param[out] ppBase	base address of memory block
 * @retval SCE_OK		success
 * @retval <SCE_OK		Error
 */
#if !defined(__INTELLISENSE__)
int sceKernelGetMemBlockBase(SceUID uid, void **ppBase)
	__attribute__((__nonnull__(2)));
#else	/* !defined(__INTELLISENSE__) */
int sceKernelGetMemBlockBase(SceUID uid, void **ppBase);
#endif	/* !defined(__INTELLISENSE__) */

/**
 * Find memory block by virtual range (base address and size)
 *  If size == 0, API returns a memory block which contains 'start'
 *  If size > 0, API returns a memory block just fit range [start, start + size].
 * @param[in]	vaddr	base address
 * @param[in]	size	address size
 * @retval		>=SCE_OK	block id
 * @retval		<SCE_OK		error
 */
SceUID sceKernelFindMemBlockByAddr(
	void *uaddr,
	SceSize size);

/**
 * type for memory block type used in sceKernelAllocMemBlock
 */
typedef int		SceKernelMemoryType;

/**
 * information structure for memory block
 */
typedef struct SceKernelMemBlockInfo {
	SceSize						size;			/**< sizeof this */
	void						*mappedBase;	/**< mapped base address */
	SceSize						mappedSize;		/**< mapped size */

	SceKernelMemoryType			memoryType;		/**< memory type like cache, uncache */

	SceUInt32					access;			/**< memory access permission */
	SceKernelMemBlockType		type;			/**< Memory Block type */

} SceKernelMemBlockInfo;

/*----- memory access permission -----*/

/**
 * readable memory
 */
#define SCE_KERNEL_MEMORY_ACCESS_R		0x04U

/**
 * writable memory
 */
#define SCE_KERNEL_MEMORY_ACCESS_W		0x02U

/**
 * executable memory
 */
#define SCE_KERNEL_MEMORY_ACCESS_X		0x01U

/*----- memory type -----*/

/**
 * uncache normal memory
 */
#define SCE_KERNEL_MEMORY_TYPE_NORMAL_NC			0x80

/**
 * cache normal memory
 */
#define SCE_KERNEL_MEMORY_TYPE_NORMAL				0xD0

/**
 * Get memory block information by giving virtual address
 * @param[in]		vbase	base address
 * @param[inout]	pInfo	pointer to information structure
 */
#if !defined(__INTELLISENSE__)
int sceKernelGetMemBlockInfoByAddr(
	void *vbase,
	SceKernelMemBlockInfo *pInfo)
	__attribute__((__nonnull__(1,2), __warn_unused_result__));
#else	/* !defined(__INTELLISENSE__) */
int sceKernelGetMemBlockInfoByAddr(
	void *vbase,
	SceKernelMemBlockInfo *pInfo);
#endif	/* !defined(__INTELLISENSE__) */

/**
 * Get memory block informaton by virtuak address range
 * @param[in]		vbase	base address
 * @param[in]		vsize   size
 * @param[inout]	pInfo	information structure
 */
#if !defined(__INTELLISENSE__)
int sceKernelGetMemBlockInfoByRange(
	void *vbase,
	SceSize vsize,
	SceKernelMemBlockInfo *pInfo)
	__attribute__((__nonnull__(1,3), __warn_unused_result__));
#else	/* !defined(__INTELLISENSE__) */
int sceKernelGetMemBlockInfoByRange(
	void *vbase,
	SceSize vsize,
	SceKernelMemBlockInfo *pInfo);
#endif	/* !defined(__INTELLISENSE__) */

#endif	/* !defined(_LANGUAGE_ASSEMBLY) */

SCE_CDECL_END

#endif  /* _DOLCESDK_PSP2_KERNEL_SYSMEM_MEMBLOCK_H_ */
