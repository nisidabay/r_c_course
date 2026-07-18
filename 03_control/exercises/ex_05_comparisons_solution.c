/*
 * Solution 05: Comparisons (==, !=, <, >, <=, >=)
 *
 * Reads two integers and prints which is greater or if they're equal.
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
    long val1 = strtol(buf, &endptr, 10);
    if (errno == ERANGE || endptr == buf || val1 < INT_MIN || val1 > INT_MAX) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }
    a = (int)val1;

    errno = 0;
    long val2 = strtol(endptr, &endptr, 10);
    if (errno == ERANGE || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }
    if (*endptr != '\0' && *endptr != '\n') {
        fprintf(stderr, "Trailing characters\n");
        return EXIT_FAILURE;
    }
    b = (int)val2;

    if (a > b) {
        printf("a is greater\n");
    } else if (a < b) {
        printf("b is greater\n");
    } else {
        printf("equal\n");
    }

    return EXIT_SUCCESS;
}
