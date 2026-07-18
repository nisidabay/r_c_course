/*
 * Exercise 03: Pass by Value — SOLUTION
 *
 * Arguments are ALWAYS copied into the function's parameters.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* Define triple: takes int n, multiplies by 3, prints local value, returns nothing */
void triple(int n)
{
    n = n * 3;
    printf("  Inside triple: n = %d\n", n);
}

/* Define add_them: takes int a and int b, returns their sum */
int add_them(int a, int b)
{
    return a + b;
}

int main(void) {
    char buf[BUFSZ];
    int x, y;

    printf("Enter two integers separated by space: ");
    if (fgets(buf, BUFSZ, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;   /* input was truncated — drain residue */
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

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
    triple(x);
    printf("After triple:  x = %d (unchanged!)\n", x);

    int sum = add_them(x, y);
    printf("add_them(%d, %d) = %d\n", x, y, sum);

    return EXIT_SUCCESS;
}
