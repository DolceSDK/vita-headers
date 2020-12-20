#ifndef _DOLCESDK_PSP2_NP_NP_RANKING_H
#define _DOLCESDK_PSP2_NP_NP_RANKING_H

#include <psp2/rtc.h>
#include <psp2/np/np_common.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#define SCE_NP_SCORE_COMMENT_MAXLEN			(63)
#define SCE_NP_SCORE_GAMEINFO_MAXSIZE		(189)
#define SCE_NP_SCORE_CENSOR_COMMENT_MAXLEN		(255)
#define SCE_NP_SCORE_SANITIZE_COMMENT_MAXLEN	(255)

#define SCE_NP_SCORE_NORMAL_UPDATE			0
#define SCE_NP_SCORE_FORCE_UPDATE			1

#define SCE_NP_SCORE_DESCENDING_ORDER		0
#define SCE_NP_SCORE_ASCENDING_ORDER		1

#define SCE_NP_SCORE_MAX_RANGE_NUM_PER_REQUEST	(100)
#define SCE_NP_SCORE_MAX_NPID_NUM_PER_REQUEST	(101)
#define SCE_NP_SCORE_MAX_SELECTED_FRIENDS_NUM	(100)

#define SCE_NP_SCORE_MAX_RANGE_NUM_PER_TRANS	SCE_NP_SCORE_MAX_RANGE_NUM_PER_REQUEST
#define SCE_NP_SCORE_MAX_NPID_NUM_PER_TRANS		SCE_NP_SCORE_MAX_NPID_NUM_PER_REQUEST

#define SCE_NP_SCORE_MAX_CTX_NUM	(32)

#define SCE_NP_SCORE_BINDMODE_ALL_FORBIDDEN	(0x0000)
#define SCE_NP_SCORE_BINDMODE_RDONLY			(0x0001)
#define SCE_NP_SCORE_BINDMODE_WRONLY			(0x0002)
#define SCE_NP_SCORE_BINDMODE_RDWR				(SCE_NP_SCORE_BINDMODE_RDONLY|SCE_NP_SCORE_BINDMODE_WRONLY)
#define SCE_NP_SCORE_BINDMODE_DEFAULT			SCE_NP_SCORE_BINDMODE_RDWR

/* obsolete value */
#define SCE_NP_SCORE_GAMEINFO_OBSOLETE_SIZE_MAX	(192)
#define SCE_NP_SCORE_GAMEINFO_SIZE_MAX		SCE_NP_SCORE_GAMEINFO_OBSOLETE_SIZE_MAX


#if ! defined(__LANGUAGE_ASSEMBLY)

/* type definition */
typedef	SceUInt32	SceNpScoreBoardId;
typedef SceInt64		SceNpScoreValue;
typedef	SceUInt32	SceNpScoreRankNumber;
typedef	SceInt32		SceNpScorePcId;

typedef	struct SceNpScoreGameInfo{
	SceSize		infoSize;
	SceUInt8	pad[4];
	SceUInt8	data[SCE_NP_SCORE_GAMEINFO_MAXSIZE];
	SceUInt8	pad2[3];
} SceNpScoreGameInfo;

typedef	struct SceNpScoreComment{
	char utf8Comment[SCE_NP_SCORE_COMMENT_MAXLEN+1];
} SceNpScoreComment;

typedef	struct SceNpScoreRankData{
	SceNpId					npId;
	SceUInt8				reserved[49];
	SceUInt8				pad0[3];
	SceNpScorePcId			pcId;
	SceNpScoreRankNumber	serialRank;
	SceNpScoreRankNumber	rank;
	SceNpScoreRankNumber	highestRank;
	SceInt32					hasGameData;
	SceUInt8					pad1[4];
	SceNpScoreValue			scoreValue;
	SceRtcTick				recordDate;
} SceNpScoreRankData;

typedef	struct SceNpScorePlayerRankData{
	SceInt32				hasData;
	SceUInt8				pad0[4];
	SceNpScoreRankData	rankData;
} SceNpScorePlayerRankData;

typedef	struct SceNpScoreBoardInfo{
	SceUInt32		rankLimit;
	SceUInt32		updateMode;
	SceUInt32		sortMode;
	SceUInt32		uploadNumLimit;
	SceSize		uploadSizeLimit;
} SceNpScoreBoardInfo;

typedef struct SceNpScoreNpIdPcId {
	SceNpId npId;
	SceNpScorePcId pcId;
	SceUInt8 pad[4];
} SceNpScoreNpIdPcId;

