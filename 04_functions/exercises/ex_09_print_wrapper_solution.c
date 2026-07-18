/*
 * Exercise 09: Print Wrapper (my_print) — SOLUTION
 *
 * Wrap printf with error checking and NULL-pointer validation.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- my_print: prints value with delimiter, checks errors ---- */
int my_print(int val, const char *delim)
{
    if (delim == NULL) {
        fprintf(stderr, "Error: NULL pointer provided for delimiter\n");
        return EXIT_FAILURE;
    }

    if (printf("Value: %d%s", val, delim) < 0) {
        perror("printf");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    int rc;

    rc = my_print(42, "| ");
    if (rc != EXIT_SUCCESS)
        return EXIT_FAILURE;

    rc = my_print(99, "\n");
    if (rc != EXIT_SUCCESS)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
