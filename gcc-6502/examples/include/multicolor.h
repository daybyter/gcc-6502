#ifndef _MULTICOLOR_H_
#define _MULTICOLOR_H_


/**
 * The background color.
 */
extern unsigned char background_multicolor;


/**
 * A pointer to the CIA 2 (controls the VIC bank).
 */
extern unsigned char *cia2;


/**
 * The foreground color.
 */
extern unsigned char foreground_multicolor;


/**
 * Precalculated multicolor bitmaps for each color.
 */
extern unsigned char multicolor_bitmaps[4];


/**
 * A pointer to the screen buffer.
 */
extern unsigned char *screenbuffer;


/**
 * A pointer to the text buffer.
 */
extern unsigned char *textbuffer;


/**
 * A pointer to the VIC registers.
 */
extern unsigned char *vic;


// Utility macros
#define abs(x) ((x<0) ? (-(x)) : (x))


/**
 * Draw a box.
 *
 * @param x The horizontal coordinate of the upper left corner.
 * @param y The vertical coordinate of the upper left corner.
 * @param x2 The horizontal coordinate of the lower right corner.
 * @param y2 The vertical coordinate of the lower right corner.
 * @param color The color to use.
 */
void box_multicolor( unsigned int x
		     , unsigned char y
		     , unsigned int x2
		     , unsigned char y2
		     , unsigned char color);


/**
 * Compute the address of a byte in the bitmap for a given coordinate pair.
 *
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 *
 * @return The address as a pointer.
 */
unsigned char *calculateBitmapPointer_multicolor( unsigned int x
							 , unsigned char y);


/**
 * Clear the screen.
 */
void clearscreen_multicolor( void);


/**
 * Draw a frame.
 *
 * @param x The horizontal coordinate of the upper left corner.
 * @param y The vertical coordinate of the upper left corner.
 * @param x2 The horizontal coordinate of the lower right corner.
 * @param y2 The vertical coordinate of the lower right corner.
 * @param color The color to use.
 */
void frame_multicolor( unsigned int x
		       , unsigned char y
		       , unsigned int x2
		       , unsigned char y2
		       , unsigned char color);


/**
 * Get the max color index.
 *
 * @return The max color index.
 */
unsigned int getMaxColor_multicolor( void);


/**
 * Get the max horizontal pixel coordinate.
 *
 * @return The max horizontal pixel coordinate.
 */
unsigned int getMaxX_multicolor( void);


/**
 * Get the max vertical pixel coordinate.
 *
 * @return The max vertical pixel coordinate.
 */
unsigned char getMaxY_multicolor( void);


/**
 * Init the multicolor graphics mode.
 */
void grafmode_multicolor( void);


/**
 * A faster method to draw horizontal lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param x2 The second horizontal coordinate.
 * @param color The color to plot.
 */
void horizontalLine_multicolor( unsigned int x
				, unsigned char y
				, unsigned int x2
				, unsigned char color);


/**
 * Plot a pixel in multicolor mode.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 0-3
 */
void plot_multicolor( unsigned int x, unsigned char y, unsigned char color);


/**
 * Set the background color.
 *
 * @param color The new background color.
 */
void setBackgroundColor_multicolor( unsigned char color);


/**
 * Set the foreground color.
 *
 * @param color The new foreground color.
 */
void setForegroundColor_multicolor( unsigned char color);


/**
 * A faster method to draw vertical lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param y2 The second vertical coordinate.
 * @param color The color to plot.
 */
void verticalLine_multicolor( unsigned int x
			      , unsigned char y1
			      , unsigned char y2
			      , unsigned char color);

#endif
