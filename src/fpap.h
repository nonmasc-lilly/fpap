#ifndef X__FPAP_H__X
#define X__FPAP_H__X
#include <limits.h>

#if !__STDC__
#	error "This is not a standard C compiler"
#endif

/* define FPAP_types */
typedef unsigned char FPAP_BYTE;
typedef unsigned short FPAP_WORD;
typedef unsigned long FPAP_DWORD;

#define FPAP_BYTE_MAX UCHAR_MAX
#define FPAP_WORD_MAX USHRT_MAX
#define FPAP_DWORD_MAX ULONG_MAX

typedef FPAP_WORD FPAP_COORD;
typedef FPAP_DWORD FPAP_COLOR;
typedef FPAP_BYTE FPAP_BOOL;
enum {
	FPAP_PROPERTY_NULL	= 0x00,
	FPAP_PROPERTY_INPUT	= 0x01,
	FPAP_PROPERTY_INPUT_POP	= 0x02,
	FPAP_PROPERTY_VSYNC	= 0x03,
	FPAP_PROPERTY_ROTATION	= 0x04
}; typedef FPAP_BYTE FPAP_PROPERTY;
enum {
	FPAP_SUCCESS		= 0x00,
	FPAP_NO_WINDOW_SYSTEM	= 0x01,
	FPAP_NO_WINDOW		= 0x02,
	FPAP_WINDOW_CLOSED	= 0x03,
	FPAP_UNDEFINED_PROPERTY	= 0x04,
	FPAP_INACCESSIBLE	= 0x05
}; typedef FPAP_BYTE FPAP_ERROR;
typedef void *FPAP_PTR;
typedef const void *FPAP_CONST_PTR;
typedef FPAP_PTR FPAP_STR;
typedef FPAP_PTR FPAP;

#define FPAP_TRUE 1
#define FPAP_FALSE 0

#define FPAP_BOOL_MIN FPAP_FALSE
#define FPAP_BOOL_MAX FPAP_TRUE

#define FPAP_PTR_MIN 0
/* May be undefined behaviour */
#define FPAP_PTR_MAX (unsigned long)((void*)-1)

#define FPAP_ERROR_MIN 0
#define FPAP_ERROR_MAX FPAP_BYTE_MAX
#define FPAP_PROPERTY_MIN 0
#define FPAP_PROPERTY_MAX FPAP_BYTE_MAX

#define FPAP_COORD_MAX FPAP_DWORD_MAX
#define FPAP_COLOR_MAX FPAP_DWORD_MAX
#define CONST_PTR_MIN FPAP_PTR_MIN
#define CONST_PTR_MAX FPAP_PTR_MAX

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
	FPAP_CONST_PTR value);
FPAP_ERROR fpap_get(FPAP instance, FPAP_PROPERTY property, FPAP_PTR value);

#endif
