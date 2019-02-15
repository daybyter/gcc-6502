
#include "hires.h"
#include <string.h>


#define PRECALCULATE_RASTERSTART 1


/**
 * The background color.
 */
unsigned char background_hires;


/**
 * The foreground color.
 */
unsigned char foreground_hires;


#ifdef PRECALCULATE_RASTERSTART
/**
 * A table of start addresses for each raster line.
 */
unsigned char *rasterstart_addy_hires[200];
#endif


/**
 * Compute the address of a byte in the bitmap for a given coordinate pair.
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 *
 * @return The address as a pointer.
 */
inline unsigned char *calculateBitmapPointer_hires( unsigned int x, unsigned char y) {

  #ifdef PRECALCULATE_RASTERSTART

  return rasterstart_addy_hires[y] + (x & 0xfff8);

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
