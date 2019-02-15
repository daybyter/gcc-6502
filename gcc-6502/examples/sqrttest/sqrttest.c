#include "math.h"
#include <stdio.h>


// see: http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
//assumes little endian
void printBits(size_t const size, void const * const ptr) {
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--) {
        for (j=7;j>=0;j--) {
            byte = (b[i] >> j) & 1;
	    putc(byte, stdout);
        }
    }
    puts("");
}


int main( int argc, char **argv) {

  float f =  0.15625;
  
  printf( "\016sqrt( 0.15625) is: %f \n", sqrtf( f));
  printf( "float %f is: ", f);
  printBits( sizeof(float), &f);
  printf( "\n");
  
  float converted = convertCBM_2_IEEE754( f);
    
  printf( "IEEE 754 converted: ");
  printBits( sizeof(float), &converted);
  printf( "\n");

  long i  = *(long*)&converted;  // evil floating point bit level hacking
  i >>= 1;
  printf( "i >> 1 is: ");
  printBits( sizeof(long), &i);

  
  printf("Magic number: ");
  long magic = 0x5f3759dfL;
  printBits( sizeof(long), &magic);
  printf( "\n");
  
  i  = 0x5f3759dfL - i; // what the fuck?
  printf( "magic - (i >> 1): ");
  printBits( sizeof(long), &i);
  printf( "\n");

  // Convert i to a float again. Should be about y = 2.61486
  float seed = convertIEEE754_2_CBM( *( float *)&i);
  printf( "seed is: %f\n", seed);

  float sqrt = f * seed * (1.5f - 0.5f * f * seed * seed);

  printf( "Sqrt is: %f\n", sqrt);
  
  for( float fe = 0.0; fe < 1.0; fe += 0.1) {
    printf( "\016sqrt of %f is:", fe);
    printf( "%f", sqrtf(fe));
    printf( "\n");
  } 
}

