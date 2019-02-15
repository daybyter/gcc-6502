/**
 * 256 color mode of the c64 dtv. 
 * See: http://dtvhacking.cbm8bit.com/common/tech/256-mode.html
 */


/**
 * The background color.
 */
unsigned char background_256color;


/**
 * The DTV blitter register base address.
 */
unsigned char * dtv_blitter = (unsigned char *)0xd300;


/**
 * The DTV extended VIC base address.
 */
unsigned char *dtv_vic = (unsigned char *)0xd000;


/**
 * The foreground color.
 */
unsigned char foreground_256color;


/**
 * Compute the address of a byte in the bitmap for a given coordinate pair.
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 *
 * @return The address as an unsigned int.
 */
inline unsigned int calculateBitmapAddress_256color( unsigned int x, unsigned char y) {

  // Compute the address of the byte to modify.
  unsigned int addy = (y << 8) + (y << 6) + x;

  return addy;
}


/**
 * Copy some ram from normal 64kb ram to the extended ram above 64kb.
 *
 * @param source memory address of the source
 * @param destination memory address of the destination
 * @param source_step number of bytes to increase the source address after each copy.
 * @param destination_step number of bytes to increase the destination address.
 * @param length The number of bytes to copy.
 */
void copy2screen( unsigned long source
		  , unsigned long destination
		  , unsigned int source_step
		  , unsigned int destination_step
		  , unsigned int length) {

  dtv_blitter[ 0x00] = source & 0xff;  // Set source address low byte
  dtv_blitter[ 0x01] = ( source >> 8) & 0xff;  // Source address mid byte.
  dtv_blitter[ 0x02] = ( (source >> 16) & 0xff) + 0x40; // Source high byte
  // + 0x40 to indicate, that the source is in RAM (and not ROM)

  dtv_blitter[ 0x03] = destination & 0xff;  // Destination low byte.
  dtv_blitter[ 0x04] = (destination >> 8) & 0xff;  // Destination mid byte.
  dtv_blitter[ 0x05] = ((destination >> 16) & 0xff) + 0x40;  // Destination
  // high byte + 0x40 to indicate ram
  
  // Set source and destination step to 1
  dtv_blitter[ 0x06] = source_step & 0xff;               // SOURCE STEP LOW
  dtv_blitter[ 0x07] = ( source_step >> 8) & 0xff;       // SOURCE STEP HIGH
  dtv_blitter[ 0x08] = destination_step & 0xff;          // DESTINATION STEP LOW
  dtv_blitter[ 0x09] = ( destination_step >> 8) & 0xff;  // DESTINATION STEP HIGH

  // Set the length of the block to copy.
  dtv_blitter[ 0x0A] = length & 0xff;         // LENGTH LOW
  dtv_blitter[ 0x0B] = ( length >> 8) & 0xff; // LENGTH HIGH
}
