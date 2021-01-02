#ifndef _DOLCESDK_PSP2_LIBIME_LIBIME_API_H_
#define _DOLCESDK_PSP2_LIBIME_LIBIME_API_H_

#include <psp2/kernel/clib.h>
#include <psp2/sdk_version.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SCE_IME_MAX_PREEDIT_LENGTH      30
#define SCE_IME_MAX_TEXT_LENGTH        2048


#define SCE_IME_LANGUAGE_DANISH               0x00000001ULL
#define SCE_IME_LANGUAGE_GERMAN               0x00000002ULL
#define SCE_IME_LANGUAGE_ENGLISH_US           0x00000004ULL
#define SCE_IME_LANGUAGE_SPANISH              0x00000008ULL
#define SCE_IME_LANGUAGE_FRENCH               0x00000010ULL
#define SCE_IME_LANGUAGE_ITALIAN              0x00000020ULL
#define SCE_IME_LANGUAGE_DUTCH                0x00000040ULL
#define SCE_IME_LANGUAGE_NORWEGIAN            0x00000080ULL
#define SCE_IME_LANGUAGE_POLISH               0x00000100ULL
#define SCE_IME_LANGUAGE_PORTUGUESE_PT        0x00000200ULL
#define SCE_IME_LANGUAGE_RUSSIAN              0x00000400ULL
#define SCE_IME_LANGUAGE_FINNISH              0x00000800ULL
#define SCE_IME_LANGUAGE_SWEDISH              0x00001000ULL
#define SCE_IME_LANGUAGE_JAPANESE             0x00002000ULL
#define SCE_IME_LANGUAGE_KOREAN               0x00004000ULL
#define SCE_IME_LANGUAGE_SIMPLIFIED_CHINESE   0x00008000ULL
#define SCE_IME_LANGUAGE_TRADITIONAL_CHINESE  0x00010000ULL
#define SCE_IME_LANGUAGE_PORTUGUESE_BR        0x00020000ULL
#define SCE_IME_LANGUAGE_ENGLISH_GB           0x00040000ULL
#define SCE_IME_LANGUAGE_TURKISH              0x00080000ULL



#define SCE_IME_TYPE_DEFAULT             0
#define SCE_IME_TYPE_BASIC_LATIN         1
#define SCE_IME_TYPE_NUMBER              2
#define SCE_IME_TYPE_EXTENDED_NUMBER     3
#define SCE_IME_TYPE_URL                 4
#define SCE_IME_TYPE_MAIL                5



#define SCE_IME_ENTER_LABEL_DEFAULT 0
#define SCE_IME_ENTER_LABEL_SEND    1
#define SCE_IME_ENTER_LABEL_SEARCH  2
#define SCE_IME_ENTER_LABEL_GO      3

/**
 * Enable multiline text input.
 * This option can NOT be used for libime.
 */
#define SCE_IME_OPTION_MULTILINE               0x01

/**
 * Disable auto capitalization.
  */
#define SCE_IME_OPTION_NO_AUTO_CAPITALIZATION  0x02

/**
 * Disable the function to assist text input such as predictive text and converted text.
 */
#define SCE_IME_OPTION_NO_ASSISTANCE           0x04


/**
 * IME was opened.
 */
#define SCE_IME_EVENT_OPEN             0

/**
 * The text was updated
 */
#define SCE_IME_EVENT_UPDATE_TEXT      1

/**
 * The caret index was updated.
 */
#define SCE_IME_EVENT_UPDATE_CARET     2

/**
 * The size which IME covers was changed.
 */
#define SCE_IME_EVENT_CHANGE_SIZE      3

/**
* The close button was pressed.
*/
#define SCE_IME_EVENT_PRESS_CLOSE      4

/**
* The enter button was pressed.
*/
#define SCE_IME_EVENT_PRESS_ENTER      5


/**
 * The work buffer size
 */
#define SCE_IME_WORK_BUFFER_SIZE      (20*1024)


/**
 * The IME text filter.
 */
typedef SceInt32 (*SceImeTextFilter)(
	SceWChar16 *outText, SceUInt32 *outTextLength,
	const SceWChar16 *srcText, SceUInt32 srcTextLength);

typedef struct
{
	SceUInt32 x;
	SceUInt32 y;
	SceUInt32 width;
	SceUInt32 height;
} SceImeRect;

typedef struct
{
	SceUInt32 preeditIndex;  ///< The preedit length in the preedit.
	SceUInt32 preeditLength; ///< The length of the preedit.
	SceUInt32 caretIndex;    ///< The current caret index

	/// The NULL terminated string being edited.
	/// The maximum length of this string is SCE_MAX_PREEDIT_LENGTH + maxTextLength
	SceWChar16 *str;

	SceUInt32 editIndex;       // The index where the editing operation is done
	SceInt32 editLengthChange; // The change in the text length by editing operation
} SceImeEditText;


typedef union
{
	SceImeRect rect;
	SceImeEditText text;
	SceUInt32 caretIndex;
	SceUChar8 reserved[40];
} SceImeEventParam;

/**
 * The IME event struct.
 */
typedef struct
{
	SceUInt32 id;            ///< The IME event ID.
	SceImeEventParam param;
} SceImeEvent;


typedef struct
{
	SceUInt32 x;
	SceUInt32 y;
	SceUInt32 height;
	SceUInt32 index;
} SceImeCaret;

typedef struct
{
	SceUInt32 x;
	SceUInt32 y;
	SceUInt32 height;
} SceImePreeditGeometry;

typedef void (*SceImeEventHandler)(void* arg, const SceImeEvent *e);


/**
 * The parameter struct for sceImeOpen.
 */
typedef struct
{
	SceUInt32 sdkVersion;           ///< The sdk version

	/// The input method. This field is not used for the current release and must be zero.
	SceUInt32 inputMethod;
	SceUInt64 supportedLanguages;
	SceBool languagesForced;
	SceUInt32 type;
	SceUInt32 option;

	void *work;
	void *arg;
	SceImeEventHandler handler;
	SceImeTextFilter filter;        ///< The text filter.

	SceWChar16 *initialText;        ///< The initial text.
	SceUInt32 maxTextLength;        ///< The maximum length of edit string.

	/// The buffer used when editing.
	/// The length of the buffer must be SCE_IME_MAX_PREEDIT_LENGTH + maxTextLength + 1.
	SceWChar16 *inputTextBuffer;

	SceUChar8 enterLabel;
	SceUChar8 reserved[7];
} SceImeParam;



static inline
void sceImeParamInit(SceImeParam *param)
{
	sceClibMemset(param, 0x0, sizeof(SceImeParam));
	param->sdkVersion = SCE_PSP2_SDK_VERSION;
}

/**
 * Open IME.
 */
SceInt32 sceImeOpen(const SceImeParam *param);

/**
 * Update IME.
 */
SceInt32 sceImeUpdate(void);


/**
 * Set text.
 */
SceInt32 sceImeSetText(const SceWChar16 *text, SceUInt32 length);

/**
 * Set the index and the geometry parameter of the caret.
 *
 * The caret index may not be what is specified by the parameter according to the input method such as languages.
 */
SceInt32 sceImeSetCaret(const SceImeCaret *caret);

SceInt32 sceImeSetPreeditGeometry(const SceImePreeditGeometry *preedit);

/**
 * Close IME.
 */
SceInt32 sceImeClose(void);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _DOLCESDK_PSP2_LIBIME_LIBIME_API_H_ */
