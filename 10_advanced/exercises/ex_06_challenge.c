/*
 * Exercise 06 — Challenge: Generic Sorter
 *
 * Write a program that sorts both int and double arrays using qsort
 * with function pointers and _Generic.
 *
 * Expected output:
 *   Ints:   1 2 5 8 9
 *   Doubles: 1.5 2.7 3.1 4.0 5.5
 *
 * Hints:
 *   - Write comparator functions: cmp_int, cmp_double
 *   - qsort for each array
 *   - _Generic to pick the right comparator? Or just call qsort directly
 *   - Print both sorted arrays
 *   - #include <stdlib.h>, <stdio.h>
 */
