/*
 * Exercise 05: Function Prototypes — SOLUTION
 *
 * A prototype tells the compiler about a function before its definition.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* ---- function prototypes ---- */

/* Prototype for is_positive: takes int, returns int (1 if > 0, 0 otherwise) */
int is_positive(int n);

/* Prototype for multiply: takes two ints, returns int */
int multiply(int a, int b);

/* Prototype for print_status: takes int (the value) and int (the positive flag),
 * returns nothing */
void print_status(int val, int is_pos);

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
    int pos_x = is_positive(x);
    print_status(x, pos_x);

    /* call multiply */
    int prod = multiply(x, y);
    printf("%d * %d = %d\n", x, y, prod);

    return EXIT_SUCCESS;
}

/* ---- function definitions (below main) ---- */

int is_positive(int n)
{
    if (n > 0) {
        return 1;
    }
    return 0;
}

int multiply(int a, int b)
{
    return a * b;
}

void print_status(int val, int is_pos)
{
    if (is_pos) {
        printf("%d is positive.\n", val);
    } else {
        printf("%d is NOT positive.\n", val);
    }
}
