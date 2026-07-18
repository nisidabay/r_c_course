/*
 * 10_pointer_to_const.c — const int *p (pointer to const data)
 * Group 06 - Pointers 101
 *
 *   const int *p = &x;
 *
 * The DATA at the address is CONSTANT through this pointer — you
 * CANNOT modify it via *p.  But the POINTER ITSELF can be reassigned
 * to point somewhere else.
 *
 * Contrast with 09_const_pointer.c (int *const p).
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 10;
    int y = 20;

    /* p is a pointer to const int: cannot modify via *p */
    const int *p = &x;

    printf("const int *p = &x  ->  *p = %d\n", *p);
    printf("                        p  = %p\n", (void *)p);

    /* CAN change x directly (x is not const) */
    x = 11;
    printf("\nAfter x = 11:\n");
    printf("const int *p = &x  ->  *p = %d\n", *p);

    /* CAN reassign the pointer to point elsewhere */
    p = &y;
    printf("\nAfter p = &y:\n");
    printf("const int *p = &y  ->  *p = %d\n", *p);

    /* CANNOT modify data through a const int* */
    puts("\nWhat you CANNOT do: *p = 99  (modify through const pointer)");
    /* *p = 99;  // COMPILE ERROR: assignment of read-only location '*p' */

    return EXIT_SUCCESS;
}

// Thinking in C:
// const int *p means "p is a pointer to const int".
// Read it right-to-left: p is a pointer to int that is const.
// The data is read-only through this pointer, but the pointer
// itself can be moved.  Use this for function parameters when
// you want to promise not to modify the caller's data.
