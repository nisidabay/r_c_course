/*
 * Exercise 11 — errno
 *
 * Write a function safe_strtol that parses a string into a long and
 * returns 0 on success, -1 on error.  Use errno properly.
 *
 * Then write a function open_config that tries to open "config.txt",
 * and if it fails, prints the error using perror and returns NULL.
 *
 * Hints:
 *   - Remember: errno = 0 before the call
 *   - strtol returns LONG_MIN/LONG_MAX on overflow AND sets errno = ERANGE
 *   - strtol returns 0 with endptr == str on no conversion (but errno is NOT set)
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
