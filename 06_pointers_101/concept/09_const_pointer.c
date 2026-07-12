/*
 * 09_const_pointer.c — int *const p (const pointer to data)
 * Group 06 - Pointers 101
 *
 *   int *const p = &x;
 *
 * The pointer itself is CONSTANT — you CANNOT reassign it to point
 * somewhere else.  But the data AT the address CAN be modified.
 *
 * Contrast with 10_pointer_to_const.c (const int *p).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 10;

    /* p is a const pointer: cannot change WHERE it points */
    int *const p = &x;

    printf("x = %d\n", x);
    printf("int *const p = &x  ->  *p = %d\n", *p);
    printf("                      p  = %p\n", (void *)p);

    /* CAN modify the data through the pointer */
    *p = 99;
    printf("\nAfter *p = 99:\n");
    printf("x = %d\n", x);
    printf("int *const p = &x  ->  *p = %d\n", *p);

    /* CANNOT reassign the pointer itself */
    puts("\nWhat you CANNOT do: p = &y  (reassign the pointer)");
    /* int y = 20; */
    /* p = &y;   // COMPILE ERROR: assignment of read-only variable 'p' */

    return EXIT_SUCCESS;
}

// Thinking in C:
// int *const p means "p is a const pointer to (non-const) int".
// Read it right-to-left: p is a const pointer to int.
// The pointer itself is frozen — it will always point to the
// same address.  But you can write through it.  Use this when
// you want to guarantee a pointer always refers to one location.
