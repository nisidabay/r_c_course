/*
 * 02_dereference.c — * operator to read/write through a pointer
 *
 * A pointer holds an address. The * ("dereference") operator goes
 * to that address and lets you read or write the value stored there.
 *
 * Think of it like a signpost: the pointer tells you WHERE something
 * is, and dereferencing lets you touch WHAT is there.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int  x = 42;
    int *p = &x;          /* p stores the address of x */

    /* -- Reading through a pointer -- */
    printf("x  = %d\n", x);
    printf("p  = %p\n", (void *)p);
    printf("*p = %d\n\n", *p);   /* read x via pointer */

    /* -- Writing through a pointer -- */
    *p = 99;                      /* write to x through p */
    printf("After *p = 99:\n");
    printf("x  = %d\n", x);
    printf("*p = %d\n\n", *p);

    /* -- It's the same variable, just accessed differently -- */
    x = 7;
    printf("After x = 7:\n");
    printf("x  = %d\n", x);
    printf("*p = %d\n", *p);      /* still reflects x */

    return EXIT_SUCCESS;
}

/*
 * Thinking in C:
 *   p holds the address of x — &x was the key that unlocked p.
 *   *p reads the value AT that address; *p = value WRITES through it.
 *   The pointer and the variable are two ways to reach one piece of memory.
 */
