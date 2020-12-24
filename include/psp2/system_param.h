#ifndef _DOLCESDK_PSP2_SYSTEM_PARAM_H_
#define _DOLCESDK_PSP2_SYSTEM_PARAM_H_

#include <psp2/types.h>


/*J システムパラメータID型 */
/*E type of system parameter id */
typedef SceUInt32 SceSystemParamId;

#define SCE_SYSTEM_PARAM_ID_LANG					(1)		/*J 言語設定（整数値） */
															/*E Settings of language (Integer) */
#define SCE_SYSTEM_PARAM_ID_ENTER_BUTTON_ASSIGN		(2)		/*J 決定ボタンの割り当て */
															/*E Assignment of ENTER button */
#define SCE_SYSTEM_PARAM_ID_USER_NAME				(3)		/*J 表示用ユーザーネーム（文字列, UTF-8で最大16文字、バッファサイズは最低 SCE_SYSTEM_PARAM_USER_NAME_MAXSIZE byte を確保する） */
															/*E User name to display (String, UTF-8, up to 16 characters, Allocate at least SCE_SYSTEM_PARAM_USER_NAME_MAXSIZE bytes ) */
#define SCE_SYSTEM_PARAM_ID_DATE_FORMAT				(4)		/*J 日付表示形式（整数値） */
															/*E Date display format (Integer) */
#define SCE_SYSTEM_PARAM_ID_TIME_FORMAT				(5)		/*J 時間表示形式（整数値） */
															/*E Time display format (Integer) */
#define SCE_SYSTEM_PARAM_ID_TIME_ZONE				(6)		/*J タイムゾーン（整数値, オフセット） */
															/*E Time zone (Integer, by offset) */
#define SCE_SYSTEM_PARAM_ID_SUMMERTIME				(7)		/*J サマータイム（整数値, 0:無効, 1:有効) */
															/*E Daylight savings time (Integer, 0:Disabled, 1:Enabled) */

/*J 言語設定 */
/*E Settings of language */
typedef SceInt32 SceSystemParamLang;

#define SCE_SYSTEM_PARAM_LANG_JAPANESE				(0)		/*J 日本語 */
															/*E Japanese */
#define SCE_SYSTEM_PARAM_LANG_ENGLISH_US			(1)		/*J 英語(US) */
															/*E English(US) */
#define SCE_SYSTEM_PARAM_LANG_FRENCH				(2)		/*J フランス語 */
															/*E French */
#define SCE_SYSTEM_PARAM_LANG_SPANISH				(3)		/*J スペイン語 */
															/*E Spanish */
#define SCE_SYSTEM_PARAM_LANG_GERMAN				(4)		/*J ドイツ語 */
															/*E German */
#define SCE_SYSTEM_PARAM_LANG_ITALIAN				(5)		/*J イタリア語 */
															/*E Italian */
#define SCE_SYSTEM_PARAM_LANG_DUTCH					(6)		/*J オランダ語 */
															/*E Dutch */
#define SCE_SYSTEM_PARAM_LANG_PORTUGUESE_PT			(7)		/*J ポルトガル語 */
															/*E Portuguese */
#define SCE_SYSTEM_PARAM_LANG_RUSSIAN				(8)		/*J ロシア語 */
															/*E Russian */
#define SCE_SYSTEM_PARAM_LANG_KOREAN				(9)		/*J 韓国語 */
															/*E Korean  */
#define SCE_SYSTEM_PARAM_LANG_CHINESE_T				(10)	/*J 中国語(繁体字) */
															/*E Chinese (traditional characters) */
#define SCE_SYSTEM_PARAM_LANG_CHINESE_S				(11)	/*J 中国語(簡体字) */
															/*E Chinese (simplified characters) */
#define SCE_SYSTEM_PARAM_LANG_FINNISH				(12)	/*J フィンランド語 */
															/*E Finnish */
#define SCE_SYSTEM_PARAM_LANG_SWEDISH				(13)	/*J スウェーデン語 */
															/*E Swedish */
#define SCE_SYSTEM_PARAM_LANG_DANISH				(14)	/*J デンマーク語 */
															/*E Danish */
#define SCE_SYSTEM_PARAM_LANG_NORWEGIAN				(15)	/*J ノルウェー語 */
															/*E Norwegian */
#define SCE_SYSTEM_PARAM_LANG_POLISH				(16)	/*J ポーランド語 */
															/*E Polish */
#define SCE_SYSTEM_PARAM_LANG_PORTUGUESE_BR			(17)	/*J ブラジルポルトガル語 */
															/*E Brazil Portuguese */
#define SCE_SYSTEM_PARAM_LANG_ENGLISH_GB			(18)	/*J 英語(GB) */
															/*E English(GB) */
#define SCE_SYSTEM_PARAM_LANG_TURKISH				(19)	/*J トルコ語 */
															/*E Turkish */

/*J 決定ボタンの割り当て */
/*E Assignment of ENTER button */
#define SCE_SYSTEM_PARAM_ENTER_BUTTON_ASSIGN_CIRCLE	(0)		/*J ◯ボタン決定 */
															/*E o button */
#define SCE_SYSTEM_PARAM_ENTER_BUTTON_ASSIGN_CROSS	(1)		/*J ☓ボタン決定 */
															/*E x button */

/*J 表示ユーザーネーム */
/*E User name to display */
#define SCE_SYSTEM_PARAM_USER_NAME_MAXSIZE			(17)	/*J 表示ユーザーネーム格納バッファ最大サイズ(NUL終端含む) */
															/*E Max size of buffer to receive user name (include null terminate) */

/*J 日付表示形式 */
/*E Date display format */
#define SCE_SYSTEM_PARAM_DATE_FORMAT_YYYYMMDD		(0)		/*J 年／月／日 */
															/*E Year/Month/Day */
#define SCE_SYSTEM_PARAM_DATE_FORMAT_DDMMYYYY		(1)		/*J 日／月／年 */
															/*E Day/Month/Year */
#define SCE_SYSTEM_PARAM_DATE_FORMAT_MMDDYYYY		(2)		/*J 月／日／年 */
															/*E Month/Day/Year */

/*J 時間表示形式 */
/*E Time display format */
#define SCE_SYSTEM_PARAM_TIME_FORMAT_12HOUR			(0)		/*J 12時間 */
															/*E 12-hour clock */
#define SCE_SYSTEM_PARAM_TIME_FORMAT_24HOUR			(1)		/*J 24時間 */
															/*E 24-hour clock */

#endif	/* _DOLCESDK_PSP2_SYSTEM_PARAM_H_ */
