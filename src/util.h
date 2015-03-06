#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

/*
 * Print an pretty formatted error message and then kill everything.
 */
void die(char *);

/*
 * Spawn an arbitrary command.
 */
void spawn(void *, uint32_t, uint32_t, uint32_t);

#endif

