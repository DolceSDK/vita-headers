#ifndef _DOLCESDK_PSP2_MESSAGE_DIALOG_H_
#define _DOLCESDK_PSP2_MESSAGE_DIALOG_H_

#include <psp2/kernel/clib.h>
#include <psp2/common_dialog/common_api.h>
#include <psp2/sdk_version.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*J エラーコード ------------------------------------------------------------------------- */
/*E Error code --------------------------------------------------------------------------- */

/*J パラメータが不正 */
/*E parameter is illegal */
#define SCE_MSG_DIALOG_ERROR_PARAM			-2146432511	/*0x80100a01 */

/*J 必要なモジュールがロードされていない */
/*E required module is not loaded */
#define SCE_MSG_DIALOG_ERROR_MODULE			-2146432510	/* 0x80100a02 */

/*J 定数 --------------------------------------------------------------------------------- */
/*E Constants ---------------------------------------------------------------------------- */

/*J ユーザ指定メッセージ文字列最大サイズ（NUL終端含む） */
/*E Maximum size for user message strings (include NUL terminator) */
#define SCE_MSG_DIALOG_USER_MSG_SIZE				(512)

/*J メッセージダイアログ呼び出しモード */
/*E Mode for calling MsgDialog functions */
typedef SceInt32 SceMsgDialogMode;
#define SCE_MSG_DIALOG_MODE_INVALID					(0)
#define SCE_MSG_DIALOG_MODE_USER_MSG				(1)
#define SCE_MSG_DIALOG_MODE_SYSTEM_MSG				(2)
#define SCE_MSG_DIALOG_MODE_ERROR_CODE				(3)
#define SCE_MSG_DIALOG_MODE_PROGRESS_BAR			(4)

/*J システム定型文タイプ */
/*E Types of system prepared message */
typedef SceInt32 SceMsgDialogSystemMessageType;
#define SCE_MSG_DIALOG_SYSMSG_TYPE_INVALID							(0)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT								(1)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_NOSPACE							(2)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_MAGNETIC_CALIBRATION				(3)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT_SMALL						(5)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_WAIT_CANCEL						(6)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_NOSPACE_CONTINUABLE				(9)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_LOCATION_DATA_OBTAINING			(10)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_LOCATION_DATA_FAILURE			(11)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_LOCATION_DATA_FAILURE_RETRY		(12)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_PATCH_FOUND						(13)

/*J TRC向け定型文 */
/*E System messages for TRC */
#define SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_MIC_DISABLED					(100)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_WIFI_REQUIRED_OPERATION		(101)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_WIFI_REQUIRED_APPLICATION	(102)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_EMPTY_STORE					(103)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_PSN_AGE_RESTRICTION			(104)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_PSN_CHAT_RESTRICTION			(105)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_TRC_MIC_DISABLED_CONTINUABLE		(106)

/*J ダイアログのボタンセット */
/*E Types of button on dialog */
typedef SceInt32 SceMsgDialogButtonType;
#define SCE_MSG_DIALOG_BUTTON_TYPE_OK				(0)
#define SCE_MSG_DIALOG_BUTTON_TYPE_YESNO			(1)
#define SCE_MSG_DIALOG_BUTTON_TYPE_NONE				(2)
#define SCE_MSG_DIALOG_BUTTON_TYPE_OK_CANCEL		(3)
#define SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL			(4)
#define SCE_MSG_DIALOG_BUTTON_TYPE_3BUTTONS			(5)

/*J ボタンID */
/*E Ids of button */
typedef SceInt32 SceMsgDialogButtonId;
#define SCE_MSG_DIALOG_BUTTON_ID_INVALID			(0)
#define SCE_MSG_DIALOG_BUTTON_ID_OK					(1)
#define SCE_MSG_DIALOG_BUTTON_ID_YES				(1)
#define SCE_MSG_DIALOG_BUTTON_ID_NO					(2)
#define SCE_MSG_DIALOG_BUTTON_ID_RETRY				(3)
#define SCE_MSG_DIALOG_BUTTON_ID_BUTTON1			(1)
#define SCE_MSG_DIALOG_BUTTON_ID_BUTTON2			(2)
#define SCE_MSG_DIALOG_BUTTON_ID_BUTTON3			(3)

/*J プログレスバータイプ */
/*E Types of progress bar */
typedef SceInt32 SceMsgDialogProgressBarType;
#define SCE_MSG_DIALOG_PROGRESSBAR_TYPE_PERCENTAGE	(0)

/*J プログレスバーターゲット */
/*E Target of progress bar */
typedef SceInt32 SceMsgDialogProgressBarTarget;
#define SCE_MSG_DIALOG_PROGRESSBAR_TARGET_BAR_DEFAULT	(0)

