/*
 * ex_02_dereference.c
 * Group 06 — Pointers 101
 * Exercise 02: dereference operator (*) — reading and writing through pointers
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * Use * to read values through pointers and to write through them.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int  x = 42;
    int *p;          /* declare p as a pointer to int */

    /* 1. Make p point to x using the address-of operator */
    p = &x;  // FIX ME

    /* 2. Print the VALUE of x directly and through p */
    printf("x  = %d\n", x);
    printf("*p = %d  (should equal x)\n", *p);  // FIX ME

    /* 3. Write a new value (99) through p, then print x */
    *p = 99;  // FIX ME
    printf("After writing through p:\n");
    printf("x  = %d (expected: 99)\n", x);
    printf("*p = %d (expected: 99)\n", *p);

    /* 4. Change x directly to 7, then read through p to confirm */
    x = 7;
    printf("After x = 7:\n");
    printf("x  = %d\n", x);
    printf("*p = %d  (p still points to x, so this must be 7)\n", *p);

    return EXIT_SUCCESS;
}

/*
 * After filling the blanks:
 *   p = &x makes p point to x.
 *   *p reads the value AT the address p holds.
 *   *p = 99 writes 99 into x through the pointer.
 *   Changing x directly is reflected when reading through p.
 */
