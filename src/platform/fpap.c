typedef void *S_WINDOW;

static FPAP_BOOL s_winsys_init(void);
static S_WINDOW s_create_window(
  struct s_fpap *fpap,
  FPAP_WORD width,
  FPAP_WORD height,
  const char *name
);
static void s_window_context(struct s_fpap *fpap);
static void s_handle_window_resize(struct s_fpap *fpap);
static void s_window_frame(struct s_fpap *fpap);
static void s_destroy_window(S_WINDOW window);
static void s_destroy_winsys(void);


#if defined WIN_GLFW
#include "glfw.c"
#elif defined WIN_XLIB
#include "xlib.c"
#else
#error "unimplemented platform"
#endif


