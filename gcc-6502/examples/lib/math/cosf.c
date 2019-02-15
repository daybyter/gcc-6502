
#include "math.h"

/**
 * cos method.
 *
 * @param radians The input angle as radians.
 *
 * @return cos(radians)
 */
float cosf( float radians) {

  // Just call the sine functions with a shifted argument.
  return sinf( (PI/2) - radians);
}
