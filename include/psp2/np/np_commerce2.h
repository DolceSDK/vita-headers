#ifndef _DOLCESDK_PSP2_NP_NP_COMMERCE2_H_
#define _DOLCESDK_PSP2_NP_NP_COMMERCE2_H_

#include <psp2/np/np_common.h>
#include <psp2/rtc.h>

#define SCE_NP_COMMERCE2_LEAST_HTTP_POOL_SIZE (36 * 1024)
#define SCE_NP_COMMERCE2_LEAST_SSL_POOL_SIZE  (96 * 1024)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

/*
 * Np Commerce2 Context
 */
#define SCE_NP_COMMERCE2_CTX_MAX						1
#define SCE_NP_COMMERCE2_REQ_MAX						1

/*
 * Np Commerce2 Current version
 */
#define SCE_NP_COMMERCE2_VERSION					2

/*
 * Np Commerce2 string length (without NULL termination)
 */
#define SCE_NP_COMMERCE2_CURRENCY_CODE_LEN              3
#define SCE_NP_COMMERCE2_CURRENCY_SYMBOL_LEN            3
#define SCE_NP_COMMERCE2_THOUSAND_SEPARATOR_LEN         4
#define SCE_NP_COMMERCE2_DECIMAL_LETTER_LEN             4
#define SCE_NP_COMMERCE2_SP_NAME_LEN                    256
#define SCE_NP_COMMERCE2_CATEGORY_ID_LEN                56
#define SCE_NP_COMMERCE2_CATEGORY_NAME_LEN              256
#define SCE_NP_COMMERCE2_CATEGORY_DESCRIPTION_LEN       1024
#define SCE_NP_COMMERCE2_PRODUCT_ID_LEN                 48
#define SCE_NP_COMMERCE2_PRODUCT_NAME_LEN               256
#define SCE_NP_COMMERCE2_PRODUCT_SHORT_DESCRIPTION_LEN  1024
#define SCE_NP_COMMERCE2_PRODUCT_LONG_DESCRIPTION_LEN   4000
#define SCE_NP_COMMERCE2_PRODUCT_LEGAL_DESCRIPTION_LEN  4000
#define SCE_NP_COMMERCE2_SKU_ID_LEN                     56
#define SCE_NP_COMMERCE2_SKU_NAME_LEN                   180
#define SCE_NP_COMMERCE2_URL_LEN                        256
#define SCE_NP_COMMERCE2_RATING_SYSTEM_ID_LEN           16
#define SCE_NP_COMMERCE2_RATING_DESCRIPTION_LEN         60

/* max count of sku in checking out */
#define SCE_NP_COMMERCE2_SKU_CHECKOUT_MAX			16

#define SCE_NP_COMMERCE2_RECV_BUF_SIZE (256 * 1024)

/*
 * Np Commerce2 API
 */
int
sceNpCommerce2Init(
	void
	);

int
sceNpCommerce2Term(
	void
	);

int
sceNpCommerce2CreateCtx(
	SceUInt32 version,
	SceUInt32 *ctxId
	);

int
sceNpCommerce2DestroyCtx(
	SceUInt32 ctxId
	);

int
sceNpCommerce2GetShortfallOfLibsslPool(
	SceUInt32 ctxId,
	SceInt32 *shortfall
	);

int
sceNpCommerce2GetShortfallOfLibhttpPool(
	SceUInt32 ctxId,
	SceInt32 *shortfall
	);

int
sceNpCommerce2DestroyReq(
	SceUInt32 reqId
	);

int
sceNpCommerce2AbortReq(
	SceUInt32 reqId
	);

int
sceNpCommerce2CreateSessionCreateReq(
	SceUInt32 ctxId,
	SceUInt32 *reqId
	);

int
sceNpCommerce2CreateSessionStart(
	SceUInt32 reqId
	);

int
sceNpCommerce2CreateSessionGetResult(
	SceUInt32 reqId,
	void *buf,
	SceSize bufLen,
	SceSize *fillSize
	);

/* symbolPosition */
#define SCE_NP_COMMERCE2_SYM_POS_PRE   0
#define SCE_NP_COMMERCE2_SYM_POS_POST  1

typedef struct SceNpCommerce2SessionInfo_
{
	char currencyCode[SCE_NP_COMMERCE2_CURRENCY_CODE_LEN + 1];
	SceUInt32 decimals;
	char currencySymbol[SCE_NP_COMMERCE2_CURRENCY_SYMBOL_LEN + 1];
	SceUInt32 symbolPosition;    /* SCE_NP_COMMERCE2_SYM_POS_XXX */
	SceBool symbolWithSpace;
	char thousandSeparator[SCE_NP_COMMERCE2_THOUSAND_SEPARATOR_LEN + 1];
	char decimalLetter[SCE_NP_COMMERCE2_DECIMAL_LETTER_LEN + 1];
	SceUChar8 padding[2];
	SceUInt32 reserved[16];
} SceNpCommerce2SessionInfo;

