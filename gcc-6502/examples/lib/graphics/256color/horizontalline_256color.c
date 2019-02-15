#include "256color.h"


/**
 * A faster method to draw horizontal lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param x2 The second horizontal coordinate.
 * @param color The color to plot.
 */
void horizontalLine_256color( unsigned int x
			      , unsigned char y
			      , unsigned int x2
			      , unsigned char color) {

  // Check boundaries
  if( y > getMaxY_256color()) {
    return;
  }
  if( x2 < x) {
    unsigned int swap = x;
    x = x2;
    x2 = swap;
  }
  if( x2 > getMaxX_256color()) {
    x2 = getMaxX_256color();
  }
  
  // Just copy the byte with the color to the bitmap buffer via DMA.
  copy2screen( (unsigned long)(unsigned int)&color
	       , screenbuffer_addy + (unsigned long)calculateBitmapAddress_256color( x,y)
	       , 0  // Since we only copy 1 byte, the steps don't matter.
	       , 1 
	       , x2 - x + 1);
  
}
