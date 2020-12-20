#ifndef _DOLCESDK_PSP2_APPUTIL_H_
#define _DOLCESDK_PSP2_APPUTIL_H_

#include <psp2/types.h>
#include <psp2/error.h>
#include <psp2/kernel/types.h>
#include <psp2/system_param.h>
#include <psp2/np/np_common.h>
#include <psp2/np/np_message.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */


/*
 * Error number definition
 */

/*J 共通エラーコード */
/*E common error code */

/*J パラメータが不正である */
/*E invalid parameter */
#define SCE_APPUTIL_ERROR_PARAMETER								(-2146433536)	/* 0x80100600 */

/*J 初期化が行われていない */
/*E initialization not yet */
#define SCE_APPUTIL_ERROR_NOT_INITIALIZED						(-2146433535)	/* 0x80100601 */

/*J メモリ確保に失敗した */
/*E memory allocation failed */
#define SCE_APPUTIL_ERROR_NO_MEMORY								(-2146433534)	/* 0x80100602 */

/*J コンテンツが現在マウント状態である */
/*E contents already mounted */
#define SCE_APPUTIL_ERROR_BUSY									(-2146433533)	/* 0x80100603 */

/*J コンテンツが現在マウント状態でない */
/*E contents not mounted */
#define SCE_APPUTIL_ERROR_NOT_MOUNTED							(-2146433532)	/* 0x80100604 */

/*J APIの呼び出し権限が無い */
/*E permission denied */
#define SCE_APPUTIL_ERROR_NO_PERMISSION							(-2146433531)	/* 0x80100605 */

/*J パスコードが一致しない */
/*E passcode mismatch */
#define SCE_APPUTIL_ERROR_PASSCODE_MISMATCH						(-2146433530)	/* 0x80100606 */

/*J 関数呼び出し時のスタックサイズが足りない */
/*E stack size is insufficient to call api */
#define SCE_APPUTIL_ERROR_STACKSIZE_TOO_SHORT					(-2146433376)	/* 0x801006a0 */

/*J イベント通知系エラーコード */
/*E event error code */

/*J イベントパースした結果が不正である */
/*E invalid event data */
#define SCE_APPUTIL_ERROR_APPEVENT_PARSE_INVALID_DATA			(-2146433504)	/* 0x80100620 */


/*J セーブデータ系エラーコード */
/*E savedata error code */

/*J 指定したセーブデータスロットIDにスロットデータが存在する */
/*E savedata slot data already exists */
#define SCE_APPUTIL_ERROR_SAVEDATA_SLOT_EXISTS					(-2146433472)	/* 0x80100640 */

/*J 指定したセーブデータスロットIDにスロットデータが存在しない */
/*E savedata slot data not found */
#define SCE_APPUTIL_ERROR_SAVEDATA_SLOT_NOT_FOUND				(-2146433471)	/* 0x80100641 */

/*J セーブデータを書き込むだけの空き容量がセーブデータ領域にない */
/*E not enough space for write savedata at savedata space */
#define SCE_APPUTIL_ERROR_SAVEDATA_NO_SPACE_QUOTA				(-2146433470)	/* 0x80100642 */

/*J セーブデータを書き込むだけの空き容量がファイルシステムにない */
/*E not enough space for write savedata at file system */
#define SCE_APPUTIL_ERROR_SAVEDATA_NO_SPACE_FS					(-2146433469)	/* 0x80100643 */


/*J 追加コンテンツ系エラーコード */
/*E additional contents error code */

/*J 追加コンテンツの権利が無い */
/*E entitlement of additional contents is not exist */
#define SCE_APPUTIL_ERROR_DRM_NO_ENTITLEMENT					(-2146433440)	/* 0x80100660 */


/*J マウント系エラーコード */
/*E mount error code */

/*J フォトデータ用デバイスが存在しない */
/*E photo data device not found */
#define SCE_APPUTIL_ERROR_PHOTO_DEVICE_NOT_FOUND				(-2146433408)	/* 0x80100680 */

/*J ミュージックデータ用デバイスが存在しない */
/*E music data device not found */
#define SCE_APPUTIL_ERROR_MUSIC_DEVICE_NOT_FOUND				(-2146433403)	/* 0x80100685 */

/*J マウント数オーバー */
/*E mount limit over */
#define SCE_APPUTIL_ERROR_MOUNT_LIMIT_OVER						(-2146433402)	/* 0x80100686 */

/*
 * constants
 */

/*J アプリケーションデータドライブ名 */
/*E drive name of application */
#define SCE_APPUTIL_APP_DRIVE_NAME								"app0:"

/*J セーブデータドライブ名 */
/*E drive name of savedata */
#define SCE_APPUTIL_SAVEDATA_DRIVE_NAME							"savedata0:"

/*J	セーブデータ追加ドライブ名 */
/*E additional drive name of savedata */
#define SCE_APPUTIL_SAVEDATA_DRIVE_NAME_ADD						"savedata1:"

/*J 追加コンテンツドライブ名 */
/*E drive name of addcont */
#define SCE_APPUTIL_ADDCONT_DRIVE_NAME							"addcont0:"

/*J 追加コンテンツ追加ドライブ名 */
/*E additional drive name of addcont */
#define SCE_APPUTIL_ADDCONT_DRIVE_NAME_ADD						"addcont1:"

/*E max size of screenshot content path */
/*J フォトデータドライブ名 */
/*E drive name of photo data */
#define SCE_APPUTIL_PHOTO_DRIVE_NAME							"photo0:"

/*J ミュージックデータドライブ名 */
/*E drive name of music data */
#define SCE_APPUTIL_MUSIC_DRIVE_NAME							"music0:"


/*J イベント通知タイプ */
/*E event type */
#define SCE_APPUTIL_APPEVENT_TYPE_INVALID						(0)				/*J 不正なイベントタイプ */
																				/*E invalid event */
#define SCE_APPUTIL_APPEVENT_TYPE_NP_INVITE_MESSAGE				(1)				/*J 招待メッセージ */
																				/*E invitation message */
#define SCE_APPUTIL_APPEVENT_TYPE_NP_APP_DATA_MESSAGE			(2)				/*J ゲームデータ添付メッセージ */
																				/*E game data attachment message */
																/* reserved (3) */
																/* reserved (4) */
#define SCE_APPUTIL_APPEVENT_TYPE_LIVEAREA						(5)				/*J LiveArea(TM) からの起動 */
																				/*E Boot-up from LiveArea(TM) */
																/* reserved (6) */
																/* reserved (7) */
#define SCE_APPUTIL_APPEVENT_TYPE_SCREENSHOT_NOTIFICATION		(8)				/*J スクリーンショットノーティフィケーション */
																/* reserved (9) */
																/* reserved (10) */
#define SCE_APPUTIL_APPEVENT_TYPE_NP_ACTIVITY					(11)			/*J アクティビティからの起動 */
																				/*E Boot-up from Activity */
