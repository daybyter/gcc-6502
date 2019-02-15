#include "multicolor.h"
#include <string.h>

/**
 * Init the multicolor graphics mode.
 */
void grafmode_multicolor( void) {

  cia2[0] &= 0xfc;  // Set the VIC bank to the 3rd bank
  cia2[0] |= 0x01;  // 0x8000 - 0x7fff to make room for bigger apps.
  
  vic[17] |= 0x20;     // Set bit 5 of $d011 to activate hires mode.
  
  vic[24] |= 0x08;     // Set screenbuf to vic-base + 8192;
  
  vic[24] &= 0x0f;   // Move the screen ram right before the bitmap.
  vic[24] |= 0x70;   // at 0x5c00
  
  textbuffer = (unsigned char *)0x9c00;
  
  // Set a pointer to the screen buffer.
  screenbuffer = (unsigned char *)0xa000;
  
  // Set multicolor mode.
  vic[0x16] |= 0x10;
    
  // Set the color 3 to black
  memset( (void *)0xd800, 0, 1000);
      
  // Set the background color to white
  vic[0x21] = 1;
}
