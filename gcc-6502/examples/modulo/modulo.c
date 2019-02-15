/**
 * Test of gcc modulo calculation.
 */

#include <stdio.h>


int main( int argc, char **argv) {

  int c;

  for( int a = 10; a <= 100; ++a) {
    for( int b = 5; b < 8; ++b) {
      c = a % b;
      printf( "%d mod %d is %d\n", a, b, c);
    }
  }
}
