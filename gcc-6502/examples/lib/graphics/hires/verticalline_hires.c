#include "hires.h"


/**
 * A faster method to draw vertical lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param y2 The second vertical coordinate.
 * @param color The color to plot.
 */
void verticalLine_hires( unsigned int x
			 , unsigned char y1
			 , unsigned char y2
			 , unsigned char color) {

  // Make sure, that y1 < y2
  if( y2 < y1) {
    unsigned char swap = y1;
    y1 = y2;
    y2 = swap;
  }

  // Compute a pointer to the first bitmap address.
  unsigned char *bitmap_p = calculateBitmapPointer_hires( x, y1);

  // Compute the bitmask to use.
  unsigned char bitmask = (0x80 >> ( x & 7));

  if( color == 1) {
  
    for( unsigned char currentY = y1; currentY <= y2; ) {

      *bitmap_p |= bitmask;

      // Advance the pointer to the next byte in the screen buffer.
      bitmap_p += ( ( ++currentY & 7) == 0) ? 313 : 1;
    }

  } else {
    
    for( unsigned char currentY = y1; currentY <= y2; ) {

      *bitmap_p &= ~bitmask;

      // Advance the pointer to the next byte in the screen buffer.
      bitmap_p += ( ( ++currentY & 7) == 0) ? 313 : 1;
    }
  }
}
