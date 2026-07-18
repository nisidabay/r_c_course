/*
 * ex_07_swap_value.c — SOLUTION
 * Group 06 — Pointers 101
 * Exercise 07: swap by value (fails — contrast with pointer swap)
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- swap that FAILS: receives copies, changes are local ---- */
static void swap_by_value(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;

    printf("  (inside swap_by_value: x = %d, y = %d)\n", x, y);
}

int main(void)
{
    int a = 5;
    int b = 10;

    printf("Before: a = %d, b = %d\n", a, b);

    swap_by_value(a, b);   /* passes copies — will NOT change a and b */

    printf("After:  a = %d, b = %d\n", a, b);

    puts("\nResult: a and b are UNCHANGED.");
    puts("C passes by value — swap_by_value only swapped its local copies.");
    puts("To actually swap, you need pointers.");

    return EXIT_SUCCESS;
}
