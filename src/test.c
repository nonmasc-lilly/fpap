#include <stdio.h>
#include <stdlib.h>

#include "fpap.h"

int main(int argc, char **argv) {
        FPAP instance;
        int i;
        FPAP_COLOR buffer[8*8];
        FPAP_BOOL changed = FPAP_TRUE;
        fpap_init(&instance, 800, 800, "Window", FPAP_VSYNC);
        i = 0;
        for(i = 0; i < 64; i++) {
                buffer[i] = 0xFFFF00FF;
        }
        while(fpap_frame(&instance) != FPAP_WINDOW_CLOSED) {
                if(changed == FPAP_TRUE) {
                        changed = FPAP_FALSE;
                        fpap_draw(&instance, buffer, 8, 8);
                }
                buffer[0] = ~buffer[0];
                changed = FPAP_TRUE;
        }
        fpap_term(&instance);
        exit(0);
}
