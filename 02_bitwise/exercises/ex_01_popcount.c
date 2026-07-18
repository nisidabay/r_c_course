/*
 * Exercise 01 — Count set bits (popcount)
 *
 * Write a function that counts how many bits are 1 (set) in an
 * unsigned int.
 *
 * Hints:
 *   - Check each bit position from 0 to 31
 *   - (n >> i) & 1 gives you the i-th bit
 *   - Or use the trick: n & (n - 1) clears the lowest set bit
 *
 * Expected output:
 *   Enter a number: 42
 *   42 in binary: 00000000 00000000 00000000 00101010
 *   Set bits: 3
 *
 *   (42 = 32 + 8 + 2 → bits 5, 3, 1 are set)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
