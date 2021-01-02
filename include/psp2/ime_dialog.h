#ifndef _DOLCESDK_PSP2_IME_DIALOG_H_
#define _DOLCESDK_PSP2_IME_DIALOG_H_

#include <psp2/kernel/clib.h>
#include <psp2/common_dialog/common_api.h>
#include <psp2/sdk_version.h>
#include <psp2/libime.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*J エラーコード */
/*E error code */
#define SCE_IME_DIALOG_ERROR_PARAM					(0x80102001)
#define SCE_IME_DIALOG_ERROR_INTERNAL				(0x80102002)
#define SCE_IME_DIALOG_ERROR_INVALID_DIALOG_MODE	(0x80102003)
#define SCE_IME_DIALOG_ERROR_INVALID_TEXT_BOX_MODE	(0x80102004)
#define SCE_IME_DIALOG_ERROR_INVALID_TITLE			(0x80102005)

#define SCE_IME_DIALOG_MAX_TITLE_LENGTH				(128)
#define SCE_IME_DIALOG_MAX_TEXT_LENGTH				(2048)

#define SCE_IME_DIALOG_DIALOG_MODE_DEFAULT			(0)
#define SCE_IME_DIALOG_DIALOG_MODE_WITH_CANCEL		(1)

#define SCE_IME_DIALOG_TEXTBOX_MODE_DEFAULT			(0x00)
#define SCE_IME_DIALOG_TEXTBOX_MODE_PASSWORD		(0x01)
#define SCE_IME_DIALOG_TEXTBOX_MODE_WITH_CLEAR		(0x02)

#define SCE_IME_DIALOG_BUTTON_NONE					(0)
#define SCE_IME_DIALOG_BUTTON_CLOSE					(1)
#define SCE_IME_DIALOG_BUTTON_ENTER					(2)

typedef struct SceImeDialogParam {
	SceUInt32 sdkVersion;			///< The sdk version

	/// The input method. This field is not used for the current release and must be zero.
	SceUInt32 inputMethod;
	SceUInt64 supportedLanguages;
	SceBool languagesForced;
	SceUInt32 type;
	SceUInt32 option;
	SceImeTextFilter filter;		///< The text filter.

	SceUInt32 dialogMode;
	SceUInt32 textBoxMode;
	const SceWChar16 *title;		/*J タイトル部分表示文字列 */
									/*E string displayed title area */
	SceUInt32 maxTextLength;		/*J 最大文字数 */
									/*E The maximum length */
	SceWChar16 *initialText;

	SceWChar16 *inputTextBuffer;	/*J 結果の文字列の格納先 */
									/*E Pointer to the buffer of the input string */

	SceCommonDialogParam commonParam;

	SceUChar8 enterLabel;
	SceChar8 reserved[35];			/*J 予約領域 */
									/*E reserved area */
} SceImeDialogParam;

/*J GetResult構造体 */
/*E structure for GetResult */
typedef struct SceImeDialogResult {
	SceInt32 result;											/*J ダイアログ実行結果 */
																/*E result of dialog */
	SceInt32 button;

	SceChar8 reserved[28];										/*J 予約領域 */
																/*E reserved range */
} SceImeDialogResult;

/*J パラメータ初期化関数 */
/*E function for initializing parameter */
static inline
void sceImeDialogParamInit( SceImeDialogParam *param )
{
	sceClibMemset( param, 0x0, sizeof(SceImeDialogParam) );
	_sceCommonDialogSetMagicNumber( &param->commonParam );
	param->sdkVersion = SCE_PSP2_SDK_VERSION;
}

/*J ImeDialog の機能を開始する */
/*E Start ImeDialog */
SceInt32 sceImeDialogInit( const SceImeDialogParam *param );

/*J ImeDialog のステータスを取得する */
/*E Get running status of ImeDialog */
SceCommonDialogStatus sceImeDialogGetStatus( void );

/*J ImeDialog の機能を中断する */
/*E Abort ImeDialog */
SceInt32 sceImeDialogAbort( void );

/*J ImeDialog の結果を取得する */
/*E Get result of ImeDialog */
SceInt32 sceImeDialogGetResult( SceImeDialogResult* result );

/*J ImeDialog の機能を終了する */
/*E Terminate ImeDialog */
SceInt32 sceImeDialogTerm( void );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_IME_DIALOG_H_ */
