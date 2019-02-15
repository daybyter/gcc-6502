#include "multicolor.h"


/**
 * Plot a pixel in multicolor mode.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 0-3
 */
void plot_multicolor( unsigned int x, unsigned char y, unsigned char color) {

  // Just double x for now.
  x <<= 1;
  
  // Compute the address of the byte to modify.
  unsigned char *screenp = calculateBitmapPointer_multicolor( x, y);

  *screenp &= (~(0xc0 >> (x & 7)));
  *screenp |= ((color << 6) >> (x & 7));
}

