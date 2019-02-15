#include "256color.h"


/**
 * Just clear the screen.
 */
void clearscreen_256color( void) {

  // Just fill the screenbuffer with 0.
  copy2screen( (unsigned long)(unsigned int)&background_256color
	       , screenbuffer_addy
	       , 0
	       , 1
	       , 64000U);
}