#define SCE_APPUTIL_APPEVENT_TYPE_TELEPORT						(12)			/*J Teleportによる起動 */
																				/*E Boot-up by Teleport */
#define SCE_APPUTIL_APPEVENT_TYPE_SESSION_INVITATION			(13)			/*J Session/Invitation */
																				/*E session/invitation */
#define SCE_APPUTIL_APPEVENT_TYPE_GAME_CUSTOM_DATA				(14)			/*J Game Custom Data */
																				/*E game custom data */
																/* reserved (15) */

/*E screenshot notification */
/*J イベント通知パラメータ最大サイズ */
/*E event parameter size */
#define SCE_APPUTIL_APPEVENT_PARAM_MAXSIZE						(1024)			/*J 通知パラメータ最大サイズ */
																				/*E max size of event parameter */

/*J LiveArea(TM) からの起動のパラメータ最大サイズ */
/*E event parameter size of parameter for Boot-Up from LiveArea(TM) */
#define SCE_APPUTIL_LIVEAREA_PARAM_MAX_SIZE						(1019)			/*J LiveArea(TM) からの起動のパラメータ最大サイズ */
																				/*E max size of parameter for Boot-Up from LiveArea(TM) */

/*J Activityからの起動のパラメータ最大サイズ */
/*E event parameter size of parameter for Boot-Up from Activity */
#define SCE_APPUTIL_NP_ACTIVITY_PARAM_MAXSIZE					(897)			/*J Activityからの起動のパラメータ最大サイズ */
																				/*E max size of parameter for Boot-Up from Activity */

/*J Teleportからの起動のパラメータ最大サイズ */
/*E event parameter size of parameter for Boot-Up from Teleport */
#define SCE_APPUTIL_TELEPORT_PARAM_MAXSIZE						(952)			/*J Teleportからの起動のパラメータ最大サイズ */
																				/*E max size of parameter for Boot-Up from Teleport */

/*J タイトルIDサイズ */
/*E title id size */
#define SCE_APPUTIL_TITLE_ID_DATA_SIZE							(10)			/*J タイトルIDサイズ */
																				/*E title id size */

/*J パスコードサイズ */
/*E passcode size */
#define SCE_APPUTIL_PASSCODE_DATA_SIZE							(32)			/*J パスコードサイズ */
																				/*E passcode size */

/*J マウントポイントサイズ */
/*E max size of mount point */
#define SCE_APPUTIL_MOUNTPOINT_DATA_MAXSIZE						(16)			/*J マウントポイント名最大サイズ */
																				/*E mount point max size */

/*J セーブデータスロットパラメータサイズ */
/*E savedata slot parameter size */
#define SCE_APPUTIL_SAVEDATA_SLOT_TITLE_MAXSIZE					(64)			/*J タイトル名最大サイズ */
																				/*E max size of title name */
#define SCE_APPUTIL_SAVEDATA_SLOT_SUBTITLE_MAXSIZE				(128)			/*J サブタイトル名最大サイズ */
																				/*E max size of subtitle name */
#define SCE_APPUTIL_SAVEDATA_SLOT_DETAIL_MAXSIZE				(512)			/*J 詳細情報最大サイズ */
																				/*E max size of detail info */
#define SCE_APPUTIL_SAVEDATA_SLOT_ICON_PATH_MAXSIZE				(64)			/*J サムネイル画像パス最大サイズ */
																				/*E max size of thumbnail icon file path */
#define SCE_APPUTIL_SAVEDATA_SLOT_MAX							(256)			/*J 最大スロット数 */
																				/*E max size of slot */
/*J セーブデータスロットステータス */
/*E constant value for savedata slot status */
#define SCE_APPUTIL_SAVEDATA_SLOT_STATUS_AVAILABLE				(0)				/*J 通常状態 */
																				/*E default */
#define SCE_APPUTIL_SAVEDATA_SLOT_STATUS_BROKEN					(1)				/*J 破損状態 */
																				/*E broken */
/*J 使用不可セーブデータスロットID */
/*E invalid savedata slot id */
#define SCE_APPUTIL_SAVEDATA_SLOT_ID_INVALID					(0xFFFFFFFF)

/*J セーブデータスロット検索対象 */
/*E savedata slot search type */
#define SCE_APPUTIL_SAVEDATA_SLOT_SEARCH_TYPE_EXIST_SLOT (0)	/*J 存在するスロットを対象とする */
																/*E search for exist slot */
#define SCE_APPUTIL_SAVEDATA_SLOT_SEARCH_TYPE_EMPTY_SLOT (1)	/*J 空スロットを対象とする */
																/*E search for empty slot */

/*J セーブデータスロットソートキー */
/*E savedata slot sort key */
#define SCE_APPUTIL_SAVEDATA_SLOT_SORT_KEY_SLOT_ID       (0)	/*J スロットID */
																/*E slot id */
#define SCE_APPUTIL_SAVEDATA_SLOT_SORT_KEY_USER_PARAM    (1)	/*J ユーザパラメータ */
																/*E user parameter */
#define SCE_APPUTIL_SAVEDATA_SLOT_SORT_KEY_SIZE_KIB      (2)	/*J データサイズ（KiB） */
																/*E data size (KiB) */
#define SCE_APPUTIL_SAVEDATA_SLOT_SORT_KEY_MODIFIED_TIME (3)	/*J 最終更新日時 */
																/*E last modified time */

/*J セーブデータスロットソート順 */
/*E savedata slot sort order */
#define SCE_APPUTIL_SAVEDATA_SLOT_SORT_TYPE_ASCENT       (0)	/*J 昇順 */
																/*E ascending order */
#define SCE_APPUTIL_SAVEDATA_SLOT_SORT_TYPE_DESCENT      (1)	/*J 降順 */
																/*E descending order */

/*J ワークバッファサイズ（セーブデータスロット検索向け） */
/*E work buffer size (for SaveDataSlotSearch) */
#define SCE_APPUTIL_WORKBUF_SEARCH_SLOT_DEFAULT_ELEMENT_SIZE			(16)	/*J SceAppUtilSaveDataSlot のサイズ */
																				/*E size of 'SceAppUtilSaveDataSlot' */
#define SCE_APPUTIL_WORKBUF_SEARCH_SLOT_BY_SIZE_KIB_ELEMENT_SIZE		(20)	/*J SceAppUtilSaveDataSlot + SceUInt32 のサイズ */
																				/*E size of 'SceAppUtilSaveData' + 'SceUInt32' */
#define SCE_APPUTIL_WORKBUF_SEARCH_SLOT_BY_MODIFIEDTIME_ELEMENT_SIZE	(32)	/*J SceAppUtilSaveDataSlot + SceDateTime のサイズ */
																				/*E size of 'SceAppUtilSaveData' + 'SceDateTime' */

/*J セーブデータデータパスサイズ */
/*E max size of savedata data path */
#define SCE_APPUTIL_SAVEDATA_DATA_PATH_MAXSIZE					(200)			/*J セーブデータデータパス最大サイズ */
																				/*E savedata data path max size(bytes) */
