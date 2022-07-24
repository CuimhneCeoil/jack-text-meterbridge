#include <math.h>
#include <string.h>

#include "main.h"
#include "envelopes.h"
#include "display.h""


int iec_scale(float db);

const static int sdl_delay = 80;
const static float decay = 1.0f - 0.08f;

int iec_scale(float db, int size) {
         float def = 0.0f; /* Meter deflection %age */
 
         if (db < -70.0f) {
                 def = 0.0f;
         } else if (db < -60.0f) {
                 def = (db + 70.0f) * 0.25f;
         } else if (db < -50.0f) {
                 def = (db + 60.0f) * 0.35f + 2.5f;
         } else if (db < -40.0f) {
                 def = (db + 50.0f) * 1.00f + 6.0f;
         } else if (db < -30.0f) {
                 def = (db + 40.0f) * 1.45f + 16.0f;
         } else if (db < -20.0f) {
                 def = (db + 30.0f) * 1.95f + 30.5f;
         } else if (db < 0.0f) {
                 def = (db + 20.0f) * 2.50f + 50.0f;
         } else {
                 def = 100.0f;
         }

         return (int)( (def / 100.0f) * ((float) size) );
}

int gfx_thread_dpm(void *foo)
{
	unsigned int i;
	int size;
	static float lp[MAX_METERS];


	while (1) {
		for (i=0; i<num_meters; i++) {
			const float peak = env_read(i);
			lp[i] = lp[i] * decay;
			if (peak > lp[i]) lp[i] = peak;

	        debug( 4, "Processing db=%d for channel %d\n", lp[i], i );
			size = iec_scale(20.0f * log10f(lp[i] * bias), CONSOLE_WIDTH);
			display( i, size )
		}
		SDL_Delay(sdl_delay);
	}

	return 0;
}
