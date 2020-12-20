#ifndef _DOLCESDK_PSP2_NP_NP_ACTIVITY_H_
#define _DOLCESDK_PSP2_NP_NP_ACTIVITY_H_

#include <psp2/np/np_common.h>

/*J Statusのメッセージの最大文字数(UTF-8)
	バイト数ではない。文字数にはNUL終端文字は含めない。 */
/*E Maximum number of characters of the status message (UTF-8)
	This is not the number of bytes and the null-terminator is not included. */
#define SCE_NP_ACTIVITY_STATUS_MESSAGE_MAX_NUM_CHARACTERS	256

/*J Statusのメッセージの最大改行数 */
/*E Maximum number of linefeeds of the status message. */
#define SCE_NP_ACTIVITY_STATUS_MESSAGE_MAX_NUM_LINEFEEDS	8

/*J Statusのメッセージの最大バイト数（NUL終端文字込み）。
	UTF-8の1文字は1～4バイト。
	下記のバイト数以内であっても、文字数が最大文字数を越えた場合はエラーとなる。
	 */
/*E Maximum number of bytes of the status message (including the null-terminator)
	A UTF8 character uses 1 to 4 bytes.
	If the number of characters exceeds the maximum number of characters,
	 an error occurs even if it is within the following number of bytes.
	*/
#define SCE_NP_ACTIVITY_STATUS_MESSAGE_MAX_SIZE		1025

/*J StatusのアクションURIの最大バイト数（NUL終端文字込み）
	アクションURIはASCII文字。 */
/*E Maximum number of action URI of status (including the null-terminator)
	The action URI is in the ASCII characters. */
#define SCE_NP_ACTIVITY_STATUS_ACTION_URI_MAX_SIZE	1025

/* NP Activity status message */
typedef struct SceNpActivityStatusMessage {
	/*J Statusのメッセージ(UTF-8、NUL終端文字込み)。
		最大文字数（UTF8)は256文字、最大バイト数は1025バイト(NUL終端文字込み) */
	/*E Status message (UTF-8, including the null-terminator).
		The maximum number of characters (UTF-8) is 256. The maximum number of bytes is 1025 bytes including the null-terminator. */
	 char data[SCE_NP_ACTIVITY_STATUS_MESSAGE_MAX_SIZE];
} SceNpActivityStatusMessage;

/* NP Activity status action URI */
typedef struct SceNpActivityStatusActionUri {
	/*J StatusのアクションURI。ASCII文字（NUL終端込み） */
	/*E Action URI of the status in the ASCII characters (including the NUL terminator) */
	char data[SCE_NP_ACTIVITY_STATUS_ACTION_URI_MAX_SIZE];
} SceNpActivityStatusActionUri;

/* NP Activity status with an action URI for starting up an application */
#define  SCE_NP_ACTIVITY_APP_PARAM_MAX_SIZE		897
#define  SCE_NP_ACTIVITY_APP_VER_NOT_REQUIRED   0

typedef struct SceNpActivityStatusAppStartupParam {
	/*J 実行に必要なアプリケーションバージョン(xx.yy)
		ピリオドを取り除いた3～4桁の数値として設定してください。
		SCE_NP_ACTIVITY_APP_VER_NOT_REQUIRED(0)を指定した場合は、必要なアプリケーションバージョンの指定はされません。 */
	/*E The required application version that is in the format "xx.yy".
		Please specify this value as a 4-digit number, with the period removed.
		When SCE_NP_ACTIVITY_APP_VER_NOT_REQUIRED(0) is set, the required application version is not set. */
	SceUInt32   appVersion;
	/*J アプリケーション起動の引数（NUL終端込み）
		sceHttpUriEscape()を使用してURI Escapeを実行してください。
		空の文字列を指定すると起動引数のないアプリケーション起動リンクになります */
	/*E The argument for starting up application(including the null-terminator)
		Please perform URI Escape processing by sceHttpUriEscape().
		When empty string is set, an action link without the parameter is created. */
	char escapedParam[SCE_NP_ACTIVITY_APP_PARAM_MAX_SIZE];
	/*J 予約領域 */
	/*E Reserved range */
	SceUInt8 reserved[3];
} SceNpActivityStatusAppStartupParam;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int sceNpActivityInit(
	void	*option);

int sceNpActivityTerm(void);

int sceNpActivityPostStatus(
	const SceNpActivityStatusMessage	*message,
	const SceNpActivityStatusActionUri	*actionUri,
	void *option);

int sceNpActivityPostAppStartupStatus(
	const SceNpActivityStatusMessage			*message,
	const SceNpActivityStatusAppStartupParam	*param,
	void *option);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_ACTIVITY_H_ */