int
sceNpCommerce2GetSessionInfo(
	SceNpCommerce2SessionInfo *sessionInfo,
	void *data,
	SceSize dataSize
	);

int
sceNpCommerce2GetPrice(
	const SceNpCommerce2SessionInfo *s,
	char *buf,
	SceSize buflen,
	SceUInt32 price
	);

/*
 * accessor API
 */
typedef struct SceNpCommerce2CommonData_
{
	SceUInt32 version;
	const SceUChar8 *buf_head;
	const SceUChar8 *buf_size;
	const SceUChar8 *data;
	SceSize data_size;
	const SceUChar8 *data2;
	unsigned int ov;
	SceUInt32 reserved[16];
} SceNpCommerce2CommonData;

typedef struct SceNpCommerce2Range_
{
	SceUInt32 startPosition;
	SceUInt32 count;
	SceUInt32 totalCountOfResults;
	SceUInt32 reserved[8];
} SceNpCommerce2Range;

/* ContentRatingInfo */
#define SCE_NP_COMMERCE2_CONTENT_RATING_DESC_TYPE_ICON  1
#define SCE_NP_COMMERCE2_CONTENT_RATING_DESC_TYPE_TEXT  2
typedef struct SceNpCommerce2ContentRatingDescriptor_
{
	SceNpCommerce2CommonData commonData;

	/* value */
	SceUInt32 descriptorType;
	const char *imageUrl;                  /* valid only if descType is icon */
	const char *contentRatingDescription;  /* valid only if descType is text */
	SceUInt32 reserved[8];
} SceNpCommerce2ContentRatingDescriptor;

typedef struct SceNpCommerce2ContentRatingInfo_
{
	SceNpCommerce2CommonData commonData;

	/* value */
	const char *ratingSystemId;
	const char *imageUrl;
	SceUInt32 countOfContentRatingDescriptor;
	SceUInt32 reserved[8];
} SceNpCommerce2ContentRatingInfo;

int
sceNpCommerce2GetContentRatingDescriptor(
	const SceNpCommerce2ContentRatingInfo *contentRatingInfo,
	unsigned int idx,
	SceNpCommerce2ContentRatingDescriptor *contentRatingDescriptor
	);

/* Category */

/* dataType of category */
#define SCE_NP_COMMERCE2_CAT_DATA_TYPE_THIN    0
#define SCE_NP_COMMERCE2_CAT_DATA_TYPE_NORMAL  1
#define SCE_NP_COMMERCE2_CAT_DATA_TYPE_MAX     2

typedef struct SceNpCommerce2CategoryInfo_
{
	SceNpCommerce2CommonData commonData;
	int dataType;

	/* value */
	const char *categoryId;
	SceUInt32 padding;
	SceRtcTick releaseDate;
	const char *categoryName;
	const char *categoryDescription;
	const char *imageUrl;
	const char *spName;

	/*E valid only if dataType == SCE_NP_COMMERCE2_CAT_DATA_TYPE_NORMAL */
	SceUInt32 countOfSubCategory;
	SceUInt32 countOfProduct;

	SceUInt32 reserved[16];
} SceNpCommerce2CategoryInfo;

/* Game SKU */
#define SCE_NP_COMMERCE2_SKU_PURCHASABILITY_FLAG_ON   1
#define SCE_NP_COMMERCE2_SKU_PURCHASABILITY_FLAG_OFF  0

#define SCE_NP_COMMERCE2_SKU_ANN_PURCHASED_CANNOT_PURCHASE_AGAIN  0x80000000
#define SCE_NP_COMMERCE2_SKU_ANN_PURCHASED_CAN_PURCHASE_AGAIN     0x40000000
#define SCE_NP_COMMERCE2_SKU_ANN_IN_THE_CART                      0x20000000
#define SCE_NP_COMMERCE2_SKU_ANN_CONTENTLINK_SKU                  0x10000000
#define SCE_NP_COMMERCE2_SKU_ANN_CREDIT_CARD_REQUIRED             0x08000000
#define SCE_NP_COMMERCE2_SKU_ANN_CHARGE_IMMEDIATELY               0x04000000

/* dataType of Game SKU */
#define SCE_NP_COMMERCE2_GAME_SKU_DATA_TYPE_THIN    0
#define SCE_NP_COMMERCE2_GAME_SKU_DATA_TYPE_NORMAL  1
#define SCE_NP_COMMERCE2_GAME_SKU_DATA_TYPE_MAX     2

