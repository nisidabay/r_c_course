/*
 * Exercise 07 — Variadic Functions
 *
 * Implement a variadic function sum_all(int count, ...) that sums all
 * integer arguments passed after count and prints the total.
 *
 * Expected output:
 *   sum_all(3, 10, 20, 30)  = 60
 *   sum_all(5, 1, -2, 3, -4, 5) = 3
 *   sum_all(0)  = 0
 *
 * Hints:
 *   - #include <stdarg.h>, <stdio.h>, <stdlib.h>
 *   - va_list args;
 *   - va_start(args, count);
 *   - for (int i = 0; i < count; i++) total += va_arg(args, int);
 *   - va_end(args);
 *   - printf("sum_all(...) = %d\n", total);
 */
