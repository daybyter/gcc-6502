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
   These few assembler lines replace the following C code:

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
float convertIEEE754_2_CBM( float num) {

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
    These few assembler lines replace the following C code:

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




