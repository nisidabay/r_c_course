/*
 * Exercise 02: Return Values
 *
 * Concept: The return statement sends a value back to the caller and
 *          exits the function immediately. A 'void' function returns nothing.
 *          Non-void functions must return a value on every path.
 *
 * Fill in the blanks to complete a program that defines a function 'is_even'
 * that takes an int and returns 1 if it is even, or 0 if it is odd.
 * Also define a void function 'print_result' that prints whether a number
 * is even or odd.
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

/* Define is_even: returns 1 if n is even, 0 otherwise */
/*@*/
int is_even(/*@*/)
{
    /*@*/
    if (n /*@*/ 2 == 0) {
        return /*@*/;
    }
    return /*@*/;
}

/* Define print_result: void function that prints the check result */
/*@*/
void print_result(int n, int even_flag)
{
    /*@*/
    if (/*@*/) {
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
    int flag = is_even(/*@*/);

    /* pass to print_result */
    print_result(/*@*/, /*@*/);

    return 0;
}
