#ifndef _DOLCESDK_PSP2_NP_NP_MATCHING2_H_
#define _DOLCESDK_PSP2_NP_NP_MATCHING2_H_

#include <stdbool.h>
#include <psp2/rtc.h>
#include <psp2/net.h>
#include <psp2/np/np_auth.h>
#include <psp2/np/np_common.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/*E
 *******************************************************************************
 * Sizes
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * サイズ
 *******************************************************************************
 */

#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_BIN_ATTR_EXTERNAL_MAX_SIZE   64
#define SCE_NP_MATCHING2_ROOM_BIN_ATTR_EXTERNAL_MAX_SIZE              256
#define SCE_NP_MATCHING2_ROOM_BIN_ATTR_INTERNAL_MAX_SIZE              256
#define SCE_NP_MATCHING2_ROOMMEMBER_BIN_ATTR_INTERNAL_MAX_SIZE        64
#define SCE_NP_MATCHING2_LOBBY_BIN_ATTR_INTERNAL_MAX_SIZE             256
#define SCE_NP_MATCHING2_LOBBYMEMBER_BIN_ATTR_INTERNAL_MAX_SIZE       64
#define SCE_NP_MATCHING2_USER_BIN_ATTR_MAX_SIZE                       128
#define SCE_NP_MATCHING2_CHAT_MSG_MAX_SIZE                            1024
#define SCE_NP_MATCHING2_BIN_MSG_MAX_SIZE                             1024
#define SCE_NP_MATCHING2_PRESENCE_OPTION_DATA_MAX_SIZE                16

#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_WORLD_INFO_LIST                         3848
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_USER_INFO_LIST                          17604
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_ROOM_MEMBER_DATA_EXTERNAL_LIST          15624
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_ROOM_DATA_EXTERNAL_LIST                 25768
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_CREATE_JOIN_ROOM                            1304
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_JOIN_ROOM                                   24488
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_SEARCH_ROOM                                 25776
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_SEND_ROOM_CHAT_MESSAGE                      1
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_ROOM_DATA_INTERNAL                      24488
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_ROOM_MEMBER_DATA_INTERNAL               372
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_LOBBY_INFO_LIST                         1296
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_JOIN_LOBBY                                  1124
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_SEND_LOBBY_CHAT_MESSAGE                     1
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_LOBBY_MEMBER_DATA_INTERNAL              672
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_LOBBY_MEMBER_DATA_INTERNAL_LIST         42760
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_GET_LOBBY_MEMBER_DATA_INTERNAL_LIST_NO_EX   20488
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_SIGNALING_GET_PING_INFO                     40

#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_ROOM_MEMBER_UPDATE_INFO                     396
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_ROOM_OWNER_UPDATE_INFO                      40
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_ROOM_UPDATE_INFO                            28
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_ROOM_DATA_INTERNAL_UPDATE_INFO              25404
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_ROOM_MEMBER_DATA_INTERNAL_UPDATE_INFO       493
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_ROOM_MESSAGE_INFO                           1407
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_LOBBY_MEMBER_UPDATE_INFO                    696
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_LOBBY_UPDATE_INFO                           8
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_LOBBY_MEMBER_DATA_INTERNAL_UPDATE_INFO     472
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_LOBBY_MESSAGE_INFO                         1790
#define SCE_NP_MATCHING2_EVENT_DATA_MAX_SIZE_SIGNALING_OPT_PARAM_UPDATE_INFO            8

//E Some Struct Max Sizes
/*E
 * In many circumstances using the MAX_SIZE of each event data is quite wasteful.
 * For example the JoinRoom and GetRoomDataInternal MAX_SIZEs were calculated
 * based on the max number of member slots that the library supports. To make a
 * better assessment of how much buffer space will be needed you can substract
 * the number of slots that won't be used. For example, if only 4 players are
 * supported in the game then (buffer size needed for JoinRoom and GetRoomDataInternal) =
 * _EVENT_DATA_MAX_SIZE_JoinRoom - ((SCE_NP_MATCHING2_ROOM_MAX_SLOT - 4) *
 * _MAX_SIZE_RoomMemberDataInternal).
 * The same goes for SearchRoom, GetLobbyMemberDataInternalList and GetUserInfo.
 */
#define SCE_NP_MATCHING2_MAX_SIZE_ROOM_DATA_EXTERNAL                                    1288
#define SCE_NP_MATCHING2_MAX_SIZE_ROOM_MEMBER_DATA_INTERNAL                             368
#define SCE_NP_MATCHING2_MAX_SIZE_LOBBY_MEMBER_DATA_INTERNAL                            668
#define SCE_NP_MATCHING2_MAX_SIZE_LOBBY_MEMBER_DATA_INTERNAL_NO_EXTENDED_DATA           80
#define SCE_NP_MATCHING2_MAX_SIZE_USER_INFO                                             704

/*E
 *******************************************************************************
 * IDs and miscellaneous structures, macros
 *******************************************************************************
  */
/*J
 *******************************************************************************
 * ID および雑多な構造体
 *******************************************************************************
 */

/*E Memory Info */
/*J メモリ情報 */
typedef struct SceNpMatching2MemoryInfo {
	SceSize totalMemSize;		/*E Total memory size */
	SceSize curMemUsage;		/*E Current memory usage */
	SceSize maxMemUsage;		/*E Max memory usage */
	SceUChar8 reserved[12];
} SceNpMatching2MemoryInfo;

/*E Server ID */
/*J サーバ ID */
#define SCE_NP_MATCHING2_INVALID_SERVER_ID		(0)
typedef SceUShort16 SceNpMatching2ServerId;

/*E World ID, World Number */
/*J ワールド ID、ワールド番号 */
#define SCE_NP_MATCHING2_INVALID_WORLD_ID		(0)
typedef SceUInt32 SceNpMatching2WorldId;
typedef SceUShort16 SceNpMatching2WorldNumber;
#define SCE_NP_MATCHING2_GET_WORLD_NUMBER(worldId) \
	( (SceNpMatching2WorldNumber)((worldId) & 0x0000ffffU) )

/*E Lobby ID, World Number */
/*J ロビーID、ロビー番号 */
#define SCE_NP_MATCHING2_INVALID_LOBBY_ID		(0)
typedef SceUInt64 SceNpMatching2LobbyId;
typedef SceUShort16 SceNpMatching2LobbyNumber;
#define SCE_NP_MATCHING2_GET_LOBBY_NUMBER(lobbyId) \
	( (SceNpMatching2LobbyNumber)(((lobbyId) & 0x00000000ffff0000ULL)>>16) )

/*E Room ID, Room Number */
/*J ルーム ID、ルーム番号 */
#define SCE_NP_MATCHING2_INVALID_ROOM_ID		(0)
typedef SceUInt64 SceNpMatching2RoomId;
typedef SceUShort16 SceNpMatching2RoomNumber;
#define SCE_NP_MATCHING2_GET_ROOM_NUMBER(roomId) \
	( (SceNpMatching2RoomNumber)((roomId) & 0x000000000000ffffULL) )

/*E Context ID */
/*J コンテキスト ID */
#define SCE_NP_MATCHING2_INVALID_CONTEXT_ID		(0)
typedef SceUShort16 SceNpMatching2ContextId;

/*E Request ID */
/*J リクエスト ID */
#define SCE_NP_MATCHING2_INVALID_REQUEST_ID		(0)
typedef SceUInt32 SceNpMatching2RequestId;
typedef SceUInt32 SceNpMatching2SignalingRequestId;

/*E NAT Type */
/*J NAT タイプ */
typedef SceUChar8 SceNpMatching2NatType;

/*E Search Operator */
/*J 検索条件 */
#define SCE_NP_MATCHING2_OPERATOR_EQ				1
#define SCE_NP_MATCHING2_OPERATOR_NE				2
#define SCE_NP_MATCHING2_OPERATOR_LT				3
#define SCE_NP_MATCHING2_OPERATOR_LE				4
#define SCE_NP_MATCHING2_OPERATOR_GT				5
#define SCE_NP_MATCHING2_OPERATOR_GE				6
typedef SceUChar8 SceNpMatching2Operator;

/*E Message Type */
/*J メッセージ送信タイプ */
#define SCE_NP_MATCHING2_CASTTYPE_BROADCAST			1
#define SCE_NP_MATCHING2_CASTTYPE_UNICAST			2
#define SCE_NP_MATCHING2_CASTTYPE_MULTICAST			3
#define SCE_NP_MATCHING2_CASTTYPE_MULTICAST_TEAM	4
typedef SceUChar8 SceNpMatching2CastType;

/*E Session Password */
/*J セッションパスワード */
#define SCE_NP_MATCHING2_SESSION_PASSWORD_SIZE		8
typedef struct SceNpMatching2SessionPassword {
	SceUChar8 data[SCE_NP_MATCHING2_SESSION_PASSWORD_SIZE];
} SceNpMatching2SessionPassword;

/*E Session Type */
/*J セッションタイプ */
#define SCE_NP_MATCHING2_SESSION_TYPE_LOBBY			1
#define SCE_NP_MATCHING2_SESSION_TYPE_ROOM			2
typedef SceUChar8 SceNpMatching2SessionType;

/*E Event Cause */
/*J イベント要因 */
#define SCE_NP_MATCHING2_EVENT_CAUSE_LEAVE_ACTION			1
#define SCE_NP_MATCHING2_EVENT_CAUSE_KICKOUT_ACTION			2
#define SCE_NP_MATCHING2_EVENT_CAUSE_GRANT_OWNER_ACTION		3
#define SCE_NP_MATCHING2_EVENT_CAUSE_SERVER_OPERATION		4
#define SCE_NP_MATCHING2_EVENT_CAUSE_MEMBER_DISAPPEARED		5
#define SCE_NP_MATCHING2_EVENT_CAUSE_SERVER_INTERNAL		6
#define SCE_NP_MATCHING2_EVENT_CAUSE_CONNECTION_ERROR		7
#define SCE_NP_MATCHING2_EVENT_CAUSE_NP_SIGNED_OUT			8
#define SCE_NP_MATCHING2_EVENT_CAUSE_SYSTEM_ERROR			9
#define SCE_NP_MATCHING2_EVENT_CAUSE_CONTEXT_ERROR			10
#define SCE_NP_MATCHING2_EVENT_CAUSE_CONTEXT_ACTION			11
typedef SceUChar8 SceNpMatching2EventCause;

