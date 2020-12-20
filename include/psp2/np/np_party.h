#ifndef _DOLCESDK_PSP2_NP_NP_PARTY_H_
#define _DOLCESDK_PSP2_NP_NP_PARTY_H_

#include <stdbool.h>
#include <psp2/scebase.h>
#include <psp2/kernel/clib.h>
#include <psp2/rtc.h>
#include <psp2/np/np_common.h>
#include <psp2/np/np_basic.h>


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/**
 * @brief Type indicating a party room event.
 *
 * This type represents the type of party room event that occurred. The party room events are represented by the following constants:
 * <table>
 * <tr><td><b>Constant</b></td>							<td><b>Description</b></td></tr>
 * <tr><td>SCE_NP_PARTY_ROOM_EVENT_JOINED</td>			<td>The current user joined a party.</td></tr>
 * <tr><td>SCE_NP_PARTY_ROOM_EVENT_MEMBER_JOINED</td>	<td>A member joined the party that the current user is in.</td></tr>
 * <tr><td>SCE_NP_PARTY_ROOM_EVENT_MEMBER_LEFT</td>		<td>A member left the party that the current user is in.</td></tr>
 * <tr><td>SCE_NP_PARTY_ROOM_EVENT_LEFT</td>			<td>The current user left the party.</td></tr>
 * <tr><td>SCE_NP_PARTY_ROOM_EVENT_MEMBER_PRESENCE_UPDATE</td>	<td>A member in the party that the current user is in has updated their presence.</td></tr>
 * </table>
 *
 */
typedef SceUInt16 SceNpPartyRoomEventType;
/**
 * @defgroup const_PartyRoomEventType Party Room Event Types
 *
 * @brief  Party Room Events
 * @{
 */
#define SCE_NP_PARTY_ROOM_EVENT_JOINED					(0x0001) ///< Party room event indicating that the current user has joined a party.
#define SCE_NP_PARTY_ROOM_EVENT_MEMBER_JOINED			(0x0002) ///< Party room event indicating that a member has joined the party that the current user is in.
#define SCE_NP_PARTY_ROOM_EVENT_MEMBER_LEFT				(0x0003) ///< Party room event indicating that the current user has left the party.
#define SCE_NP_PARTY_ROOM_EVENT_LEFT					(0x0004) ///< Party room event indicating that a member has left the party that the current user is in.
#define SCE_NP_PARTY_ROOM_EVENT_MEMBER_PRESENCE_UPDATE	(0x0005) ///< Party room event indicating that a member's game presence has been updated.
/** @} */ //  End of group_PartyRoomEventType

/**
 * @brief Type indicating the party member voice state.
 *
 * This type represents the party member voice state. The party member voice states are represented by the following constants:
 * <table>
 * <tr><td><b>Constant</b></td>								<td><b>Description</b></td></tr>
 * <tr><td><c>SCE_NP_PARTY_MEMBER_VOICE_STATE_UNKNOWN</c></td>		<td>A member's voice peer-to-peer connection is unknown and being established.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_MEMBER_VOICE_STATE_CONNECTED</c></td>	<td>A member's voice peer-to-peer connection has been established.
 *															            This event represents the state of a party member that is not currently talking.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_MEMBER_VOICE_STATE_DISCONNECTED</c></td> <td>A member's voice peer-to-peer connection has been disconnected.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_MEMBER_VOICE_STATE_MUTED</c></td>	<td>A remote party member has been muted in the party application.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_MEMBER_VOICE_STATE_TALKING</c></td> <td>A party member is talking.
 *															There is no corresponding event to indicate when the party member has finished talking;
 *															so the game should use a timer to expire a party member from a talking state.
 *															It is recommended that games indicate that a party member is in a talking state for
 *															up to one second after an <c>SCE_NP_PARTY_MEMBER_VOICE_STATE_TALKING</c> voice event occurs.</td></tr>
 * </table>
 */
typedef SceUChar8 SceNpPartyMemberVoiceState;


/**
 * @defgroup const_PartyMemberVoiceState Party Member Voice States
 * @brief
 * Party Member Voice States
 * @{
 */
