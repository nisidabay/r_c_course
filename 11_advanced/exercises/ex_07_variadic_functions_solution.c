/*
 * ex_07_variadic_functions_solution.c
 * Group 10 — Advanced
 * Exercise 07: variadic functions — SOLUTION
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int sum_all(int count, ...) {
    va_list args;
    int total = 0;

    va_start(args, count);
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);

    return total;
}

int main(void) {
    int r1 = sum_all(3, 10, 20, 30);
    printf("sum_all(3, 10, 20, 30)  = %d\n", r1);

    int r2 = sum_all(5, 1, -2, 3, -4, 5);
    printf("sum_all(5, 1, -2, 3, -4, 5) = %d\n", r2);

    int r3 = sum_all(0);
    printf("sum_all(0)  = %d\n", r3);

    return EXIT_SUCCESS;
}