/*E Accompanying data when joining or leaving a room or lobby */
/*J ルームもしくはロビーに参加、退出などをする際に付随可能なデータ */
#define SCE_NP_MATCHING2_PRESENCE_OPTION_DATA_SIZE			16
typedef struct SceNpMatching2PresenceOptionData {
	SceUChar8 data[SCE_NP_MATCHING2_PRESENCE_OPTION_DATA_SIZE];
	SceSize len;
} SceNpMatching2PresenceOptionData;


/*E
 *******************************************************************************
 * Attributes, Search Conditions
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * 属性、検索条件
 *******************************************************************************
 */

/*E Attribute ID */
/*J 属性 ID */
typedef SceUShort16 SceNpMatching2AttributeId;

/*E
 * Flag Attribute
 */
/*J
 * フラグ属性
 */

/*E Lobby Flag Attribute */
/*J ロビーフラグ属性 */
#define SCE_NP_MATCHING2_LOBBY_FLAG_ATTR_MEMBER_NOTIFICATION     0x20000000

/*E Room Flag Attribute */
/*J ルームフラグ属性 */
#define SCE_NP_MATCHING2_ROOM_FLAG_ATTR_OWNER_AUTO_GRANT         0x80000000
#define SCE_NP_MATCHING2_ROOM_FLAG_ATTR_CLOSED                   0x40000000
#define SCE_NP_MATCHING2_ROOM_FLAG_ATTR_FULL                     0x20000000
#define SCE_NP_MATCHING2_ROOM_FLAG_ATTR_HIDDEN                   0x10000000
#define SCE_NP_MATCHING2_ROOM_FLAG_ATTR_GLOBAL_SEARCH_AVAILABLE  0x08000000
#define SCE_NP_MATCHING2_ROOM_FLAG_ATTR_NAT_TYPE_RESTRICTION     0x04000000
#define SCE_NP_MATCHING2_ROOM_FLAG_ATTR_PROHIBITIVE_MODE         0x02000000

/*E Lobby Member Flag Attribute */
/*J ロビーメンバフラグ属性 */
#define SCE_NP_MATCHING2_LOBBYMEMBER_FLAG_ATTR_OWNER             0x80000000

/*E Room Member Flag Attribute */
/*J ルームメンバフラグ属性 */
#define SCE_NP_MATCHING2_ROOMMEMBER_FLAG_ATTR_OWNER              0x80000000
typedef SceUInt32 SceNpMatching2FlagAttr;

/*E
 * Numerical Attribute
 */
/*J
 * 数値属性
 */

/*E Room Numerical Attribute */
/*E Room External Search Numerical Attribute (8) */
/*J ルーム数値属性 */
/*J ルーム外部検索数値属性(8つ) */
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_NUM   8
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_1_ID  0x004c
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_2_ID  0x004d
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_3_ID  0x004e
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_4_ID  0x004f
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_5_ID  0x0050
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_6_ID  0x0051
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_7_ID  0x0052
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_INT_ATTR_EXTERNAL_8_ID  0x0053

/*E Numerical Attribute Structure */
/*J 数値属性構造体 */
typedef struct SceNpMatching2IntAttr {
	SceNpMatching2AttributeId id;
	SceUChar8  padding[2];
	SceUInt32 num;
} SceNpMatching2IntAttr;

/*E
 * Binary Attribute
 */
/*J
 * バイナリ属性
 */
/*E Lobby Internal Binary Attribute (2) */
/*J ロビー内部バイナリ属性(2つ) */
#define SCE_NP_MATCHING2_LOBBY_BIN_ATTR_INTERNAL_NUM             2
#define SCE_NP_MATCHING2_LOBBY_BIN_ATTR_INTERNAL_1_ID            0x0037
#define SCE_NP_MATCHING2_LOBBY_BIN_ATTR_INTERNAL_2_ID            0x0038

/*E Lobby Internal Member Binary Attribute (1) */
/*J ロビー内部ロビーメンババイナリ属性(1つ) */
#define SCE_NP_MATCHING2_LOBBYMEMBER_BIN_ATTR_INTERNAL_NUM       1
#define SCE_NP_MATCHING2_LOBBYMEMBER_BIN_ATTR_INTERNAL_1_ID      0x0039

/*E Room Internal Binary Attribute (2) */
/*J ルーム内部バイナリ属性(2つ) */
#define SCE_NP_MATCHING2_ROOM_BIN_ATTR_INTERNAL_NUM              2
#define SCE_NP_MATCHING2_ROOM_BIN_ATTR_INTERNAL_1_ID             0x0057
#define SCE_NP_MATCHING2_ROOM_BIN_ATTR_INTERNAL_2_ID             0x0058

/*E Room Internal Member Binary Attribute (1) */
/*J ルーム内部ルームメンババイナリ属性(1つ) */
#define SCE_NP_MATCHING2_ROOMMEMBER_BIN_ATTR_INTERNAL_NUM        1
#define SCE_NP_MATCHING2_ROOMMEMBER_BIN_ATTR_INTERNAL_1_ID       0x0059

/*E Room External Searchable Binary Attribute (1) */
/*J ルーム外部検索バイナリ属性(1つ) */
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_BIN_ATTR_EXTERNAL_NUM   1
#define SCE_NP_MATCHING2_ROOM_SEARCHABLE_BIN_ATTR_EXTERNAL_1_ID  0x0054

/*E Room External Binary Attribute (2) */
/*J ルーム外部バイナリ属性(2つ) */
#define SCE_NP_MATCHING2_ROOM_BIN_ATTR_EXTERNAL_NUM              2
#define SCE_NP_MATCHING2_ROOM_BIN_ATTR_EXTERNAL_1_ID             0x0055
#define SCE_NP_MATCHING2_ROOM_BIN_ATTR_EXTERNAL_2_ID             0x0056

/*E User Binary Attribute (1) */
/*J ユーザバイナリ属性(1つ) */
#define SCE_NP_MATCHING2_USER_BIN_ATTR_NUM                       1
#define SCE_NP_MATCHING2_USER_BIN_ATTR_1_ID                      0x005f

/*E Binary Attribute Structure */
/*J バイナリ属性構造体 */
typedef struct SceNpMatching2BinAttr {
	SceNpMatching2AttributeId id;
	SceUChar8 padding[2];
	const void   *ptr;
	SceSize  size;
} SceNpMatching2BinAttr;

/*E
 * Search Conditions
 */
/*J
 * 検索条件
 */

/*E Search Target Range */
/*J 検索対象範囲 */
typedef struct SceNpMatching2RangeFilter {
	SceUInt32 startIndex;
	SceUInt32 max;
} SceNpMatching2RangeFilter;
/*E StartIndex Minimum Value */
/*J StartIndexの最小値 */
#define SCE_NP_MATCHING2_RANGE_FILTER_START_INDEX_MIN	1
/*E Maximum number of rooms that can be obtained at once */
/*J 一度に取得できるルームリストの最大数 */
#define SCE_NP_MATCHING2_RANGE_FILTER_MAX				20

/*E Numerical Search Conditions */
/*J 数値検索条件 */
typedef struct SceNpMatching2IntSearchFilter {
	SceNpMatching2Operator searchOperator;
	SceUChar8 padding[3];
	SceNpMatching2IntAttr attr;
} SceNpMatching2IntSearchFilter;

/*E Binary Search Conditions */
/*J バイナリ検索条件 */
typedef struct SceNpMatching2BinSearchFilter {
	SceNpMatching2Operator searchOperator;
	SceUChar8 padding[3];
	SceNpMatching2BinAttr attr;
} SceNpMatching2BinSearchFilter;

/*E Search Result Range */
/*J 検索結果の範囲 */
typedef struct SceNpMatching2Range {
	SceUInt32 startIndex;
	SceUInt32 total;
	SceUInt32 resultCount;
} SceNpMatching2Range;

/*E
 *******************************************************************************
 * User Info
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * ユーザ情報
 *******************************************************************************
 */

/*E Information about sessions that the user has joined */
/*J ユーザが参加中のセッション情報 */
typedef struct SceNpMatching2JoinedSessionInfo {
	SceNpMatching2SessionType sessionType;
	SceUChar8 padding1[1];
	SceNpMatching2ServerId serverId;
	SceNpMatching2WorldId worldId;
	SceNpMatching2LobbyId lobbyId;
	SceNpMatching2RoomId  roomId;
	SceRtcTick joinDate;
} SceNpMatching2JoinedSessionInfo;

/*E User Info Structure */
/*J ユーザ情報構造体 */
typedef struct SceNpMatching2UserInfo {
	struct SceNpMatching2UserInfo *next;
	SceNpId npId;
	SceNpMatching2BinAttr *userBinAttr;
	SceUInt32 userBinAttrNum;
	SceNpMatching2JoinedSessionInfo *joinedSessionInfo;
	SceUInt32 joinedSessionInfoNum;
} SceNpMatching2UserInfo;

/*E
 *******************************************************************************
 * Server Info
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * サーバ情報
 *******************************************************************************
 */

/*E Server Status */
/*J サーバステータス */
#define SCE_NP_MATCHING2_SERVER_STATUS_NONE            0
#define SCE_NP_MATCHING2_SERVER_STATUS_AVAILABLE       1
#define SCE_NP_MATCHING2_SERVER_STATUS_UNAVAILABLE     2
#define SCE_NP_MATCHING2_SERVER_STATUS_BUSY            3
#define SCE_NP_MATCHING2_SERVER_STATUS_MAINTENANCE     4
typedef SceUChar8 SceNpMatching2ServerStatus;

