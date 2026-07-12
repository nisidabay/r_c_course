/*
 * Exercise 03: Pass by Value
 *
 * Concept: In C, arguments are ALWAYS copied into the function's parameters.
 *          The function works on its own copies — changes inside the function
 *          do NOT affect the original variables in the caller.
 *
 * Fill in the blanks to complete a program that demonstrates pass-by-value.
 * Define a function 'triple' that takes an int, multiplies it by 3 inside,
 * and prints the local value. Then in main, show that the original is unchanged.
 * Also define a function 'add_them' that takes two ints and returns their sum.
 *
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

// FIX ME
/* Define triple: takes int n, multiplies by 3, prints local value, returns nothing */
void triple(int n)  // FIX ME
{
    // FIX ME
    n = n * 3;  // FIX ME
    printf("  Inside triple: n = %d\n", n);
    // FIX ME
}

// FIX ME
/* Define add_them: takes int a and int b, returns their sum */
int add_them(int a, int b)  // FIX ME
{
    return a + b;  // FIX ME
}

int main(void) {
    char buf[BUFSZ];
    int x, y;

    printf("Enter two integers separated by space: ");
    if (fgets(buf, BUFSZ, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = '\0';

    /* parse first number */
    char *endptr;
    errno = 0;
    long vx = strtol(buf, &endptr, 10);
    if (errno == ERANGE || endptr == buf || vx < INT_MIN || vx > INT_MAX) {
        fprintf(stderr, "Invalid input for x\n");
        return EXIT_FAILURE;
    }
    x = (int)vx;

    /* parse second number */
    errno = 0;
    long vy = strtol(endptr, &endptr, 10);
    if (errno == ERANGE || vy < INT_MIN || vy > INT_MAX) {
        fprintf(stderr, "Invalid input for y\n");
        return EXIT_FAILURE;
    }
    if (*endptr != '\0' && *endptr != '\n') {
        fprintf(stderr, "Trailing characters\n");
        return EXIT_FAILURE;
    }
    y = (int)vy;

    printf("Before triple: x = %d\n", x);
    triple(x);  // FIX ME
    printf("After triple:  x = %d (unchanged!)\n", x);

    int sum = add_them(x, y);  // FIX ME  // FIX ME
    printf("add_them(%d, %d) = %d\n", x, y, sum);

    return EXIT_SUCCESS;
}
