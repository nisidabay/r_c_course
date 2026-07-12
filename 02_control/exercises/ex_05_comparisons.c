/*
 * Exercise 05: Comparisons (==, !=, <, >, <=, >=)
 *
 * Concept: Comparison operators produce boolean results (0 or 1).
 *          ==  equal to
 *          !=  not equal to
 *          <   less than
 *          >   greater than
 *          <=  less than or equal to
 *          >=  greater than or equal to
 *
 * Fill in the blanks to complete a program that reads two integers a and b
 * and prints:
 *   "a is greater"   if a > b
 *   "b is greater"   if a < b
 *   "equal"          if a == b
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
    int a, b;

    printf("Enter two integers (space-separated): ");
    if (fgets(buf, BUFSZ, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = '\0';

    /* parse first number */
    char *endptr;
    errno = 0;
    long val_a = strtol(buf, &endptr, 10);
    if (errno == ERANGE || endptr == buf || val_a < INT_MIN || val_a > INT_MAX) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }
    a = (int)val_a;

    /* parse second number */
    errno = 0;
    long val_b = strtol(endptr, &endptr, 10);
    if (errno == ERANGE || val_b < INT_MIN || val_b > INT_MAX) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }
    /* check that we consumed something and nothing remains */
    if (endptr == buf || (*endptr != '\0' && *endptr != '\n')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    b = (int)val_b;

    if (a > b) {  // FIX ME
        printf("a is greater\n");
    // FIX ME
    } if (a < b) {  // FIX ME
        printf("b is greater\n");
    } else {  // FIX ME
        printf("equal\n");
    }

    return EXIT_SUCCESS;
}
