/*
 * madlibs.c — A fill-in-the-blank word game
 *
 * Prompts the user for a noun, verb, adjective, adverb, and number,
 * then prints a silly story with the user's words inserted.
 *
 * Safe C Standard: uses fgets for all input, strcspn to strip newlines,
 * strtol for number parsing (see `06_pointers_101` — you'll master
 * pointers there! For now: strtol uses endptr to detect invalid input).
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic madlibs.c -o madlibs
 * Run:    ./madlibs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char noun[48];           /* 48 chars — plenty for a single word */
    char verb[48];           /* 48 chars — plenty for a single word */
    char adjective[48];      /* 48 chars — plenty for a single word */
    char adverb[48];         /* 48 chars — plenty for a single word */
    char number_str[12];     /* 12 chars — 9 digits + sign + '\n' + '\0' */

    puts("=== MadLibs ===");
    puts("Fill in the blanks below and I'll tell you a story!\n");

    /* Prompt for a noun */
    printf("Enter a noun: ");
    if (fgets(noun, sizeof(noun), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    noun[strcspn(noun, "\n")] = '\0';

    /* Prompt for a verb */
    printf("Enter a verb: ");
    if (fgets(verb, sizeof(verb), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    verb[strcspn(verb, "\n")] = '\0';

    /* Prompt for an adjective */
    printf("Enter an adjective: ");
    if (fgets(adjective, sizeof(adjective), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    adjective[strcspn(adjective, "\n")] = '\0';

    /* Prompt for an adverb */
    printf("Enter an adverb: ");
    if (fgets(adverb, sizeof(adverb), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    adverb[strcspn(adverb, "\n")] = '\0';

    /* Prompt for a number */
    printf("Enter a number: ");
    if (fgets(number_str, sizeof(number_str), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    char *endptr;
    long number = strtol(number_str, &endptr, 10);
    if (endptr == number_str || (*endptr != '\n' && *endptr != '\0')) {
        printf("Invalid input: expected a whole number.\n");
        return 1;
    }

    /* Print the completed story */
    puts("\n=== Your MadLibs Story ===\n");

    printf("One day, a %s decided to take a walk in the park.\n", noun);
    printf("Suddenly, it spotted a %s squirrel and began to %s %s.\n",
           adjective, verb, adverb);
    printf("After exactly %ld seconds of this, the %s stopped,\n", number, noun);
    printf("looked around with a puzzled expression, and walked away.\n");
    printf("The end!\n");

    return 0;
}
