/*
 * display.c
 *
 *  Created on: 24 Jul 2022
 *      Author: claude
 */

#include <unistd.h>
#include <string.h>

#include "display.h"
#include "main.h"

//int displaying = 0;
extern char* lcd_device;
extern char peak_char;
extern char meter_char;
extern int lcd;

int peaks[MAX_METERS];
int ptime[MAX_METERS];

void init_display() {
    memset( peaks, 0, MAX_METERS*sizeof(int));
    memset( ptime, 0, MAX_METERS*sizeof(int));
}

char* configure_buffer( char* display_buffer, char row ) {
    // set the standard prefix for the display
    display_buffer[0] = (char)0x1b;
    display_buffer[1] ='[';
    display_buffer[2] = row;
    display_buffer[3] = ';';
    display_buffer[4] = '0';
    display_buffer[5] = 'H';
    memset( &display_buffer[6], ' ', CONSOLE_WIDTH*sizeof(char));
    return &display_buffer[6];
}

void write_buffer_to_lcd( const char * const display_buffer, int len ) {
    int expected = len*sizeof(char);
    debug( 5, "LCD: %d (%d) characters\n", len, expected );
    int written = write( lcd, display_buffer, expected );
    if (written != expected ) {
        debug( 2, "*** only wrote %d of %d bytes\n", written, expected);
    }
    debug( 4, "LCD: %d characters written\n", written );
}

void display( int meter, int size ) {

    // peak hold
    if (size > peaks[meter]) {
        peaks[meter] = size;
        ptime[meter] = 0;
    } else if (ptime[meter]++ > 20) {
        peaks[meter] = size;
    }

    char display_buffer[DISPLAY_WIDTH];
    char* display_text = configure_buffer( display_buffer, '3'+meter );
    memset( display_text, meter_char, size*sizeof(char) );
    display_text[peaks[meter]]=peak_char;

    // write the line
    write_buffer_to_lcd( display_buffer, DISPLAY_WIDTH );
}

