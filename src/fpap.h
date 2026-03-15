#ifndef X__FPAP_H__X
#define X__FPAP_H__X
#include <limits.h>

typedef unsigned short FPAP_ERROR;
#define FPAP_SUCCESS 0
#define FPAP_NO_WINDOW_SYSTEM 1
#define FPAP_NO_WINDOW 2
#define FPAP_WINDOW_CLOSED 3

typedef unsigned char  FPAP_BYTE;
#if USHRT_MAX == 0xFFFF
typedef unsigned short FPAP_WORD;
#elif UINT_MAX == 0xFFFF
typedef unsigned int FPAP_WORD;
#endif
#if USHRT_MAX == 0xFFFFFFFF
typedef unsigned short FPAP_DWORD;
#elif UINT_MAX == 0xFFFFFFFF
typedef unsigned int FPAP_DWORD;
#elif ULONG_MAX == 0xFFFFFFFF
typedef unsigned long FPAP_DWORD;
#endif

typedef FPAP_BYTE FPAP_BOOL;
#define FPAP_TRUE 1
#define FPAP_FALSE 0
typedef FPAP_DWORD FPAP_COLOR;

typedef unsigned long FPAP_FLAGS;
#define FPAP_VSYNC 1

#define FPAP_FRAME_SERIAL 0xFFFFFFFF

typedef void *FPAP; /* Implementation defined */

typedef enum {
	FPAP_PAGESIZE, /* An FPAP_WORD determining how large a page is */

	FPAP_PROPERTY__MAX
} FPAP_PROPERTY;

FPAP_ERROR fpap_init(
  FPAP *instance,
  FPAP_WORD width,
  FPAP_WORD height,
  const char *window_name,
  FPAP_FLAGS flags
);
FPAP_ERROR fpap_frame(FPAP *instance);
FPAP_ERROR fpap_draw(
  FPAP *instance,
  FPAP_COLOR *content,
  FPAP_WORD width,
  FPAP_WORD height
);
FPAP_ERROR fpap_set(FPAP *instance, FPAP_PROPERTY property, const void *value);
FPAP_ERROR fpap_get(FPAP *instance, FPAP_PROPERTY property, void *value);
/* Poll for input, gets Null delimited list of all current input in order. */
FPAP_ERROR fpap_poll(FPAP *instance, const char **input);
FPAP_ERROR fpap_term(FPAP *instance);

#endif
