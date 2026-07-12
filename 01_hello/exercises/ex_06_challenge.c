#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    /*
     * CHALLENGE: Age Calculator
     *
     * Write a program that:
     *   1. Ask the user "Enter your birth year: "
     *   2. Read the input using fgets + strtol
     *   3. Ask the user "Enter current year: "
     *   4. Read the input using fgets + strtol
     *   5. Compute their approximate age (current_year - birth_year)
     *   6. Compute their age in months (age * 12)
     *   7. Print:
     *      "You are approximately X years old.\n"
     *      "That is about Y months!\n"
     *
     * Uncomment and complete the lines below.
     * Replace YOUR_CODE_HERE with the correct code.
     */

    /* buffer for birth year string — 12 = 4 digits + newline + null + padding */
    char birth_str[64];
    /* buffer for current year string */
    char year_str[64];
    int birth_year = 0;
    int current_year = 0;
    char *endptr;

    // printf("Enter your birth year: ");
    // if (fgets(birth_str, sizeof(birth_str), stdin) == NULL) return EXIT_FAILURE;
    // birth_str[strcspn(birth_str, "\n")] = '\0';
    // errno = 0;
    // long bv = strtol(birth_str, &endptr, 10);
    // if (errno == ERANGE || endptr == birth_str || *endptr != '\0') {
    //     fprintf(stderr, "Invalid input\n");
    //     return EXIT_FAILURE;
    // }
    // birth_year = (int)bv;

    // printf("Enter current year: ");
    // if (fgets(year_str, sizeof(year_str), stdin) == NULL) return EXIT_FAILURE;
    // year_str[strcspn(year_str, "\n")] = '\0';
    // errno = 0;
    // long cv = strtol(year_str, &endptr, 10);
    // if (errno == ERANGE || endptr == year_str || *endptr != '\0') {
    //     fprintf(stderr, "Invalid input\n");
    //     return EXIT_FAILURE;
    // }
    // current_year = (int)cv;

    int age = 0;
    int months = 0;
    // age = YOUR_CODE_HERE;
    // months = YOUR_CODE_HERE;

    // printf("You are approximately %d years old.\n", age);
    // printf("That is about %d months!\n", months);

    return EXIT_SUCCESS;
}