#define SCE_NP_PARTY_MEMBER_VOICE_STATE_UNKNOWN				(0x0000)	///< Party voice state indicating that a member's voice peer-to-peer connection is unknown and is being established.
#define SCE_NP_PARTY_MEMBER_VOICE_STATE_DISCONNECTED		(0x0001)	///< Party voice state indicating that a member's voice peer-to-peer connection has been disconnected.
#define SCE_NP_PARTY_MEMBER_VOICE_STATE_CONNECTED			(0x0002)	///< Party voice state indicating that a member's voice peer-to-peer connection has been established. This event represents the state of a party member that is not currently talking.
#define SCE_NP_PARTY_MEMBER_VOICE_STATE_TALKING				(0x0003)	///< Party voice state indicating that a member is talking. There is no corresponding event to indicate
																		///< when the party member has finished talking; so the game should use a timer to expire a party member
																		///< from a talking state. It is recommended that games indicate that a party member is in a talking state
																		///< for no less than 250 ms and no longer than one second after an <c>SCE_NP_PARTY_MEMBER_VOICE_STATE_TALKING</c>
																		///< voice event occurs. For most games, displaying an <c>SCE_NP_PARTY_MEMBER_VOICE_STATE_TALKING</c> event for
																		///< one second is recommended.
#define SCE_NP_PARTY_MEMBER_VOICE_STATE_MUTED				(0x0004)	///< Party voice state indicating that a remote party member has been muted in the party application.
/** @} */ //  end of group_PartyMemberVoiceState

/**
 * @defgroup const_Limits Party Room Limits
 * @brief Party Member Talking State Limits
 * @{
 */
#define SCE_NP_PARTY_ROOM_TALKING_LIMIT							1000000	///< The maximum time to consider a talking state to be valid, in microseconds.
/** @} */ //  end of const_Limits

/**
 * @brief Type indicating the party room state.
 *
 * This type represents the party room state. The party room states are represented by the following constants:
 * <table>
 * <tr><td><b>Constant</b></td>						<td><b>Description</b></td></tr>
 * <tr><td><c>SCE_NP_PARTY_STATE_IN_PARTY</c></td>			<td>The current user is in the party.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_STATE_NOT_IN_PARTY</c></td>		<td>The current user is not in the party.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_STATE_IN_PRIVATE_PARTY</c></td>	<td>The current user is in a private party.</td></tr>
 * </table>
 */
typedef SceUInt16 SceNpPartyState;


/**
 * @defgroup const_PartyState Party States
 * @brief Party State Defines
 * @{
 */
#define SCE_NP_PARTY_STATE_IN_PARTY						(0x0001)  ///< Party room state indicating that the current user is in the party.
#define SCE_NP_PARTY_STATE_NOT_IN_PARTY					(0x0002)  ///< Party room state indicating that the current user is not in the party.
#define SCE_NP_PARTY_STATE_IN_PRIVATE_PARTY				(0x0003)  ///< Party room state indicating that the current user is in a private party.
/** @} */ //  end of group_PartyState

/**
 * @brief Type indicating a party member ID.
 *
 * This type represents the unique ID of the party member.
 */
typedef SceUInt16 SceNpPartyRoomMemberId;

/**
 * @defgroup const_Limits Party Room Limits
 * @brief Party Room Limits
 * @{
 */
#define SCE_NP_PARTY_MEMBER_NUM_MAX		8		///< Maximum number of members in a party.
/** @} */ //  end of group_Limits

/**
 * @brief Type indicating party member flags.
 *
 * This type represents the flags of the party member.
 * The member flags are represented by the following constants:
 * <table>
 * <tr><td><b>Constant</b></td> <td><b>Description</b></td></tr>
 * <tr><td><c>SCE_NP_PARTY_MEMBER_FLAG_IS_ME</c></td> <td>The member is the current user.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_MEMBER_FLAG_IS_PARTY_LEADER</c></td> <td>The member is the party leader.</td></tr>
 * </table>
 */
typedef SceUInt8 SceNpPartyMemberFlags;


/**
 * @defgroup const_PartyMemberFlags Party Member Flags
 * @brief Party Member Flags
 * @{
 */
#define SCE_NP_PARTY_MEMBER_FLAG_IS_ME						(0x40) ///< Party member flag indicating that the member is the current user.
#define SCE_NP_PARTY_MEMBER_FLAG_IS_PARTY_LEADER			(0x80) ///< Party member flag indicating that the member is the party leader.
/** @} */ //  end of group_PartyMemberFlags

/**
 * @brief Type indicating the reason a member left the party room.
 *
 * This type represents the possible reasons a member leaves the party room. The reasons are represented by the following constants:
 * <table>
 * <tr><td><b>Constant</b></td>								<td><b>Description</b></td></tr>
 * <tr><td><c>SCE_NP_PARTY_ROOM_LEFT_REASON_USER_ACTION</c></td>	<td>Party member left due to the member's action, such as quitting the party.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_ROOM_LEFT_REASON_SERVER_ERROR</c></td>	<td>Party member left due to a server error.</td></tr>
 * <tr><td><c>SCE_NP_PARTY_ROOM_LEFT_REASON_KICKED_OUT</c></td>	<td>Party member left due to being kicked out of the party.</td></tr>
 * </table>
 */
