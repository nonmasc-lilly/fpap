#include <stdlib.h>

#include "fpap.h"

#define S_WINDOW void *
struct s_fpap {
        S_WINDOW window;
        FPAP_WORD width, height;
        FPAP_FLAGS flags;
};
#undef S_WINDOW

#include "platform/fpap.c"

FPAP_ERROR fpap_init(FPAP *instance, FPAP_WORD width, FPAP_WORD height,
const char *window_name, FPAP_FLAGS flags)
{
        struct s_fpap *fpap;
        FPAP_COLOR black = 0xFF00FFFF;

        if(!s_winsys_init()) return FPAP_NO_WINDOW_SYSTEM;

        fpap = malloc(sizeof(*fpap));
        fpap->flags = flags;

        fpap->window = s_create_window(fpap, width, height, window_name);
        if(fpap->window == NULL) return FPAP_NO_WINDOW;
        s_window_context(fpap);
        s_handle_window_resize(fpap);

        glViewport(0, 0, width, height);

        glClearColor(0, 0, 0, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(
                GL_TEXTURE_2D,
                0x00,
                0x04,
                1, 1,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                &black
        );
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        *instance = fpap;
        return FPAP_SUCCESS;
}

FPAP_ERROR fpap_frame(FPAP *instance)
{
        struct s_fpap *fpap;

        fpap = *(struct s_fpap **)instance;
        if(glfwWindowShouldClose(fpap->window)) return FPAP_WINDOW_CLOSED;

        s_window_frame(fpap);

        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);

        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f( 0.0, 0.0);
                glVertex2f(  -1.0, 1.0);
        
                glTexCoord2f( 0.0, 1.0);
                glVertex2f(  -1.0,-1.0);
        
                glTexCoord2f( 1.0, 0.0);
                glVertex2f(   1.0, 1.0);
        
                glTexCoord2f( 1.0, 1.0);
                glVertex2f(   1.0,-1.0);
        glEnd();
        glFlush();

        glDisable(GL_TEXTURE_2D);

        return FPAP_SUCCESS;
}

FPAP_ERROR fpap_draw(FPAP *instance, FPAP_COLOR *content, FPAP_WORD width,
FPAP_WORD height) {
        glTexImage2D(
                GL_TEXTURE_2D,
                0x00,
                0x04,
                width, height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                content
        );

        return FPAP_SUCCESS;
}

FPAP_ERROR fpap_term(FPAP *instance)
{
        struct s_fpap *fpap;

        fpap = *(struct s_fpap **)instance;
        s_destroy_window(fpap->window);
        s_destroy_winsys();
        free(fpap);

        return FPAP_SUCCESS;
}
