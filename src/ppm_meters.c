#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <string.h>

#include "main.h"
#include "envelopes.h"
#include "display.h";

// TODO: derive decay from sdl_delay. This should be 6 PPM = 24dB / 2.8s
// 80ms : 24dB / 2.8 * 0.08 = 0.6857 dB /frame -> decay = 10 ** (-0.6857 / 20) = 0.92409f
// 50ms : 0.42857 db / frame --> decay = 0.951856f
const static int sdl_delay = 50;
const static float decay = 0.951856f;

int gfx_thread_ppm(void *foo) {
    int  i;
    const float pi_4 = 0.785398f;
    const float pi_2 = 1.570796f;
    float theta;
    float lp[MAX_METERS];

    memset( lp, 0, MAX_METERS * sizeof( float ));

    while (1) {
        for (i = 0; i < num_meters; i++) {
            const float peak = bias * env_read(i);
            lp[i] = lp[i] * decay;
            //if (peak > lp[i]) lp[i] = 0.3f * lp[i] + 0.7f * peak;
            if (peak > lp[i])
                lp[i] = peak;
            theta = 1.09083f * log10f(lp[i]);

            if (theta < -pi_4)
                theta = -pi_4;
            if (theta > pi_4)
                theta = pi_4;
            theta += pi_4;
            int size = (int) ((theta / pi_2) * ((float) CONSOLE_WIDTH));


            display(i, size);

        }
        SDL_Delay(sdl_delay);
    }

    return 0;
}