typedef SceUInt32 SceNpPartyRoomLeftReason;


/**
 * @defgroup const_PartyRoomLeftReason Party Room Reason for Leaving Flags
 * @brief Reason for Leaving Flags
 * @{
 */
#define SCE_NP_PARTY_ROOM_LEFT_REASON_USER_ACTION				0x00000001 ///< Flag indicating that the party member left due to the member's action, such as quitting the party.
#define SCE_NP_PARTY_ROOM_LEFT_REASON_SERVER_ERROR				0x00000002 ///< Flag indicating that the party member left due to a server error.
#define SCE_NP_PARTY_ROOM_LEFT_REASON_KICKED_OUT				0x00000003 ///< Flag indicating that the party member left due to being kicked out of the party.
/** @} */ //  End of group_PartyRoomLeftReason



/**
 * @brief Structure containing general party member information.
 *
 * This structure contains general information pertaining to a party
 * member.
 *
 * @see
 * SceNpPartyMemberFlags, SceNpPartyRoomMemberId
 * @see
 * <c>SceNpBasicGamePresence</c>, <c>SceNpBasicInGamePresenceType</c>, <c>SceNpCommunicationId</c> in the <i>NP Basic Library Reference</i>.
 */
typedef struct SceNpPartyMemberInfo
{
	SceNpId						npId;												///< NP ID of the party member.
	SceNpPartyRoomMemberId		memberId;											///< Member ID of the party member.
	SceNpPartyMemberFlags		memberFlags;										///< Member flags of the party member.
	SceUChar8					reserved;											///< Reserved for internal use of NP Party library.
	SceNpBasicGamePresence		gamePresence __attribute__((__deprecated__));		///< Game presence of the party member. Deprecated; use <c>sceNpPartyGetMemberSessionInfo()</c> instead of this struct member.
	SceNpCommunicationId		commId __attribute__((__deprecated__));				///< NP Communication ID of the party member's game. Deprecated; use <c>sceNpPartyGetMemberSessionInfo()</c> instead of this struct member.
} SceNpPartyMemberInfo;

/**
 * @brief Structure containing the party member list.
 *
 * This structure lists the NP IDs of all party members.
 * It can include as many as <c>#SCE_NP_PARTY_MEMBER_NUM_MAX</c> members, where <c>#SCE_NP_PARTY_MEMBER_NUM_MAX</c> is defined as 8.
 */
typedef struct SceNpPartyMemberList
{
	SceNpId				members[SCE_NP_PARTY_MEMBER_NUM_MAX];	///< Array of NP IDs for party members.
	SceUInt8			memberNum;								///< Current count of members in the party.
	bool				privateParty;							///< Flag that when set to true indicates that only invited party members are allowed in the party.
	SceUChar8			padding[2];								///< Padding to keep the structure 4-byte aligned.
} SceNpPartyMemberList;

/**
 * @brief Structure containing party member voice information.
 *
 * This structure contains voice information pertaining to a party
 * member.
 * @see
 * SceNpPartyMemberVoiceState, SceNpPartyRoomMemberId
 */
typedef struct SceNpPartyMemberVoiceInfo
{
	SceNpPartyRoomMemberId			memberId;			///< Member ID of the party member.
	SceNpPartyMemberVoiceState		memberVoiceState;	///< Voice state of the party member. One of the states defined by <c>#SceNpPartyMemberVoiceState</c>.
	SceUChar8						padding;			///< Padding to keep the structure 4-byte aligned.
} SceNpPartyMemberVoiceInfo;