/*E Server Structure */
/*J サーバ構造体 */
typedef struct SceNpMatching2Server {
	SceNpMatching2ServerId     serverId;
	SceNpMatching2ServerStatus status;
	SceUChar8 padding[1];
} SceNpMatching2Server;


/*E
 *******************************************************************************
 * World Info
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * ワールド情報
 *******************************************************************************
 */

/*E World Structure */
/*J ワールド構造体 */
typedef struct SceNpMatching2World {
	struct SceNpMatching2World *next;
	SceNpMatching2WorldId worldId;
	SceUInt32 numOfLobby;
	SceUInt32 maxNumOfTotalLobbyMember;
	SceUInt32 curNumOfTotalLobbyMember;
	SceUInt32 curNumOfRoom;
	SceUInt32 curNumOfTotalRoomMember;
	bool withEntitlementId;
	SceNpEntitlementId entitlementId;
	SceUChar8 padding[3];
} SceNpMatching2World;


/*E
 *******************************************************************************
 * Lobby Info
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * ロビー情報
 *******************************************************************************
 */

/*E Maximum number of members for Lobby */
/*J ロビーの最大参加人数 */
#define SCE_NP_MATCHING2_LOBBY_MAX_SLOT      256

/*E Lobby Member ID */
/*J ロビーメンバ ID */
#define SCE_NP_MATCHING2_INVALID_LOBBY_MEMBER_ID	(0)
typedef SceUShort16 SceNpMatching2LobbyMemberId;

/*E Lobby Internal Member Binary Attribute */
/*J ロビー内部ロビーメンババイナリ属性 */
typedef struct SceNpMatching2LobbyMemberBinAttrInternal {
	SceRtcTick updateDate;
	SceNpMatching2BinAttr data;
	SceUChar8 padding[4];
} SceNpMatching2LobbyMemberBinAttrInternal;

/*E Lobby member info that can be retrieved from inside the lobby */
/*J ロビー内部から取得するロビーメンバ情報 */
typedef struct SceNpMatching2LobbyMemberDataInternal {
	struct SceNpMatching2LobbyMemberDataInternal *next;
	SceNpId npId;

	SceRtcTick joinDate;
	SceNpMatching2LobbyMemberId memberId;
	SceUChar8 padding[2];

	SceNpMatching2FlagAttr flagAttr; /*E Not used */

	SceNpMatching2JoinedSessionInfo *joinedSessionInfo;
	SceUInt32 joinedSessionInfoNum;
	SceNpMatching2LobbyMemberBinAttrInternal *lobbyMemberBinAttrInternal;
	SceUInt32 lobbyMemberBinAttrInternalNum;
} SceNpMatching2LobbyMemberDataInternal;

/*E Lobby Member List */
/*J ロビー内部用ロビーメンバIDリスト */
typedef struct SceNpMatching2LobbyMemberIdList {
	SceNpMatching2LobbyMemberId *memberId;
	SceUInt32 memberIdNum;
	SceNpMatching2LobbyMemberId me;
	SceUChar8 padding[6];
} SceNpMatching2LobbyMemberIdList;

/*E Lobby Internal Binary Attribute */
/*J ロビー内部バイナリ属性 */
typedef struct SceNpMatching2LobbyBinAttrInternal {
	SceRtcTick updateDate;
	SceNpMatching2LobbyMemberId updateMemberId;
	SceUChar8 padding[2];
	SceNpMatching2BinAttr data;
} SceNpMatching2LobbyBinAttrInternal;

/*E Lobby External Data */
/*J ロビー外部から取得するロビー情報 */
typedef struct SceNpMatching2LobbyDataExternal {
	struct SceNpMatching2LobbyDataExternal *next;
	SceNpMatching2ServerId serverId;
	SceUChar8 padding1[2];
	SceNpMatching2WorldId worldId;
	SceUChar8 padding2[4];
	SceNpMatching2LobbyId lobbyId;
	SceUInt32 maxSlot;
	SceUInt32 curMemberNum;
	SceNpMatching2FlagAttr flagAttr;
	/*E Not Used */
	/*J 未使用 */
	SceNpMatching2IntAttr *lobbySearchableIntAttrExternal;
	SceUInt32 lobbySearchableIntAttrExternalNum;
	SceNpMatching2BinAttr *lobbySearchableBinAttrExternal;
	SceUInt32 lobbySearchableBinAttrExternalNum;
	SceNpMatching2BinAttr *lobbyBinAttrExternal;
	SceUInt32 lobbyBinAttrExternalNum;
	SceUChar8 padding3[4];
} SceNpMatching2LobbyDataExternal;

/*E Lobby Internal Data */
/*J ロビー内部から取得するロビー情報 */
typedef struct SceNpMatching2LobbyDataInternal {
	SceNpMatching2ServerId serverId;
	SceUChar8 padding1[2];
	SceNpMatching2WorldId worldId;
	SceNpMatching2LobbyId lobbyId;

	SceUInt32 maxSlot;
	SceNpMatching2LobbyMemberIdList memberIdList;
	SceNpMatching2FlagAttr flagAttr;

	/*E Not Used */
	/*J 未使用 */
	SceNpMatching2LobbyBinAttrInternal *lobbyBinAttrInternal;
	SceUInt32 lobbyBinAttrInternalNum;
} SceNpMatching2LobbyDataInternal;

/*E Lobby Message Destination */
/*J ロビーメッセージの送信先指定 */
typedef union SceNpMatching2LobbyMessageDestination {
	SceNpMatching2LobbyMemberId unicastTarget;
	struct {
		const SceNpMatching2LobbyMemberId *memberId;
		SceUInt32 memberIdNum;
	} multicastTarget;
} SceNpMatching2LobbyMessageDestination;

/*E
 *******************************************************************************
 * Room Info
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * ルーム情報
 *******************************************************************************
 */

/*E Maximum number of members allowable in a room */
/*J ルームの最大参加人数 */
#define SCE_NP_MATCHING2_ROOM_MAX_SLOT			64

/*E Room Group ID */
/*J ルームグループ ID */
#define SCE_NP_MATCHING2_ROOM_GROUP_ID_MAX		15
typedef SceUChar8 SceNpMatching2RoomGroupId;

/*E Room Member ID */
/*J ルームメンバ ID */
#define SCE_NP_MATCHING2_INVALID_ROOM_MEMBER_ID	(0)
typedef SceUShort16 SceNpMatching2RoomMemberId;

/*E Team ID */
/*J チーム ID */
#define SCE_NP_MATCHING2_INVALID_TEAM_ID		(0)
typedef SceUChar8 SceNpMatching2TeamId;

/*E Member Roles */
/*J ルーム内での権限 */
#define SCE_NP_MATCHING2_ROLE_MEMBER			1
#define SCE_NP_MATCHING2_ROLE_OWNER				2
typedef SceUChar8 SceNpMatching2Role;

/*E Flag for indicating whether the user is allowed to join after being kicked */
/*J キックアウトしたメンバの再参加に関する設定 */
#define SCE_NP_MATCHING2_BLOCKKICKFLAG_OK		0
#define SCE_NP_MATCHING2_BLOCKKICKFLAG_NG		1
typedef SceUChar8 SceNpMatching2BlockKickFlag;

/*E Group Label */
/*J グループラベル */
#define SCE_NP_MATCHING2_GROUP_LABEL_SIZE		8
typedef struct SceNpMatching2GroupLabel {
	SceUChar8 data[SCE_NP_MATCHING2_GROUP_LABEL_SIZE];
} SceNpMatching2GroupLabel;

/*E Slot mask for room password */
/*J ルームパスワード用スロットマスク */
typedef SceUInt64 SceNpMatching2RoomPasswordSlotMask;
typedef SceUInt64 SceNpMatching2RoomJoinedSlotMask;

/*E Room Group Configuration */
/*J ルームのグループ設定 */
typedef struct SceNpMatching2RoomGroupConfig {
	SceUInt32 slotNum;
	bool withLabel;
	SceNpMatching2GroupLabel label;
	bool withPassword;
	SceUChar8 padding[2];
} SceNpMatching2RoomGroupConfig;

/*E Structure for configuring room group passwords */
/*J ルームグループのパスワード使用設定用構造体 */
typedef struct SceNpMatching2RoomGroupPasswordConfig {
	SceNpMatching2RoomGroupId groupId;
	bool withPassword;
	SceUChar8 padding[1];
} SceNpMatching2RoomGroupPasswordConfig;

/*E Room Internal Member Binary Data */
/*J ルーム内部ルームメンババイナリデータ */
typedef struct SceNpMatching2RoomMemberBinAttrInternal {
	SceRtcTick updateDate;
	SceNpMatching2BinAttr data;
	SceUChar8 padding[4];
} SceNpMatching2RoomMemberBinAttrInternal;

/*E Room Group */
/*J ルームグループ */
typedef struct SceNpMatching2RoomGroup {
	SceNpMatching2RoomGroupId groupId;
	bool withPassword;
	bool withLabel;
	SceUChar8 padding[1];
	SceNpMatching2GroupLabel label;
	SceUInt32 slotNum;
	SceUInt32 curGroupMemberNum;
} SceNpMatching2RoomGroup;

/*E Room member info retrievable outside the room */
/*J ルーム外部から取得するルームメンバ情報 */
typedef struct SceNpMatching2RoomMemberDataExternal {
	struct SceNpMatching2RoomMemberDataExternal *next;
	SceNpId npId;
	SceRtcTick joinDate;
	SceNpMatching2Role role;
	SceUChar8 padding[7];
} SceNpMatching2RoomMemberDataExternal;

/*E Room member info retrievable inside the room */
/*J ルーム内部から取得するルームメンバ情報 */
typedef struct SceNpMatching2RoomMemberDataInternal {
	struct SceNpMatching2RoomMemberDataInternal *next;
	SceNpId npId;

	SceRtcTick joinDate;
	SceNpMatching2RoomMemberId memberId;
	SceNpMatching2TeamId teamId;
	SceUChar8 padding1[1];

	SceNpMatching2RoomGroup *roomGroup;

	SceNpMatching2NatType natType;
	SceUChar8 padding2[3];
	SceNpMatching2FlagAttr flagAttr;
	SceNpMatching2RoomMemberBinAttrInternal *roomMemberBinAttrInternal;
	SceUInt32 roomMemberBinAttrInternalNum;
} SceNpMatching2RoomMemberDataInternal;

