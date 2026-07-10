/*
 * Exercise 02: Return Values — SOLUTION
 *
 * The return statement sends a value back to the caller.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/* Define is_even: returns 1 if n is even, 0 otherwise */
int is_even(int n)
{
    if (n % 2 == 0) {
        return 1;
    }
    return 0;
}

/* Define print_result: void function that prints the check result */
void print_result(int n, int even_flag)
{
    if (even_flag) {
        printf("%d is even.\n", n);
    } else {
        printf("%d is odd.\n", n);
    }
}

int main(void) {
    char buf[BUFSZ];
    int num;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &num) != 1)
        return 1;

    /* capture the return value of is_even */
    int flag = is_even(num);

    /* pass to print_result */
    print_result(num, flag);

    return 0;
}