/**
 * @brief Event handler for receiving party room events.
 *
 * This event handler handles events related to the party room.
 *
 * When the event handler is registered using <c>sceNpPartyRegisterHandler()</c>, NP
 * Party generates events for notifying the application of various party room
 * events as described by <c>#SceNpPartyRoomEventType</c>. When the application calls
 * <c>#sceNpPartyCheckCallback()</c> and an event has occurred, the event handler is
 * called.
 *
 * The application must cast the <c><i>data</i></c> pointer to the appropriate structure to
 * retrieve the associated data of the event.
 *
 * <table>
 * <tr><td><b>SceNpPartyRoomEventType</b></td>					<td><b>Datatype</b></td></tr>
 * <tr><td><c>SCE_NP_PARTY_ROOM_EVENT_JOINED</c></td>					<td><c>SceNpPartyMemberList*</c> </td></tr>
 * <tr><td><c>SCE_NP_PARTY_ROOM_EVENT_MEMBER_JOINED</c></td>			<td><c>SceNpPartyMemberInfo*</c> </td></tr>
 * <tr><td><c>SCE_NP_PARTY_ROOM_EVENT_MEMBER_LEFT</c></td>				<td><c>SceNpPartyMemberInfo*</c> </td></tr>
 * <tr><td><c>SCE_NP_PARTY_ROOM_EVENT_LEFT</c></td>					<td><c>SceNpPartyRoomLeftReason*</c> </td></tr>
 * </table>
 *
 * @note
 * Ensure the immediate return of the event handler: for example, avoid
 * processing inside the handler that might delay its return.
 *
 * @note
 * The memory area pointed to by <c><i>data</i></c> will be released after the event handler
 * returns; if needed, the <c><i>data</i></c> value must be copied onto memory within the
 * handler by the application.
 *
 * @param eventType Generated event type.
 * @param data Event data.
 * @param userdata User data set upon registering the event handler.
 *
 * @see
 * SceNpPartyRoomEventType, sceNpPartyCheckCallback, sceNpPartyRegisterHandler
 */
typedef void (*SceNpPartyRoomEventHandler)(
	SceNpPartyRoomEventType eventType,
	const void* data,
	void* userdata
	);


/**
 * @brief Event handler for receiving party voice notification events.
 *
 * This event handler handles voice notification events related to the party room.
 *
 * When the event handler is registered using <c>sceNpPartyRegisterHandler()</c>, NP
 * Party generates voice notification events for notifying the application of when various
 * members of the party are speaking. When the application calls
 * <c>sceNpPartyCheckCallback()</c> and an event has occurred, the event handler is
 * called.
 *
 * @note
 * Ensure the immediate return of the event handler; for example, avoid
 * processing inside the handler that might delay its return.
 *
 * @param memberVoiceInfo Generated event type.
 * @param userdata User data set upon registering the event handler.
 *
 * @see
 * SceNpPartyMemberVoiceInfo, sceNpPartyCheckCallback, sceNpPartyRegisterHandler
 */
typedef void (*SceNpPartyVoiceEventHandler)(
	const SceNpPartyMemberVoiceInfo* memberVoiceInfo,
	void* userdata
	);

/**
 * @brief Structure containing NP Party initialization parameters.
 *
 * This structure represents the initialization parameters for the NP Party library.
 *
 * @note
 * This structure must be initialized with <c>sceNpPartyInitParamInit()</c>.
 *
 * @see
 * sceNpPartyInitParamInit
 */
typedef struct SceNpPartyInitParam {
	SceUInt32					sdkVersion;									///< SDK version.
	SceNpCommunicationId		commId __attribute__((__deprecated__));		///< The application's NP Communication ID. Deprecated.
} SceNpPartyInitParam;

/**
 * @brief Type indicating party game-session events.
 *
 * This type represents the kind of event received from the party game-session event handler.
 * The party game-session events are represented by the following constants:
 * <table>
 * <tr><td><b>Constant</b></td>								<td><b>Description</b></td></tr>
 * <tr><td>#SCE_NP_PARTY_GAME_SESSION_UPDATE_EVENT_READY    <td>If this event is received and the event handler returns <c>SCE_OK</c>, the application will receive #SCE_NP_PARTY_GAME_SESSION_MEMBER_UPDATE_EVENT events. The data field should be cast to an #SceNpPartyGameSessionUpdateReady structure.</td></tr>
 * <tr><td>#SCE_NP_PARTY_GAME_SESSION_MEMBER_UPDATE_EVENT   <td>The event handler has a game-session update event for a party member. The application should cast the data field into a struct object of type #SceNpPartyMemberGameSessionUpdateInfo.</td></tr>
 * </table>
 */
typedef SceUInt8 SceNpPartyGameSessionEvent;

/**
 * @defgroup const_PartyGameSessionEvents Party Game-Session Events
 * @brief Game-session events
 * @{
 */
#define SCE_NP_PARTY_GAME_SESSION_UPDATE_EVENT_READY	(0x01)	///< Party game-session update will be received by the application.
#define SCE_NP_PARTY_GAME_SESSION_MEMBER_UPDATE_EVENT   (0x02)  ///< Party game-session update was received for a party member. The application should cast the data field into a struct object of type #SceNpPartyMemberGameSessionUpdateInfo.
/** @} */ //  End of group const_PartyGameSessionEvents