/*E Room Member List */
/*J ルーム内部用ルームメンバリスト */
typedef struct SceNpMatching2RoomMemberDataInternalList {
	SceNpMatching2RoomMemberDataInternal *members;
	SceUInt32 membersNum;
	SceNpMatching2RoomMemberDataInternal *me;
	SceNpMatching2RoomMemberDataInternal *owner;
} SceNpMatching2RoomMemberDataInternalList;

/*E Sort Methods */
/*J ソートメソッド */
#define SCE_NP_MATCHING2_SORT_METHOD_JOIN_DATE			(0)
#define SCE_NP_MATCHING2_SORT_METHOD_SLOT_NUMBER		(1)

/*E Room Internal Binary Attribute */
/*J ルーム内部バイナリ属性 */
typedef struct SceNpMatching2RoomBinAttrInternal {
	SceRtcTick updateDate;
	SceNpMatching2RoomMemberId updateMemberId;
	SceUChar8 padding[2];
	SceNpMatching2BinAttr data;
} SceNpMatching2RoomBinAttrInternal;

/*E Room info retrievable outside the room */
/*J ルーム外部から取得するルーム情報 */
typedef struct SceNpMatching2RoomDataExternal {
	struct SceNpMatching2RoomDataExternal *next;

	SceUShort16 maxSlot;
	SceUShort16 curMemberNum;

	SceNpMatching2ServerId serverId;
	SceUChar8 padding[2];
	SceNpMatching2WorldId worldId;
	SceNpMatching2LobbyId lobbyId;
	SceNpMatching2RoomId roomId;

	SceNpMatching2RoomPasswordSlotMask passwordSlotMask;
	SceNpMatching2RoomJoinedSlotMask joinedSlotMask;
	SceUShort16 publicSlotNum;
	SceUShort16 privateSlotNum;
	SceUShort16 openPublicSlotNum;
	SceUShort16 openPrivateSlotNum;

	SceNpId *owner;
	SceNpMatching2FlagAttr flagAttr;

	SceNpMatching2RoomGroup *roomGroup;
	SceUInt32 roomGroupNum;

	/*E Searchable Numberical Attribute */
	/*J 検索数値属性 */
	SceNpMatching2IntAttr *roomSearchableIntAttrExternal;
	SceUInt32 roomSearchableIntAttrExternalNum;

	/*E Searchable Binary Attribute */
	/*J 検索バイナリ属性 */
	SceNpMatching2BinAttr *roomSearchableBinAttrExternal;
	SceUInt32 roomSearchableBinAttrExternalNum;

	/*E Binary Attribute */
	/*J バイナリ属性 */
	SceNpMatching2BinAttr *roomBinAttrExternal;
	SceUInt32 roomBinAttrExternalNum;
} SceNpMatching2RoomDataExternal;

/*E Room Data Internal */
/*J ルーム内部から取得するルーム情報 */
typedef struct SceNpMatching2RoomDataInternal {
	SceUShort16 maxSlot;

	SceNpMatching2ServerId serverId;
	SceNpMatching2WorldId worldId;
	SceNpMatching2LobbyId lobbyId;
	SceNpMatching2RoomId roomId;

	SceNpMatching2RoomPasswordSlotMask passwordSlotMask;
	SceNpMatching2RoomJoinedSlotMask joinedSlotMask;
	SceUShort16 publicSlotNum;
	SceUShort16 privateSlotNum;
	SceUShort16 openPublicSlotNum;
	SceUShort16 openPrivateSlotNum;

	SceNpMatching2RoomMemberDataInternalList memberList;

	SceNpMatching2RoomGroup *roomGroup;
	SceUInt32 roomGroupNum;

	SceNpMatching2FlagAttr flagAttr;
	SceUChar8 padding[4];
	SceNpMatching2RoomBinAttrInternal *roomBinAttrInternal;
	SceUInt32 roomBinAttrInternalNum;
} SceNpMatching2RoomDataInternal;

/*E Room Message Destination */
/*J ルームメッセージの送信先指定 */
typedef union SceNpMatching2RoomMessageDestination {
	SceNpMatching2RoomMemberId unicastTarget;
	struct {
		const SceNpMatching2RoomMemberId *memberId;
		SceUInt32 memberIdNum;
	} multicastTarget;
	SceNpMatching2TeamId multicastTargetTeamId;
} SceNpMatching2RoomMessageDestination;

/*E Search Room Options */
/*J sceNpMatching2SearchRoom() で指定するオプション */
#define SCE_NP_MATCHING2_SEARCH_ROOM_OPTION_WITH_NPID			(0x01)
#define SCE_NP_MATCHING2_SEARCH_ROOM_OPTION_NAT_TYPE_FILTER		(0x08)
#define SCE_NP_MATCHING2_SEARCH_ROOM_OPTION_RANDOM				(0x10)

/*E
 * Options for:
 * sceNpMatching2SendRoomChatMessage()
 * sceNpMatching2SendRoomMessage()
 * sceNpMatching2SendLobbyChatMessage()
 */
/*J
 * sceNpMatching2SendRoomChatMessage()
 * sceNpMatching2SendRoomMessage()
 * sceNpMatching2SendLobbyChatMessage()
 * で指定するオプション
 */
#define SCE_NP_MATCHING2_SEND_MSG_OPTION_WITH_NPID		(0x01)

/*E Max number of white list users */
/*J ルーム入室許可ユーザ最大数 */
#define SCE_NP_MATCHING2_ROOM_ALLOWED_USER_MAX			100
/*E Max number of black list users */
/*J ルーム入室拒否ユーザ最大数 */
#define SCE_NP_MATCHING2_ROOM_BLOCKED_USER_MAX			100

/*E
 *******************************************************************************
 * Callbacks
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * コールバック関数
 *******************************************************************************
 */

/*E Callback Events */
/*J コールバック関数イベント */
typedef SceUShort16 SceNpMatching2Event;
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_WORLD_INFO_LIST                    (0x0002)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_ROOM_MEMBER_DATA_EXTERNAL_LIST     (0x0003)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SET_ROOM_DATA_EXTERNAL                 (0x0004)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_ROOM_DATA_EXTERNAL_LIST            (0x0005)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_LOBBY_INFO_LIST                    (0x0006)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SET_USER_INFO                          (0x0007)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_USER_INFO_LIST                     (0x0008)
#define SCE_NP_MATCHING2_REQUEST_EVENT_CREATE_JOIN_ROOM                       (0x0101)
#define SCE_NP_MATCHING2_REQUEST_EVENT_JOIN_ROOM                              (0x0102)
#define SCE_NP_MATCHING2_REQUEST_EVENT_LEAVE_ROOM                             (0x0103)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GRANT_ROOM_OWNER                       (0x0104)
#define SCE_NP_MATCHING2_REQUEST_EVENT_KICKOUT_ROOM_MEMBER                    (0x0105)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SEARCH_ROOM                            (0x0106)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SEND_ROOM_CHAT_MESSAGE                 (0x0107)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SEND_ROOM_MESSAGE                      (0x0108)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SET_ROOM_DATA_INTERNAL                 (0x0109)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_ROOM_DATA_INTERNAL                 (0x010a)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SET_ROOM_MEMBER_DATA_INTERNAL          (0x010b)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_ROOM_MEMBER_DATA_INTERNAL          (0x010c)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SET_SIGNALING_OPT_PARAM                (0x010d)
#define SCE_NP_MATCHING2_REQUEST_EVENT_JOIN_LOBBY                             (0x0201)
#define SCE_NP_MATCHING2_REQUEST_EVENT_LEAVE_LOBBY                            (0x0202)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SEND_LOBBY_CHAT_MESSAGE                (0x0203)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SET_LOBBY_MEMBER_DATA_INTERNAL         (0x0205)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_LOBBY_MEMBER_DATA_INTERNAL         (0x0206)
#define SCE_NP_MATCHING2_REQUEST_EVENT_GET_LOBBY_MEMBER_DATA_INTERNAL_LIST    (0x0207)
#define SCE_NP_MATCHING2_REQUEST_EVENT_SIGNALING_GET_PING_INFO                (0x0e01)
#define SCE_NP_MATCHING2_ROOM_EVENT_MEMBER_JOINED                             (0x1101)
#define SCE_NP_MATCHING2_ROOM_EVENT_MEMBER_LEFT                               (0x1102)
#define SCE_NP_MATCHING2_ROOM_EVENT_KICKEDOUT                                 (0x1103)
#define SCE_NP_MATCHING2_ROOM_EVENT_ROOM_DESTROYED                            (0x1104)
#define SCE_NP_MATCHING2_ROOM_EVENT_ROOM_OWNER_CHANGED                        (0x1105)
#define SCE_NP_MATCHING2_ROOM_EVENT_UPDATED_ROOM_DATA_INTERNAL                (0x1106)
#define SCE_NP_MATCHING2_ROOM_EVENT_UPDATED_ROOM_MEMBER_DATA_INTERNAL         (0x1107)
#define SCE_NP_MATCHING2_ROOM_EVENT_UPDATED_SIGNALING_OPT_PARAM               (0x1108)
#define SCE_NP_MATCHING2_ROOM_MSG_EVENT_CHAT_MESSAGE                          (0x2101)
#define SCE_NP_MATCHING2_ROOM_MSG_EVENT_MESSAGE                               (0x2102)
#define SCE_NP_MATCHING2_LOBBY_EVENT_MEMBER_JOINED                            (0x3201)
#define SCE_NP_MATCHING2_LOBBY_EVENT_MEMBER_LEFT                              (0x3202)
#define SCE_NP_MATCHING2_LOBBY_EVENT_LOBBY_DESTROYED                          (0x3203)
#define SCE_NP_MATCHING2_LOBBY_EVENT_UPDATED_LOBBY_MEMBER_DATA_INTERNAL       (0x3204)
#define SCE_NP_MATCHING2_LOBBY_MSG_EVENT_CHAT_MESSAGE                         (0x4201)
#define SCE_NP_MATCHING2_SIGNALING_EVENT_DEAD                                 (0x5101)
#define SCE_NP_MATCHING2_SIGNALING_EVENT_ESTABLISHED                          (0x5102)
#define SCE_NP_MATCHING2_SIGNALING_EVENT_NETINFO_RESULT                       (0x5103)
#define SCE_NP_MATCHING2_CONTEXT_EVENT_START_OVER                             (0x6f01)
#define SCE_NP_MATCHING2_CONTEXT_EVENT_STARTED                                (0x6f02)
#define SCE_NP_MATCHING2_CONTEXT_EVENT_STOPPED                                (0x6f03)

