/*
 * 09_print_wrapper.c — printf wrapper with error checking
 * Group 03 - Functions
 *
 * printf returns the number of characters printed, or a negative
 * value on error.  Wrapping printf in a helper lets us check the
 * return value and handle NULL pointer parameters consistently.
 *
 * This shows how to build small, safe wrappers around standard
 * library functions.
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- wrapper: prints value with delimiter, checks errors ---- */
int my_print(int value, const char *delimiter)
{
    if (delimiter == NULL) {
        fprintf(stderr, "Error: NULL pointer provided for delimiter\n");
        return EXIT_FAILURE;
    }

    if (printf("Value: %d%s", value, delimiter) < 0) {
        perror("printf");
        return EXIT_FAILURE;
    }

    /* If delimiter doesn't end with newline, print one */
    if (*delimiter != '\n') {
        puts("");
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    puts("=== printf wrapper with error checking ===");
    puts("");

    my_print(42, "\n");    /* prints "Value: 42" then newline */
    my_print(42, " | ");   /* prints "Value: 42 | "            */
    my_print(42, ", ");    /* prints "Value: 42, "             */

    puts("");
    puts("All calls completed without error.");

    return EXIT_SUCCESS;
}

// Thinking in C:
// printf returns a value — ignoring it means missing errors on
// output failures (full disk, broken pipe, etc.).  Wrapping it
// in a helper that checks the return and validates parameters
// is a simple but effective safety pattern.  Always check NULL
// pointers when your function receives a pointer parameter.