/*J セーブデータデータ保存モード */
/*E constant value for savedata data save mode */
#define SCE_APPUTIL_SAVEDATA_DATA_SAVE_MODE_FILE				(0)				/*J ファイル操作 */
																				/*E File operation */
#define SCE_APPUTIL_SAVEDATA_DATA_SAVE_MODE_FILE_TRUNCATE		(1)				/*J ファイル操作（オフセット + バッファサイズでファイルを切り詰める） */
																				/*E File operation (truncate at sum of offset and buffer size) */
#define SCE_APPUTIL_SAVEDATA_DATA_SAVE_MODE_DIRECTORY			(2)				/*J ディレクトリ操作 */
																				/*E Directory operation */
/*J セーブデータデータ削除モード */
/*E constant value for savedata data remove mode */
#define SCE_APPUTIL_SAVEDATA_DATA_REMOVE_MODE_DEFAULT			(0)				/*J デフォルト動作 */
																				/*E default */
#define SCE_APPUTIL_SAVEDATA_DATA_REMOVE_MODE_KEEP_SLOT			(1)				/*J スロットは削除せずにファイル／ディレクトリのみを削除する */
																				/*E remove file/directory with keeping slot alive */
/*J セーブデータデータ指定最大数 */
/*E max num of savedata data */
#define SCE_APPUTIL_SAVEDATA_DATA_MAXNUM						(5)				/*J セーブデータデータ指定最大数 */

/*J セーブデータ保存関数で1度に書き込み可能なサイズの上限値(単体/合計) */
/*E max writable size of sceAppUtilSaveDataDataSave() at once (single/total) */
#define SCE_APPUTIL_SAVEDATA_DATA_SAVE_MAXSIZE					(1*1024*1024)	/*J セーブデータ保存関数で1度に書き込み可能なサイズの上限値(単体/合計) */
																				/*E max writable size of sceAppUtilSaveDataDataSave() at once (single/total) */

/*J 追加コンテンツディレクトリ名サイズ */
/*E additional contents directory name length */
#define SCE_APPUTIL_NP_DRM_ADDCONT_ID_SIZE						(17)			/*J 追加コンテンツディレクトリ名のサイズ */
																				/*E additional contents directory name length */

/*J アプリケーションパラメータID */
/*E application parameter id */
#define SCE_APPUTIL_APPPARAM_ID_SKU_FLAG						(0)				/*J SKU フラグ */
																				/*E SKU flag */
/*J SKUフラグ用アプリケーションパラメータ値 */
/*E application parameter value for SCE_APPUTIL_APPPARAM_ID_SKU_FLAG */
#define SCE_APPUTIL_APPPARAM_SKU_FLAG_NONE						(0)				/*J OFF */
																				/*E off */
#define SCE_APPUTIL_APPPARAM_SKU_FLAG_TRIAL						(1)				/*J Trial */
																				/*E sku flag for trial version */
#define SCE_APPUTIL_APPPARAM_SKU_FLAG_FULL						(3)				/*J Full */
																				/*E sku flag for full version */

/*J セーフメモリー領域サイズ */
/*E safe memory buffer size */
#define SCE_APPUTIL_SAFEMEMORY_MEMORY_SIZE						(64*1024)		/*J セーフメモリー領域サイズ */
																				/*E safe memory size(bytes) */

/*J ストアブラウズタイプ */
/*E constant value for store browse type */
#define SCE_APPUTIL_STORE_BROWSE_TYPE_PRODUCT2					(3)				/*J プロダクトブラウズ */
																				/*E prodcut browse */
#define SCE_APPUTIL_STORE_BROWSE_TYPE_CATEGORY2					(4)				/*J カテゴリブラウズ */
																				/*E prodcut browse */
#define SCE_APPUTIL_STORE_BROWSE_TYPE_PRODUCT_CODE2				(5)				/*J プロダクトコード償還 */

#define SCE_APPUTIL_WEBBROWSER_LAUNCH_URL_MAXSIZE				(960)			/*J 起動URL最大長 */
																				/*E URL max length for launching web browser */

/*J ウェブブラウザーアプリケーション起動タイプ */
/*E web browse application type */
#define SCE_APPUTIL_WEBBROWSER_LAUNCH_APP_NORMAL				(0)				/*J 通常ウェブブラウザー */
																				/*E normal web browser */
#define SCE_APPUTIL_WEBBROWSER_LAUNCH_APP_MODAL					(1)				/*J モーダルウェブブラウザー */
																				/*E modal web browser */

/*J ウェブブラウザーアプリケーション起動コマンドタイプ */
/*E web browse exec command type */
#define SCE_APPUTIL_WEBBROWSER_LAUNCH_CMD_OPENURL				(0 << 2)		/*J ページオープン */
																				/*E open the page */
#define SCE_APPUTIL_WEBBROWSER_LAUNCH_CMD_SEARCH				(1 << 2)		/*J インターネット検索 */
																				/*E execute inernet serach */

/*J バックグラウンドダウンロードリストのステータスタイプ */
/*E type of status for BackGround DownLoad list */
#define SCE_APPUTIL_BGDL_STATUS_TYPE_ADDCONT					(0)				/*J 追加コンテンツタイプ */
																				/*E type of additional contents */
#define SCE_APPUTIL_BGDL_STATUS_TYPE_ADDCONT_AND_LICENSE		(1)				/*J 追加コンテンツと製品版権利 */
																				/*E type of additional contents, and product license  */

/*J スクリーンショットトリガタイプ */
/*E type of screenshot trigger */
#define SCE_APPUTIL_SCREENSHOT_TRIGGER_TYPE_USER				(0)				/*J ユーザー操作によるトリガ */
																				/*E trigger type of user operation */
#define SCE_APPUTIL_SCREENSHOT_TRIGGER_TYPE_IN_GAME				(1)				/*J ゲームによるトリガ */
																				/*E trigger type of in game */

/*J スクリーンショットコンテンツパスサイズ */
/*E max size of screenshot content path */
#define SCE_APPUTIL_SCREENSHOT_CONTENT_PATH_MAXSIZE				(1024)			/*J スクリーンショットコンテンツパス最大サイズ */

/*
 * Data Types
 */

/*J 起動属性型 */
/*E type of boot attribute */
typedef SceUInt32 SceAppUtilBootAttribute;

/*J イベント通知タイプ型 */
/*E type of event type */
typedef SceUInt32 SceAppUtilAppEventType;

/*J セーブデータスロットID型 */
/*E type of savedata slot id */
typedef SceUInt32 SceAppUtilSaveDataSlotId;

/*J セーブデータスロットステータス型 */
/*E type of savedata slot status */
typedef SceUInt32 SceAppUtilSaveDataSlotStatus;

/*J セーブデータデータ保存モード型 */
/*E type of savedata data save mode */
typedef SceUInt32 SceAppUtilSaveDataDataSaveMode;

