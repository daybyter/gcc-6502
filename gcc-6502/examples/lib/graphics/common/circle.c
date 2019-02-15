
/**
 * Draw a circle.
 * @see: http://members.chello.at/~easyfilter/bresenham.html
 *
 * @param x horizontal coordinate of the center.
 * @param y vertical coordinate of the center.
 * @param radius The radius of the circle.
 * @param color The color to use.
 */
void circle(unsigned int x
	    , unsigned char y
	    , unsigned int radius
	    , unsigned char color) {
  
  int curx = -r;
  int cury = 0;
  int err = 2-2*r; /* II. Quadrant */
  
  do {
    plot(x - curx, y + cury, color); /*   I. Quadrant */
    plot(x - cury, y - curx, color); /*  II. Quadrant */
    plot(x + curx, y - cury, color); /* III. Quadrant */
    plot(x + cury, y + curx, color); /*  IV. Quadrant */
    r = err;
      
    // e_xy+e_y < 0
    if (r <= cury) {
      err += ++cury*2+1;
    }
    
    // e_xy+e_x > 0 or no 2nd y-step 
    if (r > curx || err > cury) {
      err += ++curx*2+1;
    }
  } while (curx < 0);
}
