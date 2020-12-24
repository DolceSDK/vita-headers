#ifndef _DOLCESDK_PSP2_NETCHECK_DIALOG_H_
#define _DOLCESDK_PSP2_NETCHECK_DIALOG_H_

#include <psp2/kernel/clib.h>
#include <psp2/common_dialog/common_api.h>
#include <psp2/sdk_version.h>
#include <psp2/np/np_common.h>
#include <psp2/net.h>
#include <psp2/libnetctl.h>
#include <psp2/pspnet_adhoc.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*J エラーコード */
/*E error code */
#define SCE_NETCHECK_DIALOG_ERROR_PARAM							(0x80100c01)
#define SCE_NETCHECK_DIALOG_ERROR_INVALID_MODE					(0x80100c02)
#define SCE_NETCHECK_DIALOG_ERROR_LACK_OF_LIBHTTP_POOL_SIZE		(0x80100c03)
#define SCE_NETCHECK_DIALOG_ERROR_LACK_OF_LIBSSL_POOL_SIZE		(0x80100c04)
#define SCE_NETCHECK_DIALOG_ERROR_LATEST_PATCH_PKG_EXIST		(0x80100c05)
#define SCE_NETCHECK_DIALOG_ERROR_SIGN_OUT						(0x80100c06)
#define SCE_NETCHECK_DIALOG_ERROR_INVALID_PSPADHOC_PARAM		(0x80100c07)
#define SCE_NETCHECK_DIALOG_ERROR_INVALID_TIMEOUT_PARAM			(0x80100c08)
#define SCE_NETCHECK_DIALOG_ERROR_PSN_AGE_RESTRICTION			(0x80100c09)

/*J libhttp/libssl プールサイズチェック */
/*E libhttp/libssl pool size for checking  */
#define SCE_NETCHECK_DIALOG_LEAST_HTTP_POOL_SIZE	(36 * 1024)
#define SCE_NETCHECK_DIALOG_LEAST_SSL_POOL_SIZE		(96 * 1024)


typedef SceInt32 SceNetCheckDialogMode;
#define SCE_NETCHECK_DIALOG_MODE_INVALID			(0) /*J 無効なモード */
														/*E Invalid Mode */
#define SCE_NETCHECK_DIALOG_MODE_ADHOC_CONN			(1)	/*J Adhoc接続モード */
														/*E Adhoc Mode */
#define SCE_NETCHECK_DIALOG_MODE_PSN				(2)	/*J PSNモード */
														/*E PSN Mode */
#define SCE_NETCHECK_DIALOG_MODE_PSN_ONLINE			(3)	/*J PSN Onlineモード */
														/*E PSN Online Mode */
#define SCE_NETCHECK_DIALOG_MODE_PS3_CONNECT		(4)	/*J PS3接続モード */
														/*E PS3 Connect Mode */
#define SCE_NETCHECK_DIALOG_MODE_PSP_ADHOC_CONN		(5)	/*J PSP Adhoc接続モード */
														/*E PSP Adhoc Connect Mode */
#define SCE_NETCHECK_DIALOG_MODE_PSP_ADHOC_CREATE	(6)	/*J PSP Adhoc Create モード */
														/*E PSP Adhoc Create Mode */
#define SCE_NETCHECK_DIALOG_MODE_PSP_ADHOC_JOIN		(7)	/*J PSP Adhoc Join モード */
														/*E PSP Adhoc Join Mode */

typedef SceInt32 SceNetCheckDialogPS3ConnectAction;
#define SCE_NETCHECK_DIALOG_PS3_CONNECT_ACTION_ENTER	(0) /*J PS3 に接続する */
														/*E Connect to PS3 */
#define SCE_NETCHECK_DIALOG_PS3_CONNECT_ACTION_LEAVE	(1)	/*J PS3 から切断する */
														/*E Disconnect from PS3 */

typedef struct SceNetCheckDialogPS3ConnectParam {
	SceNetCheckDialogPS3ConnectAction action;
	char ssid[SCE_NET_CTL_SSID_LEN];
	char wpaKey[SCE_NET_CTL_WIFI_SECURITY_KEY_LEN];
	char titleId[9 + 1];
} SceNetCheckDialogPS3ConnectParam;

#define SCE_NETCHECK_DIALOG_INITIAL_AGE_RESTRICTION	(-1)/*J デフォルト年齢制限(初期値)*/
														/*E (initial) default age restriction */
#define SCE_NETCHECK_DIALOG_COUNTRY_CODE_LEN		(2)	/*J 国コード桁 */
														/*E country code length */