/*J ダイアログ動作環境設定フラグ */
/*E Flags for setting dialog environment */
typedef SceUInt32 SceMsgDialogEnvFlag;
#define SCE_MSG_DIALOG_ENV_FLAG_DEFAULT				(0)

/*J フォントサイズ */
/*E Font size */
typedef SceInt32 SceMsgDialogFontSize;
#define SCE_MSG_DIALOG_FONT_SIZE_DEFAULT			(0)
#define SCE_MSG_DIALOG_FONT_SIZE_SMALL				(1)

/*J ボタン文言文字列最大サイズ（NULL終端含む） */
/*E Maximum size for button strings (include NULL terminator) */
#define SCE_MSG_DIALOG_BUTTON_MSG_SIZE				(64)

/*J 構造体 -------------------------------------------------------------------------------- */
/*E Structures ---------------------------------------------------------------------------- */

/*J ユーザ指定文字列ボタン設定用構造体 */
/*E Structure for setting user message buttons */
typedef struct SceMsgDialogButtonsParam {
	const SceChar8 *msg1;				/*J ボタン1向け文字列 */
										/*E message for button 1 */
	SceMsgDialogFontSize fontSize1;		/*J ボタン1文言フォントサイズ */
										/*E font size for button 1 */
	const SceChar8 *msg2;				/*J ボタン2向け文字列 */
										/*E message for button 2 */
	SceMsgDialogFontSize fontSize2;		/*J ボタン2文言フォントサイズ */
										/*E font size for button 2 */
	const SceChar8 *msg3;				/*J ボタン3向け文字列 */
										/*E message for button 3 */
	SceMsgDialogFontSize fontSize3;		/*J ボタン3文言フォントサイズ */
										/*E font size for button 3 */
	SceChar8 reserved[32];				/*J 予約領域 （ゼロで埋めること） */
										/*E Reserved range (must be filled by zero) */
} SceMsgDialogButtonsParam;

/*J ユーザ指定メッセージダイアログ設定用構造体 */
/*E Structure for setting user message dialog */
typedef struct SceMsgDialogUserMessageParam {
	SceMsgDialogButtonType buttonType;				/*J ボタンタイプ */
													/*E Type of button set */
	const SceChar8 *msg;							/*J 画面表示文字列 */
													/*E Displayed message */
	SceMsgDialogButtonsParam *buttonParam;			/*J ボタンパラメータ */
													/*E Parameter of each button */
	SceChar8 reserved[28];							/*J 予約領域 （ゼロで埋めること） */
													/*E Reserved range (must be filled by zero) */
} SceMsgDialogUserMessageParam;

/*J システム定型文ダイアログ設定用構造体 */
/*E Structure for setting system prepared message dialog */
typedef struct SceMsgDialogSystemMessageParam {
	SceMsgDialogSystemMessageType sysMsgType;		/*J 定型文タイプ */
													/*E System message type */
	SceInt32 value;									/*J 追加指定数値 */
													/*E Additional value */
	SceChar8 reserved[32];							/*J 予約領域 （ゼロで埋めること） */
													/*E reserved range (must be filled by zero) */
} SceMsgDialogSystemMessageParam;

/*J エラーコード表示ダイアログ設定用構造体 */
/*E Structure for setting error code dialog */
typedef struct SceMsgDialogErrorCodeParam {
	SceInt32 errorCode;								/*J 表示するエラーコード */
													/*E Displayed error code */
	SceChar8 reserved[32];							/*J 予約領域 （ゼロで埋めること） */
													/*E reserved range (must be filled by zero) */
} SceMsgDialogErrorCodeParam;

/*J プログレスバーダイアログ設定用構造体 */
/*E Structure for setting progress bar dialog */
typedef struct SceMsgDialogProgressBarParam {
	SceMsgDialogProgressBarType barType;			/*J プログレスバータイプ */
													/*E Progress bar type */
	SceMsgDialogSystemMessageParam sysMsgParam;		/*J 画面表示定型文指定 */
													/*E Displayed system message */
	const SceChar8 *msg;							/*J 画面表示文字列 */
													/*E Displayed user message */
	SceChar8 reserved[32];							/*J 予約領域 （ゼロで埋めること） */
													/*E Reserved range (must be filled by zero) */
} SceMsgDialogProgressBarParam;

