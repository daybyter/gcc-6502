/**
 * Code for time operations.
 */

#include <stdio.h>  // Just for the NULL definition...
#include "time.h"

// Base address of the CIA 1 in the c64.
volatile unsigned char *cia1 = (unsigned char *)0xdc00;

/**
 * Convert a bcd number from a cia register to a 8 bit int (char).
 * Bit 7 is never used in the CIA registers, so it is masked here.
 *
 * @param bcd The BCD from the CIA register. 
 *
 * @return The BCD as an 8 bit int (char).
 */
char bcd2int( char bcd) {

  return (bcd & 0x0f) + 10 * ((bcd >> 4) & 7);
}

/**
 * Init the cia1 tod clock.
 */
void init_timer() {

  cia1[14] = 0x80;  // Set to 50 Hz.
  cia1[15] = 0;     // Set TOD clock
  cia1[11] = cia1[10] = cia1[9] = 0;  // Init to 0:00:00:00
  cia1[8] = 0;
}

/**
 * Get the current system time.
 *
 * @param tp Pointer to a time var to be set, or NULL.
 *
 * @return The current system time as seconds. Not necessarily the epoch
 *         time (since 1.1.1970), since the c64 has no battery buffered
 *         realtime clock in it's stock configuration.
 */
time_t time( time_t *tp) {

  time_t result;

  // Just add the BCD number from the CIA realtime clock.
  
  result = (time_t)bcd2int( cia1[11]) * 3600L;  // The hours
  result += (time_t)bcd2int( cia1[10]) * 60L;   // The minutes
  result += (time_t)bcd2int( cia1[9]);          // The seconds
  result += (time_t)bcd2int( cia1[8]) / 10L;    // The 1/10 s to restart clock

  // Write register 8 to restart clock.
  // cia1[8] = 0;
  
  // If the user passed a var in tp, set it.
  if( tp != NULL) {
    *tp = result;
  }

  return result;  // Return the system time as seconds.
}
