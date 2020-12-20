#ifndef _DOLCESDK_PSP2_NP_NP_TUS_H
#define _DOLCESDK_PSP2_NP_NP_TUS_H

#include <psp2/rtc.h>
#include <psp2/np/np_common.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#define SCE_NP_TUS_DATA_INFO_MAX_SIZE		384
#define SCE_NP_TUS_MAX_CTX_NUM	(32)
#define SCE_NP_TUS_MAX_SLOT_NUM_PER_REQUEST	(64)
#define SCE_NP_TUS_MAX_USER_NUM_PER_REQUEST	(101)
#define SCE_NP_TUS_MAX_SELECTED_FRIENDS_NUM	(100)
#define SCE_NP_TUS_MAX_SLOT_NUM_PER_TRANS	SCE_NP_TUS_MAX_SLOT_NUM_PER_REQUEST
#define SCE_NP_TUS_MAX_USER_NUM_PER_TRANS	SCE_NP_TUS_MAX_USER_NUM_PER_REQUEST

#define SCE_NP_TUS_BINDMODE_ALL_FORBIDDEN	(0x0000)
#define SCE_NP_TUS_BINDMODE_RDONLY			(0x0001)
#define SCE_NP_TUS_BINDMODE_WRONLY			(0x0002)
#define SCE_NP_TUS_BINDMODE_RDWR			(SCE_NP_TUS_BINDMODE_RDONLY|SCE_NP_TUS_BINDMODE_WRONLY)
#define SCE_NP_TUS_BINDMODE_DEFAULT		SCE_NP_TUS_BINDMODE_RDWR


#if ! defined(__LANGUAGE_ASSEMBLY)

/* type definition */
typedef	SceInt32		SceNpTusSlotId;
typedef struct SceNpTusVirtualUserId {
	char data[SCE_NP_ONLINEID_MAX_LENGTH];
	char term;
	char dummy[3];
} SceNpTusVirtualUserId;

typedef	struct SceNpTusVariable{
	SceNpId ownerId;
	SceInt32 hasData;
	SceRtcTick lastChangedDate;
	SceUInt8 pad[4];
	SceNpId lastChangedAuthorId;
	SceInt64 variable;
	SceInt64 oldVariable;
	SceUInt8 reserved[16];
} SceNpTusVariable;

typedef	struct SceNpTusDataInfo{
	size_t infoSize;
	SceUInt8 pad[4];
	SceUInt8 data[SCE_NP_TUS_DATA_INFO_MAX_SIZE];
} SceNpTusDataInfo;

typedef	struct SceNpTusDataStatus{
	SceNpId ownerId;
	SceInt32 hasData;
	SceRtcTick lastChangedDate;
	SceNpId lastChangedAuthorId;
	void *data;
	size_t dataSize;
	SceUInt8 pad[4];
	SceNpTusDataInfo info;
} SceNpTusDataStatus;

typedef struct SceNpTusGetFriendsVariableOptParam{
	SceSize size;				/* (IN) set sizeof(SceNpTusGetFriendsVariableOptParam) */
	SceUInt32 *startSerialRank;	/* (IN) set pointer to startSerialRank. If unnecessary, set NULL. */
	SceUInt32 *hits;			/* (OUT) The total number of friends with TUS variable.If unnecessary, set NULL. */
} SceNpTusGetFriendsVariableOptParam;

typedef struct SceNpTusGetFriendsDataStatusOptParam{
	SceSize size;				/* (IN) set sizeof(SceNpTusGetFriendsDataStatusOptParam) */
	SceUInt32 *startSerialRank;	/* (IN) set pointer to startSerialRank.If unnecessary, set NULL.*/
	SceUInt32 *hits;			/* (OUT) The total number of friends with TUS DataStatus.If unnecessary, set NULL.*/
} SceNpTusGetFriendsDataStatusOptParam;

typedef enum {
	SCE_NP_TUS_OPETYPE_EQUAL = 1,
	SCE_NP_TUS_OPETYPE_NOT_EQUAL,
	SCE_NP_TUS_OPETYPE_GREATER_THAN,
	SCE_NP_TUS_OPETYPE_GREATER_OR_EQUAL,
	SCE_NP_TUS_OPETYPE_LESS_THAN,
	SCE_NP_TUS_OPETYPE_LESS_OR_EQUAL
} SceNpTusOeratorType;

typedef enum {
	SCE_NP_TUS_VARIABLE_SORTTYPE_DESCENDING_DATE=1,
	SCE_NP_TUS_VARIABLE_SORTTYPE_ASCENDING_DATE,
	SCE_NP_TUS_VARIABLE_SORTTYPE_DESCENDING_VALUE,
	SCE_NP_TUS_VARIABLE_SORTTYPE_ASCENDING_VALUE
} SceNpTusVariableSortType;

typedef enum {
	SCE_NP_TUS_DATASTATUS_SORTTYPE_DESCENDING_DATE=1,
	SCE_NP_TUS_DATASTATUS_SORTTYPE_ASCENDING_DATE
} SceNpTusDataStatusSortType;


