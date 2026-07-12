/*
 * Exercise 04: Scope — Local vs Global Variables
 *
 * Concept: "Scope" is where a variable is visible. Global scope = visible
 *          everywhere. Local/block scope = visible only inside { } where
 *          declared. Inner scopes can shadow outer names.
 *
 * Fill in the blanks to complete a program that uses a global counter,
 * a local variable, and a block scope to demonstrate visibility rules.
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
/* Declare a global int called counter, initialized to 0 */
int counter = 0;  // FIX ME  // FIX ME

// FIX ME
/* Define increment_counter: adds 1 to the global counter, prints it */
void increment_counter(void)  // FIX ME
{
    // FIX ME
    counter = counter + 1;  // FIX ME
    printf("  Global counter is now: %d\n", counter);  // FIX ME
}

int main(void) {
    char buf[BUFSZ];
    int local_val;

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
    local_val = (int)val;

    printf("Initial counter: %d\n", counter);
    printf("Initial local_val: %d\n", local_val);

    increment_counter();
    increment_counter();

    printf("After 2 increments, counter = %d\n", counter);

    // FIX ME
    /* Block scope: create a new int called local_val that shadows the outer one */
    {
        int local_val = 999;  // FIX ME
        printf("Inside block: local_val = %d\n", local_val);
    }

    printf("Outside block: local_val = %d (original restored)\n", local_val);

    return EXIT_SUCCESS;
}
