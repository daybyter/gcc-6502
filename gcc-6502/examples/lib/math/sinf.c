#include "math.h"


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
