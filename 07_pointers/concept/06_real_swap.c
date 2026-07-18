/*
 * 06_real_swap.c — Swap via pointers
 * Group 06 - Pointers 101
 *
 * The canonical swap idiom using pointers.  To modify a variable
 * at the caller, pass its ADDRESS (with &) and dereference inside
 * the function (with *).  This is the single most important use of
 * pointers in C.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- swap that WORKS: receives addresses, modifies originals ---- */
static void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;

    printf("  (inside swap: x = %d, y = %d)\n", *x, *y);
}

int main(void)
{
    int a = 21;
    int b = 17;

    printf("Before swap: a = %d, b = %d\n", a, b);

    swap(&a, &b);   /* pass addresses, not copies */

    printf("After  swap: a = %d, b = %d\n", a, b);

    if (a == 17 && b == 21) {
        puts("SUCCESS: swap worked — values are exchanged.");
    } else {
        puts("FAIL: swap did not work.");
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// &a gives the address of a; *x reads/writes through that address.
// The swap function receives copies of the ADDRESSES, not copies
// of the data.  Writing through the pointer reaches the original
// variables in main's stack frame.  This is the key to understanding
// output parameters and mutation in C.
