/*
 * Exercise 02: Return Values — SOLUTION
 *
 * The return statement sends a value back to the caller.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

/* Define is_even: returns 1 if n is even, 0 otherwise */
int is_even(int n)
{
    if (n % 2 == 0) {
        return 1;
    }
    return 0;
}

/* Define print_result: void function that prints the check result */
void print_result(int n, int even_flag)
{
    if (even_flag) {
        printf("%d is even.\n", n);
    } else {
        printf("%d is odd.\n", n);
    }
}

int main(void) {
    char buf[BUFSZ];
    int num;

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
    num = (int)val;

    /* capture the return value of is_even */
    int flag = is_even(num);

    /* pass to print_result */
    print_result(num, flag);

    return EXIT_SUCCESS;
}
