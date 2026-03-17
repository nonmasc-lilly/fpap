#include <string.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

char s_key(FPAP_BYTE *page, int glfw_key, int mods)
{
	switch (glfw_key) {
	case GLFW_KEY_SPACE:
		return ' ';
	case GLFW_KEY_APOSTROPHE:
		if (mods & GLFW_MOD_SHIFT)
			return '\"';
		return '\'';
	case GLFW_KEY_COMMA:
		if (mods & GLFW_MOD_SHIFT)
			return '<';
		return ',';
	case GLFW_KEY_MINUS:
		if (mods & GLFW_MOD_SHIFT)
			return '_';
		return '-';
	case GLFW_KEY_PERIOD:
		if (mods & GLFW_MOD_SHIFT)
			return '>';
		return '.';
	case GLFW_KEY_SLASH:
		if (mods & GLFW_MOD_SHIFT)
			return '?';
		return '/';
	case GLFW_KEY_LEFT_BRACKET:
		if (mods & GLFW_MOD_SHIFT)
			return '{';
		return '[';
	case GLFW_KEY_BACKSLASH:
		if (mods & GLFW_MOD_SHIFT)
			return '|';
		return '\\';
	case GLFW_KEY_RIGHT_BRACKET:
		if (mods & GLFW_MOD_SHIFT)
			return '}';
		return ']';
	case GLFW_KEY_GRAVE_ACCENT:
		if (mods & GLFW_MOD_SHIFT)
			return '~';
		return '`';

	case GLFW_KEY_ESCAPE:
		return '\x1B';
	case GLFW_KEY_ENTER:
		return '\x0D';
	case GLFW_KEY_TAB:
		return '\x09';
	case GLFW_KEY_BACKSPACE:
		return '\x08';

	case GLFW_KEY_LEFT:
		*page = 1;
		return 'A';
	case GLFW_KEY_RIGHT:
		*page = 1;
		return 'D';
	case GLFW_KEY_UP:
		*page = 1;
		return 'W';
	case GLFW_KEY_DOWN:
		*page = 1;
		return 'S';

	case GLFW_KEY_DELETE:
		return '\x7F';

	case GLFW_KEY_F1:
	case GLFW_KEY_F2:
	case GLFW_KEY_F3:
	case GLFW_KEY_F4:
	case GLFW_KEY_F5:
	case GLFW_KEY_F6:
	case GLFW_KEY_F7:
	case GLFW_KEY_F8:
	case GLFW_KEY_F9:
	case GLFW_KEY_F10:
	case GLFW_KEY_F11: case GLFW_KEY_F12:
	case GLFW_KEY_F13:
	case GLFW_KEY_F14:
	case GLFW_KEY_F15:
	case GLFW_KEY_F16:
	case GLFW_KEY_F17:
	case GLFW_KEY_F18:
	case GLFW_KEY_F19:
	case GLFW_KEY_F20:
	case GLFW_KEY_F21:
	case GLFW_KEY_F22:
	case GLFW_KEY_F23:
	case GLFW_KEY_F24:
	case GLFW_KEY_F25:
		*page = 1;
		return '0' + (glfw_key - GLFW_KEY_F1);

	case GLFW_KEY_0:
		if (mods & GLFW_MOD_SHIFT)
			return ')';
		return '0';
	case GLFW_KEY_1:
		if (mods & GLFW_MOD_SHIFT)
			return '!';
		return '1';
	case GLFW_KEY_2:
		if (mods & GLFW_MOD_SHIFT)
			return '@';
		return '2';
	case GLFW_KEY_3:
		if (mods & GLFW_MOD_SHIFT)
			return '#';
		return '3';
	case GLFW_KEY_4:
		if (mods & GLFW_MOD_SHIFT)
			return '$';
		return '4';
	case GLFW_KEY_5:
		if (mods & GLFW_MOD_SHIFT)
			return '%';
		return '5';
	case GLFW_KEY_6:
		if (mods & GLFW_MOD_SHIFT)
			return '^';
		return '6';
	case GLFW_KEY_7:
		if (mods & GLFW_MOD_SHIFT)
			return '&';
		return '7';
	case GLFW_KEY_8:
		if (mods & GLFW_MOD_SHIFT)
			return '*';
		return '8';
	case GLFW_KEY_9:
		if (mods & GLFW_MOD_SHIFT)
			return '(';
		return '9';
	case GLFW_KEY_SEMICOLON:
		if (mods & GLFW_MOD_SHIFT)
			return ':';
		return ';';
	case GLFW_KEY_EQUAL:
		if (mods & GLFW_MOD_SHIFT)
			return '+';
		return '=';
	case GLFW_KEY_A:
		if (mods & GLFW_MOD_CONTROL)
			return '\x01';
		else if (mods & GLFW_MOD_SHIFT)
			return 'A';
		return 'a';
	case GLFW_KEY_B:
		if (mods & GLFW_MOD_CONTROL)
			return '\x02';
		else if (mods & GLFW_MOD_SHIFT)
			return 'B';
		return 'b';
	case GLFW_KEY_C:
		if (mods & GLFW_MOD_CONTROL)
			return '\x03';
		else if (mods & GLFW_MOD_SHIFT)
			return 'C';
		return 'c';
	case GLFW_KEY_D:
		if (mods & GLFW_MOD_CONTROL)
			return '\x04';
		else if (mods & GLFW_MOD_SHIFT)
			return 'D';
		return 'd';
	case GLFW_KEY_E:
		if (mods & GLFW_MOD_CONTROL)
			return '\x05';
		else if (mods & GLFW_MOD_SHIFT)
			return 'E';
		return 'e';
	case GLFW_KEY_F:
		if (mods & GLFW_MOD_CONTROL)
			return '\x06';
		else if (mods & GLFW_MOD_SHIFT)
			return 'F';
		return 'f';
	case GLFW_KEY_G:
		if (mods & GLFW_MOD_CONTROL)
			return '\x07';
		else if (mods & GLFW_MOD_SHIFT)
			return 'G';
		return 'g';
	case GLFW_KEY_H:
		if (mods & GLFW_MOD_CONTROL)
			return '\x08';
		else if (mods & GLFW_MOD_SHIFT)
			return 'H';
		return 'h';
	case GLFW_KEY_I:
		if (mods & GLFW_MOD_CONTROL)
			return '\x09';
		else if (mods & GLFW_MOD_SHIFT)
			return 'I';
		return 'i';
	case GLFW_KEY_J:
		if (mods & GLFW_MOD_CONTROL)
			return '\x0A';
		else if (mods & GLFW_MOD_SHIFT)
			return 'J';
		return 'j';
	case GLFW_KEY_K:
		if (mods & GLFW_MOD_CONTROL)
			return '\x0B';
		else if (mods & GLFW_MOD_SHIFT)
			return 'K';
		return 'k';
	case GLFW_KEY_L:
		if (mods & GLFW_MOD_CONTROL)
			return '\x0C';
		else if (mods & GLFW_MOD_SHIFT)
			return 'L';
		return 'l';
	case GLFW_KEY_M:
		if (mods & GLFW_MOD_CONTROL)
			return '\x0D';
		else if (mods & GLFW_MOD_SHIFT)
			return 'M';
		return 'm';
	case GLFW_KEY_N:
		if (mods & GLFW_MOD_CONTROL)
			return '\x0E';
		else if (mods & GLFW_MOD_SHIFT)
			return 'N';
		return 'n';
	case GLFW_KEY_O:
		if (mods & GLFW_MOD_CONTROL)
			return '\x0F';
		else if (mods & GLFW_MOD_SHIFT)
			return 'O';
		return 'o';
	case GLFW_KEY_P:
		if (mods & GLFW_MOD_CONTROL)
			return '\x10';
		else if (mods & GLFW_MOD_SHIFT)
			return 'P';
		return 'p';
	case GLFW_KEY_Q:
		if (mods & GLFW_MOD_CONTROL)
			return '\x11';
		else if (mods & GLFW_MOD_SHIFT)
			return 'Q';
		return 'q';
	case GLFW_KEY_R:
		if (mods & GLFW_MOD_CONTROL)
			return '\x12';
		else if (mods & GLFW_MOD_SHIFT)
			return 'R';
		return 'r';
	case GLFW_KEY_S:
		if (mods & GLFW_MOD_CONTROL)
			return '\x13';
		else if (mods & GLFW_MOD_SHIFT)
			return 'S';
		return 's';
	case GLFW_KEY_T:
		if (mods & GLFW_MOD_CONTROL)
			return '\x14';
		else if (mods & GLFW_MOD_SHIFT)
			return 'T';
		return 't';
	case GLFW_KEY_U:
		if (mods & GLFW_MOD_CONTROL)
			return '\x15';
		else if (mods & GLFW_MOD_SHIFT)
			return 'U';
		return 'u';
	case GLFW_KEY_V:
		if (mods & GLFW_MOD_CONTROL)
			return '\x16';
		else if (mods & GLFW_MOD_SHIFT)
			return 'V';
		return 'v';
	case GLFW_KEY_W:
		if (mods & GLFW_MOD_CONTROL)
			return '\x17';
		else if (mods & GLFW_MOD_SHIFT)
			return 'W';
		return 'w';
	case GLFW_KEY_X:
		if (mods & GLFW_MOD_CONTROL)
			return '\x18';
		else if (mods & GLFW_MOD_SHIFT)
			return 'X';
		return 'x';
	case GLFW_KEY_Y:
		if (mods & GLFW_MOD_CONTROL)
			return '\x19';
		else if (mods & GLFW_MOD_SHIFT)
			return 'Y';
		return 'y';
	case GLFW_KEY_Z:
		if (mods & GLFW_MOD_CONTROL)
			return '\x1A';
		else if (mods & GLFW_MOD_SHIFT)
			return 'Z';
		return 'z';
	default:
		return '\0';
	}
}

