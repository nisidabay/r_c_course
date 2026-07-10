#include <stdio.h>

int main(void)
{
    char input[32];
    int birth_year;
    int current_year;

    printf("Enter your birth year: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &birth_year);

    printf("Enter current year: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &current_year);

    int age = current_year - birth_year;
    int months = age * 12;

    printf("You are approximately %d years old.\n", age);
    printf("That is about %d months!\n", months);

    return 0;
}
