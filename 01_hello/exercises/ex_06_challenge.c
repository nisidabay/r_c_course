#include <stdio.h>

int main(void)
{
    /*
     * CHALLENGE: Age Calculator
     *
     * Write a program that:
     *   1. Ask the user "Enter your birth year: "
     *   2. Read the input using fgets + sscanf
     *   3. Ask the user "Enter current year: "
     *   4. Read the input using fgets + sscanf
     *   5. Compute their approximate age (current_year - birth_year)
     *   6. Compute their age in months (age * 12)
     *   7. Print:
     *      "You are approximately X years old.\n"
     *      "That is about Y months!\n"
     *
     * Uncomment and complete the lines below.
     * Replace YOUR_CODE_HERE with the correct code.
     */

    char input[32];
    int birth_year = 0;
    int current_year = 0;

    // printf("Enter your birth year: ");
    // fgets(input, sizeof(input), stdin);
    // sscanf(input, "%d", &birth_year);

    // printf("Enter current year: ");
    // fgets(input, sizeof(input), stdin);
    // sscanf(input, "%d", &current_year);

    int age = 0;
    int months = 0;
    // age = YOUR_CODE_HERE;
    // months = YOUR_CODE_HERE;

    // printf("You are approximately %d years old.\n", age);
    // printf("That is about %d months!\n", months);

    return 0;
}