/*E Request Callback */
/*J リクエストコールバック */
typedef void (*SceNpMatching2RequestCallback)(
	SceNpMatching2ContextId        ctxId,
	SceNpMatching2RequestId        reqId,
	SceNpMatching2Event            event,
	int     errorCode,
	const void *data,
	void   *arg
	);

/*E Lobby Event Callback */
/*J ロビーイベントコールバック */
typedef void (*SceNpMatching2LobbyEventCallback)(
	SceNpMatching2ContextId         ctxId,
	SceNpMatching2LobbyId           lobbyId,
	SceNpMatching2Event             event,
	const void *data,
	void   *arg
	);

/*E Room Event Callback */
/*J ルームイベントコールバック */
typedef void (*SceNpMatching2RoomEventCallback)(
	SceNpMatching2ContextId         ctxId,
	SceNpMatching2RoomId            roomId,
	SceNpMatching2Event             event,
	const void *data,
	void   *arg
	);

/*E Lobby Message Callback */
/*J ロビーメッセージコールバック */
typedef void (*SceNpMatching2LobbyMessageCallback)(
	SceNpMatching2ContextId        ctxId,
	SceNpMatching2LobbyId          lobbyId,
	SceNpMatching2LobbyMemberId    srcMemberId,
	SceNpMatching2Event            event,
	const void *data,
	void   *arg
	);

/*E Room Message Callback */
/*J ルームメッセージコールバック */
typedef void (*SceNpMatching2RoomMessageCallback)(
	SceNpMatching2ContextId        ctxId,
	SceNpMatching2RoomId           roomId,
	SceNpMatching2RoomMemberId     srcMemberId,
	SceNpMatching2Event            event,
	const void *data,
	void   *arg
	);

/*E Signaling Callback */
/*J シグナリングコールバック */
typedef void (*SceNpMatching2SignalingCallback)(
	SceNpMatching2ContextId        ctxId,
	SceNpMatching2RoomId           roomId,
	SceNpMatching2RoomMemberId     peerMemberId,
	SceNpMatching2Event            event,
	int     errorCode,
	void   *arg
	);

/*E Context Callback */
/*J コンテキストコールバック */
typedef void (*SceNpMatching2ContextCallback)(
	SceNpMatching2ContextId  ctxId,
	SceNpMatching2Event      event,
	SceNpMatching2EventCause eventCause,
	int   errorCode,
	void *arg
	);

/*E
 *******************************************************************************
 * Request and Response Structures for each API
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * API 毎のリクエスト、レスポンス構造体
 *******************************************************************************
 */

#define SCE_NP_MATCHING2_REQUEST_TIMEOUT_DEFAULT	(10*1000000)	// 10 seconds
#define SCE_NP_MATCHING2_REQUEST_TIMEOUT_MIN		(3*1000000)		// 3 seconds

/*E Request Optional Parameter Structure */
/*J 共通のオプション構造体 */
typedef struct SceNpMatching2RequestOptParam {
	SceNpMatching2RequestCallback cbFunc;
	void *cbFuncArg;
	SceUInt32 timeout; // 0 == default
	SceUShort16 appReqId;
	SceUChar8 padding[2];
} SceNpMatching2RequestOptParam;

/*
 * sceNpMatching2GetWorldInfoList()
 */
typedef struct SceNpMatching2GetWorldInfoListRequest {
	SceNpMatching2ServerId serverId;
} SceNpMatching2GetWorldInfoListRequest;

typedef struct SceNpMatching2GetWorldInfoListResponse {
	SceNpMatching2World *world;
	SceUInt32 worldNum;
} SceNpMatching2GetWorldInfoListResponse;

/*
 * sceNpMatching2SetUserInfo()
 */
typedef struct SceNpMatching2SetUserInfoRequest{
	SceNpMatching2ServerId serverId;
	SceUChar8 padding[2];
	const SceNpMatching2BinAttr *userBinAttr;
	SceUInt32 userBinAttrNum;
} SceNpMatching2SetUserInfoRequest;

/*
 * sceNpMatching2GetUserInfoList()
 */
#define SCE_NP_MATCHING2_GET_USER_INFO_LIST_NPID_NUM_MAX		25
typedef struct SceNpMatching2GetUserInfoListRequest {
	SceNpMatching2ServerId serverId;
	SceUChar8 padding[2];
	const SceNpId *npId;
	SceUInt32 npIdNum;
	const SceNpMatching2AttributeId *attrId;
	SceUInt32 attrIdNum;
	int option; // Not used
} SceNpMatching2GetUserInfoListRequest;

typedef struct SceNpMatching2GetUserInfoListResponse {
	SceNpMatching2UserInfo *userInfo;
	SceUInt32 userInfoNum;
} SceNpMatching2GetUserInfoListResponse;

/*
 * sceNpMatching2GetRoomMemberDataExternalList()
 */
typedef struct SceNpMatching2GetRoomMemberDataExternalListRequest {
	SceNpMatching2RoomId roomId;
} SceNpMatching2GetRoomMemberDataExternalListRequest;

typedef struct SceNpMatching2GetRoomMemberDataExternalListResponse {
	SceNpMatching2RoomMemberDataExternal *roomMemberDataExternal;
	SceUInt32 roomMemberDataExternalNum;
} SceNpMatching2GetRoomMemberDataExternalListResponse;

/*
 * sceNpMatching2SetRoomDataExternal()
 */
typedef struct SceNpMatching2SetRoomDataExternalRequest {
	SceNpMatching2RoomId roomId;
	const SceNpMatching2IntAttr *roomSearchableIntAttrExternal;
	SceUInt32 roomSearchableIntAttrExternalNum;
	const SceNpMatching2BinAttr *roomSearchableBinAttrExternal;
	SceUInt32 roomSearchableBinAttrExternalNum;
	const SceNpMatching2BinAttr *roomBinAttrExternal;
	SceUInt32 roomBinAttrExternalNum;
} SceNpMatching2SetRoomDataExternalRequest;

/*
 * sceNpMatching2GetRoomDataExternalList()
 */
#define SCE_NP_MATCHING2_GET_ROOM_DATA_EXTERNAL_LIST_ROOM_NUM_MAX		20
typedef struct SceNpMatching2GetRoomDataExternalListRequest {
	const SceNpMatching2RoomId *roomId;
	SceUInt32 roomIdNum;
	const SceNpMatching2AttributeId *attrId;
	SceUInt32 attrIdNum;
} SceNpMatching2GetRoomDataExternalListRequest;

typedef struct SceNpMatching2GetRoomDataExternalListResponse {
	SceNpMatching2RoomDataExternal *roomDataExternal;
	SceUInt32 roomDataExternalNum;
} SceNpMatching2GetRoomDataExternalListResponse;

/*
 * sceNpMatching2CreateJoinRoom()
 */

#define SCE_NP_MATCHING2_ADD_SLOTNUM_TO_ROOM_PASSWORD_SLOT_MASK(mask, slotNumber) \
	( (mask) |= (SceUInt64)(0x1ULL<<(64-(slotNumber))) )

/*E Signaling Option Parameter */
/*J シグナリングオプションパラメータ */
typedef SceUChar8 SceNpMatching2SignalingType;
#define SCE_NP_MATCHING2_SIGNALING_TYPE_NONE		0
#define SCE_NP_MATCHING2_SIGNALING_TYPE_MESH		1
#define SCE_NP_MATCHING2_SIGNALING_TYPE_STAR		2
typedef SceUChar8 SceNpMatching2SignalingFlag;
#define SCE_NP_MATCHING2_SIGNALING_FLAG_MANUAL_MODE	0x01
typedef struct SceNpMatching2SignalingOptParam {
	SceNpMatching2SignalingType type;
	SceNpMatching2SignalingFlag flag;
	SceNpMatching2RoomMemberId hubMemberId;
	SceUChar8 reserved2[4];
} SceNpMatching2SignalingOptParam;

typedef struct SceNpMatching2CreateJoinRoomRequest {
	SceNpMatching2WorldId  worldId;
	SceUChar8 padding1[4];
	SceNpMatching2LobbyId  lobbyId;

	SceUInt32           maxSlot;
	SceNpMatching2FlagAttr flagAttr;
	const SceNpMatching2BinAttr *roomBinAttrInternal;
	SceUInt32           roomBinAttrInternalNum;
	const SceNpMatching2IntAttr *roomSearchableIntAttrExternal;
	SceUInt32           roomSearchableIntAttrExternalNum;
	const SceNpMatching2BinAttr *roomSearchableBinAttrExternal;
	SceUInt32           roomSearchableBinAttrExternalNum;
	const SceNpMatching2BinAttr *roomBinAttrExternal;
	SceUInt32           roomBinAttrExternalNum;
	const SceNpMatching2SessionPassword      *roomPassword;
	const SceNpMatching2RoomGroupConfig      *groupConfig;
	SceUInt32                        groupConfigNum;
	const SceNpMatching2RoomPasswordSlotMask *passwordSlotMask;
	const SceNpId      *allowedUser;
	SceUInt32  allowedUserNum;
	const SceNpId      *blockedUser;
	SceUInt32  blockedUserNum;

	const SceNpMatching2GroupLabel *joinRoomGroupLabel;
	const SceNpMatching2BinAttr    *roomMemberBinAttrInternal;
	SceUInt32              roomMemberBinAttrInternalNum;
	SceNpMatching2TeamId      teamId;
	SceUChar8 padding2[3];

	const SceNpMatching2SignalingOptParam *sigOptParam;
	SceUChar8 padding3[4];
} SceNpMatching2CreateJoinRoomRequest;

