#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    /* buffer for user's name — large enough for typical names */
    char name[32];
    /* buffer for favorite number string */
    char favorite_str[64];
    int fav;

    printf("Enter your name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    /* Strip trailing newline */
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your favorite number: ");
    if (fgets(favorite_str, sizeof(favorite_str), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    favorite_str[strcspn(favorite_str, "\n")] = '\0';

    /*
     * strtol parses a string into a long with full error detection.
     * Always check the result with errno and endptr.
     */
    char *endptr;
    errno = 0;
    long val = strtol(favorite_str, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == favorite_str || *endptr != '\0') {
        fprintf(stderr, "Invalid input: expected a number.\n");
        return EXIT_FAILURE;
    }
    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Out of int range\n");
        return EXIT_FAILURE;
    }
    fav = (int)val;

    printf("Hello, %s! Your favorite number is %d.\n", name, fav);

    return EXIT_SUCCESS;
}
