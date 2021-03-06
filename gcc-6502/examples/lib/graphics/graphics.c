/**
 * Some simple graphics routines for the commodore 64.
 *
 * Author(s): Andreas Rueckert <arueckert67@t-online.de>
 */

#include "graphics.h"
#include "256color/256color.h"
#include "hires/hires.h"
#include "multicolor/multicolor.h"
#include <string.h>


/**
 * Pointers to the graphics functions.
 */

// Draw a box.
void (*box)( unsigned int x
	     , unsigned char y
	     , unsigned int x2
	     , unsigned char y2
	     , unsigned char color);


// Clear the screen.
void (*clearscreen)( void);


// Draw a frame.
void (*frame)( unsigned int x
	       , unsigned char y
	       , unsigned int x2
	       , unsigned char y2
	       , unsigned char color);

// Pointer to the getMax* functions. 
unsigned int (*getMaxX)(void); // = &getMaxX_text;
unsigned char (*getMaxY)(void); // = &getMaxY_text;
unsigned int (*getMaxColor)(void); // = &getMaxColor_text;

// Draw fast horizontal lines.
void (*horizontalLine)(unsigned int x
		       , unsigned char y
		       , unsigned int x2
		       , unsigned char color);

// Plot a single pixel.
void (*plot)( unsigned int x, unsigned char y, unsigned char color);

// Set the background color
void (*setBackgroundColor)( unsigned char color);

// Set the foreground color
void (*setForegroundColor)( unsigned char color);

// Draw a vertical line.
void (*verticalLine)( unsigned int x, unsigned char y1, unsigned char y2, unsigned char color);


/**
 * The current graphics mode.
 */
unsigned char current_graphicmode;


/**
 * A pointer to the screen buffer.
 */
unsigned char *screenbuffer;

/**
 * A pointer to the text buffer.
 */
unsigned char *textbuffer = (unsigned char *)1024;

/**
 * A pointer to the VIC registers.
 */
unsigned char *vic = (unsigned char *)0xd000;

/**
 * A pointer to the copied character rom.
 */
unsigned char *char_ram = (unsigned char *)0x3000;

/**
 * A pointer to the CIA 2 (controls the VIC bank).
 */
unsigned char *cia2 = (unsigned char *)0xdd00;


/**
 * Convert a character to c64 screen code.
 *
 * @param c The character to convert.
 * @return The converted character or a space, if there is
 *         no proper conversion possible.
 */
char convert2c64screencode( char c) {

  if( c >= 'A' && c <= 'Z') {
    return c - 'A' + 1;
  }

  if( c >= 'a' && c <= 'z') {
    return c - 'a' + 1;
  }

  if( c >= '0' && c <= '9') {
    return c -'0' + 48;
  }
  
  return ' '; /* Return a space as default. */
}



/**
 * Get the current border color.
 *
 * @return The current border color.
 */
unsigned char getBorderColor() {
  return vic[0x20];
}

/**
 * Enter the graphics mode.
 * 
 * @param mode The selected graphics mode.
 */
void grafmode( unsigned char mode) {

  // Store the selected graphics mode.
  current_graphicmode = mode;
  
  if( mode == TEXTMODE_40_25) {
    
    textmode();
    
  } else {  // This is a bitmap mode.

    if( mode == GRAFMODE_160_200_4) {

      grafmode_multicolor();

      // Set the plot method to multicolor plot.
      box = &box_multicolor;
      clearscreen = &clearscreen_multicolor;
      frame = &frame_multicolor;
      horizontalLine = &horizontalLine_multicolor;
      plot = &plot_multicolor;
      verticalLine = &verticalLine_multicolor;
      getMaxX = &getMaxX_multicolor;
      getMaxY = &getMaxY_multicolor;
      getMaxColor = &getMaxColor_multicolor;
      setBackgroundColor = &setBackgroundColor_multicolor;
      setForegroundColor = &setForegroundColor_multicolor;
      
    } else if( mode == GRAFMODE_320_200_2) {

      grafmode_hires();
      
      box = &box_hires;
      clearscreen = &clearscreen_hires;
      frame = &frame_hires;
      horizontalLine = &horizontalLine_hires;
      plot = &plot_hires;
      verticalLine = &verticalLine_hires;
      getMaxX = &getMaxX_hires;
      getMaxY = &getMaxY_hires;
      getMaxColor = &getMaxColor_hires;
      setBackgroundColor = &setBackgroundColor_hires;
      setForegroundColor = &setForegroundColor_hires;
      
    } else if( mode == GRAFMODE_320_200_256) {
      
      grafmode_256color();
      
      box = &box_256color;
      clearscreen = &clearscreen_256color;
      frame = &frame_256color;
      horizontalLine = &horizontalLine_256color;
      plot = &plot_256color;
      verticalLine = &verticalLine_256color;
      getMaxX = &getMaxX_256color;
      getMaxY = &getMaxY_256color;
      getMaxColor = &getMaxColor_256color;
      setBackgroundColor = &setBackgroundColor_256color;
      setForegroundColor = &setForegroundColor_256color;
    }
  }
}

/* signum function */
int sgn(int x){
  return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

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
	   , unsigned char color) {

  // Use special routines for vertical lines.
  if( x1 == x2) {
    verticalLine( x1, y1, y2, color);
  }
  
  // Implementation taken from
  // https://de.wikipedia.org/wiki/Bresenham-Algorithmus#C-Implementierung  
  int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;

  /* Entfernung in beiden Dimensionen berechnen */
   dx = x2 - x1;
   dy = y2 - y1;

/* Vorzeichen des Inkrements bestimmen */
   incx = sgn(dx);
   incy = sgn(dy);
   if(dx<0) dx = -dx;
   if(dy<0) dy = -dy;

/* feststellen, welche Entfernung größer ist */
   if( dx > dy) {
      /* x ist schnelle Richtung */
      pdx=incx; pdy=0;    /* pd. ist Parallelschritt */
      ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
      es =dy;   el =dx;   /* Fehlerschritte schnell, langsam */
   } else {
      /* y ist schnelle Richtung */
      pdx=0;    pdy=incy; /* pd. ist Parallelschritt */
      ddx=incx; ddy=incy; /* dd. ist Diagonalschritt */
      es =dx;   el =dy;   /* Fehlerschritte schnell, langsam */
   }

   /* Initialisierungen vor Schleifenbeginn */
   x = x1;
   y = y1;
   err = el/2;
   plot(x,y,color);

   /* Pixel berechnen */
   for(t=0; t<el; ++t) { /* t zaehlt die Pixel, el ist auch Anzahl */
   
      /* Aktualisierung Fehlerterm */
      err -= es;
      if(err<0) {
          /* Fehlerterm wieder positiv (>=0) machen */
          err += el;
          /* Schritt in langsame Richtung, Diagonalschritt */
          x += ddx;
          y += ddy;
      } else {
          /* Schritt in schnelle Richtung, Parallelschritt */
          x += pdx;
          y += pdy;
      }
      plot(x,y,color);
   }
}


/**
 * Set a new border color.
 *
 * @param color The new border color.
 */
void setBorderColor( unsigned char color) {
  vic[0x20] = color;
}

/**
 * Return to the text mode.
 */
/*
void textmode( void) {

  unsigned char *vic = (unsigned char *)0xd000;

  //plot = &plot_text;
  getMaxX = &getMaxX_text;
  getMaxY = &getMaxY_text;
  getMaxColor = &getMaxColor_text;

  // ToDo: set VIC bank to 0 and textbuffer back to 1024.
}
*/

