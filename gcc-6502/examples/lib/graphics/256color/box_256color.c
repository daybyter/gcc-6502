#include "256color.h"


/**
 * Draw a box.
 *
 * @param x The horizontal coordinate of the upper left corner.
 * @param y The vertical coordinate of the upper left corner.
 * @param x2 The horizontal coordinate of the lower right corner.
 * @param y2 The vertical coordinate of the lower right corner.
 * @param color The color to use.
 */
void box_256color( unsigned int x
		   , unsigned char y
		   , unsigned int x2
		   , unsigned char y2
		   , unsigned char color) {

  // Just use horizontal lines for now.
  for( unsigned char curY = y; curY <= y2; ++curY) {    
    horizontalLine_256color( x, curY, x2, color);
  }
}