typedef struct SceNpCommerce2GameSkuInfo_
{
	SceNpCommerce2CommonData commonData;
	int dataType;

	/* value */
	const char *skuId;
	SceUInt32 skuType;
	SceUInt32 countUntilExpiration;
	SceUInt32 timeUntilExpiration;
	SceUInt32 purchasabilityFlag;
	SceUInt32 annotation;
	SceBool downloadable;
	SceUInt32 price;
	const char *skuName;

	/*E valid only if dataType == SCE_NP_COMMERCE2_GAME_SKU_DATA_TYPE_NORMAL */
	const char *productId;
	const char *contentLinkUrl;

	SceUInt32 countOfRewardInfo;
	SceUInt32 skuAttr;
	SceUInt32 salesType;
	SceUInt32 firstPlayExpiration;
	SceUInt32 countOfApplicableRewardInfo;
	SceUInt32 countOfGameSkuEntitlementInfo;
	SceUInt32 reserved1;
	SceRtcTick playableDate;
	SceRtcTick chargeDate;
	SceUInt32 chargeModel;
	const char *augmentedDescription;
	SceUInt32 reserved2[8];
} SceNpCommerce2GameSkuInfo;

/* Game Product */

/* dataType of Game Product */
#define SCE_NP_COMMERCE2_GAME_PRODUCT_DATA_TYPE_THIN    0
#define SCE_NP_COMMERCE2_GAME_PRODUCT_DATA_TYPE_NORMAL  1
#define SCE_NP_COMMERCE2_GAME_PRODUCT_DATA_TYPE_MAX     2

typedef struct SceNpCommerce2GameProductInfo_
{
	SceNpCommerce2CommonData commonData;
	int dataType;

	/* value */
	const char *productId;
	SceUInt32 countOfSku;
	SceRtcTick releaseDate;
	const char *productName;
	const char *productShortDescription;
	const char *imageUrl;
	const char *spName;

	/*E valid only if dataType == SCE_NP_COMMERCE2_GAME_PRODUCT_DATA_TYPE_NORMAL */
	const char *productLongDescription;
	const char *legalDescription;

	SceUInt32 productAttr;
	SceUInt32 padding;
	SceUInt32 reserved[20];
} SceNpCommerce2GameProductInfo;

int
sceNpCommerce2GetGameSkuInfoFromGameProductInfo(
	const SceNpCommerce2GameProductInfo *gameProductInfo,
	SceUInt32 idx,
	SceNpCommerce2GameSkuInfo *gameSkuInfo
	);

/*
 * Content
 */
#define SCE_NP_COMMERCE2_CONTENT_TYPE_CATEGORY  1
#define SCE_NP_COMMERCE2_CONTENT_TYPE_PRODUCT   2
typedef struct SceNpCommerce2ContentInfo_
{
	SceNpCommerce2CommonData commonData;

	/* value */
	SceUInt32 contentType;
	SceUInt32 reserved[8];
} SceNpCommerce2ContentInfo;

int
sceNpCommerce2GetCategoryInfoFromContentInfo(
	const SceNpCommerce2ContentInfo *contentInfo,
	SceNpCommerce2CategoryInfo *categoryInfo
	);
int
sceNpCommerce2GetGameProductInfoFromContentInfo(
	const SceNpCommerce2ContentInfo *contentInfo,
	SceNpCommerce2GameProductInfo *gameProductInfo
	);


/*
 * GetCategoryContents
 */
#define SCE_NP_COMMERCE2_GETCAT_MAX_COUNT 60

typedef struct SceNpCommerce2GetCategoryContentsResult_
{
	SceNpCommerce2CommonData commonData;

	/* value */
	SceNpCommerce2Range rangeOfContents;
	SceUInt32 reserved[8];
} SceNpCommerce2GetCategoryContentsResult;

int
sceNpCommerce2GetCategoryContentsCreateReq(
	SceUInt32 ctxId,
	SceUInt32 *reqId
	);
int
sceNpCommerce2GetCategoryContentsStart(
	SceUInt32 reqId,
	const char *categoryId,
	SceUInt32 startPosition,
	SceUInt32 maxCountOfResults
	);
int
sceNpCommerce2GetCategoryContentsGetResult(
	SceUInt32 reqId,
	void *buf,
	SceSize bufSize,
	SceSize *fillSize
	);
int
sceNpCommerce2InitGetCategoryContentsResult(
	SceNpCommerce2GetCategoryContentsResult *result,
	void *data,
	SceSize dataSize
	);
int
sceNpCommerce2DestroyGetCategoryContentsResult(
	SceNpCommerce2GetCategoryContentsResult *result
	);
