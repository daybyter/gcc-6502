#include "hires.h"


/**
 * Plot a pixel in hires mode.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 1 = foreground color, 0 = background color.
 */
void plot_hires( unsigned int x, unsigned char y, unsigned char color) {

  // Compute the address of the byte to modify.
  unsigned char *screenp = calculateBitmapPointer_hires( x, y);

  // Compute the bitmask to use.
  unsigned char bitmask = (0x80 >> ( x & 7));

  if( color == 1) {
    *screenp |= bitmask;
  } else {
    *screenp &= ~bitmask;
  }
}
