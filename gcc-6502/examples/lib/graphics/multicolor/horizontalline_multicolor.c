#include "multicolor.h"


/**
 * A faster method to draw horizontal lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param x2 The second horizontal coordinate.
 * @param color The color to plot.
 */
void horizontalLine_multicolor( unsigned int x
				, unsigned char y
				, unsigned int x2
				, unsigned char color) {

  // Check boundaries
  if( y > getMaxY_multicolor()) {
    return;
  }
  if( x2 < x) {
    unsigned int swap = x;
    x = x2;
    x2 = swap;
  }
  if( x2 > getMaxX_multicolor()) {
    x2 = getMaxX_multicolor();
  }
  
  // Compute the address of start and end in the screenbuffer
  unsigned char *startScreenp = calculateBitmapPointer_multicolor( x, y);
  unsigned char *endScreenp = calculateBitmapPointer_multicolor( x2, y);
      
  // Check, if x and x2 are in the same byte, so we have to draw a very
  // short line with <= 8 pixels.
  if( startScreenp == endScreenp)  {  // x and x2 are in the same byte?
    unsigned char bitmask = ( 0xff >> ( x & 7)) - ( 0xff >> ( x2 & 7));

    *startScreenp &= ~bitmask;
    *startScreenp |= ( multicolor_bitmaps[ color] & bitmask);
    
    // We are done.
    
  } else {

    // Compute bitmask of first byte, if it is not a full byte
    // (8 pixels to paint in this byte).
    if( ( x & 7) != 0) {
      unsigned char bitmask = ( 0xff >> (x & 7));

      *startScreenp &= ~bitmask;
      *startScreenp |= ( multicolor_bitmaps[ color] & bitmask);

      startScreenp += 8;  // Advance to the the screenbuffer byte.
    }

    // Compute bitmask of last byte, if it is not a full byte.
    if( ( x2 & 7) != 0) {
      unsigned char bitmask = ~( 0xff >> ( x2 & 7));

      *endScreenp &= ~bitmask;
      *endScreenp |= ( multicolor_bitmaps[ color] & bitmask);
      
      endScreenp -= 8;
    }

    // Now paint the full bytes between start and end.

    // Set all bits in the full bytes.
    while( startScreenp <= endScreenp) {
      *startScreenp = multicolor_bitmaps[ color];
      startScreenp += 8;
    }
  }
}
