/*
 * ex_04_pointers_params.c
 * Group 06 — Pointers 101
 * Exercise 04: pass-by-value vs pointer parameters
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Understand why pass-by-value CANNOT modify caller variables,
 * and how pointers solve this problem.
 */

#include <stdio.h>

/* PART A: A function that FAILS to swap — pass-by-value */
void swap_fails(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
    printf("  Inside swap_fails: a=%d, b=%d\n", a, b);
}

/* PART B: A function that WORKS — pointer parameters */
void swap_works(int *a, int *b)
{
    int temp = /* @FILL_ME */;   /* read value at address a */
    *a = /* @FILL_ME */;         /* write b's value into a's location */
    /* @FILL_ME */ = temp;       /* write saved temp into b's location */
}

int main(void)
{
    int x = 10;
    int y = 20;

    /* Demonstrate FAIL first */
    printf("=== PASS-BY-VALUE FAILS ===\n");
    printf("Before swap_fails:  x=%d, y=%d\n", x, y);
    swap_fails(/* @FILL_ME */, /* @FILL_ME */);  /* what do we pass? */
    printf("After  swap_fails:  x=%d, y=%d\n", x, y);

    /* Demonstrate pointer solution */
    printf("\n=== POINTERS FIX IT ===\n");
    printf("Before swap_works: x=%d, y=%d\n", x, y);
    swap_works(/* @FILL_ME */, /* @FILL_ME */);  /* what do we pass here? */
    printf("After  swap_works: x=%d, y=%d\n", x, y);

    return 0;
}

/*
 * After filling the blanks:
 *   swap_fails(x, y) — passes COPIES, original x/y unchanged.
 *   swap_works(&x, &y) — passes ADDRESSES, original x/y ARE changed.
 *   Inside swap_works: temp = *a;  *a = *b;  *b = temp;
 */
