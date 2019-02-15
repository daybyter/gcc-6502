#include "256color.h"


/**
 * Enable the 256 color grafphics mode.
 * @see: http://dtvhacking.cbm8bit.com/common/tech/256-mode.html
 */
void grafmode_256color() {

  dtv_vic[ 0x3f] = 0x01;   // Enable extended features
  dtv_vic[ 0x3c] = 0x55;   // Enable linear mode
  dtv_vic[ 0x11] = 0x5b;
  dtv_vic[ 0x16] = 0x18;
  dtv_vic[ 0x4c] = 0x08;   // Step = 8.

  // Set the screen buffer to address 0x10000
  dtv_vic[ 0x49] = screenbuffer_addy & 0xff;         // Screen location LOW
  dtv_vic[ 0x4a] = (screenbuffer_addy >> 8) & 0xff;  // Screen location MID
  dtv_vic[ 0x4b] = (screenbuffer_addy >> 16) & 0xff;   // Screen location HIGH

  // Redefine palette and add missing grays.
  unsigned char *palette = (unsigned char*)53760;
  for( unsigned int i = 0; i <= 15; ++i) {
    palette[i] = i;
  }
}