/*J セーブデータデータ削除モード型 */
/*E type of savedata data remove mode */
typedef SceUInt32 SceAppUtilSaveDataDataRemoveMode;

/*J セーブデータスロット検索対象型 */
/*E type od savedata slot search type */
typedef SceUInt32 SceAppUtilSaveDataSlotSearchType;

/*J セーブデータスロット検索ソートキー型 */
/*E type of savedata slot sort key */
typedef SceUInt32 SceAppUtilSaveDataSlotSortKey;

/*J セーブデータスロット検索ソート順型 */
/*E type of savedata slot sort type */
typedef SceUInt32 SceAppUtilSaveDataSlotSortType;


/*J アプリケーションパラメータID型 */
/*E type of application parameter id */
typedef SceUInt32 SceAppUtilAppParamId;

/*J バックグラウンドダウンロードリストステータスタイプ型 */
/*E type of BackGround DownLoad list status */
typedef SceUInt32 SceAppUtilBgdlStatusType;

/*J スクリーンショットトリガタイプ型 */
/*E type of screenshot triger type */
typedef SceUInt32 SceAppUtilScreenShotTriggerType;
/*
 * Structures
 */

/*J ライブラリ初期化設定用構造体 */
/*E library initialize parameter structure */
typedef struct SceAppUtilInitParam {

	SceSize		workBufSize;					/*J ワークメモリ用バッファサイズ */
												/*E work memory buffer size */
	SceChar8	reserved[60];					/*J 予約領域 */
												/*E reserved range */
} SceAppUtilInitParam;

/*J 作業用バッファ領域構造体 */
/*E structure for working buffer */
typedef struct SceAppUtilWorkBuffer {

	void *buf;									/*J バッファ先頭 */
												/*E top of buffer */
	SceUInt32 bufSize;							/*J バッファサイズ */
												/*E buffer size */
	SceChar8 reserved[32];						/*J 予約領域 */
												/*E reserved range */
} SceAppUtilWorkBuffer;

/*J 起動パラメータ取得用構造体 */
/*E boot parameter structure */
typedef struct SceAppUtilBootParam {

	SceAppUtilBootAttribute		attr;			/*J 起動属性 */
												/*E boot attribute */
	SceUInt32					appVersion;		/*J アプリケーションのバージョン */
												/*E application version */
	SceChar8					reserved[32];	/*J 予約領域 */
												/*E reserved range */
} SceAppUtilBootParam;


/*J イベントパラメータ取得用構造体 */
/*E event parameter structure */
typedef struct SceAppUtilAppEventParam {

	SceAppUtilAppEventType	type;											/*J イベント通知タイプ */
																			/*E event type */
	SceUChar8				data[ SCE_APPUTIL_APPEVENT_PARAM_MAXSIZE ];		/*J 取得したイベントパラメータ */
																			/*E event parameter */
} SceAppUtilAppEventParam;

/*J 招待メッセージ取得用構造体 */
/*E invitation message structure */
typedef struct SceAppUtilNpInviteMessageParam {

	SceNpCommunicationId	commId;											/*J コミュニケーションID */
																			/*E communication id */
	SceUChar8				uid[ SCE_NP_MESSAGE_MAX_MESSAGE_ID_SIZE+1 ];	/*J メッセージID (NUL終端文字列, US-ASCII) */
																			/*E message id (NULL terminate, US-ASCII) */
} SceAppUtilNpInviteMessageParam;

/*J ゲームデータ添付メッセージ取得用構造体 */
/*E game data attachment message structure */
typedef struct SceAppUtilNpAppDataMessageParam {

	SceNpCommunicationId	commId;											/*J コミュニケーションID */
																			/*E communication id */
	SceUChar8				uid[ SCE_NP_MESSAGE_MAX_MESSAGE_ID_SIZE+1 ];	/*J メッセージID (NUL終端文字列, US-ASCII) */
																			/*E message id (NULL terminate, US-ASCII) */
} SceAppUtilNpAppDataMessageParam;

/*J LiveArea(TM) からの起動パラメータ取得用構造体 */
/*E Parameter for boot-up from LiveArea(TM) structure */
typedef struct SceAppUtilLiveAreaParam {
	SceUChar8				param[SCE_APPUTIL_LIVEAREA_PARAM_MAX_SIZE];		/*J イベントパラメータ(NUL終端文字列, US-ASCII) */
																			/*E event parameter(NULL terminate, US-ASCII) */
	SceChar8				reserved[32];									/*J 予約領域 */
																			/*E reserved range */
} SceAppUtilLiveAreaParam;

/*J スクリーンショットノーティフィケーション構造体 */
/*E structure for ScreenShot notification */
typedef struct SceAppUtilScreenShotNotification {
	SceAppUtilScreenShotTriggerType		triggerType;												/*J トリガータイプ */
																									/*E trigger type */
	SceUChar8							contentPath[SCE_APPUTIL_SCREENSHOT_CONTENT_PATH_MAXSIZE];	/*J スクリーンショットファイルのパス */
																									/*E path of screenshot file */
	SceChar8							reserved[32];												/*J 予約領域*/
																									/*E reserved area */
} SceAppUtilScreenShotNotification;

/*J Activityからの起動パラメータ取得用構造体 */
/*E Parameter for boot-up from Activity structure */
typedef struct SceAppUtilNpActivityParam {
	SceChar8				param[SCE_APPUTIL_NP_ACTIVITY_PARAM_MAXSIZE];		/*J イベントパラメータ(NUL終端文字列, US-ASCII) */
																			/*E event parameter(NULL terminate, US-ASCII) */
	SceChar8				reserved[32];									/*J 予約領域 */
																			/*E reserved range */
} SceAppUtilNpActivityParam;

/*J Teleportからの起動パラメータ取得用構造体 */
/*E Parameter for boot-up from Teleport structure */
typedef struct SceAppUtilTeleportParam {
	SceChar8				param[SCE_APPUTIL_TELEPORT_PARAM_MAXSIZE];		/*J イベントパラメータ(NUL終端文字列, US-ASCII) */
																			/*E event parameter(NULL terminate, US-ASCII) */
	SceChar8				reserved[32];									/*J 予約領域 */
																			/*E reserved range */
} SceAppUtilTeleportParam;


/*J マウントポイント構造体 */
/*E mount point structure */
typedef struct SceAppUtilMountPoint {

	SceChar8	data[ SCE_APPUTIL_MOUNTPOINT_DATA_MAXSIZE ];				/*J マウントポイント名 */
																			/*E mount point */
} SceAppUtilMountPoint;

/*J タイトルID構造体 */
/*E title id structure */
typedef struct SceAppUtilTitleId {

	SceChar8 data[ SCE_APPUTIL_TITLE_ID_DATA_SIZE ];			/*J タイトルID */
																/*E title id */
	SceChar8 padding[6];										/*J パディング領域 */
																/*E padding */
} SceAppUtilTitleId;

