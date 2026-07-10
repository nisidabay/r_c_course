/*
 * 01_address_of.c — & operator, %p, and the idea that variables live at addresses
 *
 * Every variable in C occupies memory. The & ("address-of") operator
 * yields the memory address where a variable is stored. The %p format
 * specifier prints that address in hexadecimal.
 *
 * This is the foundation: once you know a variable's address, you can
 * create a pointer to it (next file). For now, we just observe that
 * addresses exist and are real.
 */

#include <stdio.h>

int main(void)
{
    int    x = 42;
    double pi = 3.14159;
    char   ch = 'A';

    /* -- Print values and their addresses -- */
    printf("x  = %d\n",    x);
    printf("&x = %p\n\n", (void *)&x);

    printf("pi  = %f\n",    pi);
    printf("&pi = %p\n\n", (void *)&pi);

    printf("ch  = %c\n",    ch);
    printf("&ch = %p\n\n", (void *)&ch);

    /* -- Different variables have different addresses -- */
    printf("Each variable lives at a unique address.\n");
    printf("The address is a number that tells us WHERE the data is.\n");

    return 0;
}

/*
 * Thinking in C:
 *   Every variable has a location — &x gives you that address.
 *   %p prints the address; cast to (void*) because that's what printf expects.
 *   Addresses are just numbers; we'll soon store them in pointers.
 */