typedef struct SceNpScoreGetFriendRankingOptParam{
	SceSize size;								/* (IN) set sizeof(SceNpScoreGetFriendRankingOptParam) */
	SceNpScoreRankNumber	*startSerialRank;	/* (IN) set pointer to startSerialRank. If unnecessary, set NULL.*/
	SceNpScoreRankNumber	*hits;				/* (OUT) The total number of friends with score.If unnecessary, set NULL. */
} SceNpScoreGetFriendRankingOptParam;

/* prototype */

int sceNpScoreInit(
	SceInt32	threadPriority,
	SceInt32	cpuAffinityMask,
	void		*option
);
int	sceNpScoreTerm(void);

int	sceNpScoreCreateTitleCtx(
	const SceNpCommunicationId *titleId,
	const SceNpCommunicationPassphrase *passphrase,
	const SceNpId *selfNpId
);

int	sceNpScoreDeleteTitleCtx(
	SceInt32 titleCtxId
);
#define sceNpScoreDestroyTitleCtx(_titleCtxId) sceNpScoreDeleteTitleCtx(_titleCtxId)

int	sceNpScoreCreateRequest(
	SceInt32 titleCtxId
);
#define sceNpScoreCreateTransactionCtx(_titleCtxId) sceNpScoreCreateRequest(_titleCtxId)

int	sceNpScoreDeleteRequest (
	SceInt32 reqId
);
#define sceNpScoreDestroyTransactionCtx(_reqId) sceNpScoreDeleteRequest(_reqId)

int sceNpScoreAbortRequest (
	SceInt32 reqId
);
#define sceNpScoreAbortTransaction(_reqId) sceNpScoreAbortRequest(_reqId)

int sceNpScoreSetTimeout(
	SceInt32 id,
	SceInt32 resolveRetry,
	SceInt32 resolveTimeout,
	SceInt32 connTimeout,
	SceInt32 sendTimeout,
	SceInt32 recvTimeout
);

int sceNpScoreSetPlayerCharacterId (
	SceInt32 id,
	SceNpScorePcId pcId
);

int sceNpScoreChangeModeForOtherSaveDataOwners(
	SceInt32 ctxId,
	SceInt32 mode
	);

int	sceNpScoreGetBoardInfo(
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	SceNpScoreBoardInfo *boardInfo,
	void *option
);


int	sceNpScoreRecordScore (
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	SceNpScoreValue score,
	const SceNpScoreComment *scoreComment,
	const SceNpScoreGameInfo *gameInfo,
	SceNpScoreRankNumber *tmpRank,
	const SceRtcTick *compareDate,
	void *option
);

int	sceNpScoreRecordGameData (
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	SceNpScoreValue score,
	SceSize	totalSize,
	SceSize	sendSize,
	const void	*data,
	void *option
);

int	sceNpScoreGetGameData (
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	const SceNpId *npId,
	SceSize	*totalSize,
	SceSize	recvSize,
	void		*data,
	void *option
);

int	sceNpScoreGetRankingByNpId(
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	const SceNpId			*npIdArray,
	SceSize					npIdArraySize,
	SceNpScorePlayerRankData *rankArray,
	SceSize					rankArraySize,
	SceNpScoreComment	*commentArray,
	SceSize				commentArraySize,
	SceNpScoreGameInfo *infoArray,
	SceSize				infoArraySize,
	SceSize	arrayNum,
	SceRtcTick	*lastSortDate,
	SceNpScoreRankNumber	*totalRecord,
	void *option
);

int	sceNpScoreGetRankingByRange(
	SceInt32					reqId,
	SceNpScoreBoardId		boardId,
	SceNpScoreRankNumber	startSerialRank,
	SceNpScoreRankData		*rankArray,
	SceSize					rankArraySize,
	SceNpScoreComment		*commentArray,
	SceSize					commentArraySize,
	SceNpScoreGameInfo		*infoArray,
	SceSize					infoArraySize,
	SceSize					arrayNum,
	SceRtcTick				*lastSortDate,
	SceNpScoreRankNumber	*totalRecord,
	void *option
);


int sceNpScoreGetRankingByNpIdPcId(
	SceInt32 reqId,
	SceNpScoreBoardId boardId,
	const SceNpScoreNpIdPcId *idArray,
	SceSize idArraySize,
	SceNpScorePlayerRankData *rankArray,
	SceSize rankArraySize,
	SceNpScoreComment *commentArray,
	SceSize commentArraySize,
	SceNpScoreGameInfo *infoArray,
	SceSize infoArraySize,
	SceSize arrayNum,
	SceRtcTick *lastSortDate,
	SceNpScoreRankNumber *totalRecord,
	void *option
);

