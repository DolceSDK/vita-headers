/**
 * \usergroup{SceNotificationUtil}
 * \usage{psp2/notification_util.h,SceNotificationUtil_stub,SCE_SYSMODULE_NOTIFICATION_UTIL}
 */


#ifndef _DOLCESDK_PSP2_NOTIFICATION_UTIL_H_
#define _DOLCESDK_PSP2_NOTIFICATION_UTIL_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Errors
 */
#define SCE_NOTIFICATION_UTIL_ERROR_INTERNAL               (-2146409727) /* 0x80106301 */

/**
 * Constants
 */
#define SCE_NOTIFICATION_UTIL_TEXT_MAX                     (0x3F)

/**
 * Callback for when a BGDL-type notification is cancelled through the notification tray
 */
typedef void (*SceNotificationUtilCancelCallback)(void *userData);

/**
 * Structs
 */
typedef struct SceNotificationUtilSendParam {
	SceWChar16 text[SCE_NOTIFICATION_UTIL_TEXT_MAX+1];       // must be null-terminated
	char unk_80[0x3E8];
	SceInt32 unk_468;                                        // must be set to 0
	SceInt32 unk_46C;                                        // must be set to 0
} SceNotificationUtilSendParam;

typedef struct SceNotificationUtilProgressInitParam {
	SceWChar16 text[SCE_NOTIFICATION_UTIL_TEXT_MAX+1];       // must be null-terminated
	SceWChar16 subText[SCE_NOTIFICATION_UTIL_TEXT_MAX+1];    // must be null-terminated
	char unk_100[0x3E8];
	SceNotificationUtilCancelCallback cancelCallback;
	void *userData;                                          // optional data for the callback
	SceWChar16 cancelText[SCE_NOTIFICATION_UTIL_TEXT_MAX+1]; // must be null-terminated
} SceNotificationUtilProgressInitParam;

typedef struct SceNotificationUtilProgressUpdateParam {
	SceWChar16 text[SCE_NOTIFICATION_UTIL_TEXT_MAX+1];       // must be null-terminated
	SceWChar16 subText[SCE_NOTIFICATION_UTIL_TEXT_MAX+1];    // must be null-terminated
	SceFloat progress;                                       // from 0.0 to 100.0
} SceNotificationUtilProgressUpdateParam;

typedef struct SceNotificationUtilProgressFinishParam {
	SceWChar16 text[SCE_NOTIFICATION_UTIL_TEXT_MAX+1];       // must be null-terminated
	SceWChar16 subText[SCE_NOTIFICATION_UTIL_TEXT_MAX+1];    // must be null-terminated
	char unk_100[0x3E8];
} SceNotificationUtilProgressFinishParam;

/**
 * Initialize notification util for use with BG application.
 *
 * Does not need to be called for normal applications.
 */
SceInt32 sceNotificationUtilBgAppInitialize(void);

/**
 * Send notification.
 */
SceInt32 sceNotificationUtilSendNotification(const SceNotificationUtilSendParam* sendParam);

/**
 * Clean notifications for calling app from notification history.
 */
SceInt32 sceNotificationUtilCleanHistory(void);

/**
 * Start BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressBegin(const SceNotificationUtilProgressInitParam* initParam);

/**
 * Update BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressUpdate(const SceNotificationUtilProgressUpdateParam* updateParam);

/**
 * Finish BGDL-type notification.
 */
SceInt32 sceNotificationUtilProgressFinish(const SceNotificationUtilProgressFinishParam* finishParam);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_NOTIFICATION_UTIL_H_ */
