/*
 * Exercise 04: Scope — SOLUTION
 *
 * Scope is where a variable is visible.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* Declare a global int called counter, initialized to 0 */
int counter = 0;

/* Define increment_counter: adds 1 to the global counter, prints it */
void increment_counter(void)
{
    counter = counter + 1;
    printf("  Global counter is now: %d\n", counter);
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

    /* Block scope: create a new int called local_val that shadows the outer one */
    {
        int local_val = 999;
        printf("Inside block: local_val = %d\n", local_val);
    }

    printf("Outside block: local_val = %d (original restored)\n", local_val);

    return EXIT_SUCCESS;
}
