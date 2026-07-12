/*
 * Exercise 01: If / Else
 *
 * Concept: Conditional execution with if, else if, and else.
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program should read an integer and print:
 *   "positive" if > 0
 *   "negative" if < 0
 *   "zero" if == 0
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

    // FIX ME
    if (num > 0) {
        printf("positive\n");
    // FIX ME
    } else if (num < 0) {  // FIX ME
        printf("negative\n");
    } else {  // FIX ME
        printf("zero\n");
    }

    return EXIT_SUCCESS;
}
