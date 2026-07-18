/*
 * Concept: Parameters and Arguments (Pass by Value)
 * Group 03 - Functions
 *
 * In C, arguments are ALWAYS copied into the function's parameters.
 * The function works on its own copies — changes inside the function
 * do NOT affect the original variables in the caller.
 *
 * This is called "call by value" or "pass by value".
 */

#include <stdio.h>
#include <stdlib.h>

/* Attempt to swap two ints — this FAILS because C passes by value */
void swap_attempt(int a, int b)
{
    printf("  [swap_attempt] before: a=%d, b=%d\n", a, b);

    int temp = a;
    a = b;
    b = temp;

    printf("  [swap_attempt] after:  a=%d, b=%d\n", a, b);
    /* a and b are local copies — original x and y in main are untouched */
}

/* Increment an int by 1 — also works only on the copy */
void increment(int n)
{
    n = n + 1;
    printf("  [increment] inside: n=%d\n", n);
}

/* Double-check: a function that *does* use its parameter (read-only) */
int add_ten(int n)
{
    return n + 10;   /* reads n — no side effect on the caller */
}

int main(void)
{
    int x = 10;
    int y = 20;

    puts("=== Pass by Value Demo ===");

    printf("Before swap:  x=%d, y=%d\n", x, y);
    swap_attempt(x, y);
    printf("After swap:   x=%d, y=%d\n\n", x, y);

    /* x and y are UNCHANGED — the swap inside the function was useless */

    int val = 7;
    printf("Before increment: val=%d\n", val);
    increment(val);
    printf("After increment:  val=%d\n\n", val);

    /* val is still 7 — increment worked on a copy */

    int result = add_ten(val);
    printf("add_ten(val) = %d, but val is still %d\n", result, val);

    puts("\nKey takeaway: functions receive COPIES of the arguments.");
    puts("To actually change a variable, we need pointers (Group 07).");

    return EXIT_SUCCESS;
}

// Thinking in C:
// Pass-by-value is one of C's most important rules.  Every argument is
// copied into the parameter — the function cannot modify the caller's
// variable.  This prevents accidental mutation and keeps functions
// predictable.  When you MUST mutate, C gives you pointers (later).
