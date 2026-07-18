/*
 * Exercise 05 — Growable Array
 *
 * Start with a small array and grow it dynamically as needed.
 *
 * Expected output:
 *   Capacity: 4, elements: 1 2 3 4
 *   Capacity: 8, elements: 1 2 3 4 5 6 7 8
 *
 * Hints:
 *   - int capacity = 4; int *arr = malloc(capacity * sizeof(int));
 *   - int count = 0;
 *   - When count == capacity: capacity *= 2; arr = realloc(arr, capacity * sizeof(int));
 *   - #include <stdlib.h>, <stdio.h>
 */
