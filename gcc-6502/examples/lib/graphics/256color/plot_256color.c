#include "256color.h"


/**
 * Plot a pixel in multicolor mode.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 0-255
 */
void plot_256color( unsigned int x, unsigned char y, unsigned char color) {

  // Just copy the byte with the color to the bitmap buffer via DMA.
  copy2screen( (unsigned long)(unsigned int)&color
	       , screenbuffer_addy + (unsigned long)calculateBitmapAddress_256color( x,y)
	       , 1  // Since we only copy 1 byte, the steps don't matter.
	       , 1 
	       , 1);
}
