#include <stdlib.h>

#include "fpap.h"

struct s_fpap {
	void *window;
	FPAP_WORD width, height;
	FPAP_BOOL vsync;
};
#include "platform/fpap.c"

FPAP_ERROR fpap_init(FPAP *instance, FPAP_COORD width, FPAP_COORD height,
FPAP_STR name)
{
	struct s_fpap *fpap;
	FPAP_COLOR black = 0xFF000000;

	if (!s_winsys_init())
		return FPAP_NO_WINDOW_SYSTEM;

	fpap = malloc(sizeof(*fpap));
	fpap->window = s_create_window(fpap, width, height, name);
	if (fpap->window == NULL)
		return FPAP_NO_WINDOW;
	s_window_context(fpap);
	s_handle_window_resize(fpap);

	glViewport(0, 0, width, height);

	glClearColor(0, 0, 0, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0x00, 0x04, 1, 1, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, &black);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	*instance = fpap;
	return FPAP_SUCCESS;
}

FPAP_ERROR fpap_frame(FPAP instance)
{
	struct s_fpap *fpap;

	fpap = (struct s_fpap *)instance;
	if (glfwWindowShouldClose(fpap->window))
		return FPAP_WINDOW_CLOSED;

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

FPAP_ERROR fpap_draw(FPAP instance, FPAP_COLOR *content, FPAP_COORD width,
FPAP_COORD height)
{
	glTexImage2D(GL_TEXTURE_2D, 0x00, 0x04, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, content);

	return FPAP_SUCCESS;
}

FPAP_ERROR fpap_term(FPAP instance)
{
	struct s_fpap *fpap;

	fpap = (struct s_fpap *)instance;
	s_destroy_window(fpap->window);
	s_destroy_winsys();
	free(fpap);

	return FPAP_SUCCESS;
}

FPAP_ERROR fpap_set(FPAP instance, FPAP_PROPERTY property,
const FPAP_PTR value)
{
	struct s_fpap *fpap;

	fpap = (struct s_fpap *)instance;
	switch (property) {
	case FPAP_PROPERTY_VSYNC:
		fpap->vsync = *(FPAP_BOOL *)value;
		break;
	default:
		return FPAP_UNDEFINED_PROPERTY;
	}
	return FPAP_SUCCESS;
}

FPAP_ERROR fpap_get(FPAP instance, FPAP_PROPERTY property, FPAP_PTR value)
{
	struct s_fpap *fpap;

	fpap = (struct s_fpap *)instance;
	switch (property) {
	case FPAP_PROPERTY_VSYNC:
		*(FPAP_BOOL *)value = fpap->vsync;
		break;
	default:
		return FPAP_UNDEFINED_PROPERTY;
	}
	return FPAP_SUCCESS;
}