/*J パスコード構造体 */
/*E passcode structure */
typedef struct SceAppUtilPassCode {

	SceUChar8	data[ SCE_APPUTIL_PASSCODE_DATA_SIZE ];			/*J パスコード */
																/*E passcode */
} SceAppUtilPassCode;


/*J セーブデータスロットパラメータ構造体 */
/*E savedata slot parameter structure */
typedef struct SceAppUtilSaveDataSlotParam {

	SceAppUtilSaveDataSlotStatus	status;															/*J ステータス */
																									/*E status */
	SceChar8						title[ SCE_APPUTIL_SAVEDATA_SLOT_TITLE_MAXSIZE ];				/*J タイトル名 (NUL終端, UTF-8) */
																									/*E title name (NULL termination, UTF-8) */
	SceChar8						subTitle[ SCE_APPUTIL_SAVEDATA_SLOT_SUBTITLE_MAXSIZE ];			/*J サブタイトル名 (NUL終端, UTF-8) */
																									/*E subtitle name (NULL termination, UTF-8) */
	SceChar8						detail[ SCE_APPUTIL_SAVEDATA_SLOT_DETAIL_MAXSIZE ];				/*J 詳細情報 (NUL終端, UTF-8) */
																									/*E detail info (NULL termination, UTF-8) */
	SceChar8						iconPath[ SCE_APPUTIL_SAVEDATA_SLOT_ICON_PATH_MAXSIZE ];		/*J サムネイルアイコンパス (NUL終端) */
																									/*E thumbnail icon path (NULL termination) */
	SceInt32						userParam;														/*J ユーザパラメータ */
																									/*E user parameter */
	SceUInt32						sizeKiB;														/*J データサイズ(KiB) */
																									/*E data size (KiB) */
	SceDateTime						modifiedTime;													/*J 最終更新日時 */
																									/*E last modified time */
	SceChar8						reserved[48];													/*J 予約領域 */
																									/*E reserved range */
} SceAppUtilSaveDataSlotParam;

/*J 空きスロットパラメータ指定構造体 (セーブデータダイアログ用) */
/*E structure specifying empty slot parameter (for savedata dialog) */
typedef struct SceAppUtilSaveDataSlotEmptyParam {

	SceChar8	*title;							/*J タイトル文字列 */
												/*E title string */
	SceChar8	*iconPath;						/*J アイコンファイルパス */
												/*E path to icon file */
	void		*iconBuf;						/*J アイコン画像バッファ */
												/*E buffer of icon image */
	SceSize		iconBufSize;					/*J アイコン画像バッファサイズ */
												/*E buffer size of icon image */
	SceChar8	reserved[32];					/*J 予約領域 */
												/*E reserved range */
} SceAppUtilSaveDataSlotEmptyParam;

/*J セーブデータスロット構造体 (セーブデータダイアログ用) */
/*E savedata slot structure (for savedata dialog) */
typedef struct SceAppUtilSaveDataSlot {

	SceAppUtilSaveDataSlotId id;						/*J スロットID */
														/*E slot id */
	SceAppUtilSaveDataSlotStatus status;				/*J スロットステータス */
														/*E slot status */
	SceInt32 userParam;									/*J ユーザパラメータ */
														/*E parameter for free usage */
	SceAppUtilSaveDataSlotEmptyParam *emptyParam;		/*J 空スロットパラメータ指定 */
														/*E settings for empty slot */
} SceAppUtilSaveDataSlot;

/*J セーブデータスロット検索条件構造体（セーブデータダイアログ用） */
/*E structure specifying finding savedata slot (for savedata dialog) */
typedef struct SceAppUtilSaveDataSlotSearchCond {

	SceAppUtilSaveDataSlotSearchType	type;			/*J 検索対象 */
														/*E search target */
	SceAppUtilSaveDataSlotId			from;			/*J 検索開始スロットID */
														/*E slot id for search starting */
	SceUInt32							range;			/*J 検索範囲 */
														/*E search range */
	SceAppUtilSaveDataSlotSortKey		key;			/*J ソートキー */
														/*E sort key */
	SceAppUtilSaveDataSlotSortType		order;			/*J ソート順 */
														/*E sort type */
	SceChar8							reserved[32];	/*J 予約領域 */
														/*E resered range */
} SceAppUtilSaveDataSlotSearchCond;

/*J セーブデータスロット検索結果構造体（セーブデータダイアログ用） */
/*E structure for result of searching savedata slot (for savedatadialog) */
typedef struct SceAppUtilSlotSearchResult {

	SceUInt32 hitNum;									/*J 検索結果件数 */
														/*E number of result for searching savedata slot */
	SceAppUtilSaveDataSlot *slotList;					/*J セーブデータスロット構造体（セーブデータ用） */
														/*E structure for savedata slot (for savedata dialog) */
	SceChar8 reserved[32];								/*J 予約領域 */
														/*E reserved range */
} SceAppUtilSlotSearchResult;

/*J セーブデータ保存データ指定用構造体 */
/*E savedata data save structure */
typedef struct SceAppUtilSaveDataDataSaveItem {

	const SceChar8 *dataPath;						/*J データ(ファイル/ディレクトリ)パス */
													/*E path to savedata data */
	const void *buf;								/*J セーブデータバッファ */
													/*E buffer of savedata file */
	SceSize bufSize;								/*J セーブデータバッファサイズ */
													/*E buffer size of savedata file */
	SceChar8 padding[4];							/*J パディング */
													/*E padding */
	SceOff offset;									/*J セーブデータ書込み先のオフセット */
													/*E offset of savedata file */
	SceAppUtilSaveDataDataSaveMode mode;			/*J セーブデータデータ保存モード */
													/*E savedata data save mode */
	SceChar8 reserved[36];							/*J 予約領域 */
													/*E reserved range */
} SceAppUtilSaveDataDataSaveItem;

/*J セーブデータ削除データ指定用構造体 */
/*E savedata data remove structure */
typedef struct SceAppUtilSaveDataDataRemoveItem {

	const SceChar8 *dataPath;						/*J データ(ファイル/ディレクトリ)パス */
													/*E path to savedata data */
	SceAppUtilSaveDataDataRemoveMode mode;			/*J セーブデータデータ削除モード */
													/*E savedata data remove mode */
	SceChar8 reserved[36];							/*J 予約領域 */
													/*E reserved range */
} SceAppUtilSaveDataDataRemoveItem;

/*J セーブデータデータスロット構造体 */
/*E savedata data slot structure */
typedef struct SceAppUtilSaveDataDataSlot {

	SceAppUtilSaveDataSlotId id;					/*J スロットID */
													/*E slot id */
	SceAppUtilSaveDataSlotParam *slotParam;			/*J セーブデータスロットパラメータ構造体 */
													/*E savedata slot parameter structure */
	SceChar8 reserved[32];							/*J 予約領域 */
													/*E reserved range */
} SceAppUtilSaveDataDataSlot;


