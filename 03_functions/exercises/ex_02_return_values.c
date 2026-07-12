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
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* Define is_even: returns 1 if n is even, 0 otherwise */
// FIX ME
int is_even(int n)  // FIX ME
{
    // FIX ME
    if (n % 2 == 0) {  // FIX ME
        return 1;  // FIX ME
    }
    return 0;  // FIX ME
}

/* Define print_result: void function that prints the check result */
// FIX ME
void print_result(int n, int even_flag)
{
    // FIX ME
    if (even_flag) {  // FIX ME
        printf("%d is even.\n", n);
    } else {
        printf("%d is odd.\n", n);
    }
}

int main(void) {
    char buf[BUFSZ];
    int num;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = '\0';

    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Out of int range\n");
        return EXIT_FAILURE;
    }
    num = (int)val;

    /* capture the return value of is_even */
    int flag = is_even(num);  // FIX ME

    /* pass to print_result */
    print_result(num, flag);  // FIX ME  // FIX ME

    return EXIT_SUCCESS;
}
