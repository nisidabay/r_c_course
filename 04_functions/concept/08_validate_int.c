/*
 * 08_validate_int.c — is_valid_int helper function
 * Group 03 - Functions
 *
 * Encapsulate the strtol validation pattern in a reusable function so
 * the caller doesn't need to repeat the boilerplate every time.
 *
 *   int is_valid_int(const char *s, long *out);
 *
 * Returns 1 if s is a valid integer string (and stores it in *out).
 * Returns 0 on any error (NULL, empty, overflow, trailing garbage).
 *
 * This pattern keeps main() clean and puts the complexity where it
 * belongs — in a named, testable function.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void consume_remaining(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ---- helper: wraps strtol with full validation ---- */
int is_valid_int(const char *s, long *out)
{
    if (s == NULL || *s == '\0') {
        return 0;
    }

    char *endptr;
    errno = 0;
    long val = strtol(s, &endptr, 10);

    if (errno == ERANGE) {
        return 0;
    }
    if (endptr == s || *endptr != '\0') {
        return 0;
    }
    if (val < INT_MIN || val > INT_MAX) {
        return 0;
    }

    if (out != NULL) {
        *out = val;
    }
    return 1;
}

int main(void)
{
    char buf[64];

    printf("Enter a number (cents, e.g. 12345 for $123.45): ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        consume_remaining();   /* input was truncated — drain residue */
    } else if (len > 0) {
        buf[len - 1] = '\0';   /* strip trailing newline */
    }

    long price;
    if (!is_valid_int(buf, &price)) {
        fprintf(stderr, "Invalid input — enter a whole number only\n");
        return EXIT_FAILURE;
    }

    if (price < 0) {
        fprintf(stderr, "Negative values are not allowed\n");
        return EXIT_FAILURE;
    }

    printf("Price: $%ld.%02ld\n", price / 100, price % 100);

    return EXIT_SUCCESS;
}

// Thinking in C:
// Encapsulating validation in a helper function lets you parse input
// anywhere without duplicating the strtol boilerplate. The function
// returns an int (0/1) so callers can check success cleanly, and
// writes the result through an output parameter (long *out).
// This is how real C programs manage repeated patterns.
