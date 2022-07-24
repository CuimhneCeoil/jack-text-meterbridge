/*
 * display.h
 *
 *  Created on: 24 Jul 2022
 *      Author: claude
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_

/* constants for lcd access */
#define DEFAULT_DEVICE "/dev/lcd0"
#define CONSOLE_WIDTH 20
#define DISPLAY_WIDTH (CONSOLE_WIDTH+6)
#define DISPLAY_SIZE(s) (s+6)

void display( int meter, int height, int peak );
int display_init( );
const char const *display_get_error();

#endif /* SRC_DISPLAY_H_ */
