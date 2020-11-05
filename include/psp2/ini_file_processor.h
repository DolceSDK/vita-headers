/**
 * \usergroup{SceIniFileProcessor}
 * \usage{psp2/ini_file_processor.h,SceIniFileProcessor_stub,SCE_SYSMODULE_INTERNAL_INI_FILE_PROCESSOR}
 */

#ifndef _DOLCESDK_PSP2_INI_FILE_PROCESSOR_H_
#define _DOLCESDK_PSP2_INI_FILE_PROCESSOR_H_

#define SCE_INI_FILE_PROCESSOR_ERROR_MODE           ((int)0x80840002)
#define SCE_INI_FILE_PROCESSOR_ERROR_EOF            ((int)0x80840005)
#define SCE_INI_FILE_PROCESSOR_ERROR_READ_ONLY      ((int)0x80840007)
#define SCE_INI_FILE_PROCESSOR_ERROR_FILE_NOT_FOUND ((int)0x80840009)
#define SCE_INI_FILE_PROCESSOR_ERROR_KEY_NOT_FOUND  ((int)0x80840010)

#define SCE_INI_FILE_PROCESSOR_PARSE_COMPLETED      0x00840001

#ifdef __cplusplus

#include <cstddef>

namespace sce {
namespace Ini {

class MemAllocator {
public:
	typedef void* (*Allocator)(size_t size);
	typedef void (*Deallocator)(void* ptr);

	Allocator allocate;
	Deallocator deallocate;
};

class InitParameter {
public:
	InitParameter();

	int unk_0x0; // size or mode? usually 0, seen: 0x1000, 0x2000
	int unk_0x4; // size or mode? usually 0, seen: 0x1000, 0x2000
	MemAllocator* allocator; // can be NULL
	int unk_0xc;
};

class IniFileProcessor {
public:
	IniFileProcessor();
	virtual ~IniFileProcessor();

	/**
	 * Initialize INI file processor to work with file
	 *
	 * @param[in] param - ::InitParameter
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int initialize(const InitParameter* param);

	/**
	 * Terminate INI file processor
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int terminate();

	/**
	 * Terminate INI file processor when file could not be opened
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int terminateForError();

	/**
	 * Get INI as a string. The returned buffer is not null-terminated.
	 *
	 * @param[out] ini - memory where INI data is stored
	 * @param[out] size - size of the INI data
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int serialize(const char** ini, size_t* size);

	/**
	 * Process INI as a string. Size is without null-terminator.
	 *
	 * @param[in] ini - memory where INI data is stored
	 * @param[in] size - size of the INI data
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int deserialize(const char* ini, size_t size);

	/**
	 * Open INI file
	 *
	 * @param[in] path - path to the INI file to open
	 * @param[in] mode - file open mode
	 * @param[in] unk - unknown, set to 0
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int open(const char* path, const char* mode, int unk);

	/**
	 * Create new INI file and open it. If file is already present, it will be overwritten
	 *
	 * @param[in] path - path to the INI file to open
	 * @param[in] mode - file open mode
	 * @param[in] unk - unknown, set to 0
	 *
	 * @return 0 on success, < 0 on error.
	 *
	 */
	int create(const char* path, const char* mode, int unk);

	/**
	 * Close INI file
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int close();

	/**
	 * Cleanup temp files
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int cleanup();

	/**
	 * Get total number of keys in the opened INI file
	 *
	 * @return toatal number of keys, < 0 on error.
	 */
	int size();

	/**
	 * Add key and set value for it
	 *
	 * @param[in] key - key string
	 * @param[in] value - value string
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int add(const char* key, const char* value);

	/**
	 * Delete key and corresponding value from INI file
	 *
	 * @param[in] key - key string
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int del(const char* key);

	/**
	 * Set value corresponding to set key
	 *
	 * @param[in] key - key string
	 * @param[in] value - value string
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int set(const char* key, const char* value);

	/**
	 * Find value corresponding to set key
	 *
	 * @param[in] key - key string
	 * @param[out] val - buffer to store value string if found
	 * @param[in] size - size of the output buffer
	 * @param[in] offset - offset into the value corresponding to key
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int get(const char* key, char* val, size_t size, size_t offset);

	/**
	 * Parse key and corresponding value, one key per call until eof
	 *
	 * @param[out] key - buffer to store key string
	 * @param[out] val - buffer to store value string
	 * @param[in] size - size of output buffers
	 *
	 * @return 0 on success, < 0 on error.
	 *
	 */
	int parse(char* key, char* val, size_t size);

	/**
	 * Reset parser to the beginning of the file
	 *
	 * @return 0 on success, < 0 on error.
	 */
	int reset();

private:
	void *context;
};

} // namespace Ini
} // namespace sce

#endif // __cplusplus

#endif // _DOLCESDK_PSP2_INI_FILE_PROCESSOR_H_
