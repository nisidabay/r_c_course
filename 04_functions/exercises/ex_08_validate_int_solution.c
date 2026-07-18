/*
 * Exercise 08: Validate Integer (is_valid_int) — SOLUTION
 *
 * Encapsulate the strtol validation pattern in a reusable function.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* ---- is_valid_int: returns 1 if s is a valid integer, 0 otherwise ---- */
int is_valid_int(const char *s, long *out)
{
    if (s == NULL || *s == '\0')
        return 0;

    char *endptr;
    errno = 0;
    long val = strtol(s, &endptr, 10);

    if (errno == ERANGE)
        return 0;                     /* overflow / underflow */
    if (endptr == s || *endptr != '\0')
        return 0;                     /* no digits or trailing garbage */
    if (val < INT_MIN || val > INT_MAX)
        return 0;                     /* out of int range */

    if (out != NULL)
        *out = val;

    return 1;                         /* valid integer */
}

int main(void)
{
    char buf[BUFSZ];

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;   /* input was truncated — drain residue */
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    long value;
    if (is_valid_int(buf, &value)) {
        printf("Valid: %ld\n", value);
    } else {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
