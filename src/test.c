#include <stdio.h>
#include <stdlib.h>

#include "fpap.h"

int main(int argc, char **argv) {
        FPAP instance;
        FPAP_COLOR buffer[8*8] = {0xFF000000};
        int i;

        fpap_init(&instance, 800, 800, "Window", FPAP_VSYNC);
        for(i = 0; i < 8; i++)
                buffer[i + i * 8] = 0xFFFF00FF;

        fpap_draw(&instance, buffer, 8, 8);
        while(fpap_frame(&instance) != FPAP_WINDOW_CLOSED);

        fpap_term(&instance);
        exit(0);
}
