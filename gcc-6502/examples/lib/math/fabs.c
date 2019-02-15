#include "math.h"


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