static void s_window_size_callback(GLFWwindow *window, int width, int height)
{
	static struct s_fpap *fpap = NULL;

	if (fpap == NULL) {
		fpap = (struct s_fpap *)window;
		return;
	}
	fpap->width = width;
	fpap->height = height;
	glViewport(0, 0, width, height);
}
static void s_window_key_callback(GLFWwindow *window, int key, int scancode,
int action, int mods)
{
	static struct s_fpap *fpap = NULL;
	struct s_input_event *event;

	if (fpap == NULL) {
		fpap = (struct s_fpap *)window;
		return;
	}

	event = fpap->input.content + fpap->input.top;
	event->character = s_key(&event->page, key, mods);
	if (event->character == '\0')
		memset(event, 0, sizeof(*event));
	else
		event->pressed = action == GLFW_PRESS || action == GLFW_REPEAT;

	fpap->input.top += 1;
	if (fpap->input.top >= fpap->input.capacity)
		fpap->input.top = 0;
}
static FPAP_BOOL s_winsys_init(void)
{
	return !!glfwInit();
}
static void *s_create_window(struct s_fpap *fpap, FPAP_WORD width,
FPAP_WORD height, const char *window_name)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	return glfwCreateWindow(width, height, window_name, NULL, NULL);
}
static void s_window_context(struct s_fpap *fpap)
{
	glfwMakeContextCurrent(fpap->window);
	if (fpap->vsync)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);
}
static void s_handle_window_resize(struct s_fpap *fpap)
{
	s_window_size_callback((GLFWwindow*)fpap, 0, 0);
	glfwSetWindowSizeCallback(fpap->window, s_window_size_callback);
}
static void s_handle_window_input(struct s_fpap *fpap)
{
	s_window_key_callback((GLFWwindow*)fpap, 0, 0, 0, 0);
	glfwSetKeyCallback(fpap->window, s_window_key_callback);
}
static void s_window_frame(struct s_fpap *fpap)
{
	glfwSwapBuffers(fpap->window);
	glfwPollEvents();
}
static void s_destroy_window(void *window)
{
	glfwDestroyWindow(window);
}
static void s_destroy_winsys(void)
{
	glfwTerminate();
}
