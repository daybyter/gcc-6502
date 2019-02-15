#ifndef _256COLOR_H_
#define _256COLOR_H_


/**
 * Address of the screen memory.
 */
#define screenbuffer_addy 0x10000L


/**
 * The background color.
 */
extern unsigned char background_256color;


/**
 * The DTV extended VIC base address.
 */
extern unsigned char *dtv_vic;


/**
 * The foreground color.
 */
extern unsigned char foreground_256color;


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
void box_256color( unsigned int x
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
 * @return The address as an unsigned int.
 */
unsigned int calculateBitmapAddress_256color( unsigned int x, unsigned char y);


/**
 * Just clear the screen.
 */
void clearscreen_256color( void);


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
		  , unsigned int length);


/**
 * Draw a frame.
 *
 * @param x The horizontal coordinate of the upper left corner.
 * @param y The vertical coordinate of the upper left corner.
 * @param x2 The horizontal coordinate of the lower right corner.
 * @param y2 The vertical coordinate of the lower right corner.
 * @param color The color to use.
 */
void frame_256color( unsigned int x
		     , unsigned char y
		     , unsigned int x2
		     , unsigned char y2
		     , unsigned char color);

/**
 * Get the max color index.
 *
 * @return The max color index.
 */
unsigned int getMaxColor_256color( void);


/**
 * Get the max horizontal pixel coordinate.
 *
 * @return The max horizontal pixel coordinate.
 */
unsigned int getMaxX_256color( void);


/**
 * Get the max vertical pixel coordinate.
 *
 * @return The max vertical pixel coordinate.
 */
unsigned char getMaxY_256color( void);


/**
 * Enable the 256 color grafphics mode.
 * @see: http://dtvhacking.cbm8bit.com/common/tech/256-mode.html
 */
void grafmode_256color();


/**
 * A faster method to draw horizontal lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param x2 The second horizontal coordinate.
 * @param color The color to plot.
 */
void horizontalLine_256color( unsigned int x
			      , unsigned char y
			      , unsigned int x2
			      , unsigned char color);


/**
 * Plot a pixel in multicolor mode.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 0-255
 */
void plot_256color( unsigned int x, unsigned char y, unsigned char color);


/**
 * Set the background color.
 *
 * @param color The new background color.
 */
void setBackgroundColor_256color( unsigned char color);


/**
 * Set the foreground color.
 *
 * @param color The new foreground color.
 */
void setForegroundColor_256color( unsigned char color);


/**
 * A faster method to draw vertical lines.
 * 
 * @param x The horizontal coordinate.
 * @param y1 The first vertical coordinate.
 * @param y2 The second vertical coordinate.
 * @param color The color to plot.
 */
void verticalLine_256color( unsigned int x
			    , unsigned char y1
			    , unsigned char y2
			    , unsigned char color);

#endif
