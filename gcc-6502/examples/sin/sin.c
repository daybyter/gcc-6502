// Test app for graphics mode

#include "graphics.h"
#include "math.h"

int main( int argc, char **argv) {

  grafmode( GRAFMODE_320_200_2);
  
  int resX = 320;
  int resY = 200;
  int y;
  
  for( int x = 0; x < resX; ++x) {

    y = resY / 2 - resY / 2 * sinf( 2 * PI * x / resX);

    plot( x, y, 1);
  }


  textmode(); 
}
