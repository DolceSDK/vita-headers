#ifndef _DOLCESDK_PSP2_NP_NP_MESSAGE_H_
#define _DOLCESDK_PSP2_NP_NP_MESSAGE_H_

#include <psp2/scebase.h>
#include <psp2/types.h>
#include <psp2/kernel/clib.h>
#include <psp2/np/np_common.h>
#include <psp2/np/np_error.h>

#if defined(_LANGUAGE_C_PLUS_PLUS) || defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/*E Constants ---------------------------------------------------------------------------- */

/*E Message type definition */
typedef SceInt32 SceNpMessageType;
#define SCE_NP_MESSAGE_TYPE_INVALID					(0)			/*E Invalid message						*/
#define SCE_NP_MESSAGE_TYPE_APP_DATA_ATTACHMENT		(1)			/*E App data attachement message		*/
#define SCE_NP_MESSAGE_TYPE_INVITATION_ATTACHMENT	(2)			/*E Invitation data attachement message	*/
#define SCE_NP_MESSAGE_TYPE_STORE_LINK_ATTACHMENT	(3)			/*E Store link attachement message		*/

/*E Message filter definition */
typedef SceInt32 SceNpMessageFilter;
#define SCE_NP_MESSAGE_FILTER_NONE					(0x0000)	/*E Don't use filter						*/
#define SCE_NP_MESSAGE_FILTER_INCLUDE_USED			(0x0001)	/*E gets messages even if they are used		*/
#define SCE_NP_MESSAGE_FILTER_INCLUDE_EXPIRED		(0x0002)	/*E gets messages even if they are expired	*/

#define SCE_NP_MESSAGE_FILTER_IGNORE_USED			SCE_NP_MESSAGE_FILTER_INCLUDE_USED
#define SCE_NP_MESSAGE_FILTER_IGNORE_EXPIRED		SCE_NP_MESSAGE_FILTER_INCLUDE_EXPIRED

/*E Maximum number definitions */
#define SCE_NP_MESSAGE_MAX_MESSAGE_ID_SIZE			(70)		/*E max byte size of message id			 */
#define SCE_NP_MESSAGE_MAX_PREVIEW_SIZE				(128)		/*E max byte size of the message preview */
#define SCE_NP_MESSAGE_MAX_RECIPIENTS				(16)		/*E max destinations for send message dialog	*/
#define SCE_NP_MESSAGE_MAX_BODY_SIZE				(512)		/*E max message body size (byte)				*/
#define SCE_NP_MESSAGE_MAX_ATTACHMENT_SIZE			(1024*1024)	/*E max attachment data size (byte)				*/
#define SCE_NP_MESSAGE_MAX_INDEX_ICON_SIZE			(64*1024)	/*E max index icon size (byte)					*/

/*E Message flag definition */
#define SCE_NP_MESSAGE_FLAG_SEEN					0x02		/*E Message has been read						*/
#define SCE_NP_MESSAGE_FLAG_DELETED					0x08		/*E Message is "deleted" for removal by later EXPUNGE */
#define SCE_NP_MESSAGE_FLAG_USED					0x80		/*E Attached data has been used					*/

/*E Structures ---------------------------------------------------------------------------- */

/*E Setting structure for message detail dialog mode */
typedef struct SceNpMessageParam {
	SceUInt32			sdkVersion;		/*E SDK version will be overwritten（Please use sceNpMessageParamInit() to initialize）	*/
	SceNpMessageType	messageType;	/*E define message type to process		*/
	SceNpMessageFilter	filter;			/*E filter of the NP Message			*/
	SceChar8			reserved[32];	/*E reserved (must be filled with 0x00）*/
} SceNpMessageParam;


/*E NP Message ID definition */
typedef struct SceNpMessageId {
	SceChar8	uid[SCE_NP_MESSAGE_MAX_MESSAGE_ID_SIZE];
	SceChar8	term;
	SceChar8	padding[1];
} SceNpMessageId;

