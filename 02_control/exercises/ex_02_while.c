/*
 * Exercise 02: While Loops
 *
 * Concept: A while loop repeats a block while a condition is true.
 *
 * Fill in the blanks to complete a program that reads a positive integer n
 * and prints the numbers from n down to 1 (one per line).
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
    if (n <= 0) {
        fprintf(stderr, "Must be positive\n");
        return EXIT_FAILURE;
    }

    int i = n;  // FIX ME
    // FIX ME
    while (i >= 1) {  // FIX ME
        printf("%d\n", i);
        i--;  // FIX ME
    }

    return EXIT_SUCCESS;
}
