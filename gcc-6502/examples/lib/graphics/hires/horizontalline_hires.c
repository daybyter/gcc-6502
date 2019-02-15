#include "hires.h"


/**
 * A faster method to draw horizontal lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param x2 The second horizontal coordinate.
 * @param color The color to plot.
 */
void horizontalLine_hires( unsigned int x
			   , unsigned char y
			   , unsigned int x2
			   , unsigned char color) {

  // Check boundaries
  if( y > getMaxY_hires()) {
    return;
  }
  if( x2 < x) {
    unsigned int swap = x;
    x = x2;
    x2 = swap;
  }
  if( x2 > getMaxX_hires()) {
    x2 = getMaxX_hires();
  }
  
  // Compute the address of start and end in the screenbuffer
  unsigned char *startScreenp = calculateBitmapPointer_hires( x, y);
  unsigned char *endScreenp = calculateBitmapPointer_hires( x2, y);
      
  // Check, if x and x2 are in the same byte, so we have to draw a very
  // short line with <= 8 pixels.
  if( startScreenp == endScreenp)  {  // x and x2 are in the same byte?
    unsigned char bitmask = ( 0xff >> ( x & 7)) - ( 0xff >> ( x2 & 7));

    if( color == 0) {
      *startScreenp &= ~bitmask;
    } else {
      *startScreenp |= bitmask;
    }  // We are done.
    
  } else {

    // Compute bitmask of first byte, if it is not a full byte
    // (8 pixels to paint in this byte).
    if( ( x & 7) != 0) {
      unsigned char bitmask = ( 0xff >> (x & 7));

      if( color == 0) {
	*startScreenp &= ~bitmask;
      } else {
	*startScreenp |= bitmask;
      }
      startScreenp += 8;  // Advance to the the screenbuffer byte.
    }

    // Compute bitmask of last byte, if it is not a full byte.
    if( ( x2 & 7) != 0) {
      unsigned char bitmask = ~( 0xff >> ( x2 & 7));

      if( color == 0) {
	*endScreenp &= ~bitmask;
      } else {
	*endScreenp |= bitmask;
      }
      endScreenp -= 8;
    }

    // Now paint the full bytes between start and end.
    if( color == 1) {

      // Set all bits in the full bytes.
      while( startScreenp <= endScreenp) {
	*startScreenp = 0xff;
	startScreenp += 8;
      }
    } else {

      // Delete all bits in the full bytes.
      while( startScreenp <= endScreenp) {
	*startScreenp = 0;
	startScreenp += 8;
      }
    }
  }
}
 
