#include "hires.h"
#include <string.h>


/**
 * Clear the screen.
 */
void clearscreen_hires( void) {
  
    // Clear the screen.
    memset( screenbuffer, 0, 8000);

    // Clear the text ram (used as color ram now).
    memset( textbuffer, ( foreground_hires << 4)
	    + background_hires, 1000);
}
