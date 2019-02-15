#include "hires.h"


/**
 * Draw a frame.
 *
 * @param x The horizontal coordinate of the upper left corner.
 * @param y The vertical coordinate of the upper left corner.
 * @param x2 The horizontal coordinate of the lower right corner.
 * @param y2 The vertical coordinate of the lower right corner.
 * @param color The color to use.
 */
void frame_hires( unsigned int x
		  , unsigned char y
		  , unsigned int x2
		  , unsigned char y2
		  , unsigned char color) {

  horizontalLine_hires( x, y, x2, color);
  horizontalLine_hires( x, y2, x2, color);
  if( abs( y2 - y) > 1) {
    verticalLine_hires( x, y + 1, y2 - 1, color);
    verticalLine_hires( x2, y + 1, y2 - 1, color);
  }
}
