/**
 * Copy the 8 bytes of a character bitmap to a buffer.
 * 
 * @param c The petscii code of the character to copy.
 * @param buffer A pointer to an 8 byte buffer for the bitmap.
 */
inline void copy_single_character( char c, unsigned char *buffer) {
  
  unsigned char *mem_config = (unsigned char *)1;
  unsigned old_config;
  unsigned char *src = (unsigned char *)0xd000 + 8 * (int)convert2c64screencode(c);
 
  /* Store the old mem bank config. */
  old_config = *mem_config;

  /* disable IRQs, while we copy. */
  __asm__ __volatile__ ("sei");

  *mem_config = 0x33;  /* Make cpu see the character ROM. */

  /* Do the actual copy. Unrolled loop to be a bit faster. */
  *buffer++ = *src++;
  *buffer++ = *src++;
  *buffer++ = *src++;
  *buffer++ = *src++;
  *buffer++ = *src++;
  *buffer++ = *src++;
  *buffer++ = *src++;
  *buffer = *src;
  
  /* Restore old mem banking. */
  *mem_config = old_config;

  /* Enable IRQs again. */
  __asm__ __volatile__ ("cli");
}


/**
 * Draw a character at a given bitmap position.
 *
 * @param c The petscii code of the character.
 * @param x The horiontal screen position.
 * @param y The vertical screen position.
 * @param color The color to use.
 */
void drawCharacter( char c
		    , unsigned int x
		    , unsigned char y
		    , unsigned char color) {

  // Create a buffer for the character bitmap
  unsigned char bitmap_buffer[8];

  // Copy the character bitmap from the rom to the bitmap buffer.
  copy_single_character( c, bitmap_buffer);
  
  // Read the character bitmap from the copied rom and just
  // plot the pixels.
  for( int line = 0; line < 8; ++line) {

    unsigned int cur_x = x;
    for( unsigned char bitmask = 0x80; bitmask != 0; bitmask >>= 1) {
      if( ( bitmap_buffer[line] & bitmask) != 0) {
	plot( cur_x, y, color);
      }
      ++cur_x;
    }
    ++y;
  }
}


/**
 * Draw a string at a given bitmap position.
 *
 * @param s The string to draw.
 * @param x The horiontal screen position.
 * @param y The vertical screen position.
 * @param color The color to use.
 */
void drawString( char *s
		 , unsigned int x
		 , unsigned char y
		 , unsigned char color) {

  while( *s != 0) {
    drawCharacter( *s++, x, y, color);
    x += 8;
  }
}
  
