#include <stdio.h>
#include <stdlib.h>

#include "fpap.h"

int main(int argc, char **argv) {
	FPAP instance;
	FPAP_BOOL vsync = FPAP_TRUE;
	FPAP_COLOR buffer[8*8] = {0xFF000000};
	struct fpap_ext_input_event input_event;
	int i;
	unsigned long angle;
	FPAP_BYTE value;

	fpap_init(&instance, 800, 800, "Window");
	fpap_set(instance, FPAP_PROPERTY_VSYNC, &vsync);
	buffer[0] = 0xFFFF0000;
	buffer[7] = 0xFFFF00FF;
	buffer[7 * 8] = 0xFFFF00FF;
	buffer[7 * 8 + 7] = 0xFFFF00FF;

	angle = 0;
	fpap_draw(instance, buffer, 8, 8);
	while (fpap_frame(instance) != FPAP_WINDOW_CLOSED) {
		angle += 1;
		value = angle / 1000;
		fpap_set(instance, FPAP_PROPERTY_ROTATION, &value);
		fpap_get(instance, FPAP_PROPERTY_INPUT_POP, &input_event);
		if (input_event.pressed && input_event.character == 'q')
			break;
	}

	fpap_term(instance);
	exit(0);
}
