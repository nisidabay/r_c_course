/*
 * 07_swap_value.c — Swap by value (contrast with 06_real_swap)
 * Group 06 - Pointers 101
 *
 * C passes everything BY VALUE — the callee gets a COPY.  A function
 * that tries to swap using parameters alone swaps the copies, leaving
 * the caller's variables untouched.  Compare with 06_real_swap to see
 * WHY pointers are needed for mutation.
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
    int a = 21;
    int b = 17;

    printf("Before swap_by_value: a = %d, b = %d\n", a, b);

    swap_by_value(a, b);   /* passes copies of 21 and 17 */

    printf("After  swap_by_value: a = %d, b = %d\n", a, b);

    puts("\nResult: a and b are UNCHANGED.");
    puts("swap_by_value only swapped its own local copies.");
    puts("To actually swap, you need pointers (06_real_swap).");

    return EXIT_SUCCESS;
}

// Thinking in C:
// C is pass-by-value — always.  swap_by_value(a,b) copies the
// values 21 and 17 into parameters x and y.  Swapping x and y
// changes only the copies.  The original a and b in main are
// untouched.  Pointers solve this by passing the ADDRESS instead
// of the value, letting the function write through to the caller's
// memory.
