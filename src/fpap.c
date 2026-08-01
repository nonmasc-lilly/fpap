#include <stdlib.h>

#include "fpap.h"

struct s_input_event {
	char character;
	FPAP_BYTE page;
	FPAP_BOOL pressed;
};

struct s_fpap {
	void *window;
	struct {
		struct s_input_event *content;
		FPAP_DWORD capacity, top;
	} input;
	FPAP_WORD width, height;
	FPAP_BYTE rotation;
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

	fpap = calloc(1,sizeof(*fpap));
	fpap->input.capacity = 0x100;
	fpap->input.top = 0;
	fpap->input.content = calloc(1, fpap->input.capacity);
	fpap->rotation = 0;

	fpap->window = s_create_window(fpap, width, height, name);
	if (fpap->window == NULL)
		return FPAP_NO_WINDOW;
	s_window_context(fpap);
	s_handle_window_resize(fpap);
	s_handle_window_input(fpap);

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
	float tex_coords[4 * 2];

	fpap = (struct s_fpap *)instance;
	if (glfwWindowShouldClose(fpap->window))
		return FPAP_WINDOW_CLOSED;

	s_window_frame(fpap);

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	#define TX_0x 0.0
	#define TX_0y 0.0
	#define TX_1x 0.0
	#define TX_1y 1.0
	#define TX_2x 1.0
	#define TX_2y 0.0
	#define TX_3x 1.0
	#define TX_3y 1.0
	switch (fpap->rotation & 0x03) {
	default:
	case 0:
		tex_coords[0] = TX_0x;
		tex_coords[1] = TX_0y;

		tex_coords[2] = TX_1x;
		tex_coords[3] = TX_1y;

		tex_coords[4] = TX_2x;
		tex_coords[5] = TX_2y;

		tex_coords[6] = TX_3x;
		tex_coords[7] = TX_3y;
		break;
	case 1:
		tex_coords[0] = TX_1x;
		tex_coords[1] = TX_1y;

		tex_coords[2] = TX_3x;
		tex_coords[3] = TX_3y;

		tex_coords[4] = TX_0x;
		tex_coords[5] = TX_0y;

		tex_coords[6] = TX_2x;
		tex_coords[7] = TX_2y;
		break;
	case 2:
		tex_coords[0] = TX_3x;
		tex_coords[1] = TX_3y;

		tex_coords[2] = TX_2x;
		tex_coords[3] = TX_2y;

		tex_coords[4] = TX_1x;
		tex_coords[5] = TX_1y;

		tex_coords[6] = TX_0x;
		tex_coords[7] = TX_0y;
		break;
	case 3:
		tex_coords[0] = TX_2x;
		tex_coords[1] = TX_2y;

		tex_coords[2] = TX_0x;
		tex_coords[3] = TX_0y;

		tex_coords[4] = TX_3x;
		tex_coords[5] = TX_3y;

		tex_coords[6] = TX_1x;
		tex_coords[7] = TX_1y;
		break;
	}

	glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(tex_coords[0], tex_coords[1]);
		glVertex2f(  -1.0, 1.0);
	
		glTexCoord2f(tex_coords[2], tex_coords[3]);
		glVertex2f(  -1.0,-1.0);
	
		glTexCoord2f(tex_coords[4], tex_coords[5]);
		glVertex2f(   1.0, 1.0);
	
		glTexCoord2f(tex_coords[6], tex_coords[7]);
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
	case FPAP_PROPERTY_ROTATION:
		fpap->rotation = *(FPAP_BYTE*)value;
		break;
	default:
		return FPAP_UNDEFINED_PROPERTY;
	}
	return FPAP_SUCCESS;
}

FPAP_ERROR fpap_get(FPAP instance, FPAP_PROPERTY property, FPAP_PTR value)
{
	struct s_fpap *fpap;
	struct s_input_event *event;
	struct fpap_ext_input_event *value_input;

	fpap = (struct s_fpap *)instance;
	switch (property) {
	case FPAP_PROPERTY_VSYNC:
		*(FPAP_BOOL *)value = fpap->vsync;
		break;
	case FPAP_PROPERTY_INPUT:
	case FPAP_PROPERTY_INPUT_POP:
		if (fpap->input.top == 0)
			event = fpap->input.content + fpap->input.capacity - 1;
		else
			event = fpap->input.content + fpap->input.top - 1;

		value_input = value;
		value_input->character = event->character;
		value_input->page = event->page;
		value_input->pressed = event->pressed;

		if (property == FPAP_PROPERTY_INPUT || event->character
		== '\0')
			break;

		if (fpap->input.top == 0)
			fpap->input.top = fpap->input.capacity - 1;
		else
			fpap->input.top -= 1;

		break;
	case FPAP_PROPERTY_ROTATION:
		*(FPAP_BYTE*)value = fpap->rotation;
		break;
	default:
		return FPAP_UNDEFINED_PROPERTY;
	}
	return FPAP_SUCCESS;
}
