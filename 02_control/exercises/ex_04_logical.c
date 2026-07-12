/*
 * Exercise 04: Logical Operators (&&, ||, !)
 *
 * Concept: Combine boolean expressions with && (AND), || (OR), and ! (NOT).
 *
 * Fill in the blanks to complete a program that reads an integer and prints
 * whether it is in the range [10, 50] inclusive.
 *
 * Hint: Use logical AND (&&) to check both bounds.
 *
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
 */

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int num;
    bool in_range;

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
    in_range = (num >= 10) && (num <= 50);  // FIX ME // FIX ME // FIX ME

    if (in_range) {
        printf("In range\n");
    } else {
        printf("Out of range\n");
    }

    return EXIT_SUCCESS;
}
