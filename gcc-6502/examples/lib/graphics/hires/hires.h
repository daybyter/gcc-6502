#ifndef _HIRES_H_
#define _HIRES_H_


/**
 * The background color.
 */
extern unsigned char background_hires;


/**
 * A pointer to the CIA 2 (controls the VIC bank).
 */
extern unsigned char *cia2;


/**
 * The foreground color.
 */
extern unsigned char foreground_hires;


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
void box_hires( unsigned int x
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
extern unsigned char *calculateBitmapPointer_hires( unsigned int x
						    , unsigned char y);


/**
 * Clear the screen.
 */
void clearscreen_hires( void);


/**
 * Get the max color index.
 *
 * @return The max color index.
 */
unsigned int getMaxColor_hires( void);

  
/**
 * Get the max horizontal pixel coordinate.
 *
 * @return The max horizontal pixel coordinate.
 */
unsigned int getMaxX_hires( void);


/**
 * Get the max vertical pixel coordinate.
 *
 * @return The max vertical pixel coordinate.
 */
unsigned char getMaxY_hires( void);


/**
 * Init the hires graphics mode.
 */
void grafmode_hires( void);


/**
 * Draw a frame.
 *
 * @param x The horizontal coordinate of the upper left corner.
 * @param y The vertical coordinate of the upper left corner.
 * @param x2 The horizontal coordinate of the lower right corner.
 * @param y2 The vertical coordinate of the lower right corner.
 * @param color The color to use.
 */
void frame_hires( unsigned int x
		  , unsigned char y
		  , unsigned int x2
		  , unsigned char y2
		  , unsigned char color);

 
/**
 * A faster method to draw horizontal lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param x2 The second horizontal coordinate.
 * @param color The color to plot.
 */
void horizontalLine_hires( unsigned int x
			   , unsigned char y1
			   , unsigned int x2
			   , unsigned char color);


/**
 * Plot a pixel in hires mode.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 1 = foreground color, 0 = background color.
 */
void plot_hires( unsigned int x, unsigned char y, unsigned char color);


/**
 * Set the background color.
 *
 * @param color The new background color.
 */
void setBackgroundColor_hires( unsigned char color);


/**
 * Set the foreground color.
 *
 * @param color The new foreground color.
 */
void setForegroundColor_hires( unsigned char color);


/**
 * A faster method to draw vertical lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param y2 The second vertical coordinate.
 * @param color The color to plot.
 */
void verticalLine_hires( unsigned int x
			 , unsigned char y1
			 , unsigned char y2
			 , unsigned char color);

#endif
