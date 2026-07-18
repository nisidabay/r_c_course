/*
 * Exercise 04 — Toggle a bit
 *
 * Write a function that toggles (flips) bit position i in n and
 * returns the new value.
 *
 * Hint: XOR with a mask made of (1 << i).
 *
 * Expected output:
 *   Enter a number: 42
 *   42 in binary: 00000000 00000000 00000000 00101010
 *   Enter bit to toggle (0-31): 1
 *   After toggle:   00000000 00000000 00000000 00101000  (40)
 *   Toggle again:   00000000 00000000 00000000 00101010  (42)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
