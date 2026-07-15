/*
 * 07_strtol_validation.c — Full strtol validation pattern
 * Group 03 - Functions
 *
 * strtol (string to long) is the CORRECT way to parse integers from
 * user input in C.  Complete validation requires FOUR checks:
 *   1. errno = 0 before the call
 *   2. errno == ERANGE  → overflow or underflow
 *   3. endptr == buf    → no digits found
 *   4. *endptr != '\0'  → trailing garbage after the number
 *
 * Optionally, check against INT_MIN/INT_MAX before downcasting to int.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char buf[64];

    printf("Enter an integer: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = '\0';

    char *endptr;
    errno = 0;
    long number = strtol(buf, &endptr, 10);

    /* Check 1: overflow/underflow */
    if (errno == ERANGE) {
        fprintf(stderr, "Input number is too large or too small\n");
        return EXIT_FAILURE;
    }

    /* Check 2: no digits found */
    if (endptr == buf) {
        fprintf(stderr, "Invalid input format: no digits found\n");
        return EXIT_FAILURE;
    }

    /* Check 3: trailing garbage */
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input format: trailing characters\n");
        return EXIT_FAILURE;
    }

    /* Check 4: bounds before downcasting to int */
    if (number < INT_MIN || number > INT_MAX) {
        fprintf(stderr, "Number is out of range for an integer\n");
        return EXIT_FAILURE;
    }

    int num = (int)number;

    printf("You entered: %d\n", num);

    if (num > 0) {
        puts("Positive");
    } else if (num < 0) {
        puts("Negative");
    } else {
        puts("Zero");
    }

    return EXIT_SUCCESS;
}

// Thinking in C:
// strtol is the ONLY safe way to parse integers from strings.
// sscanf and atoi give you no way to detect errors — strtol tells
// you exactly what went wrong through errno and endptr inspection.
// strcspn remove "\n" from a string.
// Always perform all four checks; skipping even one is a bug.
