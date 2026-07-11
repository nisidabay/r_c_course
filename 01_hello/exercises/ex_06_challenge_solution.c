#include <stdio.h>
#include <string.h>

int main(void)
{
    char input[32];
    int birth_year;
    int current_year;

    printf("Enter your birth year: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    /*
     * sscanf returns how many items it matched. Always check!
     * Later (Group 03+) you'll use strtol for full error detection
     * (pointers from Group 06 make it click).
     */
    if (sscanf(input, "%d", &birth_year) != 1) {
        printf("Invalid input: expected a year.\n");
        return 1;
    }

    printf("Enter current year: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    if (sscanf(input, "%d", &current_year) != 1) {
        printf("Invalid input: expected a year.\n");
        return 1;
    }

    int age = current_year - birth_year;
    int months = age * 12;

    printf("You are approximately %d years old.\n", age);
    printf("That is about %d months!\n", months);

    return 0;
}