typedef struct SceNpMatching2CreateJoinRoomResponse {
	SceNpMatching2RoomDataInternal *roomDataInternal;
} SceNpMatching2CreateJoinRoomResponse;

/*
 * sceNpMatching2JoinRoom()
 */
typedef struct SceNpMatching2JoinRoomRequest {
	SceNpMatching2RoomId             roomId;
	const SceNpMatching2SessionPassword   *roomPassword;
	const SceNpMatching2GroupLabel        *joinRoomGroupLabel;
	const SceNpMatching2BinAttr           *roomMemberBinAttrInternal;
	SceUInt32                     roomMemberBinAttrInternalNum;
	SceNpMatching2PresenceOptionData optData;
	SceNpMatching2TeamId             teamId;
	SceUChar8 padding[3];
	const SceNpId                   *blockedUser;	// PROHIBITIVE_FLAG must be enabled
	SceUInt32                     blockedUserNum;	// PROHIBITIVE_FLAG must be enabled
} SceNpMatching2JoinRoomRequest;

typedef struct SceNpMatching2JoinRoomResponse {
	SceNpMatching2RoomDataInternal *roomDataInternal;
} SceNpMatching2JoinRoomResponse;

/*
 * sceNpMatching2LeaveRoom()
 */
typedef struct SceNpMatching2LeaveRoomRequest {
	SceNpMatching2RoomId roomId;
	SceNpMatching2PresenceOptionData optData;
	SceUChar8 padding[4];
} SceNpMatching2LeaveRoomRequest;

/*
 * sceNpMatching2GrantRoomOwner()
 */
typedef struct SceNpMatching2GrantRoomOwnerRequest {
	SceNpMatching2RoomId roomId;
	SceNpMatching2RoomMemberId newOwner;
	SceUChar8 padding[2];
	SceNpMatching2PresenceOptionData optData;
} SceNpMatching2GrantRoomOwnerRequest;

/*
 * sceNpMatching2KickoutRoomMember()
 */
typedef struct SceNpMatching2KickoutRoomMemberRequest {
	SceNpMatching2RoomId roomId;
	SceNpMatching2RoomMemberId target;
	SceNpMatching2BlockKickFlag blockKickFlag;
	SceUChar8 padding[1];
	SceNpMatching2PresenceOptionData optData;
} SceNpMatching2KickoutRoomMemberRequest;

/*
 * sceNpMatching2SearchRoom()
 */
typedef struct SceNpMatching2SearchRoomRequest {
	int option;
	SceNpMatching2WorldId          worldId;
	SceNpMatching2LobbyId          lobbyId;
	SceNpMatching2RangeFilter      rangeFilter;
	SceNpMatching2FlagAttr         flagFilter;
	SceNpMatching2FlagAttr         flagAttr;
	const SceNpMatching2IntSearchFilter *intFilter;
	SceUInt32                   intFilterNum;
	const SceNpMatching2BinSearchFilter *binFilter;
	SceUInt32                   binFilterNum;
	const SceNpMatching2AttributeId     *attrId;
	SceUInt32                   attrIdNum;
} SceNpMatching2SearchRoomRequest;

typedef struct SceNpMatching2SearchRoomResponse {
	SceNpMatching2Range range;
	SceNpMatching2RoomDataExternal *roomDataExternal;
} SceNpMatching2SearchRoomResponse;

/*
 * sceNpMatching2SendRoomMessage()
 */
typedef struct SceNpMatching2SendRoomMessageRequest {
	SceNpMatching2RoomId roomId;
	SceNpMatching2CastType castType;
	SceUChar8 padding[3];
	SceNpMatching2RoomMessageDestination dst;
	const void *msg;
	SceSize msgLen;
	int option;
} SceNpMatching2SendRoomMessageRequest;

/*
 * sceNpMatching2SendRoomChatMessage()
 */
typedef struct SceNpMatching2SendRoomChatMessageRequest {
	SceNpMatching2RoomId roomId;
	SceNpMatching2CastType castType;
	SceUChar8 padding[3];
	SceNpMatching2RoomMessageDestination dst;
	const void *msg;
	SceSize msgLen;
	int option;
} SceNpMatching2SendRoomChatMessageRequest;

typedef struct SceNpMatching2SendRoomChatMessageResponse {
	bool filtered;
} SceNpMatching2SendRoomChatMessageResponse;

/*
 * sceNpMatching2SetRoomDataInternal()
 */
typedef struct SceNpMatching2SetRoomDataInternalRequest {
	SceNpMatching2RoomId roomId;
	SceNpMatching2FlagAttr flagFilter;
	SceNpMatching2FlagAttr flagAttr;
	const SceNpMatching2BinAttr *roomBinAttrInternal;
	SceUInt32           roomBinAttrInternalNum;
	const SceNpMatching2RoomGroupPasswordConfig *passwordConfig;
	SceUInt32 passwordConfigNum;
	const SceNpMatching2RoomPasswordSlotMask *passwordSlotMask;
	const SceNpMatching2RoomMemberId *ownerPrivilegeRank;
	SceUInt32 ownerPrivilegeRankNum;
	SceUChar8 padding[4];
} SceNpMatching2SetRoomDataInternalRequest;

/*
 * sceNpMatching2GetRoomDataInternal()
 */
typedef struct SceNpMatching2GetRoomDataInternalRequest {
	SceNpMatching2RoomId roomId;
	const SceNpMatching2AttributeId *attrId;
	SceUInt32 attrIdNum;
} SceNpMatching2GetRoomDataInternalRequest;

typedef struct SceNpMatching2GetRoomDataInternalResponse {
	SceNpMatching2RoomDataInternal *roomDataInternal;
} SceNpMatching2GetRoomDataInternalResponse;

/*
 * sceNpMatching2SetRoomMemberDataInternal()
 */
typedef struct SceNpMatching2SetRoomMemberDataInternalRequest {
	SceNpMatching2RoomId       roomId;
	SceNpMatching2RoomMemberId memberId;
	SceNpMatching2TeamId       teamId;
	SceUChar8 padding[5];
	SceNpMatching2FlagAttr     flagFilter;
	SceNpMatching2FlagAttr     flagAttr;
	const SceNpMatching2BinAttr     *roomMemberBinAttrInternal;
	SceUInt32               roomMemberBinAttrInternalNum;
} SceNpMatching2SetRoomMemberDataInternalRequest;

/*
 * sceNpMatching2GetRoomMemberDataInternal()
 */
typedef struct SceNpMatching2GetRoomMemberDataInternalRequest {
	SceNpMatching2RoomId roomId;
	SceNpMatching2RoomMemberId memberId;
	SceUChar8 padding[6];
	const SceNpMatching2AttributeId *attrId;
	SceUInt32 attrIdNum;
} SceNpMatching2GetRoomMemberDataInternalRequest;

typedef struct SceNpMatching2GetRoomMemberDataInternalResponse {
	SceNpMatching2RoomMemberDataInternal *roomMemberDataInternal;
} SceNpMatching2GetRoomMemberDataInternalResponse;

/*
 * sceNpMatching2SetSignalingOptParam()
 */
typedef struct SceNpMatching2SetSignalingOptParamRequest {
	SceNpMatching2RoomId roomId;
	SceNpMatching2SignalingOptParam sigOptParam;
} SceNpMatching2SetSignalingOptParamRequest;

/*
 * sceNpMatching2GetLobbyInfoList()
 */
typedef struct SceNpMatching2GetLobbyInfoListRequest {
	SceNpMatching2WorldId      worldId;
	SceNpMatching2RangeFilter  rangeFilter;
	const SceNpMatching2AttributeId *attrId;
	SceUInt32 attrIdNum;
} SceNpMatching2GetLobbyInfoListRequest;

typedef struct SceNpMatching2GetLobbyInfoListResponse {
	SceNpMatching2Range range;
	SceNpMatching2LobbyDataExternal *lobbyDataExternal;
} SceNpMatching2GetLobbyInfoListResponse;

/*
 * sceNpMatching2JoinLobby()
 */
typedef struct SceNpMatching2JoinLobbyRequest {
	SceNpMatching2LobbyId            lobbyId;
	const SceNpMatching2JoinedSessionInfo *joinedSessionInfo;
	SceUInt32 joinedSessionInfoNum;
	const SceNpMatching2BinAttr           *lobbyMemberBinAttrInternal;
	SceUInt32                     lobbyMemberBinAttrInternalNum;
	SceNpMatching2PresenceOptionData optData;
	SceUChar8 padding[4];
} SceNpMatching2JoinLobbyRequest;

typedef struct SceNpMatching2JoinLobbyResponse {
	SceNpMatching2LobbyDataInternal *lobbyDataInternal;
} SceNpMatching2JoinLobbyResponse;

/*
 * sceNpMatching2LeaveLobby()
 */
typedef struct SceNpMatching2LeaveLobbyRequest {
	SceNpMatching2LobbyId lobbyId;
	SceNpMatching2PresenceOptionData optData;
	SceUChar8 padding[4];
} SceNpMatching2LeaveLobbyRequest;

/*
 * sceNpMatching2SetLobbyMemberDataInternal()
 */
typedef struct SceNpMatching2SetLobbyMemberDataInternalRequest {
	SceNpMatching2LobbyId       lobbyId;
	SceNpMatching2LobbyMemberId memberId;
	SceUChar8 padding1[2];
	SceNpMatching2FlagAttr      flagFilter;	/*E Not Used */
	SceNpMatching2FlagAttr      flagAttr;	/*E Not Used */
	const SceNpMatching2JoinedSessionInfo *joinedSessionInfo;
	SceUInt32 joinedSessionInfoNum;
	const SceNpMatching2BinAttr      *lobbyMemberBinAttrInternal;
	SceUInt32                lobbyMemberBinAttrInternalNum;
	SceUChar8 padding2[4];
} SceNpMatching2SetLobbyMemberDataInternalRequest;