/*J 追加コンテンツデータ構造体 */
/*E additional contents data structure */
typedef struct SceAppUtilDrmAddcontId {

	SceChar8 data[ SCE_APPUTIL_NP_DRM_ADDCONT_ID_SIZE ];		/*J 追加コンテンツディレクトリ名 */
																/*E additional contents directory name */
	SceChar8 padding[3];										/*J パディング領域 */
																/*E padding */
} SceAppUtilDrmAddcontId;


/*J ストアブラウザ起動パラメータ */
/*E store browser launch parameter */
typedef struct SceAppUtilStoreBrowseParam {

	SceUInt32 type;									/*J ストアブラウズタイプ */
													/*E store browse type */
	const SceChar8 *id;								/*J ターゲットID */
													/*E target id */
} SceAppUtilStoreBrowseParam;


/*J ウェブブラウザーアプリケーション起動パラメータ */
/*E web browser application launch parameter */
typedef struct SceAppUtilWebBrowserParam {

	const SceChar8*		wbstr;						/*J launchModeで指定されるコマンドに渡される文字列 */
													/*E string which is passed to the command specified by launchMode */
	SceUInt32			wbstrLength;				/*J wbstr の長さ(バイト) */
													/*E the length of wbstr (byte) */
	SceUInt32			launchMode;					/*J ウェブブラウザーアプリケーション起動時の動作モード */
													/*E the running mode at launch of web browser application */
	SceUInt32			reserved0;					/*J 予約領域 */
													/*E reserved area */
} SceAppUtilWebBrowserParam;


/*J ウェブブラウザアプリケーションクッキー初期化パラメータ */
/*E web browser application init cookie parameter */
typedef struct SceAppUtilWebBrowserResetCookieParam {
	SceChar8			reserved[32];				/*J 予約領域 */
													/*E reserved area */
} SceAppUtilWebBrowserResetCookieParam;


/*J ウェブブラウザアプリケーションクッキー追加パラメータ */
/*E web browser application add cookie parameter */
typedef struct SceAppUtilWebBrowserAddCookieParam {

	const SceChar8*		wbstr;						/*J cookie の送信元URL文字列 */
													/*E string which is source URL of cookie */
	const SceChar8*		wbstrName;					/*J NAME文字列 */
													/*E string which is NAME value of cookie */
	const SceChar8*		wbstrValue;					/*J VALUE文字列 */
													/*E string which is VALUE value of cookie */
	const SceChar8*		wbstrExpires;				/*J Cookie有効期限文字列 */
													/*E string which is Expires value of cookie */
	const SceChar8*		wbstrPath;					/*J path文字列 */
													/*E string which is Path value of cookie */
	const SceChar8*		wbstrDomain;				/*J Cookie Domain文字列 */
													/*E string which is Domain value of cookie */
	SceBool				isSecure;					/*J secure 指定 */
													/*E flag which appends Secure value of cookie */
	SceChar8			reserved[32];				/*J 予約領域 */
} SceAppUtilWebBrowserAddCookieParam;


/*J バックグラウンドダウンロードリストステータス構造体 */
/*E structure for BackGround DownLoad list status */
typedef struct SceAppUtilBgdlStatus {

	SceAppUtilBgdlStatusType	type;					/*J ステータスタイプ */
														/*E status Type */
	SceUInt32					addcontNumReady;		/*J ダウンロードが完了した追加コンテンツの数 */
														/*E number of additional contents completely downloaded */
	SceUInt32					addcontNumNotReady;		/*J ダウンロードが完了していない追加コンテンツの数 */
														/*E number of additional contents not downloaded yet */
	SceUInt32					licenseReady;			/*J 製品版へのアップグレード権利のダウンロード状態(0:未完了, 1:完了) */
														/*E download state of upgrade license to Full version(0:not completed,1:completed) */
	SceChar8					reserved[28];			/*J 予約領域*/
														/*E reserved area */
} SceAppUtilBgdlStatus;

/*J Session/Invitation取得用構造体 */
/*E session/invitation structure */
typedef struct SceAppUtilSessionInvitationParam {
	SceNpSessionId			sessionId;										/*J セッションID (NUL終端文字列, US-ASCII) */
																			/*E session id (NULL terminate, US-ASCII) */
	SceNpInvitationId		invitationId;									/*J 招待ID (NUL終端文字列, US-ASCII) */
																			/*E invitation id (NULL terminate, US-ASCII) */
} SceAppUtilSessionInvitationParam;

/*J Game Custom Data取得用構造体 */
/*E game custom data structure */
typedef struct SceAppUtilGameCustomDataParam {
	SceNpGameCustomDataId	gameCustomDataId;								/*J ゲームカスタムデータID (NUL終端文字列, US-ASCII) */
																			/*E game custom data id (NULL terminate, US-ASCII) */
} SceAppUtilGameCustomDataParam;

/*
 * Functions
 */

/*J ライブラリの初期化処理を行う */
/*E initialize apputil library */
SceInt32 sceAppUtilInit(

		const SceAppUtilInitParam	*initParam,				/*J 初期化パラメータ設定用構造体 */
															/*E initialize parameter structure */
		SceAppUtilBootParam			*bootParam				/*J 起動パラメータ格納用構造体 */
															/*E boot parameter structure */
);

/*J ライブラリの終了処理を行う */
/*E shutdown apputil library */
SceInt32 sceAppUtilShutdown( void );


/*J アプリケーションイベントを受信する */
/*E receive application event */
SceInt32 sceAppUtilReceiveAppEvent(

		SceAppUtilAppEventParam	*eventParam						/*J イベントパラメータ */
																/*E event parameter */
);

/*J 招待メッセージイベントパラメータを解釈する */
/*E parse event parameter for invitation message structure */
SceInt32 sceAppUtilAppEventParseNpInviteMessage(

		const SceAppUtilAppEventParam		*eventParam,		/*J イベントパラメータ */
																/*E event parameter */
		SceAppUtilNpInviteMessageParam		*param				/*J 招待メッセージ取得用構造体 */
																/*E invitation message structure */
);

/*J ゲームデータ添付メッセージイベントパラメータを解釈する */
/*E parse event parameter for game data attachment message structure */
SceInt32 sceAppUtilAppEventParseNpAppDataMessage(

		const SceAppUtilAppEventParam		*eventParam,		/*J イベントパラメータ */
																/*E event parameter */
		SceAppUtilNpAppDataMessageParam		*param				/*J ゲームデータ添付メッセージ取得用構造体 */
																/*E game data attachment message structure */
);

/*J LiveArea(TM) からのアプリケーションイベントパラメータを解釈する */
/*E parse event parameter for application event from LiveArea(TM) */
SceInt32 sceAppUtilAppEventParseLiveArea(
		const SceAppUtilAppEventParam			*eventParam,	/*J イベントパラメータ */
																/*E event parameter */
		SceAppUtilLiveAreaParam					*param			/*J LiveArea(TM) からのアプリケーションイベントパラメータ取得用構造体 */
																/*E parameter for application event from LiveArea(TM) */
);

