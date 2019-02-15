#include "math.h"


/**
 * Square root function for a float input.
 * Based on the fast algorithm for inverse square roots.
 * But since x * (1/sqrt(x) = sqrt(x) ...
 * @see https://en.wikipedia.org/wiki/Fast_inverse_square_root
 * @see http://stackoverflow.com/questions/19542275/fast-square-root-optimization
 *
 * @param f The float input.
 *
 * @return The square root of f.
 */
float sqrtf( float f) {
  volatile float converted = convertCBM_2_IEEE754( f);

  volatile union { // get bits for floating value
    float x;
    long i;
  } u;

  u.x = converted;
  
  u.i  = 0x5f3759dfL - (u.i >> 1); // what the fuck?

  // Convert i to a float again.
  volatile float seed = convertIEEE754_2_CBM( u.x);

  volatile float sqrt = seed * (1.5f - 0.5f * f * seed * seed);

#ifdef higher_precision

  // Do another iteration for higher precision
  seed * (1.5f - 0.5f * f * seed * seed);
#endif
  
  return f * sqrt;
}


/**
 * @see http://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
 */
/*
float sqrtf( float m) {
int i=0; 
while( (i*i) <= m ) {
          i++;
}
i--; 
float d = m - i*i; 
float p=d/(2*i); 
float a=i+p; 
return a-(p*p)/(2*a);
}  
*/
/**
 * Square root function for a float input.
 * @see http://stackoverflow.com/questions/1623375/writing-your-own-square-root-function
 *
 * @param f The float input.
 *
 * @return The square root of f.
 */
/*
float sqrtf_first( float f) {

  float errorMargin = 0.0004;  // The desired error margin.
  
  if( f < 0) {
    return NaN;
  }
  
  float a = 1;
  float b = f;
    
  while( fabs( a - b ) > errorMargin) {
    a = ( a + b) * 0.5f;
    b = f / a;
  }
  
  return a;
}
*/
