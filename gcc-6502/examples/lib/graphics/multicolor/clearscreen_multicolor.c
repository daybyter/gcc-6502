#include "multicolor.h"
#include <string.h>


/**
 * Clear the screen.
 */
void clearscreen_multicolor( void) {
  
    // Clear the screen.
    memset( screenbuffer, 0, 8000);

    // Clear the text ram (used as color ram now).
    memset( textbuffer, ( foreground_multicolor << 4)
	    + background_multicolor, 1000);
    
    // Set the colorram color 3 to black
    memset( (void *)0xd800, 0, 1000);
}
