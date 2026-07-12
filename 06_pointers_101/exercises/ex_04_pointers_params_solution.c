/*
 * ex_04_pointers_params.c — SOLUTION
 * Group 06 — Pointers 101
 * Exercise 04: pass-by-value vs pointer parameters
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
    int temp = *a;     /* read value at address a */
    *a = *b;           /* write b's value into a's location */
    *b = temp;         /* write saved temp into b's location */
}

int main(void)
{
    int x = 10;
    int y = 20;

    /* Demonstrate FAIL first */
    printf("=== PASS-BY-VALUE FAILS ===\n");
    printf("Before swap_fails:  x=%d, y=%d\n", x, y);
    swap_fails(x, y);
    printf("After  swap_fails:  x=%d, y=%d\n", x, y);

    /* Demonstrate pointer solution */
    printf("\n=== POINTERS FIX IT ===\n");
    printf("Before swap_works: x=%d, y=%d\n", x, y);
    swap_works(&x, &y);
    printf("After  swap_works: x=%d, y=%d\n", x, y);

    return 0;
}
