#include <stdio.h>
#include <string.h>

/* consume_remaining: if the input line was longer than the buffer,
 * discard the excess characters so the next fgets doesn't read stale data.
 */
static void consume_remaining(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(void)
{
    /* buffer for birth year string — 12 = 4 digits + newline + null + padding */
    char birth_str[12];
    /* buffer for current year string — 12 = 4 digits + newline + null + padding */
    char year_str[12];
    int birth_year;
    int current_year;

    printf("Enter your birth year: ");
    if (fgets(birth_str, sizeof(birth_str), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    size_t len = strlen(birth_str);
    if (len > 0 && birth_str[len - 1] != '\n')
        consume_remaining();

    /*
     * sscanf returns how many items it matched. Always check!
     * Here it parses the birth_str buffer as an integer.
     * Later (Group 03+) you'll use strtol for full error detection
     * (pointers from Group 06 make it click).
     */
    if (sscanf(birth_str, "%d", &birth_year) != 1) {
        printf("Invalid input: expected a year.\n");
        return 1;
    }

    printf("Enter current year: ");
    if (fgets(year_str, sizeof(year_str), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    len = strlen(year_str);
    if (len > 0 && year_str[len - 1] != '\n')
        consume_remaining();

    if (sscanf(year_str, "%d", &current_year) != 1) {
        printf("Invalid input: expected a year.\n");
        return 1;
    }

    int age = current_year - birth_year;
    int months = age * 12;

    printf("You are approximately %d years old.\n", age);
    printf("That is about %d months!\n", months);

    return 0;
}
