#ifndef _DOLCESDK_PSP2_NP_NP_BASIC_H
#define _DOLCESDK_PSP2_NP_NP_BASIC_H

#include <psp2/rtc.h>
#include <psp2/np/np_common.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * @defgroup ConstantList Constant list
 * @brief
 * Various constants used by the NP basic library
 * @{
 */
/**
 * @defgroup ConstantList 定数リスト
 * @brief
 * NP Basicライブラリで使用する各種定数
 * @{
 */

/*  Maximum size of title */
/** タイトル名の最大サイズ */
#define SCE_NP_BASIC_TITLE_SIZE_MAX                   128

/*  Maximum size of InGame data messages */
/** InGameデータメッセージの最大サイズ */
#define SCE_NP_BASIC_IN_GAME_MESSAGE_SIZE_MAX         512

/*  Maximum size of Play Session Log description */
/** 一緒に遊んだログの説明の最大サイズ */
#define SCE_NP_BASIC_PLAY_SESSION_DESCRIPTION_SIZE_MAX 512

/*  The time for a Join Game Acknowledgment request to timeout */
/** ゲーム参加承認要求がタイムアウトする時間 */
#define SCE_NP_BASIC_JOIN_GAME_REQUEST_TIMEOUT_SEC		30   /* 30 sec */

/*  Maximum size of Join Game Acknowledgment deny reason messages */
/** ゲーム参加承認の拒否理由のメッセージサイズの最大値 */
#define SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_DENY_REASON_SIZE_MAX        128


/** @} */

/*
 * @defgroup ErrorCodeList Error code list
 * @brief
 * Error codes returned by the NP Basic library
 * @{
 */
/**
 * @defgroup ErrorCodeList エラーコードリスト
 * @brief
 * NP Basicライブラリが返すエラーコード
 * @{
 */
/*  Base error code of the NP Basic library */
/** NP Basicライブラリのエラーコードベース */
#define SCE_NP_BASIC_ERROR_BASE                0x80551d00
/*  Unknown error */
/** 不明なエラー */
#define SCE_NP_BASIC_ERROR_UNKNOWN             0x80551d01
/*  Invalid argument */
/** 不正な引数 */
#define SCE_NP_BASIC_ERROR_INVALID_ARGUMENT    0x80551d02
/*  There is not enough memory */
/** メモリ不足 */
#define SCE_NP_BASIC_ERROR_OUT_OF_MEMORY       0x80551d03
/*  Not initialized */
/** 初期化されていない */
#define SCE_NP_BASIC_ERROR_NOT_INITIALIZED     0x80551d04
/*  Already initialized */
/** すでに初期化されている */
#define SCE_NP_BASIC_ERROR_ALREADY_INITIALIZED 0x80551d05
/*  Signed out */
/** サインアウトしている */
#define SCE_NP_BASIC_ERROR_SIGNED_OUT          0x80551d06
/*  Not online */
/** オンラインでない */
#define SCE_NP_BASIC_ERROR_NOT_ONLINE          0x80551d07
/*  Searched data cannot be found */
/** 検索したデータがない */
#define SCE_NP_BASIC_ERROR_DATA_NOT_FOUND      0x80551d08
/*  Busy. Tokens have been used up */
/** ビジーである。トークンを使い切っている */
#define SCE_NP_BASIC_ERROR_BUSY                0x80551d09
/*  Not ready for communication */
/** コミュニケーションする準備が整っていない */
#define SCE_NP_BASIC_ERROR_NOT_READY_TO_COMMUNICATE 0x80551d0a
/*  NP Communication ID has not been supplied */
/** NPコミュニケーションIDが提供されていない */
#define SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED      0x80551d0b
/* Queue for communication between processes overflows. This error code returns through SceNpServiceStateCallback. */
/** プロセス間通信キューが溢れた。SceNpServiceStateCallback経由で返るエラーコードです。 */
#define SCE_NP_BASIC_ERROR_IPC_QUEUE_OVERFLOWED     0x80551d0c
/*  NP Communication ID is not written in param.sfo */
/** param.sfoにNPコミュニケーションIDが記述されていない */
#define SCE_NP_BASIC_ERROR_NO_NP_COMM_ID_IN_PARAM_SFO 0x80551d0e
/*  Response was sent on a timed out Join Game Acknowledgment request */
/** タイムアウトしたゲーム参加承認要求に応答が送信された */
#define SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_TIMEDOUT 0x80551d0f
/*  Response was sent on a canceled Join Game Acknowledgment request */
/** キャンセルされたゲーム参加承認要求に応答が送信された */
#define SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_CANCELED 0x80551d10
/*  Response was sent on a invalid Join Game Acknowledgment request */
/** 無効なゲーム参加承認要求に応答が送信された */
#define SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_INVALID 0x80551d11
/*  Join Ggame Aacknowledgment was set without registering handler */
/** ハンドラを登録せずにゲーム参加承認機能が設定された */
#define SCE_NP_BASIC_ERROR_NO_JOIN_GAME_ACK_HANDLER 0x80551d12

/** @} */

/*
 * @brief InGame data message
 *
 * Represents the InGame data message sent by the game.
 */
/**
 * @brief InGameデータメッセージ
 *
 * ゲームによって送信されるInGameデータメッセージを表します。
 *
 */
typedef struct SceNpBasicInGameDataMessage
{
	/* Arbitrary data */
	SceUInt8 data[SCE_NP_BASIC_IN_GAME_MESSAGE_SIZE_MAX];	/**< 任意のデータ */
	/* Actual data size */
	SceSize dataSize;										/**< 実際のデータサイズ */
} SceNpBasicInGameDataMessage;

/*
 * @brief Event handler of InGame data message
 *
 * Event handler for notifying incomming InGame data messages.
 *
 * @note
 * Copy data received with this handler to a game-side memory area while this handler is being called,
 * as they cannot be accessed after leaving this handler.
 *
 * @param from     Message sender
 * @param message  Message
 * @param userdata User data at the time of handler registration
 */
/**
 * @brief InGame データメッセージのイベントハンドラ
 *
 * InGameデータメッセージ到着を通知するイベントハンドラです。
 *
 * @note
 * このハンドラで受信したデータは、このハンドラから抜けるとアクセスできなくなるため、
 * このハンドラを呼び出している間にゲーム側のメモリ領域にコピーしてください。
 *
 * @param from     メッセージの送信者
 * @param message  メッセージ
 * @param userdata ハンドラ登録時のユーザデータ
 */
typedef void(*SceNpBasicInGameDataMessageEventHandler)(
	const SceNpId *from,
	const SceNpBasicInGameDataMessage *message,
	void *userdata
	);

/* ****************************************************************************
 *
 * General APIs
 *
 * ***************************************************************************/

/*
 * @brief Initialize NP Basic library
 *
 * This function initializes the NP Basic library.
 *
 * @param opt Option (Reserved for future extension; specify NULL)
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN Unknown error
 * @retval SCE_NP_BASIC_ERROR_ALREADY_INITIALIZED The NP Basic library is already initialized
 *
 * @note
 * This function is not multithread safe.
 *
 * @note
 * Because this function entails communication between processes on the system process side in order to
 * request processing to the system process, this function can block other processes for a long period of
 * time depending on the system process load. Do not call this function from a thread onto which you do
 * not want the effects of the system process load (the rendering thread, for example).
 *
 * @see
 * sceNpBasicTerm()
 */
/**
 * @brief NP Basicライブラリの初期化
 *
 * NP Basic ライブラリを初期化します。
 *
 * @param opt オプション(将来拡張用:NULLを指定してください)
 *
 * @retval SCE_OK 成功
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN 不明なエラー
 * @retval SCE_NP_BASIC_ERROR_ALREADY_INITIALIZED NP Basicライブラリはすでに初期化されている
 *
 * @note
 * 本関数はマルチスレッドセーフではありません。
 *
 * @note
 * 本関数はシステムプロセス側へのプロセス間通信を伴いシステムプロセスへ処理を依頼するため、
 * システムプロセスの負荷の状況によっては長時間ブロックする可能性があります。
 * システムプロセスの負荷に影響を受けたくないスレッド（描画スレッドなど）から本関数を呼び出さないでください。
 *
 * @see
 * sceNpBasicTerm()
 */
int sceNpBasicInit(void *opt);

/*
 * @brief Terminate the NP Basic library
 *
 * This function terminates the NP Basic library.
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN Unknown error
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED The NP Basic library has not been initialized
 *
 * @note
 * This function is not multithread safe.
 *
 * @note
 * Because this function entails communication between processes on the system process side in order to
 * request processing to the system process, this function can block other processes for a long period of
 * time depending on the system process load. Do not call this function from a thread onto which you do
 * not want the effects of the system process load (the rendering thread, for example).
 *
 * @see
 * sceNpBasicInit()
 */
/**
 * @brief NP Basicライブラリの終了
 *
 * NP Basic ライブラリを終了します。
 *
 * @retval SCE_OK 成功
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN 不明なエラー
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていない
 *
 * @note
 * 本関数はマルチスレッドセーフではありません。
 *
 * @note
 * 本関数はシステムプロセス側へのプロセス間通信を伴いシステムプロセスへ処理を依頼するため、
 * システムプロセスの負荷の状況によっては長時間ブロックする可能性があります。
 * システムプロセスの負荷に影響を受けたくないスレッド（描画スレッドなど）から本関数を呼び出さないでください。
 *
 * @see
 * sceNpBasicInit()
 */
int sceNpBasicTerm(void);

/*
 * @brief Check callback
 *
 * This function is for checking event occurrences.
 * Call this function regularly after registering an event handler using
 * sceNpBasicRegisterInGameDataMessageHandler(). If an event has occurred, that event's event handler will be called.
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED The NP Basic library has not been initialized
 *
 * @note
 * This function is not multithread safe.
 *
 * @note
 * The event handler will be executed in the context of the thread that calls this function.
 *
 * @see
 * sceNpBasicRegisterInGameDataMessageHandler()
 */
/**
 * @brief コールバックのチェック
 *
 * イベントが発生しているかどうか確認するための関数です。
 * sceNpBasicRegisterInGameDataMessageHandler()でイベントハンドラを登録したあと、
 * 定期的に本関数を呼び出してください。もしイベントが発生していれば、
 * そのイベントのイベントハンドラが呼び出されます。
 *
 * @retval SCE_OK 成功
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basic ライブラリが初期化されていない
 *
 * @note
 * 本関数はマルチスレッドセーフではありません。
 *
 * @note
 * イベントハンドラは、本関数を呼び出すスレッドのコンテキストで実行されます。
 *
 * @see
 * sceNpBasicRegisterInGameDataMessageHandler()
 */
int sceNpBasicCheckCallback(void);

/* ****************************************************************************
 *
 * InGame Data Message related APIs
 * InGame データメッセージ関連API
 *
 * ***************************************************************************/

/*
 * @brief Send InGame data message
 *
 * Sends an InGame data message to a specified address.
 * It is also possible to specify a recipient other than a friend.
 * The message will not be saved on the server.
 * Message will reach recipients satisfying the follwing conditions:
 * (1) the recipient is using the NP Basic library;
 * (2) the same NP communication ID is being used for the address;
 * (3) the recipient's NP service state is "Online".
 *
 * @param to Message address
 * @param message Message to be sent
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basic library has not been initialized
 * @retval SCE_NP_BASIC_ERROR_BUSY Busy. Sending frequency is too high.
 * @retval SCE_NP_BASIC_ERROR_NOT_READY_TO_COMMUNICATE Handler and NP communication ID have not been registered
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT Invalid argument
 * @retval SCE_NP_BASIC_ERROR_SIGNED_OUT Signed out
 * @retval SCE_NP_BASIC_ERROR_NOT_ONLINE Not online
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN Unknown error
 */
/**
 * @brief InGameデータメッセージの送信
 *
 * InGame データメッセージを指定した宛先に送信します。
 * フレンドでない宛先も指定することが可能です。
 * メッセージはサーバに保存されません。
 * メッセージは以下の条件の相手に届きます。
 * (1)NP Basicライブラリを使用している。
 * (2)宛先が同一のNPコミュニケーションIDを使っている。
 * (3)相手のNPのサービス状態が「オンライン」である。
 *
 * @param to メッセージの宛先
 * @param message 送信するメッセージ
 *
 * @retval SCE_OK 成功
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていない
 * @retval SCE_NP_BASIC_ERROR_BUSY ビジーである。送信頻度が高すぎます。
 * @retval SCE_NP_BASIC_ERROR_NOT_READY_TO_COMMUNICATE ハンドラとNPコミュニケーションIDが登録されていない
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT 不正な引数
 * @retval SCE_NP_BASIC_ERROR_SIGNED_OUT サインアウトしている
 * @retval SCE_NP_BASIC_ERROR_NOT_ONLINE オンラインでない
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN 不明なエラー
 */
int sceNpBasicSendInGameDataMessage(
	const SceNpId *to, const SceNpBasicInGameDataMessage *message
	);

/*
 * @brief Register an InGame data message handler
 *
 * This function registers the handler for receiving InGame data messages.
 *
 * @param handler InGame data message handler
 * @param context  Np Communication ID
 * @param userdata Arbitrary user data to pass to the handler
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED The NP Basic library has not been initialized
 * @retval SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED NP Communication ID has not been supplied
 *
 * @note
 * This function is not multithread safe.
 *
 * @note
 * Because this function entails communication between processes on the system process side in order to
 * request processing to the system process, this function can block other processes for a long period of
 * time depending on the system process load. Do not call this function from a thread onto which you do
 * not want the effects of the system process load (the rendering thread, for example).
 *
 * @note
 * If <c><i>commId</i></c> is not specified, the NP Communication ID specified in <c>sceNpInit()</c>
 * of the NP library will be used.
 * If <c><i>commId</i></c> is NULL and the NP Communication ID is not specified in <c>sceNpInit()</c>
 * either, <c>SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED</c> will be returned.
 *
 * @see
 * sceNpBasicUnregisterInGameDataMessageHandler
 */
/**
 * @brief InGameデータメッセージハンドラの登録
 *
 * InGameデータメッセージハンドラを登録します。
 *
 * @param handler InGameデータメッセージハンドラ
 * @param context  NPコミュニケーションID
 * @param userdata ハンドラに渡したい任意のユーザデータ
 *
 * @retval SCE_OK 成功
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていない
 * @retval SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED NPコミュニケーションIDが提供されてない
 *
 * @note
 * 本関数はマルチスレッドセーフではありません。
 *
 * @note
 * 本関数はシステムプロセス側へのプロセス間通信を伴いシステムプロセスへ処理を依頼するため、
 * システムプロセスの負荷の状況によっては長時間ブロックする可能性があります。
 * システムプロセスの負荷に影響を受けたくないスレッド（描画スレッドなど）から本関数を呼び出さないでください。
 *
 * @note
 * <c><i>commId</i></c>が指定されない場合、NPライブラリの<c>sceNpInit()</c>に指定したNPコミュニケーションIDが使用されます。
 * <c><i>commId</i></c>がNULLで、<c>sceNpInit()</c>にも指定していなかった場合は、
 * <c>SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED</c>が返ります。
 *
 * @see
 * sceNpBasicUnregisterInGameDataMessageHandler(), sceNpBasicCheckCallback()
 */
int sceNpBasicRegisterInGameDataMessageHandler(
	const SceNpBasicInGameDataMessageEventHandler handler,
	const SceNpCommunicationId *commId,
	void *userdata
	);

/*
 * @brief Unregister the InGame data message handler
 *
 * This function unregisters the InGame data message handler.
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED The NP Basic library has not been initialized
 *
 * @note
 * This function is not multithread safe.
 *
 * @note
 * Because this function entails communication between processes on the system process side in order to
 * request processing to the system process, this function can block other processes for a long period of
 * time depending on the system process load. Do not call this function from a thread onto which you do
 * not want the effects of the system process load (the rendering thread, for example).
 *
 * @see
 * sceNpBasicRegisterInGameDataMessageHandler()
 */
/**
 * @brief InGaemデータメッセージハンドラの登録解除
 *
 * InGameデータメッセージハンドラの登録を解除します。
 *
 * @retval SCE_OK 成功
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていない
 *
 * @note
 * 本関数はマルチスレッドセーフではありません。
 *
 * @note
 * 本関数はシステムプロセス側へのプロセス間通信を伴いシステムプロセスへ処理を依頼するため、
 * システムプロセスの負荷の状況によっては長時間ブロックする可能性があります。
 * システムプロセスの負荷に影響を受けたくないスレッド（描画スレッドなど）から本関数を呼び出さないでください。
 *
 * @see
 * sceNpBasicRegisterInGameDataMessageHandler()
 */
int sceNpBasicUnregisterInGameDataMessageHandler(
	void
	);

/* ****************************************************************************
 *
 * Play Session Log related APIs
 * 一緒に遊んだログ関連API
 *
 * ***************************************************************************/

/*
 * @brief Play Session Log description
 *
 * This structure represents a description of the Play Session Log.
 * It can be used for the purpose of describing gameplay, such as the contents of
 * the gaming session, quest names, level names, etc.
 */
/**
 * @brief 一緒に遊んだログの説明
 *
 * この構造体は、一緒に遊んだログの説明文を表します。
 * ゲーム内で遊んだ時の様子、クエスト名、レベル名など、
 * ゲームプレイを説明する目的で使用することができます。
 */
typedef struct SceNpBasicPlaySessionLogDescription {
	/* Text describing the log */
	char text[SCE_NP_BASIC_PLAY_SESSION_DESCRIPTION_SIZE_MAX]; /**< ログを説明するテキスト */
} SceNpBasicPlaySessionLogDescription;

/*
 * @brief Play Session Log
 *
 * This structure represents the Play Session Log.
 */
/**
 * @brief 一緒に遊んだログ
 *
 * この構造体は、一緒に遊んだログを表します。
 */
typedef struct SceNpBasicPlaySessionLog {
	/* Date played */
	SceRtcTick date;                         /**< 遊んだ日付 */
	/* Players met */
	SceNpId withWhom;                        /**< 一緒に遊んだプレイヤー */
	/* Np communication ID at the time of play */
	SceNpCommunicationId commId;             /**< 遊んだ時のコミュニケーションID */
	/* Title of the game played */
	char title[SCE_NP_BASIC_TITLE_SIZE_MAX]; /**< 一緒に遊んだゲームのタイトル名 */
	/* Log description */
	SceNpBasicPlaySessionLogDescription description;          /**< ログの説明 */
} SceNpBasicPlaySessionLog;

/*
 * @brief Play Session Log type
 *
 * This enumerated type represents the type of Play Session log.
 */
/**
 * @brief 一緒に遊んだログのタイプ
 *
 * この列挙型は、一緒に遊んだログのタイプを表します。
 */
typedef enum {
	/* Invalid type */
	SCE_NP_BASIC_PLAY_SESSION_LOG_TYPE_INVALID       = -1, /**< 無効なタイプ */
	/* Log of all titles */
	SCE_NP_BASIC_PLAY_SESSION_LOG_TYPE_ALL           = 0,  /**< 全タイトルのログ */
	/* Log filtered with the same NP Communication ID */
	SCE_NP_BASIC_PLAY_SESSION_LOG_TYPE_BY_NP_COMM_ID = 1,  /**< 同一NPコミュニケーションIDでフィルタされたログ */
	/* Maximum */
	SCE_NP_BASIC_PLAY_SESSION_LOG_TYPE_MAX           = 2   /**< 最大 */
} SceNpBasicPlaySessionLogType;

/*
 * @brief Record Play Session Log
 *
 * Records the Play Session Log with the specified users.
 * When this function is called, the library completes the time of calling and
 * the called game title. These are recorded in the system's database along with
 * <c><i>withWhom</i></c> and <c><i>description</i></c> as Play Session Log.
 * The recorded Play Session Log can be obtained with <c>sceNpBasicGetPlaySessionLog()</c>,
 *  and is also displayed on system software applications (ex. Friends Application).
 *
 * @param withWhome Player who has taken part in the same online gaming session
 * @param description Session description
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basic library has not been initialized
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT Invalid argument
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN Unknown error
 * @retval SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED NP Communication ID is not supplied
 *
 * @note
 * Do not call this function from the rendering thread, as it entails flash writing.
 *
 * @see
 * sceNpBasicGetPlaySessionLog(), sceNpBasicGetPlaySessionLogSize()
 */
/**
 * @brief 一緒に遊んだログを記録
 *
 * 指定したユーザとの一緒に遊んだログを記録します。
 * この関数を呼び出すと、呼び出した時点の時刻と呼び出したゲームタイトル名を
 * ライブラリが補完し、<c><i>withWhom</i></c>、<c><i>description</i></c>と共に、
 * システム内のデータベースに一緒に遊んだログとして記録されます。
 * 記録されたログは、sceNpBasicGetPlaySessionLog()で取り出すことができ、
 * また、システムソフトウェアのアプリケーション(例: フレンドのアプリケーション)にも表示されます。
 *
 * @param withWhom 同じオンラインゲームセッションで遊んだプレイヤー
 * @param description セッションの説明
 *
 * @retval SCE_OK 成功時
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていません
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT 不正な引数
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN 不明なエラー
 * @retval SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED NPコミュニケーションIDが与えられてません
 *
 * @note
 * 本関数はフラッシュ書き込みを伴うため描画スレッドから呼び出さないでください。
 *
 * @see
 * sceNpBasicGetPlaySessionLog(), sceNpBasicGetPlaySessionLogSize()
 */
int sceNpBasicRecordPlaySessionLog(const SceNpId *withWhom,
								   const SceNpBasicPlaySessionLogDescription *description);

/*
 * @brief Obtain the size of the Play Session Log
 *
 * Obtains the number of Play Session Logs.
 *
 * @param type Log type
 * @parma size Log size
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basic library has not been initialized
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT Invalid argument
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN Unknown error
 * @retval SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED NP Communication ID is not supplied
 *
 * @note
 * Do not call this function from the rendering thread, as it entails flash reading.
 *
 * @see
 * sceNpBasicRecordPlaySessionLog()
 */
/**
 * @brief 一緒に遊んだログのサイズの取得
 *
 * 一緒に遊んだログの数を取得します。
 *
 * @param type ログのタイプ
 * @param size ログのサイズ
 *
 * @retval SCE_OK 成功時
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていません
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT 不正な引数
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN 不明なエラー
 * @retval SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED NPコミュニケーションIDが与えられてません
 *
 * @note
 * 本関数はフラッシュ読み込みを伴うため描画スレッドから呼び出さないでください。
 *
 * @see
 * sceNpBasicRecordPlaySessionLog()
 */
int sceNpBasicGetPlaySessionLogSize(SceNpBasicPlaySessionLogType type,
									SceSize *size);

/*
 * @brief Obtain Play Session Log
 *
 * Obtains Play Session Logs.
 *
 * @param type  Log type
 * @param index Index to be obtained
 * @param log   Address for storing obtained log
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basic library has not been initialized
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT Invalid argument
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN Unknown error
 * @retval SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED NP Communication ID is not supplied
 *
 * @note
 * Do not call this function from the rendering thread, as it entails flash reading.
 *
 * @see
 * sceNpBasicRecordPlaySessionLog()
 */
/**
 * @brief 一緒に遊んだログの取得
 *
 * 一緒に遊んだログを取得します。
 *
 * @param type  ログのタイプ
 * @param index 取得するインデックス
 * @param log   取得したログを格納する宛先
 *
 * @retval SCE_OK 成功時
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていません
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT 不正な引数
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN 不明なエラー
 * @retval SCE_NP_BASIC_ERROR_NO_COMM_ID_SUPPLIED NPコミュニケーションIDが与えられてません
 *
 * @note
 * 本関数はフラッシュ読み込みを伴うため描画スレッドから呼び出さないでください。
 *
 * @see
 * sceNpBasicRecordPlaySessionLog()
 */
int sceNpBasicGetPlaySessionLog(SceNpBasicPlaySessionLogType type,
								unsigned int index,
								SceNpBasicPlaySessionLog *log);

/* ****************************************************************************
 *
 * Join Game Acknowledgment
 * ゲーム参加の承認
 *
 * ***************************************************************************/
/*
 * @brief Join Game Acknowledgment Response Types
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_ALLOW</c> signifies to the user they are allowed to join
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY</c> signifies to the user they cannot join
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_FULL</c> signifies to the user they cannot join due to the game being full
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_WITH_REASON</c> signifies to the user they cannot join but allowed for supplied text to be displayed
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_TIMEOUT</c> signifies to the user they cannot join because a timeout occurred
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_GENERAL</c> signifies to the user they cannot join due to a general error
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_GAME_DOES_NOT_EXIST</c> signifies to the user they cannot join because the game session no longer exists
 *
 * @see
 * SceNpBasicJoinGameAckResponseType, SceNpBasicJoinGameAckResponse
 */
/**
 * @brief ゲーム参加承認応答のタイプ
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_ALLOW</c>は、ユーザがゲームへの参加を許可されることを示します。
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY</c>は、ユーザがゲームへの参加を拒否されたことを示します。
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_FULL</c>は、ゲームが定員に達しているため、ユーザがゲームに参加できないことを示します。
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_WITH_REASON</c>は、ユーザはゲームには参加できないが、指定テキストの表示が許可されていることを示します。
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_TIMEOUT</c>は、タイムアウトが発生したために、ユーザがゲームに参加できないことを示します。
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_GENERAL</c>は、一般的なエラーが原因で、ユーザがゲームに参加できないことを示します。
 *
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_GAME_DOES_NOT_EXIST</c>は、ゲームセッションが存在しなくなったため、ユーザがゲームに参加できないことを示します。
 *
 * @see
 * SceNpBasicJoinGameAckResponseType, SceNpBasicJoinGameAckResponse
 */
typedef enum {
	/* Unknown */
	/** 不明 */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_UNKNOWN			= 0,
	/* Allow to Join */
	/** 参加を許可 */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_ALLOW				= 1,
	/* Not allowed to join */
	/** 参加を拒否 */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY				= 2,
	/* Not allowed to join */
	/** 参加を拒否(定員に達しているため) */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_FULL			= 3,
	/* Not allowed to join, with supplied text to be displayed */
	/** 参加を拒否 （指定のテキストを表示） */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_WITH_REASON	= 4,
	/* System timeout of Join Game Acknowledgment Request. Value only used by system */
	/** ゲーム参加確認要求のシステムタイムアウト。値はシステムによってのみ使用される */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_TIMEOUT		= 5,
	/* System error of Join Game Acknowledgment Request. Value only used by system */
	/** ゲーム参加確認要求のシステムエラー。値はシステムによってのみ使用される */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_GENERAL		= 6,
	/* System error game does not exist. Value only used by the system */
	/** ゲームが存在しないことを示すシステムエラー。値はシステムによってのみ使用される */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_SYSTEM_ERROR_GAME_DOES_NOT_EXIST		= 7,
	/* Max enum value for SceNpBasicJoinGameAckResponseType */
	/** SceNpBasicJoinGameAckResponseTypeの列挙値の最大値 */
	SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_MAX				= 8
} SceNpBasicJoinGameAckResponseType;

/*
 * @brief Event handler for the Join Game Acknowledgment Request received event
 *
 * This event handler handles events related to Join Game Acknowledgment Requests. If a Join Game
 * Acknowledgement is received the game must respond to it via sceNpBasicJoinGameAckResponseSend().
 * The Np Basic library will keep the request in memory until it has been responded to. Failing to
 * respond to a Join Game Acknowledgment requests will result in future Join Game
 * Acknowledgment requests being auto responded with DENY.
 *
 * @note
 * The event handler is called after a Join Game Acknowledgment is received. The event is generated
 * when the application calls sceNpBasicCheckCallback().
 *
 * @note
 * Avoid performing processing that entails a long time within the event handler and ensure its
 * immediate return.
 *
 * @param fromNpId NP ID of user issuing the Join Game Acknowledgment request.
 * @param userdata User data set upon registering the event handler
 *
 * @see
 * sceNpBasicCheckCallback(), sceNpBasicJoinGameAckResponseSend
 */
/**
 * @brief ゲーム参加承認要求の受信イベントのイベントハンドラ
 *
 * ゲーム参加承認要求に関するイベントを取り扱うイベントハンドラです。
 * ゲーム参加承認要求が受信された場合、ゲームはゲームは<c>sceNpBasicJoinGameAckResponseSend()</c>を使って応答する必要があります。
 * NP Basicライブラリは、応答が行われるまでこの要求をメモリ内に保持します。
 * ゲーム参加承認要求に応答しないと、今後受信するゲーム参加承認要求に対し、自動的に拒否（Deny）の応答をするようになります。
 *
 * @note
 * このイベントハンドラは、ゲーム参加承認要求が受信された後に呼び出されます。
 * このイベントは、アプリケーションがsceNpBasicCheckCallback()を呼び出す際に生成されます。
 *
 * @note
 * イベントハンドラ内で長い時間を要する処理を行うことは避け、すみやかにリターンしてください。
 *
 * @param fromNpId ゲーム参加承認要求を発行するユーザのNP ID
 * @param userdata イベントハンドラ登録時に設定したユーザデータ
 *
 * @see
 * sceNpBasicCheckCallback(), sceNpBasicJoinGameAckResponseSend
 */
typedef void (*SceNpBasicJoinGameAckRequestEventHandler)(
	const SceNpId fromNpId,
	void* userdata
	);

/*
 * @brief Register the Join Game Acknowledgment Request handler
 *
 * This function registers the handler for receiving Join Game Acknowledgment Request events.
 *
 * @param handler Event handler for Join Game Acknowledgment Request events
 * @param userdata Any user data to pass to the event handler.
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED The NP Basic library has not been initialized
 * @retval SCE_NP_BASIC_ERROR_ALREADY_INITIALIZED A Join Game Ack handler is already registered.
 *
 * @note
 * This function is not multithread safe.
 *
 * @see
 * SceNpBasicJoinGameAckRequestEventHandler, sceNpBasicUnregisterJoinGameAckHandler()
 */
/**
 * @brief ゲーム参加承認要求のハンドラの登録
 *
 * この関数は、ゲーム参加承認要求のイベントを受信するためのハンドラを登録します。
 *
 * @param handler ゲーム参加承認要求イベントのイベントハンドラ
 * @param userdata イベントハンドラに渡す任意のユーザデータ
 *
 * @retval SCE_OK 成功
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていない
 * @retval SCE_NP_BASIC_ERROR_ALREADY_INITIALIZED ゲーム参加確認要求のハンドラがすでに登録済みである
 *
 * @note
 * 本関数はマルチスレッドセーフではありません。
 *
 * @see
 * SceNpBasicJoinGameAckRequestEventHandler, sceNpBasicUnregisterJoinGameAckHandler()
 */
int sceNpBasicRegisterJoinGameAckHandler(
	SceNpBasicJoinGameAckRequestEventHandler handler,
	void* userdata
	);

/*
 * @brief Unregister the Join Game Acknowledgment Request handler
 *
 * This function unregisters the handler for receiving Join Game Acknowledgment Request events.
 *
 * @retval SCE_OK Successful
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED The NP Basic library has not been initialized
 *
 * @note
 * This function is not multithread safe.
 *
 * @note
 * Because this function entails communication between processes on the system process side in order to
 * request processing to the system process, this function can block other processes for a long period of
 * time depending on the system process load. Do not call this function from a thread onto which you do
 * not want the effects of the system process load (the rendering thread, for example).
 *
 * @see
 * sceNpBasicRegisterJoinGameAckHandler()
 */
/**
 * @brief ゲーム参加承認要求のハンドラの登録解除
 *
 * この関数は、ゲーム参加承認要求のイベントを受信するためのハンドラを登録解除します。
 *
 * @retval SCE_OK 成功
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていない
 *
 * @note
 * 本関数はマルチスレッドセーフではありません。
 *
 * @note
 * 本関数はシステムプロセス側へのプロセス間通信を伴いシステムプロセスへ処理を依頼するため、
 * システムプロセスの負荷の状況によっては他のプロセスを長時間ブロックする可能性があります。
 * システムプロセスの負荷に影響を受けたくないスレッド（レンダリングスレッドなど）から本関数を呼び出さないでください。
 *
 * @see
 * sceNpBasicRegisterJoinGameAckHandler()
 */
int sceNpBasicUnregisterJoinGameAckHandler(void);

/*
 * @brief Structure containing Join Game Acknowledgment Response information
 *
 * This structure contains Join Game Acknowledgment Response information. When supplying
 * the response type the only valid values are SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_ALLOW,
 * SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY, SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_FULL,
 * and SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_WITH_REASON
 *
 * @see
 * sceNpBasicJoinGameAckResponseSend
 */
/**
 * @brief ゲーム参加承認応答の情報を格納する構造体
 *
 * この構造体は、ゲーム参加承認応答 の情報を格納します。応答タイプを提供する際に有効な値は、
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_ALLOW</c>、
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY</c>、
 * <c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_FULL</c>、
 * および<c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_WITH_REASON</c>のみです。
 *
 * @see
 * sceNpBasicJoinGameAckResponseSend
 */
typedef struct SceNpBasicJoinGameAckResponse
{
	/* NpId to send response to */
	/** 応答の送信先のNP ID */
	SceNpId npId;
	/* Join Game Acknowledgment Response Type */
	/** ゲーム参加承認応答のタイプ */
	SceNpBasicJoinGameAckResponseType type;
	/* Supplied Deny reason when SceNpBasicJoinGameAckResponseType set to SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_WITH_REASON */
	/** <c>SceNpBasicJoinGameAckResponseType</c>が<c>SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_TYPE_DENY_WITH_REASON</c>に設定されている場合に提供される拒否理由 */
	char denyReason[SCE_NP_BASIC_JOIN_GAME_ACK_RESPONSE_DENY_REASON_SIZE_MAX];
} SceNpBasicJoinGameAckResponse;


/*
 * @brief Sends a Join Game Acknowledgment Response.
 *
 * This function will send a Join Game Acknowledgment Response to a NpId supplied in the
 * SceNpBasicJoinGameAckResponse structure. On successful completion this function will
 * remove the pending request from memory in the Np Basic library. This function will
 * error when responding to a Join Game Acknowledgment request that has timed out, been
 * canceled, or was previously responded to.
 *
 * @param response Join Game Acknowledgment response information.
 *
 * @retval SCE_OK Successful completion.
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN Unknown error.
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED The NP Basic Join Game Acknowledgment Request library is not initialized.
 * @retval SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_INVALID There is no Join Game Acknowledgment pending request corresponding to NpId of the response.
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT The input argument is invalid.
 * @retval SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_TIMEDOUT The request has timed out.
 * @retval SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_CANCELED The request has been canceled by the client.
 *
 * @note
 * Because this function entails communication between processes on the system process side in order to
 * request processing to the system process, this function can block other processes for a long period of
 * time depending on the system process load. Do not call this function from a thread onto which you do
 * not want the effects of the system process load (the rendering thread, for example).
 *
 * @note
 * This function is not multithread safe.
 *
 */
/**
 * @brief ゲーム参加承認応答の送信
 *
 * この関数は、ゲーム参加承認応答を<c>SceNpBasicJoinGameAckResponse</c>構造体で提供されるNP lDに送信します。
 * 正常に終了すると、この関数はNP Basicライブラリのメモリから保留中のゲーム参加承認要求を削除します。
 * タイムアウトしたり、キャンセルされたゲーム参加承認要求、または以前応答したゲーム参加承認要求に応答した場合は、エラーが発生します。
 *
 * @param response ゲーム参加承認応答の情報
 *
 * @retval SCE_OK 正常終了
 * @retval SCE_NP_BASIC_ERROR_UNKNOWN 未知のエラー
 * @retval SCE_NP_BASIC_ERROR_NOT_INITIALIZED NP Basicライブラリが初期化されていない
 * @retval SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_INVALID ゲーム参加承認応答のNP IDに対応する保留中のゲーム参加承認要求がない
 * @retval SCE_NP_BASIC_ERROR_INVALID_ARGUMENT 入力引数が無効である
 * @retval SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_TIMEDOUT リクエストがタイムアウトした
 * @retval SCE_NP_BASIC_ERROR_JOIN_GAME_ACK_REQUEST_CANCELED リクエストがクライアントによってキャンセルされた
 *
 * @note
 * 本関数はシステムプロセス側へのプロセス間通信を伴いシステムプロセスへ処理を依頼するため、
 * システムプロセスの負荷の状況によっては他のプロセスを長時間ブロックする可能性があります。
 * システムプロセスの負荷に影響を受けたくないスレッド（レンダリングスレッドなど）から本関数を呼び出さないでください。
 *
 * @note
 * 本関数はマルチスレッドセーフではありません。
 *
 */
int sceNpBasicJoinGameAckResponseSend(const SceNpBasicJoinGameAckResponse* response);

/* ****************************************************************************
 *
 * Obsolete
 *
 * ***************************************************************************/

#define SCE_NP_BASIC_IN_GAME_PRESENCE_STATUS_SIZE_MAX 192
#define SCE_NP_BASIC_IN_GAME_PRESENCE_DATA_SIZE_MAX   128

typedef enum {
	SCE_NP_BASIC_IN_GAME_PRESENCE_TYPE_UNKNOWN = -1,
	SCE_NP_BASIC_IN_GAME_PRESENCE_TYPE_NONE     = 0,
	SCE_NP_BASIC_IN_GAME_PRESENCE_TYPE_DEFAULT  = 1,
	SCE_NP_BASIC_IN_GAME_PRESENCE_TYPE_GAME_JOINING = 2,
	SCE_NP_BASIC_IN_GAME_PRESENCE_TYPE_GAME_JOINING_ONLY_FOR_PARTY = 3,
	SCE_NP_BASIC_IN_GAME_PRESENCE_TYPE_JOIN_GAME_ACK = 4,
	SCE_NP_BASIC_IN_GAME_PRESENCE_TYPE_MAX      = 5
} SceNpBasicInGamePresenceType;

typedef struct SceNpBasicInGamePresence
{
	SceUInt32 sdkVersion;
	SceNpBasicInGamePresenceType type;
	char status[SCE_NP_BASIC_IN_GAME_PRESENCE_STATUS_SIZE_MAX];
	SceUInt8 data[SCE_NP_BASIC_IN_GAME_PRESENCE_DATA_SIZE_MAX];
	SceSize dataSize;
} SceNpBasicInGamePresence;

typedef struct SceNpBasicGamePresence
{
	SceSize size;
	char title[SCE_NP_BASIC_TITLE_SIZE_MAX];
	SceNpBasicInGamePresence inGamePresence;
} SceNpBasicGamePresence;

#ifdef __cplusplus
}
#endif /* __cplusplus */

//#include <psp2/np/np_basic_obsolete.h>

#endif /* _DOLCESDK_PSP2_NP_NP_BASIC_H */
