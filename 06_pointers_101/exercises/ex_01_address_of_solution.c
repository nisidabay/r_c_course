/*
 * ex_01_address_of.c — SOLUTION
 * Group 06 — Pointers 101
 * Exercise 01: address-of operator (&) and %p
 */

#include <stdio.h>

int main(void) {
    int    a = 10;
    double b = 3.14;
    char   c = 'X';

    /* 1. Print the VALUE of 'a' and its ADDRESS using & and %p */
    printf("a  = %d\n", a);
    printf("&a = %p\n", (void *)&a);

    /* 2. Print the VALUE of 'b' and its ADDRESS */
    printf("b  = %f\n", b);
    printf("&b = %p\n", (void *)&b);

    /* 3. Print the VALUE of 'c' and its ADDRESS */
    printf("c  = %c\n", c);
    printf("&c = %p\n", (void *)&c);

    /* 4. Complete the if-condition to confirm each address is unique */
    if ((void *)&a != (void *)&b && (void *)&b != (void *)&c) {
        printf("All three addresses are unique.\n");
    }

    return 0;
}
