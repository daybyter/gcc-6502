/**
 * Some simple implementations of math routines.
 *
 * A. Rueckert <arueckert@t-online.de>
 */

#include "math.h"

/**
 * Convert a CBM style 32 bit float to ieee format.
 *
 * @param floatAddy The address of the float to convert.
 */
inline float convertCBM_2_IEEE754( float num) {

  __asm__ __volatile__
    (
     "rol %0+2\n\t"
     "ror %0+3\n\t"
     "ror %0+2\n\t"
     : "=Zp" (num)
     : "0" (num)
     : "a", "x", "y");
  
  return num;

  /*
  // These few assembler lines replace the following C code:

  unsigned char new_byte2, new_byte3;
  unsigned char *floatAddy = (unsigned char *)&num;
  float result = num;

  // Just an ugly hack to get something going.
  // Should be done with a few machine instructions.
  new_byte3 = (floatAddy[2] & (unsigned char)0x80) | (floatAddy[3] >> 1);
  new_byte2 = ((floatAddy[3] & 0x1) << 7) | (floatAddy[2] & (unsigned char)0x7f);
  floatAddy = (unsigned char *)&result;

  floatAddy[2] = new_byte2;  // Set the new bytes.
  floatAddy[3] = new_byte3;

  return result;
  */
}

/**
 * Convert a ieee 754 float to CBM float format.
 *
 * @param floatAddy The address of the float to convert.
 */
inline float convertIEEE754_2_CBM( float num) {

  __asm__ __volatile__
    (
     "rol %0+2\n\t"
     "rol %0+3\n\t"
     "ror %0+2\n\t"
     : "=Zp" (num)
     : "0" (num)
     : "a", "x", "y");
  
  return num;

  /*
  //  These few assembler lines replace the following C code:

  unsigned char new_byte2, new_byte3;
  unsigned char *floatAddy = (unsigned char *)&num;
  float result = num;

  // Just an ugly hack to get something going.
  // Should be done with a few machine instructions.
  new_byte2 = (floatAddy[2] & 0x7f) | (floatAddy[3] & 0x80);
  new_byte3 = (floatAddy[3] << 1) | ((floatAddy[2] & 0x80) >> 7);

  floatAddy = (unsigned char *)&result;
   
  floatAddy[2] = new_byte2;  // Set the new bytes.
  floatAddy[3] = new_byte3;

  return result;
  */
}

/**
 * cos method.
 *
 * @param radians The input angle as radians.
 *
 * @return cos(radians)
 */
float cosf( float radians) {

  return sinf( (PI/2) - radians);
}

/**
 * Absolute function for floats.
 *
 * @param x The input.
 *
 * @return -x, if x < 0. x otherwise.
 */
float fabs( float x) {
  
  return (x < 0) ? -x : x;
}

/**
 * Sine method taken from 
 * http://forum.devmaster.net/t/fast-and-accurate-sine-cosine/9648
 * 
 * @param radians angle as radians.
 *
 * @return sin(radians)
 */
float sinf(float radians) {

  /* Ensure, that radians is in the -pi .. pi range. */
  while( radians > PI) {
    radians -= 2 * PI;
  }
  while( radians < -PI) {
    radians += 2 * PI;
  }
  
  const float B = 4/PI;
  const float C = -4/(PI*PI);

  float y = B * radians + C * radians * fabs(radians);

#ifdef EXTRA_PRECISION
  //  const float Q = 0.775;
  const float P = 0.225;

  y = P * (y * fabs(y) - y) + y;   // Q * y + P * y * abs(y)
#endif

  return y;
}

/**
 * Sine method taken from:
 * http://codereview.stackexchange.com/questions/5211/sine-function-in-c-c
 *
 * @param radians angle as radians.
 *
 * @return sin(radians)
 */
/*
float sinf_old(float radians) {

  // Ensure, that radians is in the -pi .. pi range.
  while( radians > PI) {
    radians -= 2 * PI;
  }
  while( radians < -PI) {
    radians += 2 * PI;
  }

  float x = radians;
  float x2 = x*x;
  float f = 1;
  float s = 0;
  int i = 1;

  s += x/f; x *= x2; f *= ++i; f *= ++i;
  s -= x/f; x *= x2; f *= ++i; f *= ++i;
  s += x/f; x *= x2; f *= ++i; f *= ++i;
  s -= x/f; x *= x2; f *= ++i; f *= ++i;
  s += x/f; x *= x2; f *= ++i; f *= ++i;
  s -= x/f; x *= x2; f *= ++i; f *= ++i;
  s += x/f; x *= x2; f *= ++i; f *= ++i;
  s -= x/f; x *= x2; f *= ++i; f *= ++i;

  return s;
}
*/

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