int
sceNpCommerce2GetCategoryInfo(
	const SceNpCommerce2GetCategoryContentsResult *result,
	SceNpCommerce2CategoryInfo *categoryInfo
	);
int
sceNpCommerce2GetContentInfo(
	const SceNpCommerce2GetCategoryContentsResult *result,
	unsigned int idx,
	SceNpCommerce2ContentInfo *contentInfo
	);
int
sceNpCommerce2GetContentRatingInfoFromCategoryInfo(
	const SceNpCommerce2CategoryInfo *categoryInfo,
	SceNpCommerce2ContentRatingInfo *contentRatingInfo
	);

/*
 * GetProductInfo
 */
typedef struct SceNpCommerce2GetProductInfoResult_
{
	SceNpCommerce2CommonData commonData;

	SceUInt32 reserved[8];
} SceNpCommerce2GetProductInfoResult;

int
sceNpCommerce2GetProductInfoCreateReq(
	SceUInt32 ctxId,
	SceUInt32 *reqId
	);
int
sceNpCommerce2GetProductInfoStart(
	SceUInt32 reqId,
	const char *categoryId,
	const char *productId
	);
int
sceNpCommerce2GetProductInfoGetResult(
	SceUInt32 reqId,
	void *buf,
	SceSize bufSize,
	SceSize *fillSize
	);
int
sceNpCommerce2InitGetProductInfoResult(
	SceNpCommerce2GetProductInfoResult *result,
	void *data,
	SceSize dataSize
	);
int
sceNpCommerce2DestroyGetProductInfoResult(
	SceNpCommerce2GetProductInfoResult *result
	);
int
sceNpCommerce2GetGameProductInfo(
	const SceNpCommerce2GetProductInfoResult *result,
	SceNpCommerce2GameProductInfo *gameProductInfo
	);
int
sceNpCommerce2GetContentRatingInfoFromGameProductInfo(
	const SceNpCommerce2GameProductInfo *gameProductInfo,
	SceNpCommerce2ContentRatingInfo *contentRatingInfo
	);

/*
 * GetProductInfoList
 */
#define SCE_NP_COMMERCE2_GETPRODLIST_MAX_COUNT 60

typedef struct SceNpCommerce2GetProductInfoListResult_
{
	SceNpCommerce2CommonData commonData;

	/* value */
	unsigned int countOfProductInfo;
	SceUInt32 reserved[8];
} SceNpCommerce2GetProductInfoListResult;

int
sceNpCommerce2GetProductInfoListCreateReq(
	SceUInt32 ctxId,
	SceUInt32 *reqId
	);
int
sceNpCommerce2GetProductInfoListStart(
	SceUInt32 reqId,
	const char *productIds[],
	SceUInt32 productNum
	);
int
sceNpCommerce2GetProductInfoListGetResult(
	SceUInt32 reqId,
	void *buf,
	SceSize bufSize,
	SceSize *fillSize
	);
int
sceNpCommerce2InitGetProductInfoListResult(
	SceNpCommerce2GetProductInfoListResult *result,
	void *data,
	SceSize dataSize
	);
int
sceNpCommerce2DestroyGetProductInfoListResult(
	SceNpCommerce2GetProductInfoListResult *result
	);
int
sceNpCommerce2GetGameProductInfoFromGetProductInfoListResult(
	const SceNpCommerce2GetProductInfoListResult *result,
	unsigned int idx,
	SceNpCommerce2GameProductInfo *gameProductInfo
	);

/*
 * Store Check
 */
#define SCE_NP_COMMERCE2_STORE_CHECK_TYPE_CATEGORY        1

#define SCE_NP_COMMERCE2_STORE_IS_EMPTY      1
#define SCE_NP_COMMERCE2_STORE_IS_NOT_EMPTY  0

int
sceNpCommerce2StartEmptyStoreCheck(
	int storeCheckType,    /* SCE_NP_COMMERCE2_STORE_CHECK_TYPE_XXX */
	const char *targetId,
	void *buf,
	SceSize bufLen,
	int *isEmpty           /* SCE_NP_COMMERCE2_STORE_IS_XXX */
	);
int
sceNpCommerce2StopEmptyStoreCheck(
	void
	);

/* Show/Hide Icon */

#define SCE_NP_COMMERCE2_ICON_DISP_LEFT    0
#define SCE_NP_COMMERCE2_ICON_DISP_CENTER  1
#define SCE_NP_COMMERCE2_ICON_DISP_RIGHT   2

int
sceNpCommerce2ShowPsStoreIcon(
	int iconDisp   /* SCE_NP_COMMERCE2_ICON_DISP_XXX */
	);
int
sceNpCommerce2HidePsStoreIcon(
	void
	);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_COMMERCE2_H_ */
