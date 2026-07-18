/*
 * Exercise 04 — calloc and realloc
 *
 * Use calloc to zero-initialize an array, then realloc to resize it.
 *
 * Expected output:
 *   After calloc: 0 0 0 0 0
 *   After realloc to 8: 0 0 0 0 0 0 0 0
 *
 * Hints:
 *   - int *arr = calloc(5, sizeof(int));
 *   - arr = realloc(arr, 8 * sizeof(int));
 *   - Check both for NULL before using
 *   - free(arr) at the end
 *   - #include <stdlib.h>, <stdio.h>
 */