/*J スクリーンショットノーティフィケーションイベントパラメータを解釈する */
/*E parse event parameter for screenshot notification */
SceInt32 sceAppUtilAppEventParseScreenShotNotification(
		const SceAppUtilAppEventParam			*eventParam,	/*J イベントパラメータ */
																/*E event parameter */
		SceAppUtilScreenShotNotification		*param			/*J スクリーンショットノーティフィケーション取得用構造体 */
																/*E parameter for ScreenShot notification */
);

/*J Activityからのアプリケーションイベントパラメータを解釈する */
/*E parse event parameter for application event from Activity */
SceInt32 sceAppUtilAppEventParseNpActivity(
		const SceAppUtilAppEventParam			*eventParam,	/*J イベントパラメータ */
																/*E event parameter */
		SceAppUtilNpActivityParam				*param			/*J Activity からのアプリケーションイベントパラメータ取得用構造体 */
																/*E parameter for application event from Activity */
);

/*J Teleport起動のアプリケーションイベントパラメータを解釈する */
/*E parse event parameter for Teleport launch. */
SceInt32 sceAppUtilAppEventParseTeleport(
		const SceAppUtilAppEventParam			*eventParam,	/*J イベントパラメータ */
																/*E event parameter */
		SceAppUtilTeleportParam				*param				/*J Teleport 起動のアプリケーションイベントパラメータ取得用構造体 */
																/*E parameter for Teleport launch*/
);


/*J セーブデータディレクトリを savedata1: としてマウントする */
/*E mount savedata directory as savedata1: */
SceInt32 sceAppUtilSaveDataMount(
		const SceAppUtilTitleId *titleId,		/*J セーブデータの品番 */
												/*E title id of savedata */
		const SceAppUtilPassCode *passCode		/*J セーブデータを作成したアプリケーションに設定したパスコード */
												/*E passcode set to application makes savedata */
);

/*J セーブデータディレクトリをアンマウントする */
/*E unmount savedata directory */
SceInt32 sceAppUtilSaveDataUmount();

