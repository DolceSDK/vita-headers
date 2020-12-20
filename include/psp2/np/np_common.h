#ifndef _DOLCESDK_PSP2_NP_NP_COMMON_H_
#define _DOLCESDK_PSP2_NP_NP_COMMON_H_

#include <psp2/np/np_npid.h>

#define SCE_NP_AVATAR_URL_MAX_LENGTH	127
#define SCE_NP_ABOUT_ME_MAX_LENGTH		63
#define SCE_NP_AVATAR_IMAGE_MAX_SIZE_LARGE	(200 * 1024U)
#define SCE_NP_AVATAR_IMAGE_MAX_SIZE_MIDDLE	(100 * 1024U)
#define SCE_NP_AVATAR_IMAGE_MAX_SIZE_SMALL	(10 * 1024U)
#define SCE_NP_AVATAR_IMAGE_MAX_SIZE		SCE_NP_AVATAR_IMAGE_MAX_SIZE_LARGE

/*J NPで使用する言語のロケール */
/*E language used by NP */
#define SCE_NP_LANG_JAPANESE			(0)		/*J 日本語 */
												/*E Japanese */
#define SCE_NP_LANG_ENGLISH				(1)		/*J 英語。sceNpManagerGetAccountRegion()の戻り値で使用。 */
												/*E English that is used as argument of sceNpManagerGetAccountRegion() */
#define SCE_NP_LANG_ENGLISH_US			(1)		/*J 英語(US) */
												/*E English(US) */
#define SCE_NP_LANG_FRENCH				(2)		/*J フランス語 */
												/*E French */
#define SCE_NP_LANG_SPANISH				(3)		/*J スペイン語 */
												/*E Spanish */
#define SCE_NP_LANG_GERMAN				(4)		/*J ドイツ語 */
												/*E German */
#define SCE_NP_LANG_ITALIAN				(5)		/*J イタリア語 */
												/*E Italian */
#define SCE_NP_LANG_DUTCH				(6)		/*J オランダ語 */
												/*E Dutch */
#define SCE_NP_LANG_PORTUGUESE			(7)		/*J ポルトガル語。sceNpManagerGetAccountRegion()の戻り値で使用。 */
												/*E Portuguese that is used as argument of sceNpManagerGetAccountRegion() */
#define SCE_NP_LANG_PORTUGUESE_PT		(7)		/*J ポルトガル語 */
												/*E Portuguese */
#define SCE_NP_LANG_RUSSIAN				(8)		/*J ロシア語 */
												/*E Russian */
#define SCE_NP_LANG_KOREAN				(9)		/*J 韓国語 */
												/*E Korean */
#define SCE_NP_LANG_CHINESE_T			(10)	/*J 中国語(繁体字) */
												/*E Chinese (traditional) */
#define SCE_NP_LANG_CHINESE_S			(11)	/*J 中国語(簡体字) */
												/*E Chinese (simplified) */
#define SCE_NP_LANG_FINNISH				(12)	/*J フィンランド語 */
												/*E Finnish */
#define SCE_NP_LANG_SWEDISH				(13)	/*J スウェーデン語 */
												/*E Swedish */
#define SCE_NP_LANG_DANISH				(14)	/*J デンマーク語 */
												/*E Danish */
#define SCE_NP_LANG_NORWEGIAN			(15)	/*J ノルウェー語 */
												/*E Norwegian */
#define SCE_NP_LANG_POLISH				(16)	/*J ポーランド語 */
												/*E Polish */
#define SCE_NP_LANG_PORTUGUESE_BR		(17)	/*J ブラジルポルトガル語 */
												/*E Brazil Portuguese */
#define SCE_NP_LANG_ENGLISH_GB			(18)	/*J 英語(GB) */
												/*E English(GB) */
#define SCE_NP_LANG_TURKISH				(19)	/*J トルコ語 */
												/*E Turkish */
#define SCE_NP_LANG_SPANISH_LA			(20)	/*J スペイン語(LA) */
												/*E Spanish(LA) */
#define SCE_NP_LANG_ARABIC				(21)	/*J アラビア語 */
												/*E Arabic */
#define SCE_NP_LANG_FRENCH_CA			(22)	/*J フランス語(カナダ) */
												/*E French (Canada) */

/* Communication ID */
typedef struct SceNpCommunicationId {
	char data[9];
	char term;
	SceUChar8 num;
	char dummy;
} SceNpCommunicationId;

/* Communication Passphrase */
#define SCE_NP_COMMUNICATION_PASSPHRASE_SIZE		(128)
typedef struct SceNpCommunicationPassphrase {
	SceUChar8 data[SCE_NP_COMMUNICATION_PASSPHRASE_SIZE];
} SceNpCommunicationPassphrase;

/* Communication Signature */
#define SCE_NP_COMMUNICATION_SIGNATURE_SIZE			(160)
typedef struct SceNpCommunicationSignature {
	SceUChar8 data[SCE_NP_COMMUNICATION_SIGNATURE_SIZE];
} SceNpCommunicationSignature;

