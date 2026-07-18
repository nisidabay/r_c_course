/*
 * Exercise 10 — Assert (assert.h)
 *
 * Add assertions to a function that computes the average of an array.
 * The function has preconditions: the array must not be NULL, and the
 * size must be positive.
 *
 * Then write a divide function that asserts the divisor is non-zero.
 *
 * Expected output:
 *   average({10, 20, 30}, 3) = 20.0
 *   safe_divide(10, 2) = 5
 *
 * Hints:
 *   - #include <assert.h>
 *   - assert(arr != NULL);
 *   - assert(n > 0);
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
