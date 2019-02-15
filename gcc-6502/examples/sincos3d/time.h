/**
 * Declarations for time operations.
 */

#ifndef _TIME_H_
#define _TIME_H_


/**
 * Define a type for timestamp values.
 */
typedef long time_t;


/**
 * Init the cia1 tod clock.
 */
void init_timer();

/**
 * Get the current system time.
 *
 * @param tp Pointer to a time var to be set, or NULL.
 *
 * @return The current system time as seconds. Not necessarily the epoch
 *         time (since 1.1.1970), since the c64 has no battery buffered
 *         realtime clock in it's stock configuration.
 */
time_t time( time_t *tp);

#endif