/*
 * sceNpMatching2GetLobbyMemberDataInternal()
 */
typedef struct SceNpMatching2GetLobbyMemberDataInternalRequest {
	SceNpMatching2LobbyId lobbyId;
	SceNpMatching2LobbyMemberId memberId;
	SceUChar8 padding[6];
	const SceNpMatching2AttributeId *attrId;
	SceUInt32 attrIdNum;
} SceNpMatching2GetLobbyMemberDataInternalRequest;

typedef struct SceNpMatching2GetLobbyMemberDataInternalResponse {
	SceNpMatching2LobbyMemberDataInternal *lobbyMemberDataInternal;
} SceNpMatching2GetLobbyMemberDataInternalResponse;

#define SCE_NP_MATCHING2_LOBBY_MEMBER_DATA_INTERNAL_LIST_MAX			256
#define SCE_NP_MATCHING2_LOBBY_MEMBER_DATA_INTERNAL_EXTENDED_DATA_LIST_MAX	64

/*
 * sceNpMatching2GetLobbyMemberDataInternalList()
 */
typedef struct SceNpMatching2GetLobbyMemberDataInternalListRequest {
	SceNpMatching2LobbyId lobbyId;
	const SceNpMatching2LobbyMemberId* memberId;
	SceUInt32 memberIdNum;
	const SceNpMatching2AttributeId *attrId;
	SceUInt32 attrIdNum;
	bool extendedData;
	SceUChar8 padding[7];
} SceNpMatching2GetLobbyMemberDataInternalListRequest;

typedef struct SceNpMatching2GetLobbyMemberDataInternalListResponse {
	SceNpMatching2LobbyMemberDataInternal *lobbyMemberDataInternal;
	SceUInt32 lobbyMemberDataInternalNum;
} SceNpMatching2GetLobbyMemberDataInternalListResponse;

/*
 * sceNpMatching2SendLobbyChatMessage()
 */
typedef struct SceNpMatching2SendLobbyChatMessageRequest {
	SceNpMatching2LobbyId lobbyId;
	SceNpMatching2CastType castType;
	SceUChar8 padding[3];
	SceNpMatching2LobbyMessageDestination dst;
	const void *msg;
	SceSize msgLen;
	int option;
} SceNpMatching2SendLobbyChatMessageRequest;

typedef struct SceNpMatching2SendLobbyChatMessageResponse {
	bool filtered;
} SceNpMatching2SendLobbyChatMessageResponse;

/*
 * sceNpMatching2SignalingGetPingInfo()
 */
typedef struct SceNpMatching2SignalingGetPingInfoRequest {
	SceNpMatching2RoomId roomId;
	SceUChar8 reserved[16];
} SceNpMatching2SignalingGetPingInfoRequest;

typedef struct SceNpMatching2SignalingGetPingInfoResponse {
	SceNpMatching2ServerId serverId;
	SceUChar8 padding1[2];
	SceNpMatching2WorldId worldId;
	SceNpMatching2RoomId roomId;
	SceUInt32 rtt;
	SceUChar8 reserved[20];
} SceNpMatching2SignalingGetPingInfoResponse;

/*E
 *******************************************************************************
 * Structures passed to Room Event Callback
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * ルームイベントコールバックで通知される構造体
 *******************************************************************************
 */

/*
 * SCE_NP_MATCHING2_ROOM_EVENT_MemberJoined
 * SCE_NP_MATCHING2_ROOM_EVENT_MemberLeft
 */
typedef struct SceNpMatching2RoomMemberUpdateInfo {
	const SceNpMatching2RoomMemberDataInternal *roomMemberDataInternal;
	SceNpMatching2EventCause eventCause;
	SceUChar8 padding[3];
	SceNpMatching2PresenceOptionData optData;
} SceNpMatching2RoomMemberUpdateInfo;

/*
 * SCE_NP_MATCHING2_ROOM_EVENT_RoomOwnerChanged
 */
typedef struct SceNpMatching2RoomOwnerUpdateInfo {
	SceNpMatching2RoomMemberId prevOwner;
	SceNpMatching2RoomMemberId newOwner;
	SceNpMatching2EventCause eventCause;
	SceUChar8 padding[3];
	const SceNpMatching2SessionPassword *roomPassword;
	SceNpMatching2PresenceOptionData optData;
} SceNpMatching2RoomOwnerUpdateInfo;

/*
 * SCE_NP_MATCHING2_ROOM_EVENT_Kickedout
 * SCE_NP_MATCHING2_ROOM_EVENT_RoomDestroyed
 */
typedef struct SceNpMatching2RoomUpdateInfo {
	SceNpMatching2EventCause eventCause;
	SceUChar8 padding[3];
	int errorCode;
	SceNpMatching2PresenceOptionData optData;
} SceNpMatching2RoomUpdateInfo;

/*
 * SCE_NP_MATCHING2_ROOM_EVENT_UpdatedRoomDataInternal
 */
typedef struct SceNpMatching2RoomDataInternalUpdateInfo {
	const SceNpMatching2RoomDataInternal      *newRoomDataInternal;
	const SceNpMatching2FlagAttr              *newFlagAttr;
	const SceNpMatching2FlagAttr              *prevFlagAttr;
	const SceNpMatching2RoomPasswordSlotMask  *newRoomPasswordSlotMask;
	const SceNpMatching2RoomPasswordSlotMask  *prevRoomPasswordSlotMask;
	const SceNpMatching2RoomGroup            **newRoomGroup;
	SceUInt32                                  newRoomGroupNum;
	const SceNpMatching2RoomBinAttrInternal  **newRoomBinAttrInternal;
	SceUInt32                                  newRoomBinAttrInternalNum;
} SceNpMatching2RoomDataInternalUpdateInfo;

/*
 * SCE_NP_MATCHING2_ROOM_EVENT_UpdatedRoomMemberDataInternal
 */
typedef struct SceNpMatching2RoomMemberDataInternalUpdateInfo {
	const SceNpMatching2RoomMemberDataInternal     *newRoomMemberDataInternal;
	const SceNpMatching2FlagAttr                   *newFlagAttr;
	const SceNpMatching2FlagAttr                   *prevFlagAttr;
	const SceNpMatching2TeamId                     *newTeamId;
	const SceNpMatching2RoomMemberBinAttrInternal **newRoomMemberBinAttrInternal;
	SceUInt32                                       newRoomMemberBinAttrInternalNum;
} SceNpMatching2RoomMemberDataInternalUpdateInfo;

/*
 * SCE_NP_MATCHING2_ROOM_EVENT_UpdatedSignalingOptParam
 */
typedef struct SceNpMatching2SignalingOptParamUpdateInfo {
	SceNpMatching2SignalingOptParam newSignalingOptParam;
} SceNpMatching2SignalingOptParamUpdateInfo;

/*E
 *******************************************************************************
 * Structures passed to Room Message Callback
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * ルームメッセージコールバックで通知される構造体
 *******************************************************************************
 */

/*
 * SCE_NP_MATCHING2_ROOM_EVENT_ChatMessage
 * SCE_NP_MATCHING2_ROOM_EVENT_Message
 */
typedef struct SceNpMatching2RoomMessageInfo {
	bool filtered;
	SceNpMatching2CastType castType;
	SceUChar8 padding[2];
	const SceNpMatching2RoomMessageDestination *dst;
	const SceNpId *srcMember;
	const void *msg;
	SceSize msgLen;
} SceNpMatching2RoomMessageInfo;

/*E
 *******************************************************************************
 * Structures passed to Lobby Event Callback
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * ロビーイベントコールバックで通知される構造体
 *******************************************************************************
 */

/*
 * SCE_NP_MATCHING2_LOBBY_EVENT_MemberJoined
 * SCE_NP_MATCHING2_LOBBY_EVENT_MemberLeft
 */
typedef struct SceNpMatching2LobbyMemberUpdateInfo {
	const SceNpMatching2LobbyMemberDataInternal *lobbyMemberDataInternal;
	SceNpMatching2EventCause eventCause;
	SceUChar8 padding[3];
	SceNpMatching2PresenceOptionData optData;
} SceNpMatching2LobbyMemberUpdateInfo;

/*
 * SCE_NP_MATCHING2_LOBBY_EVENT_LobbyDestroyed
 */
typedef struct SceNpMatching2LobbyUpdateInfo {
	SceNpMatching2EventCause eventCause;
	SceUChar8 padding[3];
	int errorCode;
} SceNpMatching2LobbyUpdateInfo;

/*
 * SCE_NP_MATCHING2_LOBBY_EVENT_UpdatedLobbyMemberDataInternal
 */
typedef struct SceNpMatching2LobbyMemberDataInternalUpdateInfo {
	SceNpMatching2LobbyMemberId memberId;
	SceUChar8 padding[2];
	SceNpId npId;
	SceNpMatching2FlagAttr                    flagFilter;
	SceNpMatching2FlagAttr                    newFlagAttr;
	const SceNpMatching2JoinedSessionInfo          *newJoinedSessionInfo;
	SceUInt32                                       newJoinedSessionInfoNum;
	const SceNpMatching2LobbyMemberBinAttrInternal *newLobbyMemberBinAttrInternal;
	SceUInt32                                       newLobbyMemberBinAttrInternalNum;
} SceNpMatching2LobbyMemberDataInternalUpdateInfo;

/*E
 *******************************************************************************
 * Structures passed to Lobby Message Callback
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * ロビーメッセージコールバックで通知される構造体
 *******************************************************************************
 */

/*
 * SCE_NP_MATCHING2_LOBBY_EVENT_ChatMessage
 */
typedef struct SceNpMatching2LobbyMessageInfo {
	bool filtered;
	SceNpMatching2CastType castType;
	SceUChar8 padding[2];
	const SceNpMatching2LobbyMessageDestination *dst;
	const SceNpId *srcMember;
	const void *msg;
	SceSize msgLen;
} SceNpMatching2LobbyMessageInfo;

