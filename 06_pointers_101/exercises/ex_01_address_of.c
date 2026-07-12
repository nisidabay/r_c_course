/*
 * ex_01_address_of.c
 * Group 06 — Pointers 101
 * Exercise 01: address-of operator (&) and %p
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * Use the & operator to get addresses and %p to print them.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int    a = 10;
    double b = 3.14;
    char   c = 'X';

    /* 1. Print the VALUE of 'a' and its ADDRESS using & and %p */
    printf("a  = %d\n", a);
    printf("&a = %p\n", (void *)&a);  // FIX ME

    /* 2. Print the VALUE of 'b' and its ADDRESS */
    printf("b  = %f\n", b);
    printf("&b = %p\n", (void *)&b);  // FIX ME

    /* 3. Print the VALUE of 'c' and its ADDRESS */
    printf("c  = %c\n", c);
    printf("&c = %p\n", (void *)&c);

    /* 4. Complete the if-condition to confirm each address is unique.
     *    Compare &a, &b, and &c — are any two the same? */
    if ((void *)&a != (void *)&b && (void *)&b != (void *)&c) {  // FIX ME  // FIX ME
        printf("All three addresses are unique.\n");
    }

    return EXIT_SUCCESS;
}

/*
 * After filling the blanks:
 *   Each variable gets its own unique memory address.
 *   &var gives you the address; %p prints it (cast to void*).
 *   Addresses from different variables are always distinct.
 */
