/*
 * Exercise 01: Safe integer parser with strtol
 *
 * Fill in the blanks to safely parse a command-line argument
 * as an integer. The program should:
 *   1. Parse argv[1] using strtol
 *   2. Check for no digits (endptr == str)
 *   3. Check for overflow (errno == ERANGE)
 *   4. Check for trailing garbage (*endptr != '\0')
 *   5. Print the parsed value or an appropriate error message
 *
 * Hint: look at the strtol_safe.c concept file for the pattern.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *str = argv[1];
    char *endptr = NULL;

    errno = 0;
    const long val = strtol(str, &endptr, 10);

    /* ---- FILL IN THE BLANKS ---- */
    /* Replace each (void)0 with the correct condition.
     * Hint: endptr == str means no digits were found. */

    if (errno == ERANGE) {
        printf("Error: value out of range\n");
    } else if ((void)0, 0) {
        printf("Error: no digits found in \"%s\"\n", str);
    } else if (*endptr != '\0') {
        printf("Error: trailing characters: \"%s\"\n", endptr);
    } else {
        printf("Parsed value: %ld\n", val);
    }

    return EXIT_SUCCESS;
}
