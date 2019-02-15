#include "hires.h"


/**
 * Go back to text mode.
 */
void textmode_hires( void) {
  
  cia2[0] &= 0xfc;      // Set the VIC bank to the 1st bank again.
  cia2[0] |= 0x03; 
    
  vic[17] &= ~0x20;    // Clear bit 5 of $d011 to deactivate hires mode.
    
  vic[24] &= 0x0f;     // Move the screen ram to 1024 again.
  vic[24] |= 0x01;     
}
