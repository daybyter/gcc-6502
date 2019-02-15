#include "hires.h"


/**
 * Init the hires graphics mode.
 */
void grafmode_hires( void) {
  cia2[0] &= 0xfc;  // Set the VIC bank to the 3rd bank
  cia2[0] |= 0x01;  // 0x8000 - 0x7fff to make room for bigger apps.
    
  vic[17] |= 0x20;     // Set bit 5 of $d011 to activate hires mode.
  
  vic[24] |= 0x08;     // Set screenbuf to vic-base + 8192;
  
  vic[24] &= 0x0f;   // Move the screen ram right before the bitmap.
  vic[24] |= 0x70;   // at 0x9c00
  
  textbuffer = (unsigned char *)0x9c00;
    
  vic[32] = 0;  // Set border color to black.
  
  // Set a pointer to the screen buffer.
  screenbuffer = (unsigned char *)0xa000;

  // Precalculate rasteline start addresses if requested
#ifdef PRECALCULATE_RASTERSTART
  for( unsigned char y = 0; y < 200; ++y) {
    
    unsigned char ytextline = y >> 3;
    unsigned int addy = (ytextline << 8)
      + (ytextline << 6)
      + (y & 7);
    
    rasterstart_addy_hires[y] = &screenbuffer_hires[addy];
  }
#endif
}