/**
 * @brief Structure containing the party game session update-ready state.
 *
 * This structure contains the party game session update-ready state. When this event is
 * received, the status should be checked by the application. If the result is <c>SCE_OK</c>,
 * the application can receive party game-session updates. Each time the library is initialized, the application
 * must wait for this event to be received by the callback. If the result is not <c>SCE_OK</c> (which is rare
 * and should not occur), the application must terminate and re-initialize the party in order
 * to attempt to use party game-session updates.
 *
 * @see SceNpPartyGameSessionEventHandler, SceNpPartyGameSessionEvent, SCE_NP_PARTY_GAME_SESSION_MEMBER_UPDATE_EVENT
 */
typedef struct SceNpPartyGameSessionUpdateReady
{
	SceUInt32 result;												///< If the result is <c>SCE_OK</c>, the application will receive game-session updates for party members.
} SceNpPartyGameSessionUpdateReady;


/**
 * @brief Type indicating party game-session update for a party member.
 *
 * This type represents whether the remote party member is in a joinable game
 * with the current application. To be joinable, the game must be compatible with the application
 * that is locally using the NP Party library.
 *
 * The game-session member update types are represented by the following constants:
 * <table>
 * <tr><td><b>Constant</b></td>									<td><b>Description</b></td></tr>
 * <tr><td>#SCE_NP_PARTY_GAME_SESSION_UPDATE_TYPE_NOT_JOINABLE	<td>The party member is not in a joinable session with the application using the NP Party library</td></tr>
 * <tr><td>#SCE_NP_PARTY_GAME_SESSION_UPDATE_TYPE_JOINABLE		<td>The party member is in a joinable session with the application using the NP Party library.</td></tr>
 * </table>
 */
typedef SceUInt8 SceNpPartyGameSessionMemberUpdateType;

/**
 * @defgroup const_PartyGameSessionUpdateTypes Party Game-Session Update Types
 * @brief Game-session update types
 * @{
 */
#define SCE_NP_PARTY_GAME_SESSION_UPDATE_TYPE_NOT_JOINABLE	(0x01)	///< Party game-session update indicating that a party member is not in a joinable session.
#define SCE_NP_PARTY_GAME_SESSION_UPDATE_TYPE_JOINABLE		(0x02)	///< Party game-session update indicating that a party member is in a joinable session.
/** @} */ //  End of group const_PartyGameSessionUpdateTypes

/**
 * @brief Structure containing a party member's game-session update.
 *
 * This structure contains general information pertaining to a party member's joinable game session
 * member.
 *
 * @see
 * SCE_NP_PARTY_GAME_SESSION_MEMBER_UPDATE_EVENT
 */
typedef struct SceNpPartyMemberGameSessionUpdateInfo
{
	SceNpPartyGameSessionMemberUpdateType	type;					///< The game-session member update type for the party member specified in <c><i>memberId</i></c>.
	SceUInt8								reserved;				///< Reserved field; do not use.
	SceNpPartyRoomMemberId					memberId;				///< The member ID of the party member related to this game-session update.
	SceUInt8								reserved2[2];			///< Reserved field; do not use.
	SceNpSessionId							sessionId;				///< Session ID of the game being played by the party member specified in <c><i>memberId</i></c>. Only valid when <c><i>type</i></c> is <c>SCE_NP_PARTY_GAME_SESSION_UPDATE_TYPE_JOINABLE</c>.
} SceNpPartyMemberGameSessionUpdateInfo;

/**
 * @brief Event handler for receiving party member game-session updates.
 *
 * This event handler handles party member game-session events.
 *
 * When the event handler is registered using <c>sceNpPartyRegisterHandler()</c>, and the
 * <c>SCE_NP_PARTY_GAME_SESSION_UPDATE_EVENT_READY</c> is received by the application, NpParty
 * will generate party-member game-session update events for notifying the application
 * of a party member's game-session information. When the application calls
 * <c>sceNpPartyCheckCallback()</c> and an event has occurred, the event handler is
 * called.
 *
 * @note
 * Ensure the immediate return of the event handler; for example, avoid
 * processing inside the handler that might delay its return.  The data must
 * be copied from this structure during the callback. Do not reference
 * <c><i>data</i></c> after the callback returns.
 *
 * @param event The type of event being returned. If <c><i>event</i></c> is
 * #SCE_NP_PARTY_GAME_SESSION_UPDATE_EVENT_READY, the <c><i>data</i></c> field should be cast to
 * #SceNpPartyGameSessionUpdateReady. If <c><i>event</i></c> is #SCE_NP_PARTY_GAME_SESSION_MEMBER_UPDATE_EVENT,
 * the <c><i>data</i></c> field should be cast to #SceNpPartyMemberGameSessionUpdateInfo.
 * @param data  The data field should be cast to the appropriate type as specified by <c><i>event</i></c>.
 * @param userdata User data that is set when the event handler is registered.
 *
 * @see
 * SceNpPartyMemberGameSessionUpdateInfo,
 * SceNpPartyGameSessionUpdateReady,
 * sceNpPartyCheckCallback(),
 * sceNpPartyRegisterHandler(),
 * SceNpPartyGameSessionEvent
 */
