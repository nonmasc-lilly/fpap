# FPAP

This is an implementation of the Framebuffer Abstraction API V01.00.XX.

```C
#include <fpap.h>

int main(void)
{
	FPAP instance;
	FPAP_BOOL vsync = FPAP_TRUE;
	FPAP_COLOR buffer[0x40] = {0xFF000000}; /* Accounts for Alpha */
	int i;

	fpap_init(&instance, 800, 800, "Hello World!");
	fpap_set(instance, FPAP_PROPERTY_VSYNC, &instance);
	for (i = 0; i < 8; i++) {
		buffer[i + i * 8] = 0xFFFF00FF; /* Magenta */
	}

	fpap_draw(instance, buffer, 8, 8);
	while(fpap_frame(instance) != FPAP_WINDOW_CLOSED) {
		/* Main Loop */
	}

	fpap_term(instance);
}
```
