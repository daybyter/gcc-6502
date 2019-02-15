
#include "multicolor.h"


#define PRECALCULATE_RASTERSTART 1


/**
 * The background color.
 */
unsigned char background_multicolor;


/**
 * The foreground color.
 */
unsigned char foreground_multicolor;


/**
 * Precalculated multicolor bitmaps for each color.
 */
unsigned char multicolor_bitmaps[4] = { 0x00       // 00000000 = color 0
					, 0x55     // 01010101 = color 1
					, 0xaa     // 10101010 = color 2
					, 0xff};   // 11111111 = color 3

#ifdef PRECALCULATE_RASTERSTART
/**
 * A table of start addresses for each raster line.
 */
unsigned char *rasterstart_addy_multicolor[200];
#endif


/**
 * Compute the address of a byte in the bitmap for a given coordinate pair.
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 *
 * @return The address as a pointer.
 */
unsigned char *calculateBitmapPointer_multicolor( unsigned int x, unsigned char y) {

  #ifdef PRECALCULATE_RASTERSTART

  return rasterstart_addy_multicolor[y] + (x & 0xfff8);

  #else
  
  // Compute the address of the byte to modify.
  unsigned int ytextline = y >> 3;
  unsigned int addy = (ytextline << 8)
    + (ytextline << 6)
    + (x & 0xfff8)
    + (y & 7);

  return &screenbuffer[addy];

  #endif
}