typedef void (*SceNpPartyGameSessionEventHandler)(
	SceNpPartyGameSessionEvent event,
	const void *data,
	void * userdata
	);

/**
 * @brief Structure for registering event handlers.
 *
 * This structure is used for registering event handlers. It is passed as an
 * argument of <c>sceNpPartyRegisterHandler()</c>. If you do not want to use event handlers,
 * set the applicable member to NULL.
 *
 * @note
 * This structure must be initialized with <c>sceNpPartyEventHandlersInit()</c>.
 *
 * @see
 * SceNpPartyRoomEventHandler, SceNpPartyVoiceEventHandler, sceNpPartyRegisterHandler, sceNpPartyEventHandlersInit
 */
typedef struct SceNpPartyEventHandlers
{
	SceUInt32									sdkVersion;					///< SDK version.
	SceNpPartyRoomEventHandler					roomEventHandler;			///< Event handler for subscribing to party room events.
	SceNpPartyVoiceEventHandler					voiceEventHandler;			///< Event handler for subscribing to party voice notification events.
	SceNpPartyGameSessionEventHandler			gameSessionEventHandler;	///< Event handler for subscribing to game-session change events for party members.
} SceNpPartyEventHandlers;

/* ****************************************************************************
 *
 * General APIs
 *
 * ***************************************************************************/

 /**
 * @defgroup func_EventHandlingFunctions Event Handling Functions
 * @brief Event Handling Functions
 */
/**
 * @defgroup func_LibraryInitializationTerminationFunctions Library Initialization and Termination Functions
 * @brief Library Initialization and Termination Functions
 */
/**
 * @defgroup func_RequestFunctions Request Functions
 * @brief Request Functions
 */

/**
 * @brief Initializes the NP Party initialization parameters structure.
 *
 * This inline function initializes the NP Party initialization parameters structure.
 * Call this function first to setup an <c>SceNpPartyInitParam</c> structure; update the <c>SceNpPartyInitParam</c>
 * structure as appropriate for the application; then call <c>sceNpPartyInit()</c> with the updated data.
 *
 * @param param NP Party initialization parameters structure to be initialized.
 * @see
 * SceNpPartyInitParam
 * @ingroup func_LibraryInitializationTerminationFunctions
 */
static inline
void sceNpPartyInitParamInit(SceNpPartyInitParam *param)
{
    sceClibMemset(param, 0x0, sizeof(SceNpPartyInitParam));
    param->sdkVersion = SCE_PSP2_SDK_VERSION;
}


/**
 * @brief Initializes the NP Party library.
 *
 * This function initializes the NP Party library. Call <c>sceNpPartyInitParamInit()</c> first to setup an
 * <c>SceNpPartyInitParam</c> structure; update the <c>SceNpPartyInitParam</c> structure as appropriate for
 * the application; then call <c>sceNpPartyInit()</c> with the updated data.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @param param NP Party initialization parameters structure.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_PARTY_ERROR_ALREADY_INITIALIZED The NP Party library is already initialized.
 * @retval SCE_NP_PARTY_ERROR_INVALID_ARGUMENT Reserved parameter is not zeroed.
 *
 * @note
 * Because this function communicates with system processes, it can block other
 * processes. The length of time it blocks depends on the system process load. Make sure to call this
 * function from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * SceNpPartyInitParam, sceNpPartyTerm
 * @ingroup func_LibraryInitializationTerminationFunctions
 */
int sceNpPartyInit(const SceNpPartyInitParam *param);

/**
 * @brief Terminates the NP Party library.
 *
 * This function terminates the NP Party library.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * Because this function communicates with system processes, it can block other processes.
 * The length of time it blocks depends on the system process load. Make sure to call this function
 * from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * sceNpPartyInit
 * @ingroup func_LibraryInitializationTerminationFunctions
 */
int
sceNpPartyTerm(void);


/**
 * @brief Retrieves the list of current party members.
 *
 * This function obtains the list of current party members.
 *
 * @param memberList NP Party member list structure.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 * @retval SCE_NP_PARTY_ERROR_INVALID_ARGUMENT One or more NULL parameters.
 * @retval SCE_NP_PARTY_ERROR_NOT_IN_A_PARTY The member is not in a party.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * Because this function communicates with system processes, it can block other
 * processes. The length of time it blocks depends on the system process load. Make sure to call this
 * function from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * SceNpPartyMemberList, sceNpPartyInit
 * @ingroup func_RequestFunctions
 */
