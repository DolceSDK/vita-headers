#ifndef _DOLCESDK_PSP2_NP_NP_AUTH_H_
#define _DOLCESDK_PSP2_NP_NP_AUTH_H_

#include <psp2/np/np_common.h>

typedef int SceNpAuthRequestId;

/*
 * ----------------------------------------------------------------
 * NP Ticket and Ticket parameter sizes
 * ----------------------------------------------------------------
 */
/* maximum size of NP Ticket */
#define SCE_NP_TICKET_MAX_SIZE			(65536)

/*E size of NP Ticket Serial ID */
#define SCE_NP_TICKET_SERIAL_ID_SIZE	(20)

/*E size of Subject Region */
#define SCE_NP_SUBJECT_REGION_SIZE		(4)

/*E size of Subject Domain */
#define SCE_NP_SUBJECT_DOMAIN_SIZE		(4)

/* size of Service ID */
#define SCE_NP_SERVICE_ID_SIZE			(24)

/* size of Entitlement ID */
#define SCE_NP_ENTITLEMENT_ID_SIZE		(32)

/* maximum size of Cookie Information */
#define SCE_NP_COOKIE_MAX_SIZE			(1024)


/*
 * ----------------------------------------------------------------
 * NP Ticket parameter types and functions
 * ----------------------------------------------------------------
 */
#define SCE_NP_TICKET_PARAM_DATA_LEN	(256)

typedef SceUInt64 SceNpTime;

typedef struct SceNpDate {
	SceUShort16 year;
	SceUChar8 month;
	SceUChar8 day;
} SceNpDate;

typedef union SceNpTicketParam {
	SceInt32	i32;
	SceInt64	i64;
	SceUInt32	u32;
	SceUInt64	u64;
	SceNpDate	date;
	SceUChar8	data[SCE_NP_TICKET_PARAM_DATA_LEN];
} SceNpTicketParam;

#define SCE_NP_TICKET_PARAM_SERIAL_ID			0	/* Binary */
#define SCE_NP_TICKET_PARAM_ISSUER_ID			1	/* SceUInt32 */
#define SCE_NP_TICKET_PARAM_ISSUED_DATE			2	/* SceNpTime */
#define SCE_NP_TICKET_PARAM_EXPIRE_DATE			3	/* SceNpTime */
#define SCE_NP_TICKET_PARAM_SUBJECT_ACCOUNT_ID	4	/* SceUInt64 */
#define SCE_NP_TICKET_PARAM_SUBJECT_ONLINE_ID	5	/* String */
#define SCE_NP_TICKET_PARAM_SUBJECT_REGION		6	/* Binary */
#define SCE_NP_TICKET_PARAM_SUBJECT_DOMAIN		7	/* String */
#define SCE_NP_TICKET_PARAM_SERVICE_ID			8	/* String */
#define SCE_NP_TICKET_PARAM_SUBJECT_STATUS		9	/* SceUInt32 */
#define SCE_NP_TICKET_PARAM_STATUS_DURATION		10	/* SceNpTime */
#define SCE_NP_TICKET_PARAM_SUBJECT_DOB			11	/* SceNpDate */
#define SCE_NP_TICKET_PARAM_MAX					12

#define SCE_NP_SUBJECT_ONLINE_ID_GET_ONLINE_ID(raw, onlineid) do { \
	for (int i=0; i<SCE_NP_ONLINEID_MAX_LENGTH; i++) { \
		(onlineid)->data[i] = (raw)[i]; \
	} \
	(onlineid)->term = '\0'; \
	} while (0)

#define SCE_NP_SUBJECT_STATUS_GET_AGE(u32)			(((u32)>>24)&0x7f)
#define SCE_NP_SUBJECT_STATUS_IS_SUSPENDED(u32)		((u32)&0x80)
#define SCE_NP_SUBJECT_STATUS_IS_CHAT_DISABLED(u32)	((u32)&0x100)
#define SCE_NP_SUBJECT_STATUS_CONTENT_RATING(u32)	((u32)&0x200)

#define SCE_NP_SUBJECT_REGION_GET_COUNTRY_CODE(raw, cc) do { \
	(cc)->data[0] = *((char *)(raw)); \
	(cc)->data[1] = *((char *)(raw)+1); \
	(cc)->term = '\0'; \
	} while (0)
#define SCE_NP_SUBJECT_REGION_GET_LANGUAGE_CODE(raw) (*((SceUChar8 *)(raw)+3))

#define SCE_NP_AUTH_LATEST_TICKET_VERSION_MAJOR		3
#define SCE_NP_AUTH_LATEST_TICKET_VERSION_MINOR		0

typedef struct SceNpTicketVersion {
	unsigned short major;
	unsigned short minor;
} SceNpTicketVersion;

/* AUTH request callback */
typedef int (*SceNpAuthCallback)(
	SceNpAuthRequestId id,
	int result,
	void *arg	/* user argument */
	);

typedef struct SceNpAuthRequestParameter {
	SceSize size;
	SceNpTicketVersion version;
	const char *serviceId;
	const void *cookie;
	SceSize cookieSize;
	const char *entitlementId;
	SceUInt32 consumedCount;
	SceNpAuthCallback ticketCb;
	void *cbArg;
} SceNpAuthRequestParameter;


/*
 * ----------------------------------------------------------------
 * NP Entitlement types and functions
 * ----------------------------------------------------------------
 */
typedef struct SceNpEntitlementId {
	unsigned char data[SCE_NP_ENTITLEMENT_ID_SIZE];
} SceNpEntitlementId;

/* SceNpEntitlementType */
#define SCE_NP_ENTITLEMENT_TYPE_NON_CONSUMABLE	0
#define SCE_NP_ENTITLEMENT_TYPE_CONSUMABLE		1

typedef struct SceNpEntitlement {
	SceNpEntitlementId id;
	SceNpTime createdDate;
	SceNpTime expireDate;
	SceUInt32 type;
	SceInt32 remainingCount;  /* may be negative */
	SceUInt32 consumedCount;
	char padding[4];
} SceNpEntitlement;


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int
sceNpAuthInit(
	void
	);

int
sceNpAuthTerm(
	void
	);


int
sceNpAuthCreateStartRequest(
	const SceNpAuthRequestParameter *param
	);

int
sceNpAuthDestroyRequest(
	SceNpAuthRequestId id
	);

int
sceNpAuthAbortRequest(
	SceNpAuthRequestId id
	);

int
sceNpAuthGetTicket(
	SceNpAuthRequestId id,
	void *buf,
	SceSize len
	);

int
sceNpAuthGetTicketParam(
	const unsigned char *ticket,
	SceSize ticketSize,
	int paramId,
	union SceNpTicketParam *param
	);
int
sceNpAuthGetEntitlementIdList(
	const unsigned char *ticket,
	SceSize ticketSize,
	SceNpEntitlementId *entIdList,
	SceSize entIdListNum
	);
int
sceNpAuthGetEntitlementById(
	const unsigned char *ticket,
	SceSize ticketSize,
	const char *entId,
	SceNpEntitlement *ent
	);

#define sceNpAuthCheckEntitlementById(ticket, ticketSize, entId) \
	sceNpAuthGetEntitlementById((ticket), (ticketSize), (entId), NULL)

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_NP_NP_AUTH_H_ */
