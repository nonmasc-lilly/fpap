# FPAP

FPAP is (ideally) the final iteration of OPAP the pixel mapping library I have
managed to make at least three fuckass versions of. An example follows:

```C
#include <fpap.h>
int main(void) {
        FPAP instance;
        FPAP_COLOR buffer[0x40] = {0xFF000000}; /* Accounts for Alpha */
        int i;

        fpap_init(&instance, 800, 800, "Hello World!", FPAP_VSYNC);
        for(i = 0; i < 8; i++) {
                buffer[i + i * 8] = 0xFFFF00FF; /* Magenta */
        }

        fpap_draw(&instance, buffer, 8, 8);
        while(fpap_frame(&instance) != FPAP_WINDOW_CLOSED) {
                /* Main Loop */
        }

        fpap_term(&instance);
}
```
