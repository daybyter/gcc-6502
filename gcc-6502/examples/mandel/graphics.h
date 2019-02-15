/**
 * Some simple graphics routines for the commodore 64.
 *
 * Author(s): Andreas Rueckert <arueckert67@t-online.de>
 */

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_


/* List of supported modes */
#define TEXTMODE_40_25      0
#define GRAFMODE_320_200_2  1  // c64 hires 320x200 pixel, 2 colors
#define GRAFMODE_160_200_4  2  // c64 multicolor 160x200 pixel, 4 colors

/**
 * Get the max horizontal coordinate.
 */
int getMaxX();

/**
 * Get the max vertical coordinate.
 */
int getMaxY();

/**
 * Get the max color index.
 */
int getMaxColor();


/**
 * Enter the graphics mode.
 * 
 * @param mode The selected graphics mode.
 */
void grafmode( unsigned char mode);

/**
 * Draw a line.
 * 
 * @param x1 The horizontal start coordinate.
 * @param y1 The vertical start coordinate.
 * @param x2 The horizontal end coordinate.
 * @param y2 The vertical end coordinate.
 * @param color 1 = foreground color, 0 = background color.
 */
void line( unsigned int x1
	   , unsigned char y1
	   , unsigned int x2
	   , unsigned char y2
	   , unsigned char color);
  
/**
 * Plot a pixel.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 1 = foreground color, 0 = background color.
 */
extern void (*plot)( unsigned int x, unsigned char y, unsigned char color);

/**
 * Return to the text mode.
 */
void textmode( void);

#endif
