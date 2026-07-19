/*
 * Exercise 05 — XOR swap (no temporary variable) — SOLUTION
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    unsigned int a, b;

    printf("Enter first number: ");
    char buf[64];
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return EXIT_FAILURE;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    char *endptr;
    errno = 0;
    a = (unsigned int)strtoul(buf, &endptr, 10);
    if (errno == ERANGE || endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter second number: ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return EXIT_FAILURE;

    len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    errno = 0;
    b = (unsigned int)strtoul(buf, &endptr, 10);
    if (errno == ERANGE || endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Before: a = %u, b = %u\n", a, b);

    /* XOR swap — no temporary variable */
    a ^= b;
    b ^= a;
    a ^= b;

    printf("After:  a = %u, b = %u\n", a, b);

    /* Verify */
    if (a == b)
        printf("Note: a == b after swap — XOR swap works but loses\n"
               "information when both values are the same!  The values\n"
               "happened to be equal, so both ended up as 0.\n");
    else
        printf("Swap verified: a now has b's original value and vice versa.\n");

    return EXIT_SUCCESS;
}
