/*
 * Exercise 02 — Power of 2 check
 *
 * Write a function that returns 1 if n is a power of 2, 0 otherwise.
 *
 * A power of 2 has exactly ONE bit set (e.g., 1, 2, 4, 8, 16...).
 * The trick: n & (n - 1) clears the lowest set bit.  If the result
 * is 0, there was only one set bit.
 *
 * But don't forget: 0 is NOT a power of 2!
 *
 * Expected output:
 *   Enter a number: 64
 *   64 is a power of 2
 *
 *   Enter a number: 42
 *   42 is NOT a power of 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
