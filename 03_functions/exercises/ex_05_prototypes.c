/*
 * Exercise 05: Function Prototypes (Forward Declarations)
 *
 * Concept: A prototype tells the compiler about a function BEFORE its
 *          definition or use. Syntax: return_type name(param_types);
 *          Without prototypes, C assumes 'int' return — which is dangerous.
 *
 * Fill in the blanks to complete a program that has prototypes at the top,
 * uses them in main(), and defines the functions below main().
 *
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* ---- function prototypes ---- */

// FIX ME
/* Prototype for is_positive: takes int, returns int (1 if > 0, 0 otherwise) */
int is_positive(int n);  // FIX ME  // FIX ME

// FIX ME
/* Prototype for multiply: takes two ints, returns int */
int multiply(int a, int b);  // FIX ME

// FIX ME
/* Prototype for print_status: takes int (the value) and int (the positive flag),
 * returns nothing */
void print_status(int val, int is_pos);  // FIX ME  // FIX ME

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

    /* call is_positive on x */
    int pos_x = is_positive(x);  // FIX ME
    print_status(x, pos_x);  // FIX ME

    /* call multiply */
    int prod = multiply(x, y);  // FIX ME  // FIX ME
    printf("%d * %d = %d\n", x, y, prod);

    return EXIT_SUCCESS;
}

/* ---- function definitions (below main) ---- */

// FIX ME
int is_positive(int n)
{
    if (n > 0) {  // FIX ME
        return 1;
    }
    return 0;
}

// FIX ME
int multiply(int a, int b)
{
    return a * b;  // FIX ME
}

// FIX ME
void print_status(int val, int is_pos)
{
    if (is_pos) {
        printf("%d is positive.\n", val);
    } else {
        printf("%d is NOT positive.\n", val);
    }
}
