#include "256color.h"


/**
 * A faster method to draw vertical lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param y2 The second vertical coordinate.
 * @param color The color to plot.
 */
void verticalLine_256color( unsigned int x
			    , unsigned char y
			    , unsigned char y2
			    , unsigned char color) {

  // Make sure, that y < y2
  if( y2 < y) {
    unsigned char swap = y;
    y = y2;
    y2 = swap;
  }

  // Check boundaries.
  if( y2 > getMaxY_256color()) {
    y2 = getMaxY_256color();
  }
  
  // Just copy the byte with the color to the bitmap buffer via DMA.
  copy2screen( (unsigned long)(unsigned int)&color
	       , screenbuffer_addy + (unsigned long)calculateBitmapAddress_256color( x,y)
	       , 0  // Since we only copy 1 byte, the steps don't matter.
	       , 320 
	       , y2 - y + 1);
}