/*J セーブデータスロットを作成する */
/*E create savedata slot */
SceInt32 sceAppUtilSaveDataSlotCreate(

		SceAppUtilSaveDataSlotId			slotId,			/*J セーブデータスロットID */
															/*E savedata slot id */
		const SceAppUtilSaveDataSlotParam	*param,			/*J セーブデータスロットパラメータ構造体 */
															/*E savedata slot parameter structure */
		const SceAppUtilMountPoint			*mountPoint		/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J セーブデータスロットを削除する */
/*E delete savedata slot */
SceInt32 sceAppUtilSaveDataSlotDelete(

		SceAppUtilSaveDataSlotId			slotId,			/*J セーブデータスロットID */
															/*E savedata slot id */
		const SceAppUtilMountPoint			*mountPoint		/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J セーブデータスロットを検索する */
/*E search savedata slot  */
SceInt32 sceAppUtilSaveDataSlotSearch(

		SceAppUtilWorkBuffer *workBuf,						/*J 作業用バッファ領域構造体 */
															/*E structrure for working buffer */
		const SceAppUtilSaveDataSlotSearchCond *cond,		/*J セーブデータスロット検索条件構造体 */
															/*E structure for savedata slot searching condition */
		SceAppUtilSlotSearchResult *result,					/*J セーブデータスロット検索結果構造体 */
															/*E structure for savedata slot searching result */
		const SceAppUtilMountPoint *mountPoint				/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J セーブデータスロットのパラメータを設定する */
/*E set savedata slot parameter */
SceInt32 sceAppUtilSaveDataSlotSetParam(

		SceAppUtilSaveDataSlotId			slotId,			/*J セーブデータスロットID */
															/*E savedata slot id */
		const SceAppUtilSaveDataSlotParam	*param,			/*J セーブデータスロットパラメータ構造体 */
															/*E savedata slot parameter structure */
		const SceAppUtilMountPoint			*mountPoint		/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J セーブデータスロットのパラメータを取得する */
/*E get savedata slot parameter */
SceInt32 sceAppUtilSaveDataSlotGetParam(

		SceAppUtilSaveDataSlotId			slotId,			/*J セーブデータスロットID */
															/*E savedata slot id */
		SceAppUtilSaveDataSlotParam			*param,			/*J セーブデータスロットパラメータ構造体 */
															/*E savedata slot parameter structure */
		const SceAppUtilMountPoint			*mountPoint		/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J セーブデータを保存する */
/*E write savedata files / directories */
SceInt32 sceAppUtilSaveDataDataSave(

	const SceAppUtilSaveDataDataSlot		*slot,			/*J セーブデータデータスロット構造体 */
															/*E savedata data slot structure */
	const SceAppUtilSaveDataDataSaveItem	*data,			/*J 保存対象のセーブデータデータ保存構造体 */
															/*E savedata data save structure */
	SceUInt32								dataNum,		/*J 保存対象のセーブデータデータの数 */
															/*E num of savedata data list */
	const SceAppUtilMountPoint				*mountPoint,	/*J マウントポイント構造体 */
															/*E mount point structure */
	SceSize									*requiredSizeKiB/*J セーブデータを保存するのに必要なサイズ(KiB) (SCE_APPUTIL_ERROR_SAVEDATA_NO_SPACEエラー発生時) */
															/*E required size (KiB) (in case of SCE_APPUTIL_ERROR_SAVEDATA_NO_SPACE error occured) */
);

/*J セーブデータを削除する */
/*E remove savedata files / directories */
SceInt32 sceAppUtilSaveDataDataRemove(

	const SceAppUtilSaveDataDataSlot		*slot,			/*J セーブデータデータスロット構造体 */
															/*E savedata data slot structure */
	const SceAppUtilSaveDataDataRemoveItem	*data,			/*J 削除対象のセーブデータデータ構造体 */
															/*E savedata data remove structure */
	SceUInt32								dataNum,		/*J 削除対象のセーブデータの数 */
															/*E num of savedata data list */
	const SceAppUtilMountPoint				*mountPoint		/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J セーブデータの最大容量と現在使用量を取得する */
/*E get savedata max size and used size */
SceInt32 sceAppUtilSaveDataGetQuota(

	SceSize								*quotaSizeKiB,		/*J 設定されているセーブデータ最大容量サイズ(KiB) */
															/*E savedata max size (KiB) */
	SceSize								*usedSizeKiB,		/*J 現在のセーブデータ使用量(KiB) */
															/*E savedata current used size (kilobyte) */
	const SceAppUtilMountPoint			*mountPoint			/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J 追加コンテンツのルートディレクトリを addcont1: としてマウントする */
/*E mount root directory of addcont as addcont1: */
SceInt32 sceAppUtilAddcontMount(

		const SceAppUtilTitleId *titleId,		/*J 追加コンテンツの品番 */
												/*E title id of addcont */
		const SceAppUtilPassCode *passCode		/*J 追加コンテンツに設定したパスコード */
												/*E passcode set to addcont */
);

SceInt32 sceAppUtilAddcontUmount();

/*J 追加コンテンツデータをオープンする */
/*E open additional contents */
SceInt32 sceAppUtilDrmOpen(

		const SceAppUtilDrmAddcontId		*dirName,		/*J 追加コンテンツディレクトリ名 */
															/*E additional contents directory name */
		const SceAppUtilMountPoint			*mountPoint		/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J 追加コンテンツデータをクローズする */
/*E close additional contents */
SceInt32 sceAppUtilDrmClose(

		const SceAppUtilDrmAddcontId		*dirName,		/*J 追加コンテンツディレクトリ名 */
															/*E additional contents directory name */
		const SceAppUtilMountPoint			*mountPoint		/*J マウントポイント構造体 */
															/*E mount point structure */
);

/*J フォトデータ用ドライブをマウントする */
/*E mount photo data drive */
SceInt32 sceAppUtilPhotoMount( void );

/*J フォトデータ用ドライブをアンマウントする */
/*E unmount photo data drive */
SceInt32 sceAppUtilPhotoUmount( void );


/*J ミュージックデータ用ドライブをマウントする */
/*E mount music data drive */
SceInt32 sceAppUtilMusicMount( void );

/*J ミュージックデータ用ドライブをアンマウントする */
/*E unmount music data drive */
SceInt32 sceAppUtilMusicUmount( void );

/*J システムパラメータ(整数値)を取得する */
/*E get system parameter for integer type */
SceInt32 sceAppUtilSystemParamGetInt(

		SceSystemParamId			paramId,				/*J システムパラメータID */
															/*E system parameter id */
		SceInt32					*value					/*J 取得した値 */
															/*E get value */
);

/*J システムパラメータ(文字列)を取得する */
/*E get system parameter for string type */
SceInt32 sceAppUtilSystemParamGetString(

		SceSystemParamId			paramId,				/*J システムパラメータID */
															/*E system parameter id */
		SceChar8					*buf,					/*J 結果取得用バッファ */
															/*E get value buffer */
		SceSize						bufSize					/*J 結果取得用バッファサイズ */
															/*E get value buffer size */
);


/*J アプリケーションパラメータ(整数値)を取得する */
/*E get application parameter for integer type */
SceInt32 sceAppUtilAppParamGetInt(

		SceAppUtilAppParamId		paramId,				/*J アプリケーションパラメータID */
															/*E application parameter id */
		SceInt32					*value					/*J 取得した値 */
															/*E get value */
);


/*J セーフメモリーにバッファ内容を保存する */
/*E save safe memory */
SceInt32 sceAppUtilSaveSafeMemory(

		const void		*buf,								/*J セーフメモリーに保存するデータのバッファ */
															/*E safe memory top address */
		SceSize			bufSize,							/*J セーフメモリーに保存するバッファのサイズ */
															/*E safe memory save buffer size */
		SceOff			offset								/*J セーフメモリー書き込み位置へのオフセット */
															/*E safe memory save offset */
);

/*J セーフメモリーに保存されている内容を読み込む */
/*E load safe memory */
SceInt32 sceAppUtilLoadSafeMemory(

		void			*buf,								/*J セーフメモリーから取得するデータ格納用バッファ */
															/*E safe memory top address */
		SceSize			bufSize,							/*J セーフメモリーから取得するデータ格納用バッファのサイズ */
															/*E safe memory load buffer size */
		SceOff			offset								/*J セーフメモリーの読み出し位置へのオフセット */
															/*E safe memory load offset */
);


/*J ストアブラウザアプリケーションを起動する */
/*E launch store browser application */
SceInt32 sceAppUtilStoreBrowse(

		SceAppUtilStoreBrowseParam	*param					/*J ストアブラウザ起動パラメータ */
															/*E store browser launch parameter */
);


/*J ウェブブラウザーアプリケーションを起動する */
/*E launch web browser application */
SceInt32 sceAppUtilLaunchWebBrowser(

		SceAppUtilWebBrowserParam	*param					/*J ウェブブラウザーアプリケーション起動パラメータ */
															/*E web browser application launch parameter */
);

/*J ウェブブラウザアプリケーションに入力するCookieデータを初期化をする */
/*E reset cookie data for adding web browser application */
SceInt32 sceAppUtilResetCookieWebBrowser(					/*J ウェブブラウザCookieデータリセットパラメータ */
		SceAppUtilWebBrowserResetCookieParam	*param		/*E web browser reset parameter for adding cookie */
);

/*J ウェブブラウザアプリケーションにクッキーを追加設定する */
/*E add cookie of web browser application */
SceInt32 sceAppUtilAddCookieWebBrowser(
		SceAppUtilWebBrowserAddCookieParam	*param			/*J ウェブブラウザクッキー追加パラメータ */
															/*E web browser add parameter of cookie */
);

/*J バックグラウンドダウンロードリストのステータス取得 */
/*E get BackGround DownLoad list status */
SceInt32 sceAppUtilBgdlGetStatus(

		SceAppUtilBgdlStatus *stat					/*J バックグラウンドダウンロードリストステータス構造体 */
													/*E structure of BackGround DownLoad list status */

);

/*J Session/Invitationイベントパラメータを解釈する */
/*E parse event parameter for session/invitation structure */
SceInt32 sceAppUtilAppEventParseSessionInvitation(

		const SceAppUtilAppEventParam		*eventParam,		/*J イベントパラメータ */
																/*E event parameter */
		SceAppUtilSessionInvitationParam	*param				/*J Session/Invitation取得用構造体 */
																/*E session/invitation structure */
);

/*J Game Custom Dataイベントパラメータを解釈する */
/*E parse event parameter for game custom data structure */
SceInt32 sceAppUtilAppEventParseGameCustomData(

		const SceAppUtilAppEventParam		*eventParam,		/*J イベントパラメータ */
																/*E event parameter */
		SceAppUtilGameCustomDataParam		*param				/*J Game Custom Data取得用構造体 */
																/*E game custom data structure */
);

/*
 * Obsolete
 */

/*J 互換のため残していますが、使用しないでください */
/*E Do not use following macros. These are kept for compatibility */
#define SCE_APPUTIL_STORE_BROWSE_TYPE_PRODUCT					(0)				/*J プロダクトブラウズ(SDK1.50互換) */
																				/*E prodcut browse(SDK1.50 compatible) */
#define SCE_APPUTIL_STORE_BROWSE_TYPE_CATEGORY					(1)				/*J カテゴリブラウズ(SDK1.50互換) */
																				/*E prodcut browse(SDK1.50 compatible) */
#define SCE_APPUTIL_STORE_BROWSE_TYPE_PRODUCT_CODE				(2)				/*J プロダクトコード償還(SDK1.50互換) */
																				/*E prodcut code redemption(SDK1.50 compatible) */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif	/* _DOLCESDK_PSP2_APPUTIL_H_ */
