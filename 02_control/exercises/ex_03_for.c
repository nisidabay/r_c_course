/*
 * Exercise 03: For Loops
 *
 * Concept: A for loop collects initialization, condition, and increment
 *          in a single line: for (init; condition; increment) { body }
 *
 * Fill in the blanks to complete a program that reads an integer n (>= 1)
 * and prints the sum 1 + 2 + ... + n.
 *
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int n;
    int sum = 0;

    printf("Enter a positive integer: ");
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
    n = (int)val;
    if (n < 1) {
        fprintf(stderr, "Must be at least 1\n");
        return EXIT_FAILURE;
    }

    // FIX ME
    for (int i = 1; i <= n; i++) {  // FIX ME // FIX ME
        sum += i;  // FIX ME
    }

    printf("Sum = %d\n", sum);

    return EXIT_SUCCESS;
}
