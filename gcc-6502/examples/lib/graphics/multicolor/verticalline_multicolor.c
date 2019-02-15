#include "multicolor.h"


/**
 * A faster method to draw vertical lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param y2 The second vertical coordinate.
 * @param color The color to plot.
 */
void verticalLine_multicolor( unsigned int x
			      , unsigned char y1
			      , unsigned char y2
			      , unsigned char color) {

  // Just double x for now.
  x <<= 1;
  
  // Make sure, that y1 < y2
  if( y2 < y1) {
    unsigned char swap = y1;
    y1 = y2;
    y2 = swap;
  }

  // Compute a pointer to the first bitmap address.
  unsigned char *bitmap_p = calculateBitmapPointer_multicolor( x, y1);

  // Compute the bitmasks to use.
  unsigned char bitmask_mask = ~(0xc0 >> (x & 7));
  unsigned char bitmask_set = ((color << 6) >> (x & 7));
  
  for( unsigned char currentY = y1; currentY <= y2; ) {

    // Mask the color bits and set the color.
    *bitmap_p &= bitmask_mask;
    *bitmap_p |= bitmask_set;

    // Advance the pointer to the next byte in the screen buffer.
    bitmap_p += ( ( ++currentY & 7) == 0) ? 313 : 1;
  }
}
