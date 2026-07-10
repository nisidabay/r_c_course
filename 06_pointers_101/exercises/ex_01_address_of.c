/*
 * ex_01_address_of.c
 * Group 06 — Pointers 101
 * Exercise 01: address-of operator (&) and %p
 *
 * Fill in the blanks (marked with /* @FILL_ME */) to complete the program.
 * Use the & operator to get addresses and %p to print them.
 */

#include <stdio.h>

int main(void) {
    int    a = 10;
    double b = 3.14;
    char   c = 'X';

    /* 1. Print the VALUE of 'a' and its ADDRESS using & and %p */
    printf("a  = %d\n", a);
    printf("&a = %p\n", (/* @FILL_ME */)&a);

    /* 2. Print the VALUE of 'b' and its ADDRESS */
    printf("b  = %f\n", b);
    printf("&b = %p\n", (void *) /* @FILL_ME */);

    /* 3. Print the VALUE of 'c' and its ADDRESS */
    printf("c  = %c\n", c);
    printf("&c = %p\n", (void *)&c);

    /* 4. Complete the if-condition to confirm each address is unique.
     *    Compare &a, &b, and &c — are any two the same? */
    if ((void *)&a /* @FILL_ME */ (void *)&b && (void *)&b /* @FILL_ME */ (void *)&c) {
        printf("All three addresses are unique.\n");
    }

    return 0;
}

/*
 * After filling the blanks:
 *   Each variable gets its own unique memory address.
 *   &var gives you the address; %p prints it (cast to void*).
 *   Addresses from different variables are always distinct.
 */
