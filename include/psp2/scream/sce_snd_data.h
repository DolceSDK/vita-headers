#ifndef _DOLCESDK_PSP2_SCREAM_SCE_SND_DATA_H_
#define _DOLCESDK_PSP2_SCREAM_SCE_SND_DATA_H_


#ifndef _DOLCESDK_PSP2_SCREAM_SCREAM_BASE_TYPES_H

    /// 8bit types
    #ifndef uint8_t
    typedef unsigned char           uint8_t;
    #endif
    #ifndef int8_t
    typedef signed char             int8_t;
    #endif

    /// 16 bit types
    #ifndef uint16_t
    typedef unsigned short          uint16_t;
    #endif
    #ifndef int16_t
    typedef signed short            int16_t;
    #endif

    /// 32 bit types
    #ifndef uint32_t
    typedef unsigned int            uint32_t;
    #endif
    #ifndef int32_t
    typedef signed int              int32_t;
    #endif

    #ifndef BOOL
    typedef int                     BOOL;
    #endif

    #ifndef float32_t
    typedef float                   float32_t;
    #endif

    /// 64 bit types
    #ifndef uint64_t
    typedef unsigned long long      uint64_t;
    #endif
    #ifndef int64_t
    typedef signed long long        int64_t;
    #endif

    #ifndef FALSE
        #define FALSE (0 == 1)
    #endif

    #ifndef TRUE
        #define TRUE (1 == 1)
    #endif

#endif //_DOLCESDK_PSP2_SCREAM_SCREAM_BASE_TYPES_H

#if (defined(_cplusplus) || defined(__cplusplus))
extern "C"
{
#endif

#if (!defined(_cplusplus) && !defined(__cplusplus))
#ifndef false
    #define false (0)
#endif

#ifndef true
    #define true (1)
#endif
#endif // (!defined(_cplusplus) && !defined(__cplusplus))

// version 2 of the SFXBlock2 structure...
/**
@ingroup screamDataStructures

@brief
Stores data for loaded Sound Banks.

This structure stores data for loaded Sound Banks.

@note
Pointers to SceScreamSFXBlock2 structures are often used as handles for Scream banks. De-referencing these pointers, and inspecting or modifying the members of this structure is not
recommended.
*/
typedef struct SceScreamSFXBlock2{
    // inspection of SceScreamSFXBlock2 not needed -- Scream uses pointers to this structure as handles
    uint32_t reserved[16];      ///< For internal use only.
} SceScreamSFXBlock2, *SceScreamSFXBlock2Ptr;

#if (defined(_cplusplus) || defined(__cplusplus))
}  //extern "C"
#endif

#endif //_DOLCESDK_PSP2_SCREAM_SCE_SND_DATA_H_

