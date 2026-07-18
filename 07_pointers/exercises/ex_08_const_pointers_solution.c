/*
 * ex_08_const_pointers.c — SOLUTION
 * Group 06 — Pointers 101
 * Exercise 08: demonstrate int *const vs const int *
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* =================================================== */
    /* PART 1: int *const p — const pointer to (non-const) int */
    /* =================================================== */
    puts("=== int *const p (const pointer) ===");
    int x = 10;

    /* p is a const pointer: cannot change WHERE it points */
    int *const p = &x;

    printf("x = %d\n", x);
    printf("*p = %d\n", *p);

    /* CAN modify the data through the pointer */
    *p = 99;
    printf("After *p = 99:\n");
    printf("x = %d\n", x);

    puts("");

    /* =================================================== */
    /* PART 2: const int *p — pointer to const int          */
    /* =================================================== */
    puts("=== const int *p (pointer to const) ===");
    int y = 20;

    /* p2 is a pointer to const int: cannot modify via *p2 */
    const int *p2 = &x;

    printf("const int *p = &x  ->  *p = %d\n", *p2);

    /* CAN reassign the pointer itself */
    p2 = &y;
    printf("After p = &y:\n");
    printf("const int *p = &y  ->  *p = %d\n", *p2);

    return EXIT_SUCCESS;
}
