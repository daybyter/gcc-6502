// Mandelbrot program for gcc 6502 on c64
// Taken from http://newt.phys.unsw.edu.au/~mcba/phys2020/notes/mandelbrot.html
// And then modified for gcc @ c64 by A Rueckert

// Original header:
/*
  A program to generate an image of the Mandelbrot set. 

  Usage: ./mandelbrot > output
         where "output" will be a binary image, 1 byte per pixel
         The program will print instructions on stderr as to how to
         process the output to produce a JPG file.

  Michael Ashley / UNSW / 13-Mar-2003
*/

#include "graphics.h"  // Simple graph lib for gcc & c64
#include <stdio.h>
#include <limits.h>

const float xCentre = -0.75;
const float yCentre = +0.0;
const float dxy     = 0.005;


int main() {

    float cx, cy;
    float zx, zy, new_zx;
    unsigned char n;
    int i, j;

    // Activate 160x200x4 multicolor mode.
    grafmode(GRAFMODE_160_200_4);
    
    // The Mandelbrot calculation is to iterate the equation
    // z = z*z + c, where z and c are complex numbers, z is initially
    // zero, and c is the coordinate of the point being tested. If
    // the magnitude of z remains less than 2 for ever, then the point
    // c is in the Mandelbrot set. We write out the number of iterations
    // before the magnitude of z exceeds 2, or UCHAR_MAX, whichever is
    // smaller.

    for( j = 0; j < (getMaxY()+1); ++j) {
      cy = yCentre + (j - (getMaxY()+1)/2)*dxy;
      for (i = 0; i < (getMaxX()+1); ++i) {
	cx = xCentre + (i - (getMaxX()+1)/2)*dxy*2;
	zx = 0.0; 
	zy = 0.0; 
	n = 0;
	while ((zx*zx + zy*zy < 4.0) && (n != 255)) {
	  new_zx = zx*zx - zy*zy + cx;
	  zy = 2.0*zx*zy + cy;
	  zx = new_zx;
	  n++;
	}
	plot(i,j,n & getMaxColor()); // Plot the result
      }
    }

    textmode();
    
    return 0;
}
