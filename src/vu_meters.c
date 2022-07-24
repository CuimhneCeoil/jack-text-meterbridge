#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <string.h>

#include "main.h"
#include "display.h"

int gfx_thread_vu(void *foo) {
    int i;
    const float angle_scale = 15.7f;
    const float angle_offset = 0.7853975f;
    const float double_angle = 2 * angle_offset;
    float theta;
    float lp[MAX_METERS];

    memset(lp, 0, MAX_METERS * sizeof(float));

    while (1) {
        for (i = 0; i < num_meters; i++) {
            lp[i] = lp[i] * 0.8f + env[i] * bias * 0.2f;
            theta = (lp[i] * angle_scale) - angle_offset;

            if (theta < -0.7853975f)
                theta = -0.7853975f;
            if (theta > 0.7853975f)
                theta = 0.7853975f;
            theta += angle_offset;
            int size = (int) ((theta / double_angle) * ((float) CONSOLE_WIDTH));

            display(i, size);
        }
        SDL_Delay(100);
    }

    return 0;
}