/* Communication Config */
typedef struct SceNpCommunicationConfig {
	const SceNpCommunicationId			*commId;
	const SceNpCommunicationPassphrase	*commPassphrase;
	const SceNpCommunicationSignature	*commSignature;
} SceNpCommunicationConfig;

/* NP country code (ISO 3166-1 two-letter system) */
typedef struct SceNpCountryCode {
	char data[2];
	char term;
	char padding[1];
} SceNpCountryCode;

/* NP Avatar URL */
typedef struct SceNpAvatarUrl {
	char data[SCE_NP_AVATAR_URL_MAX_LENGTH];
	char term;
} SceNpAvatarUrl;

/* NP USER INFO */
typedef struct SceNpUserInformation {
	SceNpId userId;
	SceNpAvatarUrl icon;		/* Avatar URL */
	SceUChar8 reserved[52];
} SceNpUserInformation;

/* My Languages */
typedef	struct SceNpMyLanguages{
	SceInt32	language1;	/* It will always be set */
	SceInt32	language2;	/* Negative when not set */
	SceInt32	language3;	/* Negative when not set */
	SceUChar8 padding[4];
} SceNpMyLanguages;

/* NP Avatar Image(for Large Size) */
typedef struct SceNpAvatarImage {
	SceUChar8 data[SCE_NP_AVATAR_IMAGE_MAX_SIZE];
	SceSize	size;
	SceUChar8	reserved[12];
} SceNpAvatarImage;

typedef enum {
	SCE_NP_AVATAR_SIZE_LARGE,
	SCE_NP_AVATAR_SIZE_MIDDLE,
	SCE_NP_AVATAR_SIZE_SMALL
} SceNpAvatarSizeType;

typedef	struct SceNpAboutMe{
	char	data[SCE_NP_ABOUT_ME_MAX_LENGTH + 1];
} SceNpAboutMe;

#define SCE_NP_PORT 3658    /* registered port for NP */


typedef SceInt32 SceNpPlatformType;
#define SCE_NP_PLATFORM_TYPE_NONE		0
#define SCE_NP_PLATFORM_TYPE_PS3		1
#define SCE_NP_PLATFORM_TYPE_VITA		2
#define SCE_NP_PLATFORM_TYPE_PS4		3

/* Np Peer Address */
typedef struct SceNpPeerAddress {
	SceNpOnlineId onlineId;
	SceNpPlatformType platform;
} SceNpPeerAddress;

/* NP title ID */
#define SCE_NP_TITLE_ID_LEN		12
typedef struct SceNpTitleId {
	char id[SCE_NP_TITLE_ID_LEN + 1];
	SceUChar8 padding[3];
} SceNpTitleId;

/* NP title secret */
#define SCE_NP_TITLE_SECRET_SIZE		128
typedef struct SceNpTitleSecret {
	SceUChar8 data[SCE_NP_TITLE_SECRET_SIZE];
} SceNpTitleSecret;

/* NP Service Label */
typedef SceUInt32 SceNpServiceLabel;
#define SCE_NP_DEFAULT_SERVICE_LABEL (0x00000000)
#define SCE_NP_INVALID_SERVICE_LABEL (0xFFFFFFFF)

/* NP Client ID */
#define SCE_NP_CLIENT_ID_MAX_LEN 128
typedef struct SceNpClientId {
	char id[SCE_NP_CLIENT_ID_MAX_LEN + 1];
	SceUInt8 padding[7];
} SceNpClientId;

/* NP Authorization Code */
#define SCE_NP_AUTHORIZATION_CODE_MAX_LEN 128
typedef struct SceNpAuthorizationCode {
	char code[SCE_NP_AUTHORIZATION_CODE_MAX_LEN + 1];
	SceUInt8 padding[7];
} SceNpAuthorizationCode;

/* NP Session ID */
#define SCE_NP_SESSION_ID_MAX_SIZE			(45)
typedef struct SceNpSessionId {
	char data[ SCE_NP_SESSION_ID_MAX_SIZE ];
	char term;
	char padding[2]; /* Padding */
} SceNpSessionId;

/* NP Invitation ID */
#define SCE_NP_INVITATION_ID_MAX_SIZE		(60)
typedef struct SceNpInvitationId {
	char data[ SCE_NP_INVITATION_ID_MAX_SIZE ];
	char term;
	char padding[3]; /* Padding */
} SceNpInvitationId;

/* GameCustomData */
typedef SceUInt64 SceNpGameCustomDataId;

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int
sceNpCmpNpId(
	const SceNpId *npid1,
	const SceNpId *npid2
	);

int
sceNpCmpNpIdInOrder(
	const SceNpId *npid1,
	const SceNpId *npid2,
	int *order
	);

int
sceNpCmpOnlineId(
	const SceNpId *npid1,
	const SceNpId *npid2
	);


int
sceNpGetPlatformType(
	const SceNpId *npId
	);

int
sceNpSetPlatformType(
	SceNpId *npId,
	SceNpPlatformType platformType
	);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_COMMON_H_ */
