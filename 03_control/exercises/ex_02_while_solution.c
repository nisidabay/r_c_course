/*
 * Solution 02: While Loops
 *
 * Reads a positive integer n and counts down from n to 1.
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
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;   /* input was truncated — drain residue */
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

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

    int i = n;
    while (i > 0) {
        printf("%d\n", i);
        i--;
    }

    return EXIT_SUCCESS;
}
