/*
 * Exercise 06: Exit Codes — SOLUTION
 *
 * main() returns an int to the OS. Use EXIT_SUCCESS and EXIT_FAILURE.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* Define safe_divide: takes int a and int b, prints result, returns
 * 0 on success, 1 if b == 0 (division by zero) */
int safe_divide(int a, int b)
{
    if (b == 0) {
        printf("Error: division by zero!\n");
        return 1;
    }

    printf("%d / %d = %d\n", a, b, a / b);
    return 0;
}

int main(void) {
    char buf[BUFSZ];
    int x, y;
    int status = 0;

    printf("Enter two integers (numerator and denominator): ");
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

    /* call safe_divide and capture its return value */
    int result = safe_divide(x, y);

    if (result != 0) {
        printf("Operation failed. ");
        return EXIT_FAILURE;
    }

    printf("Operation succeeded. ");
    return EXIT_SUCCESS;
}