int
sceNpPartyGetMembers(
	SceNpPartyMemberList* memberList
	);

/**
 * @brief Retrieves party member details
 *
 * This obtains the party member information from a valid NP ID.
 *
 * @param npId NP ID of party member.
 * @param memberInfo Party member information structure.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 * @retval SCE_NP_PARTY_ERROR_INVALID_ARGUMENT One or more NULL parameters.
 * @retval SCE_NP_PARTY_ERROR_NOT_IN_A_PARTY The member is not in a party.
 * @retval SCE_NP_PARTY_ERROR_PARTY_MEMBER_NOT_FOUND The party member with the specified NP ID was not found.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * Because this function communicates with system processes, it can block other
 * processes. The length of time it blocks depends on the system process load. Make sure to call this
 * function from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * SceNpPartyMemberInfo, sceNpPartyGetMembers
 * @ingroup func_RequestFunctions
 */
int
sceNpPartyGetMemberInfo(
    const SceNpId *npId,
    SceNpPartyMemberInfo* memberInfo
    );

/**
 * @brief Retrieves party member voice details
 *
 * This function obtains party member voice information from a valid <c>#SceNpPartyRoomMemberId</c>.
 *
 * @param memberId <c>#SceNpPartyRoomMemberId</c> of party member.
 * @param memberVoiceState <c>#SceNpPartyMemberVoiceState</c> data.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 * @retval SCE_NP_PARTY_ERROR_VOICE_NOT_ENABLED Either <c>#SceNpPartyVoiceEventHandler</c> is not registered or there was an <c>SCE_NP_PARTY_GAME_SESSION_UPDATE_EVENT_READY</c> error.
 * @retval SCE_NP_PARTY_ERROR_INVALID_ARGUMENT One or more NULL parameters.
 * @retval SCE_NP_PARTY_ERROR_NOT_IN_A_PARTY The member is not in a party.
 * @retval SCE_NP_PARTY_ERROR_PARTY_MEMBER_NOT_FOUND The party member with the specified <c>#SceNpPartyRoomMemberId</c> was not found.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * Because this function communicates with system processes, it can block other
 * processes. The length of time it blocks depends on the system process load. Make sure to call this
 * function from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * SceNpPartyMemberVoiceState, SceNpPartyRoomMemberId, SceNpPartyVoiceEventHandler
 * @ingroup func_RequestFunctions
 */
int
sceNpPartyGetMemberVoiceInfo(
	const SceNpPartyRoomMemberId memberId,
	SceNpPartyMemberVoiceState* memberVoiceState
	);

/**
 * @brief Retrieves party member game-session details.
 *
 * This function obtains a party member game session from a valid #SceNpPartyRoomMemberId. This function
 * will only return the session ID details if the return value is <c>SCE_OK</c>.
 *
 * @param memberId Party member ID (<c>#SceNpPartyRoomMemberId</c>) used to retrieve game-session details.
 * @param memberGameSessionInfo Party member game session information.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 * @retval SCE_NP_PARTY_ERROR_GAME_SESSION_NOT_ENABLED #SceNpPartyGameSessionEventHandler is not registered.
 * @retval SCE_NP_PARTY_ERROR_INVALID_ARGUMENT One or more NULL parameters.
 * @retval SCE_NP_PARTY_ERROR_NOT_IN_PARTY No local users are in a party.
 * @retval SCE_NP_PARTY_ERROR_PARTY_MEMBER_NOT_FOUND The party member with the specified #SceNpPartyRoomMemberId was not found.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * Because this function communicates with system processes, it can block other
 * processes. The length of time during which it blocks other processes depends on the system process load. Make sure to call this
 * function from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * SceNpPartyMemberGameSessionUpdateInfo, SceNpPartyRoomMemberId, SceNpPartyGameSessionEventHandler
 * @ingroup func_RequestFunctions
 */
int
sceNpPartyGetMemberSessionInfo(
	const SceNpPartyRoomMemberId memberId,
	SceNpPartyMemberGameSessionUpdateInfo* memberGameSessionInfo
	);

/**
 * @brief Retrieves the party state of the current user.
 *
 * @param state NP Party state structure
 *
 * This function retrieves the party state of the user.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 * @retval SCE_NP_PARTY_ERROR_INVALID_ARGUMENT One or more NULL parameters.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * Because this function communicates with system processes, it can block other
 * processes. The length of time it blocks depends on the system process load. Make sure to call this
 * function from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * sceNpPartyInit, SceNpPartyState
 * @ingroup func_RequestFunctions
 */