/* prototype */

int sceNpTusInit(
	SceInt32	threadPriority,
	SceInt32	cpuAffinityMask,
	void		*option);
int sceNpTusTerm(void);

int sceNpTusCreateTitleCtx(
	const SceNpCommunicationId *communicationId,
	const SceNpCommunicationPassphrase *passphrase,
	const SceNpId *selfNpId
);

int sceNpTusDeleteTitleCtx(
	SceInt32 titleCtxId
);
#define sceNpTusDestroyTitleCtx(_titleCtxId) sceNpTusDeleteTitleCtx(_titleCtxId)

int	sceNpTusCreateRequest(
	SceInt32 titleCtxId
);
#define sceNpTusCreateTransactionCtx(_titleCtxId) sceNpTusCreateRequest(_titleCtxId)


int sceNpTusDeleteRequest (
	SceInt32 reqId
);
#define sceNpTusDestroyTransactionCtx(_reqId) sceNpTusDeleteRequest(_reqId)

int sceNpTusSetTimeout (
	SceInt32 ctxId,
	SceInt32 resolveRetry,
	SceInt32 resolveTimeout,
	SceInt32 connTimeout,
	SceInt32 sendTimeout,
	SceInt32 recvTimeout
);

int sceNpTusChangeModeForOtherSaveDataOwners(
	SceInt32 ctxId,
	SceInt32 mode
	);

int sceNpTusAbortRequest(
	SceInt32 reqId
);
#define sceNpTusAbortTransaction(_reqId) sceNpTusAbortRequest(_reqId)

int sceNpTusWaitAsync (
	SceInt32 reqId,
	SceInt32 *result
);
int sceNpTusPollAsync (
	SceInt32 reqId,
	SceInt32 *result
);

int sceNpTusSetMultiSlotVariable (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	const SceInt64 variableArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusSetMultiSlotVariableVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	const SceInt64 variableArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusSetMultiSlotVariableAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	const SceInt64 variableArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusSetMultiSlotVariableVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	const SceInt64 variableArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiSlotVariable (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiSlotVariableVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiSlotVariableAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiSlotVariableVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiUserVariable (
	SceInt32	reqId,
	const SceNpId targetNpIdArray[],
	SceNpTusSlotId slotId,
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiUserVariableVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId targetVirtualUserIdArray[],
	SceNpTusSlotId slotId,
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiUserVariableAsync (
	SceInt32	reqId,
	const SceNpId targetNpIdArray[],
	SceNpTusSlotId slotId,
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiUserVariableVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId targetVirtualUserIdArray[],
	SceNpTusSlotId slotId,
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetFriendsVariable (
	SceInt32 reqId,
	SceNpTusSlotId slotId,
	SceBool includeSelf,
	SceInt32 sortType,
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	SceNpTusGetFriendsVariableOptParam *option
);

int sceNpTusGetFriendsVariableAsync (
	SceInt32 reqId,
	SceNpTusSlotId slotId,
	SceBool includeSelf,
	SceInt32 sortType,
	SceNpTusVariable variableArray[],
	SceSize variableArraySize,
	SceInt32 arrayNum,
	SceNpTusGetFriendsVariableOptParam *option
);

int sceNpTusAddAndGetVariable (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	SceNpTusSlotId slotId,
	SceInt64 inVariable,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	SceNpTusVariable *outVariable,
	SceSize outVariableSize,
	void *option
);

int sceNpTusAddAndGetVariableVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	SceNpTusSlotId slotId,
	SceInt64 inVariable,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	SceNpTusVariable *outVariable,
	SceSize outVariableSize,
	void *option
);

int sceNpTusAddAndGetVariableAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	SceNpTusSlotId slotId,
	SceInt64 inVariable,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	SceNpTusVariable *outVariable,
	SceSize outVariableSize,
	void *option
);

int sceNpTusAddAndGetVariableVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	SceNpTusSlotId slotId,
	SceInt64 inVariable,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	SceNpTusVariable *outVariable,
	SceSize outVariableSize,
	void *option
);

int sceNpTusTryAndSetVariable (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	SceNpTusSlotId slotId,
	SceInt32 opeType,
	SceInt64 variable,
	const SceInt64 *compareValue,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	SceNpTusVariable *resultVariable,
	SceSize	resultVariableSize,
	void *option
);

int sceNpTusTryAndSetVariableVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	SceNpTusSlotId slotId,
	SceInt32 opeType,
	SceInt64 variable,
	const SceInt64 *compareValue,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	SceNpTusVariable *resultVariable,
	SceSize	resultVariableSize,
	void *option
);

int sceNpTusTryAndSetVariableAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	SceNpTusSlotId slotId,
	SceInt32 opeType,
	SceInt64 variable,
	const SceInt64 *compareValue,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	SceNpTusVariable *resultVariable,
	SceSize	resultVariableSize,
	void *option
);

int sceNpTusTryAndSetVariableVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	SceNpTusSlotId slotId,
	SceInt32 opeType,
	SceInt64 variable,
	const SceInt64 *compareValue,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	SceNpTusVariable *resultVariable,
	SceSize	resultVariableSize,
	void *option
);

int sceNpTusDeleteMultiSlotVariable (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusDeleteMultiSlotVariableVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusDeleteMultiSlotVariableAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusDeleteMultiSlotVariableVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusSetData (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	SceNpTusSlotId slotId,
	SceSize totalSize,
	SceSize sendSize,
	const void *data,
	const SceNpTusDataInfo *info,
	SceSize infoStructSize,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	void *option
);

int sceNpTusSetDataVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	SceNpTusSlotId slotId,
	SceSize totalSize,
	SceSize sendSize,
	const void *data,
	const SceNpTusDataInfo *info,
	SceSize infoStructSize,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	void *option
);

int sceNpTusSetDataAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	SceNpTusSlotId slotId,
	SceSize totalSize,
	SceSize sendSize,
	const void *data,
	const SceNpTusDataInfo *info,
	SceSize infoStructSize,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	void *option
);

int sceNpTusSetDataVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	SceNpTusSlotId slotId,
	SceSize totalSize,
	SceSize sendSize,
	const void *data,
	const SceNpTusDataInfo *info,
	SceSize infoStructSize,
	const SceNpId *isLastChangedAuthor,
	const SceRtcTick *isLastChangedDate,
	void *option
);

int sceNpTusGetData (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	SceNpTusSlotId slotId,
	SceNpTusDataStatus *dataStatus,
	SceSize dataStatusSize,
	void *data,
	SceSize recvSize,
	void *option
);

int sceNpTusGetDataVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	SceNpTusSlotId slotId,
	SceNpTusDataStatus *dataStatus,
	SceSize dataStatusSize,
	void *data,
	SceSize recvSize,
	void *option
);

int sceNpTusGetDataAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	SceNpTusSlotId slotId,
	SceNpTusDataStatus *dataStatus,
	SceSize dataStatusSize,
	void *data,
	SceSize recvSize,
	void *option
);

int sceNpTusGetDataVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	SceNpTusSlotId slotId,
	SceNpTusDataStatus *dataStatus,
	SceSize dataStatusSize,
	void *data,
	SceSize recvSize,
	void *option
);

int sceNpTusGetMultiSlotDataStatus (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	SceNpTusDataStatus statusArray[],
	SceSize statusArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiSlotDataStatusVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	SceNpTusDataStatus statusArray[],
	SceSize statusArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiSlotDataStatusAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	SceNpTusDataStatus statusArray[],
	SceSize statusArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiSlotDataStatusVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	SceNpTusDataStatus statusArray[],
	SceSize statusArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiUserDataStatus (
	SceInt32	reqId,
	const SceNpId targetNpIdArray[],
	SceNpTusSlotId slotId,
	SceNpTusDataStatus statusArray[],
	SceSize statusArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiUserDataStatusVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId targetVirtualUserIdArray[],
	SceNpTusSlotId slotId,
	SceNpTusDataStatus statusArray[],
	SceSize statusArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiUserDataStatusAsync (
	SceInt32	reqId,
	const SceNpId targetNpIdArray[],
	SceNpTusSlotId slotId,
	SceNpTusDataStatus statusArray[],
	size_t statusArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetMultiUserDataStatusVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId targetVirtualUserIdArray[],
	SceNpTusSlotId slotId,
	SceNpTusDataStatus statusArray[],
	size_t statusArraySize,
	SceInt32 arrayNum,
	void *option
);

int sceNpTusGetFriendsDataStatus (
	SceInt32 reqId,
	SceNpTusSlotId slotId,
	SceBool includeSelf,
	SceInt32 sortType,
	SceNpTusDataStatus statusArray[],
	SceSize statusArraySize,
	SceInt32 arrayNum,
	SceNpTusGetFriendsDataStatusOptParam *option
);

int sceNpTusGetFriendsDataStatusAsync (
	SceInt32 reqId,
	SceNpTusSlotId slotId,
	SceBool includeSelf,
	SceInt32 sortType,
	SceNpTusDataStatus statusArray[],
	SceSize statusArraySize,
	SceInt32 arrayNum,
	SceNpTusGetFriendsDataStatusOptParam *option
);

int sceNpTusDeleteMultiSlotData (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusDeleteMultiSlotDataVUser (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusDeleteMultiSlotDataAsync (
	SceInt32	reqId,
	const SceNpId *targetNpId,
	const SceNpTusSlotId slotIdArray[],
	SceInt32 arrayNum,
	void *option
);

int sceNpTusDeleteMultiSlotDataVUserAsync (
	SceInt32	reqId,
	const SceNpTusVirtualUserId *targetVirtualUserId,
	const SceNpTusSlotId slotIdArray[],
	SceInt32 arrayNum,
	void *option
);


#endif	/* !defined(__LANGUAGE_ASSEMBLY) */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */


#endif	/* _DOLCESDK_PSP2_NP_NP_TUS_H */
