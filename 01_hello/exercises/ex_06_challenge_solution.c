#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    /* buffer for birth year string */
    char birth_str[64];
    /* buffer for current year string */
    char year_str[64];
    int birth_year;
    int current_year;

    printf("Enter your birth year: ");
    if (fgets(birth_str, sizeof(birth_str), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    birth_str[strcspn(birth_str, "\n")] = '\0';

    /*
     * strtol parses a string into a long with full error detection.
     */
    char *endptr;
    errno = 0;
    long val = strtol(birth_str, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Birth year out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == birth_str || *endptr != '\0') {
        fprintf(stderr, "Invalid input: expected a year.\n");
        return EXIT_FAILURE;
    }
    if (val < 1900 || val > 2100) {
        fprintf(stderr, "Birth year out of reasonable range\n");
        return EXIT_FAILURE;
    }
    birth_year = (int)val;

    printf("Enter current year: ");
    if (fgets(year_str, sizeof(year_str), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    year_str[strcspn(year_str, "\n")] = '\0';

    errno = 0;
    val = strtol(year_str, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Current year out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == year_str || *endptr != '\0') {
        fprintf(stderr, "Invalid input: expected a year.\n");
        return EXIT_FAILURE;
    }
    if (val < 1900 || val > 2100) {
        fprintf(stderr, "Current year out of reasonable range\n");
        return EXIT_FAILURE;
    }
    current_year = (int)val;

    int age = current_year - birth_year;
    int months = age * 12;

    printf("You are approximately %d years old.\n", age);
    printf("That is about %d months!\n", months);

    return EXIT_SUCCESS;
}
