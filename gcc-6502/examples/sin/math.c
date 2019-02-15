/**
 * Some simple implementations of math routines.
 *
 * A. Rueckert <arueckert@t-online.de>
 */

#include "math.h"

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
 * Sine method taken from:
 * http://codereview.stackexchange.com/questions/5211/sine-function-in-c-c
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

/**
 * Square root function for a float input.
 * @see http://stackoverflow.com/questions/1623375/writing-your-own-square-root-function
 *
 * @param f The float input.
 *
 * @return The square root of f.
 */
float sqrtf( float f) {

  float errorMargin = 0.0004;  // The desired error margin.
  
  if( f < 0) {
    return NaN;
  }
  
  float a = 1;
  float b = f;
    
  while( fabs ( a - b ) > errorMargin) {
    a = ( a + b) / 2;
    b = f / a;
  }
  
  return a;
}
