# FPAP

This is an implementation of the Framebuffer Abstraction API V02.00.XX.

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
	while (fpap_frame(instance) != FPAP_WINDOW_CLOSED) {
		/* Main Loop */
	}

	fpap_term(instance);
}
```

## Extensions

This fpap distrobution has a few properties and an extended type pertaining to
keyboard input. These are as such:

A struct that defines which key has been inputted and whether it was pressed
or released.
```C
struct fpap_ext_input_event {
	char character;
	FPAP_BYTE page;
	FPAP_BOOL pressed;
}
```

Properties getting the last key pressed, this will return the correct ascii
code for each visible character as well as $1-$1A for CTRL+letter, $1B for
escape, $9 for tab, $D for enter, $20 for space and $7F for delete. For all
characters hitherto the page is zero, for the following it is one:

- F1-F25 is $30-$49
- LEFT is 'A'
- RIGHT is 'D'
- UP is 'W'
- DOWN is 'S'

These properties are like so:

- `FPAP_PROPERTY_INPUT` gets the input as an `fpap_ext_input_event`.
- `FPAP_PROPERTY_INPUT_POP` gets the input as before and remove it from the
input list so it may not be retrieved.
- `FPAP_PROPERTY_ROTATION` is an `FPAP_BYTE` which may is read as an (x mod 4)
rotation such that the user may flip their view quad along the four cardinal
directions (allows for drawing columns using memset).

An example might look like so:

```C
int main(void)
{
	FPAP instance;
	struct fpap_ext_input_event input_event;

	fpap_init(&instance, 800, 800, "Hello Input!");

	while (fpap_frame(instance) != FPAP_WINDOW_CLOSED) {
		fpap_get(instance, FPAP_PROPERTY_INPUT_POP, &input_event);
		if (input_event.pressed && input_event.character == 'q') {
			break;
		}
	}

	fpap_term(instance);
}
```

## The Test Program

The test program may be run with `./make.sh -t` and draws a rotating set of
four scaled up corner pixels of multiple colors on an 8x8 grid, which may be
exitted at any time with `q`.
