#ifndef _DOLCESDK_PSP2_NP_NP_TROPHY_H_
#define _DOLCESDK_PSP2_NP_NP_TROPHY_H_

#include <psp2/np/np_common.h>
#include <psp2/np/np_error.h>
#include <psp2/rtc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* sizes */
#define SCE_NP_TROPHY_NUM_MAX							(128)

#define SCE_NP_TROPHY_GAME_TITLE_MAX_SIZE				(128)
#define SCE_NP_TROPHY_GAME_DESCR_MAX_SIZE				(1024)
#define SCE_NP_TROPHY_GROUP_TITLE_MAX_SIZE				(128)
#define SCE_NP_TROPHY_GROUP_DESCR_MAX_SIZE				(1024)
#define SCE_NP_TROPHY_NAME_MAX_SIZE						(128)
#define SCE_NP_TROPHY_DESCR_MAX_SIZE					(1024)

/* grade */
#define SCE_NP_TROPHY_GRADE_UNKNOWN						(0)
#define SCE_NP_TROPHY_GRADE_PLATINUM					(1)
#define SCE_NP_TROPHY_GRADE_GOLD						(2)
#define SCE_NP_TROPHY_GRADE_SILVER						(3)
#define SCE_NP_TROPHY_GRADE_BRONZE						(4)

/* types */
typedef SceInt32 SceNpTrophyHandle;
typedef SceInt32 SceNpTrophyContext;
typedef SceInt32 SceNpTrophyId;
typedef SceInt32 SceNpTrophyGroupId;
typedef SceInt32 SceNpTrophyGrade;

#define SCE_NP_TROPHY_INVALID_HANDLE		(-1)
#define SCE_NP_TROPHY_INVALID_CONTEXT		(-1)
#define SCE_NP_TROPHY_INVALID_TROPHY_ID		(-1)
#define SCE_NP_TROPHY_INVALID_GROUP_ID		(-2)
#define SCE_NP_TROPHY_BASE_GAME_GROUP_ID	(-1)

typedef struct SceNpTrophyGameDetails {
	SceSize size;
	SceUInt32 numGroups;
	SceUInt32 numTrophies;
	SceUInt32 numPlatinum;
	SceUInt32 numGold;
	SceUInt32 numSilver;
	SceUInt32 numBronze;
	SceChar8 title[SCE_NP_TROPHY_GAME_TITLE_MAX_SIZE];
	SceChar8 description[SCE_NP_TROPHY_GAME_DESCR_MAX_SIZE];
} SceNpTrophyGameDetails;

typedef struct SceNpTrophyGameData {
	SceSize size;
	SceUInt32 unlockedTrophies;
	SceUInt32 unlockedPlatinum;
	SceUInt32 unlockedGold;
	SceUInt32 unlockedSilver;
	SceUInt32 unlockedBronze;
	SceUInt32 progressPercentage;
} SceNpTrophyGameData;

typedef struct SceNpTrophyGroupDetails {
	SceSize size;
	SceNpTrophyGroupId groupId;
	SceUInt32 numTrophies;
	SceUInt32 numPlatinum;
	SceUInt32 numGold;
	SceUInt32 numSilver;
	SceUInt32 numBronze;
	SceChar8 title[SCE_NP_TROPHY_GROUP_TITLE_MAX_SIZE];
	SceChar8 description[SCE_NP_TROPHY_GROUP_DESCR_MAX_SIZE];
} SceNpTrophyGroupDetails;

typedef struct SceNpTrophyGroupData {
	SceSize size;
	SceNpTrophyGroupId groupId;
	SceUInt32 unlockedTrophies;
	SceUInt32 unlockedPlatinum;
	SceUInt32 unlockedGold;
	SceUInt32 unlockedSilver;
	SceUInt32 unlockedBronze;
	SceUInt32 progressPercentage;
} SceNpTrophyGroupData;

typedef struct SceNpTrophyDetails {
	SceSize size;
	SceNpTrophyId trophyId;
	SceNpTrophyGrade trophyGrade;
	SceNpTrophyGroupId groupId;
	SceBool hidden;
	SceChar8 name[SCE_NP_TROPHY_NAME_MAX_SIZE];
	SceChar8 description[SCE_NP_TROPHY_DESCR_MAX_SIZE];
} SceNpTrophyDetails;

typedef struct SceNpTrophyData {
	SceSize size;
	SceNpTrophyId trophyId;
	SceBool unlocked;
	SceUInt8 reserved[4];
	SceRtcTick timestamp;
} SceNpTrophyData;

/* trophy flag array */
#define SCE_NP_TROPHY_FLAG_SETSIZE			(128)
#define SCE_NP_TROPHY_FLAG_BITS				(sizeof(SceNpTrophyFlagMask) * 8)
#define SCE_NP_TROPHY_FLAG_BITS_ALL			((SceNpTrophyFlagMask)-1)
#define SCE_NP_TROPHY_FLAG_BITS_SHIFT		(5)
#define SCE_NP_TROPHY_FLAG_BITS_MASK		(SCE_NP_TROPHY_FLAG_BITS - 1)
#define SCE_NP_TROPHY_FLAG_BITS_MAX			(SCE_NP_TROPHY_FLAG_SETSIZE - 1)