/*J メッセージダイアログ呼び出し用構造体 */
/*E Structure for calling sceMsgDialogInit() */
typedef struct SceMsgDialogParam {
	SceUInt32 sdkVersion;							/*J SDKバージョン（sceMsgDialogParamInitを使って初期化すること） */
													/*E SDK version (must be initialized by using sceMsgDialogParamInit) */
	SceCommonDialogParam commonParam;				/*J 共通パラメータ */
													/*E Common parameter */
	SceMsgDialogMode mode;							/*J 呼び出しモード */
													/*E Mode of calling function */
	SceMsgDialogUserMessageParam *userMsgParam;		/*J ユーザ指定メッセージ表示用パラメータ */
													/*E Parameter for user message */
	SceMsgDialogSystemMessageParam *sysMsgParam;	/*J システム定型文表示用パラメータ */
													/*E Parameter for system prepared message */
	SceMsgDialogErrorCodeParam *errorCodeParam;		/*J エラーコード表示用パラメータ */
													/*E Parameter for display error code */
	SceMsgDialogProgressBarParam *progBarParam;		/*J プログレスバー表示用パラメータ */
													/*E Parameter for progress bar */
	SceMsgDialogEnvFlag flag;						/*J 環境設定フラグ */
													/*E Settings for dialog environment */
	SceChar8 reserved[32];							/*J 予約領域 （ゼロで埋めること） */
													/*E Reserved range (must be filled by zero) */
} SceMsgDialogParam;

/*J 呼び出し結果取得用構造体 */
/*E Structure for receiving result of calling function */
typedef struct SceMsgDialogResult {
	SceMsgDialogMode mode;							/*J 呼び出しモード */
													/*E Mode of function */
	SceInt32 result;								/*J ダイアログ実行結果 */
													/*E Result of executing function */
	SceMsgDialogButtonId buttonId;					/*J 選択されたボタンのID */
													/*E Id of button user selected */
	SceChar8 reserved[32];							/*J 予約領域 （ゼロで埋めること） */
													/*E Reserved range (must be filled by zero) */
} SceMsgDialogResult;

/*J 関数 -------------------------------------------------------------------------------- */
/*E Functions --------------------------------------------------------------------------- */

/*J 呼び出しパラメータ初期化用マクロ */
/*E Macro for initializing SceMsgDialogParam */
static inline
void sceMsgDialogParamInit(SceMsgDialogParam *param)
{
	sceClibMemset( param, 0x0, sizeof(SceMsgDialogParam) );
	_sceCommonDialogSetMagicNumber( &param->commonParam );
	param->sdkVersion = SCE_PSP2_SDK_VERSION;
}

/*J 機能の呼び出し */
/*E Call function */
SceInt32 sceMsgDialogInit(const SceMsgDialogParam *param);

/*J 動作ステータスの取得 */
/*E Get running status */
SceCommonDialogStatus sceMsgDialogGetStatus(void);

/*J 機能の呼び出しを中断 */
/*E Abort calling function */
SceInt32 sceMsgDialogAbort(void);

/*J 呼び出し結果の取得 */
/*E Get result of calling function */
SceInt32 sceMsgDialogGetResult(SceMsgDialogResult *result);

/*J 機能の呼び出しの終了 */
/*E Terminate calling function */
SceInt32 sceMsgDialogTerm(void);

/*J ダイアログを閉じる */
/*E Close dialog */
SceInt32 sceMsgDialogClose(void);

/*J メッセージダイアログ内のプログレスバーの進捗率を加算する */
/*E Increase the progress rate of the progress bar in the message dialog */
SceInt32 sceMsgDialogProgressBarInc(
		SceMsgDialogProgressBarTarget target,		/*J 加算対象 */
													/*E Target progress bar */
		SceUInt32 delta								/*J 加算する進捗率(%) */
													/*E Progress rate to increase(%) */
	);

/*J メッセージダイアログ内のプログレスバーの進捗率をセットする */
/*E Set the progress rate of the progress bar in the message dialog immediately */
SceInt32 sceMsgDialogProgressBarSetValue(
		SceMsgDialogProgressBarTarget target,		/*J セット対象 */
													/*E Target progress bar */
		SceUInt32 rate								/*J セットする進捗率(%) */
													/*E Progress rate to set(%) */
	);


/*J メッセージダイアログ内のプログレスバーに付加表示される文字列を設定する */
/*E Set the string displayed in the progress bar of the message dialog immediately */
SceInt32 sceMsgDialogProgressBarSetMsg(
		SceMsgDialogProgressBarTarget target,		/*J 設定対象 */
													/*E Target progress bar */
		const SceChar8 *barMsg						/*J プログレスバーに付加表示する文字列 (UTF-8で指定。NUL終端文字を含む) */
													/*E the string displayed in the progress bar(Specify in UTF-8, including the NULL termination character) */
	);


/*J 廃止 -------------------------------------------------------------------------------- */
/*E Obsolete ---------------------------------------------------------------------------- */

/*J 互換のため残していますが、使用しないでください */
/*E Do not use following macros. These are kept for compatibility */

#define SCE_MSG_DIALOG_SYSMSG_TYPE_MIC_DISABLED						(4)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_NEED_MC_CONTINUE					(7)
#define SCE_MSG_DIALOG_SYSMSG_TYPE_NEED_MC_OPERATION				(8)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_MESSAGE_DIALOG_H_ */
