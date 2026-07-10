/*
 * ex_02_dereference.c — SOLUTION
 * Group 06 — Pointers 101
 * Exercise 02: dereference operator (*) — reading and writing through pointers
 */

#include <stdio.h>

int main(void) {
    int  x = 42;
    int *p;

    /* 1. Make p point to x */
    p = &x;

    /* 2. Print the VALUE of x directly and through p */
    printf("x  = %d\n", x);
    printf("*p = %d  (should equal x)\n", *p);

    /* 3. Write a new value (99) through p */
    *p = 99;
    printf("After writing through p:\n");
    printf("x  = %d (expected: 99)\n", x);
    printf("*p = %d (expected: 99)\n", *p);

    /* 4. Change x directly to 7, then read through p to confirm */
    x = 7;
    printf("After x = 7:\n");
    printf("x  = %d\n", x);
    printf("*p = %d  (p still points to x, so this must be 7)\n", *p);

    return 0;
}
