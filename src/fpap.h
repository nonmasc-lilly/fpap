#ifndef X__FPAP_H__X
#define X__FPAP_H__X
#include <limits.h>

/* define FPAP_types*/
typedef unsigned char FPAP_BYTE;
#if USHRT_MAX >= (UCHAR_MAX * UCHAR_MAX)
	typedef unsigned short FPAP_WORD;
#elif UINT_MAX >= (UCHAR_MAX * UCHAR_MAX)
	typedef unsigned int FPAP_WORD;
#elif ULONG_MAX >= (UCHAR_MAX * UCHAR_MAX)
	typedef unsigned long FPAP_WORD;
#endif
#if USHRT_MAX >= (UCHAR_MAX * UCHAR_MAX * UCHAR_MAX * UCHAR_MAX)
	typedef unsigned short FPAP_DWORD;
#elif UINT_MAX >= (UCHAR_MAX * UCHAR_MAX * UCHAR_MAX * UCHAR_MAX)
	typedef unsigned int FPAP_DWORD;
#elif ULONG_MAX >= (UCHAR_MAX * UCHAR_MAX * UCHAR_MAX * UCHAR_MAX)
	typedef unsigned long FPAP_DWORD;
#endif
typedef FPAP_WORD FPAP_COORD;
typedef FPAP_DWORD FPAP_COLOR;
typedef FPAP_BYTE FPAP_BOOL;
typedef enum {
	FPAP_PROPERTY_NULL,
	FPAP_PROPERTY_INPUT,
	FPAP_PROPERTY_INPUT_POP,
	FPAP_PROPERTY_VSYNC
} FPAP_PROPERTY;
typedef enum {
	FPAP_SUCCESS,
	FPAP_NO_WINDOW_SYSTEM,
	FPAP_NO_WINDOW,
	FPAP_WINDOW_CLOSED,
	FPAP_UNDEFINED_PROPERTY,
	FPAP_INACCESSIBLE
} FPAP_ERROR;
typedef void *FPAP_PTR;
typedef FPAP_PTR FPAP_STR;
typedef FPAP_PTR FPAP;

#define FPAP_TRUE 1
#define FPAP_FALSE 0

struct fpap_ext_input_event {
	char character;
	FPAP_BYTE page;
	FPAP_BOOL pressed;
};

FPAP_ERROR fpap_init(FPAP *instance, FPAP_COORD width, FPAP_COORD height,
	FPAP_STR name);
FPAP_ERROR fpap_term(FPAP instance);
FPAP_ERROR fpap_frame(FPAP instance);
FPAP_ERROR fpap_draw(FPAP instance, FPAP_COLOR *content, FPAP_COORD width,
	FPAP_COORD height);
FPAP_ERROR fpap_set(FPAP instance, FPAP_PROPERTY property,
	const FPAP_PTR value);
FPAP_ERROR fpap_get(FPAP instance, FPAP_PROPERTY property, FPAP_PTR value);

#endif