#define SCE_NETCHECK_DIALOG_AGE_RESTRICTION_COUNT_MAX	(200)	/*J 国別年齢制限の個数最大値 */
														/*E The maximum number of country-specific age restriction */
typedef struct SceNetCheckDialogAgeRestriction {
	char countryCode[SCE_NETCHECK_DIALOG_COUNTRY_CODE_LEN];	/*J 国コード */
															/*E country code */
	SceInt8 age;											/*J 年齢 */
															/*E age */
	SceInt8 padding;

} SceNetCheckDialogAgeRestriction;

typedef struct SceNetCheckDialogParam {
	SceUInt32 sdkVersion;							/*J 内部使用領域 */
													/*E internal range */
	SceCommonDialogParam commonParam;				/*J 共通ダイアログパラメタ */
													/*E common dialog parameter */
	SceNetCheckDialogMode mode;						/*J 動作モード */
													/*E dialog mode */
	SceNpCommunicationId npCommunicationId;			/*J コミュニケーション ID */
													/*E Communication ID */
	SceNetCheckDialogPS3ConnectParam *ps3ConnectParam;	/*J PS3接続モードパラメタ */
													/*E PS3 connect mode parameter */
	SceNetAdhocctlGroupName *groupName;				/*J PSP Adohoc接続 Group name パラメタ */
													/*E PSP Adhoc connect Group name parameter */
	SceUInt32 timeoutUs;							/*J PSP Adohoc join 用 timeout パラメタ */
													/*E PSP Adhoc join timeout parameter */
	SceInt8 defaultAgeRestriction;					/*J デフォルト年齢制限パラメタ */
													/*E default age restriction parameter */
	SceInt8 padding[3];

	SceInt32 ageRestrictionCount;					/*J 国別年齢制限の個数 */
													/*E Number of country-specific age restriction */
	const SceNetCheckDialogAgeRestriction *ageRestriction;	/*J 国別年齢制限のリスト */
													/*E country-specific age restriction list parameter */
	SceUInt8 reserved[104];							/*J 予約領域 */
													/*E reserved range */
} SceNetCheckDialogParam;

/*J GetResult構造体 */
/*E structure for GetResult */
typedef struct SceNetCheckDialogResult {
	SceInt32 result;								/*J ダイアログ実行結果 */
													/*E result of dialog */
	SceBool psnModeSucceeded;						/*J PSN Mode 結果 */
													/*E result of psn mode */
	SceUInt8 reserved[124];							/*J 予約領域 */
													/*E reserved range */
} SceNetCheckDialogResult;

typedef struct SceNetCheckDialogPS3ConnectInfo {
	SceNetInAddr inaddr;
	SceUInt8 nickname[128];
	SceUInt8 macAddress[6];
	SceUInt8 reserved[6];
} SceNetCheckDialogPS3ConnectInfo;

/*J パラメータ初期化関数 */
/*E function for initializing parameter */
static inline
void sceNetCheckDialogParamInit(SceNetCheckDialogParam* param)
{
	sceClibMemset( param, 0x0, sizeof(SceNetCheckDialogParam) );
	_sceCommonDialogSetMagicNumber( &param->commonParam );
	param->sdkVersion = SCE_PSP2_SDK_VERSION;
	param->defaultAgeRestriction = SCE_NETCHECK_DIALOG_INITIAL_AGE_RESTRICTION;
}

/*J NetCheckDialog の機能を開始する */
/*E Start NetCheckDialog */
SceInt32 sceNetCheckDialogInit(SceNetCheckDialogParam* param);

/*J NetCheckDialog のステータスを取得する */
/*E Get running status of NetCheckDialog */
SceCommonDialogStatus sceNetCheckDialogGetStatus(void);

/*J NetCheckDialog の機能を中断する */
/*E Abort NetCheckDialog */
SceInt32 sceNetCheckDialogAbort(void);

/*J NetCheckDialog の結果を取得する */
/*E Get result of NetCheckDialog */
SceInt32 sceNetCheckDialogGetResult(SceNetCheckDialogResult* result);

/*J PS3接続モードにおけるPS3情報を取得する */
/*E Get PS3 information in PS3 connect mode */
SceInt32 sceNetCheckDialogGetPS3ConnectInfo(SceNetCheckDialogPS3ConnectInfo* info);

/*J NetCheckDialog の機能を終了する */
/*E Terminate NetCheckDialog */
SceInt32 sceNetCheckDialogTerm(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_NETCHECK_DIALOG_H_ */