/*E
 *******************************************************************************
 * Free memory needed in other module's pools
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * 必要な他モジュールの空いているプールサイズ
 *******************************************************************************
 */
#define SCE_NP_MATCHING2_LEAST_HTTP_POOL_SIZE (16*1024) // 16 KiB
#define SCE_NP_MATCHING2_LEAST_SSL_POOL_SIZE (96*1024) // 96 KiB
/*E
 *******************************************************************************
 * API Declarations
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * API 宣言
 *******************************************************************************
 */
#define SCE_NP_MATCHING2_POOLSIZE_DEFAULT (128 * 1024) // 128 KiB
#define SCE_NP_MATCHING2_THREAD_PRIORITY_DEFAULT SCE_KERNEL_DEFAULT_PRIORITY_USER
#define SCE_NP_MATCHING2_THREAD_STACK_SIZE_DEFAULT (16 * 1024) // 16 KiB
int
sceNpMatching2Init(
	SceSize poolSize,
	SceInt32 threadPriority,
	SceInt32 cpuAffinityMask,
	SceSize threadStackSize
	);

int
sceNpMatching2Term(
	void
	);

int
sceNpMatching2CreateContext(
	const SceNpId *npId,
	const SceNpCommunicationId *commId,
	const SceNpCommunicationPassphrase *passPhrase,
	SceNpMatching2ContextId *ctxId // Out
	);

int
sceNpMatching2DestroyContext(
	SceNpMatching2ContextId ctxId
	);

#define SCE_NP_MATCHING2_CONTEXT_START_TIMEOUT_DEFAULT	(20*1000000) // 20 seconds
#define SCE_NP_MATCHING2_CONTEXT_START_TIMEOUT_MIN		(5*1000000) // 5 seconds
int
sceNpMatching2ContextStart(
	SceNpMatching2ContextId ctxId,
	SceUInt64 timeout // 0 == DEFAULT
	);

int
sceNpMatching2AbortContextStart(
	SceNpMatching2ContextId ctxId
	);

int
sceNpMatching2ContextStop(
	SceNpMatching2ContextId ctxId
	);

int
sceNpMatching2SetDefaultRequestOptParam(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2RequestOptParam *optParam
	);

int
sceNpMatching2RegisterRoomEventCallback(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2RoomEventCallback cbFunc,
	void *cbFuncArg
	);

int
sceNpMatching2RegisterRoomMessageCallback(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2RoomMessageCallback cbFunc,
	void *cbFuncArg
	);

int
sceNpMatching2RegisterLobbyEventCallback(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2LobbyEventCallback cbFunc,
	void *cbFuncArg
	);

int
sceNpMatching2RegisterLobbyMessageCallback(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2LobbyMessageCallback cbFunc,
	void *cbFuncArg
	);

int
sceNpMatching2RegisterSignalingCallback(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2SignalingCallback cbFunc,
	void *cbFuncArg
	);

int
sceNpMatching2RegisterContextCallback(
	SceNpMatching2ContextCallback cbFunc,
	void *cbFuncArg
	);

#define sceNpMatching2AbortRequest(x, y) (0) // Deprecated, does nothing, never did anything on Vita

int
sceNpMatching2GetMemoryInfo(
	SceNpMatching2MemoryInfo *memInfo // Out
	);

int
sceNpMatching2GetServerLocal(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2Server *server // Out
);

int
sceNpMatching2GetWorldInfoList(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2GetWorldInfoListRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2SetUserInfo(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SetUserInfoRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2GetUserInfoList(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2GetUserInfoListRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2CreateJoinRoom(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2CreateJoinRoomRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2SearchRoom(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SearchRoomRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2JoinRoom(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2JoinRoomRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2LeaveRoom(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2LeaveRoomRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2GetRoomDataInternal(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2GetRoomDataInternalRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2SetRoomDataInternal(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SetRoomDataInternalRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2SetSignalingOptParam(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SetSignalingOptParamRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2GetRoomPasswordLocal(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2RoomId roomId,
	bool *withPassword, // Out
	SceNpMatching2SessionPassword *roomPassword // Out
	);

//int
//sceNpMatching2GetLobbyMemberIdListLocal(
//	SceNpMatching2ContextId ctxId,
//	SceNpMatching2LobbyId lobbyId,
//	SceNpMatching2LobbyMemberId *memberId,
//	uint32_t memberIdNum,
//	SceNpMatching2LobbyMemberId *me
//	);
//
int
sceNpMatching2GetSignalingOptParamLocal(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2RoomId roomId,
	SceNpMatching2SignalingOptParam *signalingOptParam // Out
	);

int
sceNpMatching2GetRoomDataExternalList(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2GetRoomDataExternalListRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2SetRoomDataExternal(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SetRoomDataExternalRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2GetRoomMemberDataInternal(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2GetRoomMemberDataInternalRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2SetRoomMemberDataInternal(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SetRoomMemberDataInternalRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2GetRoomMemberIdListLocal(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2RoomId roomId,
	int sortMethod,
	SceNpMatching2RoomMemberId *memberId, // Out
	SceUInt32 memberIdNum
	);

//int
//sceNpMatching2GetRoomMemberDataInternalLocal(
//	SceNpMatching2ContextId ctxId,
//	SceNpMatching2RoomId roomId,
//	SceNpMatching2RoomMemberId memberId,
//	SceNpMatching2AttributeId *attrId,
//	uint32_t attrIdNum,
//	SceNpMatching2RoomMemberDataInternal *member,
//	char   *buf,
//	size_t  bufLen
//	);

int
sceNpMatching2GetRoomMemberDataExternalList(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2GetRoomMemberDataExternalListRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2KickoutRoomMember(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2KickoutRoomMemberRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2GrantRoomOwner(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2GrantRoomOwnerRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2SendRoomChatMessage(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SendRoomChatMessageRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2SendRoomMessage(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SendRoomMessageRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2GetLobbyInfoList(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2GetLobbyInfoListRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);

int
sceNpMatching2JoinLobby(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2JoinLobbyRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);
int
sceNpMatching2LeaveLobby(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2LeaveLobbyRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);
int
sceNpMatching2SendLobbyChatMessage(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SendLobbyChatMessageRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);
int
sceNpMatching2SignalingGetPingInfo(
	SceNpMatching2ContextId ctxId,
	const SceNpMatching2SignalingGetPingInfoRequest *reqParam,
	const SceNpMatching2RequestOptParam *optParam,
	SceNpMatching2RequestId *assignedReqId // Out
	);


/*E
 *******************************************************************************
 * Signaling Related
 *******************************************************************************
 */
/*J
 *******************************************************************************
 * シグナリング関連
 *******************************************************************************
 */

/*
 * Np Connection Status
 */
#define SCE_NP_MATCHING2_SIGNALING_CONN_STATUS_INACTIVE		0
#define SCE_NP_MATCHING2_SIGNALING_CONN_STATUS_PENDING		1
#define SCE_NP_MATCHING2_SIGNALING_CONN_STATUS_ACTIVE		2

/*
 * Np Connection Info
 */
#define SCE_NP_MATCHING2_SIGNALING_CONN_INFO_RTT			1
#define SCE_NP_MATCHING2_SIGNALING_CONN_INFO_BANDWIDTH		2
#define SCE_NP_MATCHING2_SIGNALING_CONN_INFO_PEER_NP_ID		3
#define SCE_NP_MATCHING2_SIGNALING_CONN_INFO_PEER_ADDRESS	4
#define SCE_NP_MATCHING2_SIGNALING_CONN_INFO_MAPPED_ADDRESS	5
#define SCE_NP_MATCHING2_SIGNALING_CONN_INFO_PACKET_LOSS	6

typedef union SceNpMatching2SignalingConnectionInfo {
	SceUInt32 rtt;
	SceUInt32 bandwidth;
	SceNpId npId;
	struct {
		SceNetInAddr addr;
		SceUShort16 port;
		SceUChar8 padding[2];
	} address;
	SceUInt32 packetLoss;
} SceNpMatching2SignalingConnectionInfo;


int
sceNpMatching2SignalingGetConnectionStatus(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2RoomId roomId,
	SceNpMatching2RoomMemberId memberId,
	int *connStatus,
	SceNetInAddr *peerAddr,
	SceUShort16 *peerPort
	);

int
sceNpMatching2SignalingGetConnectionInfo(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2RoomId roomId,
	SceNpMatching2RoomMemberId memberId,
	int code,
	SceNpMatching2SignalingConnectionInfo *info
	);

/*
 * Np Signaling NetInfo
 */

/* nat staus */
#define SCE_NP_MATCHING2_SIGNALING_NETINFO_NAT_STATUS_UNKNOWN	0
#define SCE_NP_MATCHING2_SIGNALING_NETINFO_NAT_STATUS_TYPE		1
#define SCE_NP_MATCHING2_SIGNALING_NETINFO_NAT_STATUS_TYPE2		2
#define SCE_NP_MATCHING2_SIGNALING_NETINFO_NAT_STATUS_TYPE3		3

typedef struct SceNpMatching2SignalingNetInfo {
	SceSize size;
	SceNetInAddr localAddr;
	SceNetInAddr mappedAddr;
	int natStatus;
} SceNpMatching2SignalingNetInfo;

/*
 * Np Signaling NetInfo API
 */

int
sceNpMatching2SignalingGetLocalNetInfo(
	SceNpMatching2SignalingNetInfo *netinfo
	);

int
sceNpMatching2SignalingGetPeerNetInfo(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2RoomId roomId,
	SceNpMatching2RoomMemberId memberId,
	SceNpMatching2SignalingRequestId *reqId
	);

int
sceNpMatching2SignalingCancelPeerNetInfo(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2SignalingRequestId reqId
	);

int
sceNpMatching2SignalingGetPeerNetInfoResult(
	SceNpMatching2ContextId ctxId,
	SceNpMatching2SignalingRequestId reqId,
	SceNpMatching2SignalingNetInfo *netinfo
	);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_MATCHING2_H_ */
