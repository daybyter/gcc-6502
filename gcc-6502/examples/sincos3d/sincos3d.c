/**
 * Simple 3d curve plot. Taken from:
 *http://www.forum64.de/index.php?thread/45525-real-zahlen-und-funktionen-im-cc65-nutzen-zur-umsetzung/&postID=560586#post560586
 */
 
#include "graphics.h"
#include "math.h"
#include <stdio.h>
#include "time.h"

#define use_horizon_array

int main( int argc, char **argv) {
  
  int XRes, YRes;
  float xf, xfMin, xfMax, xfDelta, yf, yfMin, yfMax, yfDelta;
  float radiusf, zf, zScale;
  int x,y;
  time_t start_time, elapsed_time;

  init_timer();
  
  /* Load and initialize the graphics */
  grafmode( GRAFMODE_320_200_2);

  setForegroundColor( COLOR_BLACK);
  setBackgroundColor( COLOR_WHITE);
  
  setBorderColor( COLOR_WHITE);

  clearscreen();
  
  /* Get stuff from the graph lib */
  //XRes = getMaxX() + 1;
  XRes = 320;
  //YRes = getMaxY() + 1; 
  YRes = 200;
  unsigned char YMax = YRes - 1;

#ifdef use_horizon_array
  // Init a horizon array.
  unsigned char horizon[ 320];
  for( int i = 0; i < 320; ++i) {
    horizon[i] = 199;
  } 
#endif
  
  // Show some info
  drawString( "Sin cos curve", 200, 20, 1);

  // Get the system time when the calculation is started.
  start_time = time(NULL);
  
  /* Compute and draw a 3d function. */
  yfMin = -144.0f;
  yfMax = 144.0f;
  
  yfDelta = 2.25f;
  zScale = 20.0f;

  unsigned int XResHalf = XRes * 0.5;
  float yfMinSquare = yfMin * yfMin;

#ifdef use_horizon_array
  for( yf = yfMax- yfDelta; yf >= yfMin; yf -= yfDelta) {
#else
  for( yf = yfMin; yf < yfMax; yf += yfDelta) {
#endif
      
    xfMax = sqrtf( yfMinSquare - yf  * yf);
    xfMin = -xfMax;
    xfDelta = 1.0f;
    
    // Constant terms from the inner loop
    float yfD = yf / yfDelta;
    float a = XResHalf + yfD;
    float b=  YMax + yfD - 90;

    float yfSquare = yf * yf;
    
    for( xf = xfMin; xf < xfMax; xf += xfDelta) {
  
      radiusf = .0327f * sqrtf( xf * xf + yfSquare);
      
      zf = zScale * ( cosf( radiusf)
		      + cosf( 2*radiusf)
		      + cosf( 5 *radiusf));
      

      /* Scale to screen coordinates */
      x = 0.85f * ( xf + a);
 
      y = 0.9f * ( b - zf);

      if( y > 0 && y < YRes) {

#ifdef use_horizon_array
	// Check horizon, if we should plot
        if( y < horizon[x]) {
          
          plot( x, y, 1);
          horizon[x] = y;
        }
#else
	plot( x, y, 1);
	if( y < ( YRes - 1)) {
	  line( x, y, x, YRes-1, 0);  // Clear horizon
	}
#endif	
      }
    }
  }

  // Get the system time when the calculation has ended
  // and compute the difference to get the elapsed time.
  elapsed_time = start_time - time(NULL);

  // Display this time.
  char time_buffer[15];

  sprintf( time_buffer, "Time: %d s", (int)elapsed_time);

  drawString( time_buffer, 200, 40, 1);

  // This is just a hack to stop the program.
  // This should be a getchar() , but I cannot
  // find this method in the tinylib yet.
  while(1);
  
  // Reset to textmode.
  textmode();
  
  puts( "Done\n");
  return 0;
}
