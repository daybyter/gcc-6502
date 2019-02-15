#include "multicolor.h"


/**
 * Draw a frame.
 *
 * @param x The horizontal coordinate of the upper left corner.
 * @param y The vertical coordinate of the upper left corner.
 * @param x2 The horizontal coordinate of the lower right corner.
 * @param y2 The vertical coordinate of the lower right corner.
 * @param color The color to use.
 */
void frame_multicolor( unsigned int x
		       , unsigned char y
		       , unsigned int x2
		       , unsigned char y2
		       , unsigned char color) {

  horizontalLine_multicolor( x, y, x2, color);
  horizontalLine_multicolor( x, y2, x2, color);
  if( abs( y2 - y) > 1) {
    verticalLine_multicolor( x, y + 1, y2 - 1, color);
    verticalLine_multicolor( x2, y + 1, y2 - 1, color);
  }
}
