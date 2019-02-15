/**
 * Some simple implementations of math routines.
 *
 * A. Rueckert <arueckert@t-online.de>
 */

#ifndef _MATH_H_
#define _MATH_H_


/* Define constants. */
#define PI 3.14159265

#define NaN (0.0/0)


/**
 * cos method.
 *
 * @param radians The input angle as radians.
 *
 * @return cos(radians)
 */
float cosf( float radians);

/**
 * Absolute function for floats.
 *
 * @param x The input.
 *
 * @return -x, if x < 0. x otherwise.
 */
float fabs( float x);

/**
 * Sine method taken from:
 * http://codereview.stackexchange.com/questions/5211/sine-function-in-c-c
 *
 * @param radians angle as radians.
 *
 * @return sin(radians)
 */
float sinf(float radians);

/**
 * Square root function for a float input.
 * @see http://stackoverflow.com/questions/1623375/writing-your-own-square-root-function
 *
 * @param f The float input.
 *
 * @return The square root of f.
 */
float sqrtf( float f);

#endif