/*E NP Message entry information definition */
typedef struct SceNpMessageEntry {
	SceNpMessageId	messageId;									/*E ID of the message					*/
	SceDateTime		dateTime;									/*E message send date time				*/
	SceNpId			from;										/*E message sender's npId				*/
	SceChar8		preview[SCE_NP_MESSAGE_MAX_PREVIEW_SIZE];	/*E message for previewing				*/
	SceDateTime		expirationDate;								/*E expiration date of the message		*/
	SceUInt16		messageFlag;								/*E message flag						*/
	SceChar8		reserved[30];								/*E reserved (must be filled with 0x00)	*/
} SceNpMessageEntry;



/*E Functions --------------------------------------------------------------------------- */

/*E Initial Parameter initialize function */
static inline
void sceNpMessageParamInit(SceNpMessageParam *param)
{
	sceClibMemset(param, 0x00, sizeof(SceNpMessageParam));
	param->sdkVersion = SCE_PSP2_SDK_VERSION;
	param->messageType = SCE_NP_MESSAGE_TYPE_INVALID;
	param->filter = SCE_NP_MESSAGE_FILTER_NONE;
}

/*E Initialize Function with Parameter */
SceInt32 sceNpMessageInitWithParam(
	const SceNpMessageParam *param				/*E [in] initialize parameter	*/
);

/*E Initialize Function	*/
SceInt32 sceNpMessageInit(
	const SceNpMessageType messageType			/*E [in] define message type to process	*/
);

/*E Finalize Function	*/
SceInt32 sceNpMessageTerm(void);

/*E Synchronize message	*/
SceInt32 sceNpMessageSyncMessage(void);

/*E Count messages */
SceInt32 sceNpMessageGetMessageEntryCount(
	SceInt32				*totalCount,		/*E [out] total message count for the application and message type	*/
	SceInt32				*newCount			/*E [out] un-read messages count of totalCount						*/
);

/*E Get message entries */
/*E This API provide messages for the application and same SceNpMessageType declared at sceNpMessageInit()			*/
SceInt32 sceNpMessageGetMessageEntries(
	SceInt32				offset,				/*E [in] get message entries from the offset index					*/
												/*E      value 0 means getting from the newest message.				*/
	SceInt32				limit,				/*E [in] max messages to get (from 1 to 50)							*/
	SceNpMessageEntry		*entries,			/*E [out]set SceNpMessageEntry array for receiveing message entry	*/
												/*E      SceNpMessageEntry array size must be more than limit.		*/
	SceInt32				*storedCount		/*E [out]received message entries count will be stored				*/
);

/*E Get message entry */
SceInt32 sceNpMessageGetMessageEntry(
	SceNpMessageId			*messageId,			/*E [in] message Id to get message entry					*/
	SceNpMessageEntry		*entry				/*E [out]set SceNpMessageEntry for receiveing message entry	*/
);

/*E Get message body */
SceInt32 sceNpMessageGetMessage(
	SceNpMessageId			*messageId,			/*E [in] message Id to get message body					*/
	SceChar8				*buffer,			/*E [out]set buffer to receive message body				*/
	SceSize					bufferSize,			/*E [in] set byte size of the buffer					*/
	SceSize					*storedSize			/*E [out]received message body size will be stored		*/
);

/*E Get attached data */
SceInt32 sceNpMessageGetAttachedData(
	SceNpMessageId			*messageId,			/*E [in] message Id to get attached data				*/
	SceChar8				*buffer,			/*E [out]set buffer to receive attached data			*/
	SceSize					bufferSize,			/*E [in]  set byte size of the buffer					*/
	SceSize					*storedSize			/*E [out]received message body size will be stored		*/
);

/*E Set attached data used flag */
SceInt32 sceNpMessageSetAttachedDataUsedFlag(
	SceNpMessageId			*messageId			/*E [in] message Id to set attached data used flag		*/
);

//--------------------------- other --------------------------------------------

/*E Abort current API call */
/*E This API is asynchronous call. */
SceInt32 sceNpMessageAbort(void);

//-----------------------------------------------------------------------


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
} /* extern "C" */
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_MESSAGE_H_ */

