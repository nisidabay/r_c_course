/*
 * Exercise 05 — XOR swap (no temporary variable)
 *
 * Swap two integers using XOR — without a temporary variable.
 *
 * The classic trick:
 *   a ^= b;
 *   b ^= a;
 *   a ^= b;
 *
 * After these three lines, a and b have swapped values.
 *
 * Expected output:
 *   Before: a = 42, b = 99
 *   After:  a = 99, b = 42
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