int	sceNpScoreCensorComment (
	SceInt32	reqId,
	const char *comment,
	void *option
);

int	sceNpScoreSanitizeComment (
	SceInt32	reqId,
	const char *comment,
	char *sanitizedComment,
	void *option
);

int	sceNpScoreWaitAsync (
	SceInt32 id,
	SceInt32 *result
);
int	sceNpScorePollAsync (
	SceInt32 reqId,
	SceInt32 *result
);
int	sceNpScoreGetBoardInfoAsync(
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	SceNpScoreBoardInfo *boardInfo,
	void *option
);
int	sceNpScoreRecordScoreAsync (
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	SceNpScoreValue score,
	const SceNpScoreComment *scoreComment,
	const SceNpScoreGameInfo *gameInfo,
	SceNpScoreRankNumber *tmpRank,
	const SceRtcTick *compareDate,
	void *option
);
int	sceNpScoreRecordGameDataAsync (
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	SceNpScoreValue score,
	SceSize	totalSize,
	SceSize	sendSize,
	const void	*data,
	void *option
);

int	sceNpScoreGetGameDataAsync (
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	const SceNpId *npId,
	SceSize	*totalSize,
	SceSize	recvSize,
	void		*data,
	void *option
);

int	sceNpScoreGetRankingByNpIdAsync(
	SceInt32	reqId,
	SceNpScoreBoardId boardId,
	const SceNpId		*npIdArray,
	SceSize				npIdArraySize,
	SceNpScorePlayerRankData *rankArray,
	SceSize				rankArraySize,
	SceNpScoreComment  *commentArray,
	SceSize				commentArraySize,
	SceNpScoreGameInfo *infoArray,
	SceSize				infoArraySize,
	SceSize	arrayNum,
	SceRtcTick	*lastSortDate,
	SceNpScoreRankNumber	*totalRecord,
	void *option
);

int	sceNpScoreGetRankingByRangeAsync(
	SceInt32					reqId,
	SceNpScoreBoardId		boardId,
	SceNpScoreRankNumber	startSerialRank,
	SceNpScoreRankData		*rankArray,
	SceSize					rankArraySize,
	SceNpScoreComment		*commentArray,
	SceSize					commentArraySize,
	SceNpScoreGameInfo		*infoArray,
	SceSize					infoArraySize,
	SceSize					arrayNum,
	SceRtcTick				*lastSortDate,
	SceNpScoreRankNumber	 *totalRecord,
	void *option
);

int sceNpScoreGetRankingByNpIdPcIdAsync(
	SceInt32 reqId,
	SceNpScoreBoardId boardId,
	const SceNpScoreNpIdPcId *idArray,
	SceSize idArraySize,
	SceNpScorePlayerRankData *rankArray,
	SceSize rankArraySize,
	SceNpScoreComment *commentArray,
	SceSize commentArraySize,
	SceNpScoreGameInfo *infoArray,
	SceSize infoArraySize,
	SceSize arrayNum,
	SceRtcTick *lastSortDate,
	SceNpScoreRankNumber *totalRecord,
	void *option
);

int sceNpScoreGetFriendsRanking (
	SceInt32 reqId,
	SceNpScoreBoardId boardId,
	SceBool includeSelf,
	SceNpScoreRankData *rankArray,
	SceSize rankArraySize,
	SceNpScoreComment *commentArray,
	SceSize commentArraySize,
	SceNpScoreGameInfo *infoArray,
	SceSize infoArraySize,
	SceSize arrayNum,
	SceRtcTick *lastSortDate,
	SceNpScoreRankNumber *totalRecord,
	SceNpScoreGetFriendRankingOptParam *option
);

int sceNpScoreGetFriendsRankingAsync(
	SceInt32 reqId,
	SceNpScoreBoardId boardId,
	SceBool includeSelf,
	SceNpScoreRankData *rankArray,
	SceSize rankArraySize,
	SceNpScoreComment *commentArray,
	SceSize commentArraySize,
	SceNpScoreGameInfo *infoArray,
	SceSize infoArraySize,
	SceSize arrayNum,
	SceRtcTick *lastSortDate,
	SceNpScoreRankNumber *totalRecord,
	SceNpScoreGetFriendRankingOptParam *option
);

int	sceNpScoreCensorCommentAsync (
	SceInt32	reqId,
	const char *comment,
	void *option
);

int	sceNpScoreSanitizeCommentAsync (
	SceInt32	reqId,
	const char *comment,
	char *sanitizedComment,
	void *option
);



#endif	/* !defined(__LANGUAGE_ASSEMBLY) */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif	/* _DOLCESDK_PSP2_NP_NP_RANKING_H */
