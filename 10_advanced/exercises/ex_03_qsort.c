/*
 * Exercise 03 — qsort
 *
 * Use the standard library qsort to sort an array of integers.
 *
 * Expected output:
 *   Before: 42 7 15 3 8
 *   After:  3 7 8 15 42
 *
 * Hints:
 *   - int cmp(const void *a, const void *b) { return *(int*)a - *(int*)b; }
 *   - qsort(arr, 5, sizeof(int), cmp);
 *   - #include <stdlib.h>, <stdio.h>
 */
