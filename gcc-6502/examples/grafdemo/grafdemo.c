/**
 * Very simple graphics demo.
 */

#include "graphics.h"

int main( int argc, char **argv) {

  grafmode();  // Init hires mode.

  for( int i = 0; i < 320; ++i) {

    line( i, 0, 319-i, 199, 1);
  }

  textmode();
  
  return 0;
}
