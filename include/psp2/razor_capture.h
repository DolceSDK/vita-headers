#ifndef _DOLCESDK_PSP2_RAZOR_CAPTURE_H_
#define _DOLCESDK_PSP2_RAZOR_CAPTURE_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
	@brief		Sets a Razor GPU capture to start at the specified frame.

	@param		frameIndex			Index of frame to capture.

	@param		captureFilename		Filename to which capture is saved.

	@note		The frame index is counted as the number of calls made to
				<c>sceGxmPadHeartBeat()</c>.

	@see		sceGxmPadHeartBeat
**/

void sceRazorGpuCaptureSetTrigger(uint32_t frameIndex, const char *captureFilename);

/**
	@brief		Sets a Razor GPU capture to start at the next frame.

	@param		captureFilename		Filename to which capture is saved.

	@note		The frame index is counted as the number of calls made to
				<c>sceGxmPadHeartBeat()</c>.

	@see		sceGxmPadHeartBeat
**/

void sceRazorGpuCaptureSetTriggerNextFrame(const char *captureFilename);

/**
	@brief		Query whether a Razor GPU capture is in progress.

	@return		True if capture is in progress, false otherwise.
**/

bool sceRazorGpuCaptureIsInProgress(void);

/**
	Enables the Razor GPU Capture salvage mode.

	If salvage mode is enabled, minimal information about the jobs issued by
	libgxm to the GPU are saved in a ring buffer. If the GPU crashes, Razor
	attempts to produce a GPU Capture file based on the last 20 jobs submitted
	to the GPU. This file can be loaded into the Razor Host Tool for analysis.

	@note		This function should be called after the Razor Capture module
				is loaded, but before sceGxmInitialize().

	@note		Salvage mode should have minimal performance impact on the
				application where it is enabled.

	@note		Since capture is only performed after a GPU crash, some memory
				may have been overwritten since it was submitted to the GPU.
				Therefore, data in the generated capture may not always be
				accurate.

	@param		salvageFilename		Filename to which capture is saved if there is a GPU crash.
**/

void sceRazorGpuCaptureEnableSalvage(const char *salvageFilename);

/**
	@brief		Sets a Razor GPU capture to start at the specified frame.

	@param		frameIndex			Index of frame to capture.
	@param		captureFilename		Filename to which capture is saved.

	@note		The frame index is counted as the number of calls made to
				<c>sceGxmPadHeartBeat()</c>.

	@note		This function is deprecated: use <c>sceRazorGpuCaptureSetTrigger</c>.

	@see		sceGxmPadHeartBeat
**/

void sceRazorCaptureSetTrigger(uint32_t frameIndex, const char *captureFilename);

/**
	@brief		Sets a Razor GPU capture to start at the next frame.

	@param		captureFilename		Filename to which capture is saved.

	@note		The frame index is counted as the number of calls made to
				<c>sceGxmPadHeartBeat()</c>.

	@note		This function is deprecated: use <c>sceRazorGpuCaptureSetTriggerNextFrame</c>.

	@see		sceGxmPadHeartBeat
**/

void sceRazorCaptureSetTriggerNextFrame(const char *captureFilename);

/**
	@brief		Query whether a capture is in progress.

	@return		True if capture is in progress, false otherwise.

	@note		This function is deprecated: use <c>sceRazorGpuCaptureIsInProgress</c>.
**/

bool sceRazorCaptureIsInProgress(void);

#ifdef __cplusplus
}	/* extern "C" */
#endif


#endif	/* _DOLCESDK_PSP2_RAZOR_CAPTURE_H_ */