typedef SceUInt32 SceNpTrophyFlagMask;
typedef struct SceNpTrophyFlagArray {
	SceNpTrophyFlagMask flagBits[SCE_NP_TROPHY_FLAG_SETSIZE >> SCE_NP_TROPHY_FLAG_BITS_SHIFT];
} SceNpTrophyFlagArray;

#define SCE_NP_TROPHY_FLAG_SET(n, p) \
	((p)->flagBits[(n) >> SCE_NP_TROPHY_FLAG_BITS_SHIFT] |= (1 << ((n) & SCE_NP_TROPHY_FLAG_BITS_MASK)))
#define SCE_NP_TROPHY_FLAG_CLR(n, p) \
	((p)->flagBits[(n) >> SCE_NP_TROPHY_FLAG_BITS_SHIFT] &= ~(1 << ((n) & SCE_NP_TROPHY_FLAG_BITS_MASK)))
#define SCE_NP_TROPHY_FLAG_ISSET(n, p) \
	((p)->flagBits[(n) >> SCE_NP_TROPHY_FLAG_BITS_SHIFT] & (1 << ((n) & SCE_NP_TROPHY_FLAG_BITS_MASK)))
#define SCE_NP_TROPHY_FLAG_ZERO(p) do { \
	SceNpTrophyFlagArray *__fa = (p); \
	SceNpTrophyFlagMask __i; \
	for(__i = 0; __i < (SCE_NP_TROPHY_FLAG_SETSIZE >> SCE_NP_TROPHY_FLAG_BITS_SHIFT); __i++) \
		__fa->flagBits[__i] = 0; \
	} while(0)
#define SCE_NP_TROPHY_FLAG_SET_ALL(p) do { \
	SceNpTrophyFlagArray *__fa = (p); \
	SceNpTrophyFlagMask __i; \
	for(__i = 0; __i < (SCE_NP_TROPHY_FLAG_SETSIZE >> SCE_NP_TROPHY_FLAG_BITS_SHIFT); __i++) \
		__fa->flagBits[__i] = SCE_NP_TROPHY_FLAG_BITS_ALL; \
	} while(0)

/* functions */
int sceNpTrophyInit(void *opt);

int sceNpTrophyTerm(void);

int sceNpTrophyCreateHandle(
	SceNpTrophyHandle *handle
	);

int sceNpTrophyDestroyHandle(
	SceNpTrophyHandle handle
	);

int sceNpTrophyAbortHandle(
	SceNpTrophyHandle handle
	);

int sceNpTrophyCreateContext(
	SceNpTrophyContext *context,
	const SceNpCommunicationId *commId,
	const SceNpCommunicationSignature *commSign,
	SceUInt64 options
	);

int sceNpTrophyDestroyContext(
	SceNpTrophyContext context
	);

int sceNpTrophyUnlockTrophy(
	SceNpTrophyContext context,
	SceNpTrophyHandle handle,
	SceNpTrophyId trophyId,
	SceNpTrophyId *platinumId
	);

int sceNpTrophyGetTrophyUnlockState(
	SceNpTrophyContext context,
	SceNpTrophyHandle handle,
	SceNpTrophyFlagArray *flags,
	SceUInt32 *count
	);

int sceNpTrophyGetGameInfo(
	SceNpTrophyContext context,
	SceNpTrophyHandle handle,
	SceNpTrophyGameDetails *details,
	SceNpTrophyGameData *data
	);

int sceNpTrophyGetGroupInfo(
	SceNpTrophyContext context,
	SceNpTrophyHandle handle,
	SceNpTrophyGroupId groupId,
	SceNpTrophyGroupDetails *details,
	SceNpTrophyGroupData *data
	);

int sceNpTrophyGetTrophyInfo(
	SceNpTrophyContext context,
	SceNpTrophyHandle handle,
	SceNpTrophyId trophyId,
	SceNpTrophyDetails *details,
	SceNpTrophyData *data
	);

int sceNpTrophyGetGameIcon(
	SceNpTrophyContext context,
	SceNpTrophyHandle handle,
	void *buffer,
	SceSize *size
	);

int sceNpTrophyGetGroupIcon(
	SceNpTrophyContext context,
	SceNpTrophyHandle handle,
	SceNpTrophyGroupId groupId,
	void *buffer,
	SceSize *size
	);

int sceNpTrophyGetTrophyIcon(
	SceNpTrophyContext context,
	SceNpTrophyHandle handle,
	SceNpTrophyId trophyId,
	void *buffer,
	SceSize *size
	);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_NP_NP_TROPHY_H_ */
