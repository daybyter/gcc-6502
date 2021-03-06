/**
 * Some simple graphics routines for the commodore 64.
 *
 * Author(s): Andreas Rueckert <arueckert67@t-online.de>
 */

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_


/* List of supported modes */
#define TEXTMODE_40_25        0
#define GRAFMODE_320_200_2    1  // c64 hires 320x200 pixel, 2 colors 
#define GRAFMODE_160_200_4    2  // c64 multicolor 160x200 pixel, 4 colors 
#define GRAFMODE_320_200_256  3  // c64dtv 320x200 pixel, 256 colors 


/* List of colors in the default c64 palette */
/* Taken from: http://www.pepto.de/projects/colorvic/ */
#define	COLOR_BLACK 0
#define COLOR_WHITE 1
#define COLOR_RED 2
#define COLOR_CYAN 3
#define COLOR_PURPLE 4
#define COLOR_GREEN 5
#define COLOR_BLUE 6
#define COLOR_YELLOW 7
#define COLOR_ORANGE 8
#define COLOR_BROWN 9
#define COLOR_LIGHT_RED 10
#define COLOR_DARK_GREY 11
#define COLOR_GREY 12
#define COLOR_LIGHT_GREEN 13
#define COLOR_LIGHT_BLUE 14
#define COLOR_LIGHT_GREY 15


// Clear the screen.
extern void (*clearscreen)( void);


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
		    , unsigned char color);

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
		 , unsigned char color);

/**
 * Get the current border color.
 *
 * @return The current border color.
 */
unsigned char getBorderColor();

/**
 * Get the max horizontal coordinate.
 */
extern unsigned int (*getMaxX)(void);

/**
 * Get the max vertical coordinate.
 */
extern unsigned char (*getMaxY)(void);

/**
 * Get the max color index.
 */
extern unsigned int (*getMaxColor)(void);


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


// Set the background color
extern void (*setBackgroundColor)( unsigned char color);


/**
 * Set a new border color.
 *
 * @param color The new border color.
 */
void setBorderColor( unsigned char color);


// Set the foreground color
extern void (*setForegroundColor)( unsigned char color);


/**
 * Return to the text mode.
 */
void textmode( void);

#endif
