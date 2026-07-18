/*
 * Exercise 06 — Free and Valgrind
 *
 * Allocate memory, use it, and free it. A program with proper free
 * should show no leaks under valgrind.
 *
 * Expected output:
 *   Allocated, used, and freed 100 doubles.
 *
 * Hints:
 *   - double *data = malloc(100 * sizeof(double));
 *   - Fill with loop: data[i] = i * 1.5;
 *   - Print one value as proof
 *   - free(data);
 *   - Run with: valgrind ./program
 *   - #include <stdlib.h>, <stdio.h>
 */