int
sceNpPartyGetState(SceNpPartyState* state);

/**
 * @brief Initializes the event handler structure.
 *
 * This inline function is used to initialize the event handler structure. Call
 * this function before using <c>sceNpPartyRegisterHandler()</c>.
 *
 * @param handlers The event handler structure.
 *
 * @see
 * SceNpPartyEventHandlers, sceNpPartyRegisterHandler
 * @ingroup func_EventHandlingFunctions
 */
static inline
void sceNpPartyEventHandlersInit(SceNpPartyEventHandlers *handlers)
{
	sceClibMemset(handlers, 0x0, sizeof(SceNpPartyEventHandlers));
	handlers->sdkVersion = SCE_PSP2_SDK_VERSION;
}

/**
 * @brief Registers event handlers.
 *
 * Call this function to register event handlers.
 *
 * @param handlers Structure for the event handler registration.
 * @param userdata Any user data to pass to the event handler.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * Because this function communicates with system processes, it can block other
 * processes. The length of time it blocks depends on the system process load. Make sure to call this
 * function from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * SceNpPartyEventHandlers
 * @ingroup func_EventHandlingFunctions
 */
int
sceNpPartyRegisterHandler(
    const SceNpPartyEventHandlers *handlers,
    void *userdata
    );

/**
 * @brief Calls event handlers when an event occurs.
 *
 * This function checks for NP Party event occurrences. Call this function regularly after registering
 * an event handler using <c>sceNpPartyRegisterHandler()</c>. If an event has occurred, the NP Party library
 * calls that event's event handler.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * The event handler is executed in the context of the thread that calls this function.
 *
 * @see
 * sceNpPartyRegisterHandler
 * @ingroup func_EventHandlingFunctions
 */
int
sceNpPartyCheckCallback(void);


/**
 * @defgroup const_Limits Party Room Limits
 * @{
 */
#define SCE_NP_PARTY_ID_LENGTH 16        ///<     The length limit of the party room ID.
/** @} */ //  end of group_Limits

/**
 * @brief Structure for receiving the party ID.
 *
 * This structure contains a unique identifier for the party. This party room ID is guaranteed to be unique across parties at all times.
 *
 * @see sceNpPartyGetId()
 */
typedef struct SceNpPartyId
{
	SceUChar8  id[SCE_NP_PARTY_ID_LENGTH];   ///< Unique identifier for the party.
} SceNpPartyId;


/**
 * @brief Gets the party ID.
 *
 * This function retrieves the party room ID. Because all local users must be in the same party, if any of the local users are in a party, a party room ID will be returned.
 *
 * @param id #SceNpPartyId of the party.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 * @retval SCE_NP_PARTY_ERROR_INVALID_ARGUMENT One or more NULL parameters.
 * @retval SCE_NP_PARTY_ERROR_NOT_IN_PARTY No Local users are in a party.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @see
 *  SceNpPartyId
 * @ingroup func_RequestFunctions
 */
int
sceNpPartyGetId( SceNpPartyId * const id );


/**
 * @brief Retrieves the structure containing the party game session update-ready state.
 *
 * @param readyState Structure containing the party game session update-ready state.
 *
 * This function retrieves the structure containing the party game session update-ready state.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_PARTY_ERROR_NOT_INITIALIZED The NP Party library is not initialized.
 * @retval SCE_NP_PARTY_ERROR_INVALID_ARGUMENT One or more NULL parameters.
 * @retval SCE_NP_PARTY_ERROR_GAME_SESSION_NOT_ENABLED The #SceNpPartyGameSessionEventHandler is not registered.
 * @retval SCE_NP_PARTY_ERROR_OPERATION_IN_PROGRESS The party game session update-ready system is in progress and will finish when the <c>SceNpPartyGameSessionEventHandler</c> is called.
 *
 * @par Calling Conditions
 * Not multithread safe.
 *
 * @note
 * Because this function communicates with system processes, it can block other
 * processes. The length of time it blocks depends on the system process load. Make sure to call this
 * function from a thread that can tolerate the effects of the system process load; for example, do not
 * call this function on the rendering thread.
 *
 * @see
 * sceNpPartyRegisterHandler, SceNpPartyGameSessionEventHandler, SceNpPartyGameSessionUpdateReady
 * @ingroup func_RequestFunctions
 */
int
sceNpPartyGetGameSessionReadyState( SceNpPartyGameSessionUpdateReady* readyState );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_PARTY_H_ */

