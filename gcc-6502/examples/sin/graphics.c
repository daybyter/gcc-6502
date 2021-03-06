/**
 * Some simple graphics routines for the commodore 64.
 *
 * Author(s): Andreas Rueckert <arueckert67@t-online.de>
 */

#include "graphics.h"
#include <string.h>


/* Pointer to a plot function. */
void (*plot)( unsigned int, unsigned char, unsigned char);

// Keep the plot routines local, so they are not in the header.
void plot_hires( unsigned int x, unsigned char y, unsigned char color);
void plot_multicolor( unsigned int x, unsigned char y, unsigned char color);

// The local implementations for the different resolutions.
int getMaxX_hires(void);
int getMaxX_multicolor(void);
int getMaxX_text(void);
int getMaxY_hires(void);
int getMaxY_multicolor(void);
int getMaxY_text(void);
int getMaxColor_hires(void);
int getMaxColor_multicolor(void);
int getMaxColor_text(void);

/* Pointer to the getMax* functions. */
int (*getMaxX)(void) = &getMaxX_text;
int (*getMaxY)(void) = &getMaxY_text;
int (*getMaxColor)(void) = &getMaxColor_text;

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
 * A pointer to the CIA 2 (controls the VIC bank).
 */
unsigned char *cia2 = (unsigned char *)0xdd00;

/**
 * Get the max horizontal coordinate.
 */
int getMaxX_hires(void) { return 319; }
int getMaxX_multicolor(void) { return 159; }
int getMaxX_text(void) { return 39; }

/**
 * Get the max vertical coordinate.
 */
int getMaxY_hires(void) { return 199; }
int getMaxY_multicolor(void) { return 199; }
int getMaxY_text(void) { return 24; }

/**
 * Get the max color index.
 */
int getMaxColor_hires(void) { return 1; }
int getMaxColor_multicolor(void) { return 3; }
int getMaxColor_text(void) { return 15; }


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

    cia2[0] &= 0xfc;  // Set the VIC bank to the 2nd bank
    cia2[0] |= 0x02;  // 0x4000 - 0x7fff to make room for bigger apps.
    
    vic[17] |= 0x20;     // Set bit 5 of $d011 to activate hires mode.
    
    vic[24] |= 0x08;     // Set screenbuf to vic-base + 8192;
    
    vic[24] &= 0x0f;   // Move the screen ram right before the bitmap.
    vic[24] |= 0x70;   // at 0x5c00

    textbuffer = (unsigned char *)0x5c00;
    
    vic[32] = 0;  // Set border color to black.
  
    // Set a pointer to the screen buffer.
    screenbuffer = (unsigned char *)0x6000;

    if( mode == GRAFMODE_160_200_4) {
      vic[0x16] |= 0x10;

      // Set the color 3 to black
      memset( (void *)0xd800, 0, 1000);

      // Set the background color to white
      vic[0x21] = 1;

      // Set the plot method to multicolor plot.
      plot = &plot_multicolor;
      getMaxX = &getMaxX_multicolor;
      getMaxY = &getMaxY_multicolor;
      getMaxColor = &getMaxColor_multicolor;
      
    } else {

      // Set the plot method to hires.
      plot = &plot_hires;
      getMaxX = &getMaxX_hires;
      getMaxY = &getMaxY_hires;
      getMaxColor = &getMaxColor_hires;
    }
    
    // Clear the screen.
    memset( screenbuffer, 0, 8000);

    // Clear the text ram (used as color ram now).
    memset( textbuffer, 0xa2, 1000);
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
 * Plot a pixel in hires mode.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 1 = foreground color, 0 = background color.
 */
void plot_hires( unsigned int x, unsigned char y, unsigned char color) {

  // Compute the address of the byte to modify.
  unsigned int ytextline = y >> 3;
  unsigned int addy = (ytextline << 8)
    + (ytextline << 6)
    + (x & 0xfff8)
    + (y & 7);

  // Compute the bitmask to use.
  unsigned char bitmask = (0x80 >> ( x & 7));

  if( color == 1) {
    screenbuffer[addy] |= bitmask;
  } else {
    screenbuffer[addy] &= ~bitmask;
  }
}
/**
 * Plot a pixel in multicolor mode.
 * 
 * @param x The horizontal coordinate.
 * @param y The vertical coordinate.
 * @param color 0-3
 */
void plot_multicolor( unsigned int x, unsigned char y, unsigned char color) {

  // Just double x for now.
  x <<= 1;
  
  // Compute the address of the byte to modify.
  unsigned int ytextline = y >> 3;
  unsigned int addy = (ytextline << 8)
    + (ytextline << 6)
    + (x & 0xfff8)
    + (y & 7);

  screenbuffer[addy] &= (~(0xc0 >> (x & 7)));
  screenbuffer[addy] |= ((color << 6) >> (x & 7));
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
void textmode( void) {

  unsigned char *vic = (unsigned char *)0xd000;
 
  vic[17] &= 0xdf;  // Clear hires bit.

  //plot = &plot_text;
  getMaxX = &getMaxX_text;
  getMaxY = &getMaxY_text;
  getMaxColor = &getMaxColor_text;

  // ToDo: set VIC bank to 0 and textbuffer back to 1024.
}
