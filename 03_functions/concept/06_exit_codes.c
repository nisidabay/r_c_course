/*
 * Concept: Exit Codes — EXIT_SUCCESS, EXIT_FAILURE
 * Group 03 - Functions
 *
 * main() returns an int to the operating system.  Convention:
 *   0 (or EXIT_SUCCESS) = success
 *   nonzero (or EXIT_FAILURE) = failure
 *
 * Functions can also return error codes that main propagates to the OS.
 * EXIT_SUCCESS and EXIT_FAILURE are macros defined in <stdlib.h>.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Divides two ints: prints result, returns 0 on success or 1 on error */
int safe_divide(int a, int b)
{
    if (b == 0) {
        printf("  ERROR: division by zero!\n");
        return EXIT_FAILURE;       /* error code — caller must check */
    }

    printf("  %d / %d = %d\n", a, b, a / b);
    return EXIT_SUCCESS;           /* success code */
}

/* Parses and prints an integer from a string; returns 0 on success, 1 on error */
int try_parse(const char *input)
{
    int value;

    char *endptr;
    errno = 0;
    long val = strtol(input, &endptr, 10);

    if (errno == ERANGE || endptr == input || *endptr != '\0') {
        printf("  ERROR: could not parse '%s' as an integer.\n", input);
        return EXIT_FAILURE;
    }
    if (val < INT_MIN || val > INT_MAX) {
        printf("  ERROR: '%s' out of int range.\n", input);
        return EXIT_FAILURE;
    }
    value = (int)val;

    printf("  Parsed '%s' -> %d\n", input, value);
    return EXIT_SUCCESS;
}

int main(void)
{
    int status = 0;   /* overall program status — start as success */

    puts("=== Exit Codes ===");

    /* --- successful path --- */
    printf("\nTesting safe_divide(10, 2):\n");
    if (safe_divide(10, 2) != 0) {
        status = 1;
    }

    /* --- error path --- */
    printf("\nTesting safe_divide(5, 0):\n");
    if (safe_divide(5, 0) != 0) {
        puts("  (error detected, will return EXIT_FAILURE)");
        status = 1;
    }

    /* --- parse error --- */
    printf("\nTesting try_parse(\"hello\"):\n");
    if (try_parse("hello") != 0) {
        puts("  (parse error detected)");
        status = 1;
    }

    /* --- success case --- */
    printf("\nTesting try_parse(\"42\"):\n");
    if (try_parse("42") != 0) {
        status = 1;
    }

    /* report final status using standard macros */
    printf("\n=== Program finished ===\n");
    if (status == 0) {
        printf("All operations succeeded. Returning %d (EXIT_SUCCESS).\n",
               EXIT_SUCCESS);
        return EXIT_SUCCESS;
    } else {
        printf("One or more operations failed. Returning %d (EXIT_FAILURE).\n",
               EXIT_FAILURE);
        return EXIT_FAILURE;
    }
}

// Thinking in C:
// Every C program communicates its outcome to the OS via main's return
// value.  Use EXIT_SUCCESS (0) and EXIT_FAILURE (1) from <stdlib.h>
// instead of bare numbers — they make intent clear and are portable
// across systems that may use different numeric conventions.
