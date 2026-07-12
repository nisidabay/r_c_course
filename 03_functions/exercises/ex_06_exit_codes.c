/*
 * Exercise 06: Exit Codes — EXIT_SUCCESS, EXIT_FAILURE
 *
 * Concept: main() returns an int to the OS. Convention: 0 (EXIT_SUCCESS)
 *          = success, nonzero (EXIT_FAILURE) = failure. Functions can also
 *          return error codes that main propagates.
 *
 * Fill in the blanks to complete a program that divides two integers safely.
 * Define a function 'safe_divide' that returns 0 on success, 1 on error.
 * main() should call it and return EXIT_SUCCESS or EXIT_FAILURE accordingly.
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
/* Define safe_divide: takes int a and int b, prints result, returns
 * 0 on success, 1 if b == 0 (division by zero) */
int safe_divide(int a, int b)
{
    // FIX ME
    if (b == 0) {  // FIX ME
        printf("Error: division by zero!\n");
        return 1;  // FIX ME
    }

    printf("%d / %d = %d\n", a, b, a / b);  // FIX ME
    return 0;  // FIX ME
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
    // FIX ME
    int result = safe_divide(x, y);  // FIX ME

    if (result != 0) {
        printf("Operation failed. ");
        // FIX ME
        return EXIT_FAILURE;  // FIX ME
    }

    printf("Operation succeeded. ");
    // FIX ME
    return EXIT_SUCCESS;  // FIX ME
}
