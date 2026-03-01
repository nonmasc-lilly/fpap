#include <GLFW/glfw3.h>
#include <GL/gl.h>

static void s_window_size_callback(GLFWwindow *window, int width, int height)
{
        static struct s_fpap *fpap = NULL;

        if(fpap == NULL) {
                fpap = (struct s_fpap *)window;
                return;
        }
        fpap->width = width;
        fpap->height = height;
        glViewport(0, 0, width, height);
}
static FPAP_BOOL s_winsys_init(void)
{
        return !!glfwInit();
}
static S_WINDOW s_create_window(struct s_fpap *fpap, FPAP_WORD width,
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
        if(fpap->flags & FPAP_VSYNC) glfwSwapInterval(1);
        else                         glfwSwapInterval(0);
}
static void s_handle_window_resize(struct s_fpap *fpap)
{
        s_window_size_callback((GLFWwindow*)fpap, 0, 0);
        glfwSetWindowSizeCallback(fpap->window, s_window_size_callback);
}
static void s_window_frame(struct s_fpap *fpap)
{
        glfwSwapBuffers(fpap->window);
        glfwPollEvents();
}
static void s_destroy_window(S_WINDOW window)
{
        glfwDestroyWindow(window);
}
static void s_destroy_winsys(void)
{
        glfwTerminate();
}
