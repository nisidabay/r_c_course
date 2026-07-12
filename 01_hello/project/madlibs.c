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

static void read_input(char *prompt, char *buffer, size_t size);

int main(void) {
    char noun[48];
    char verb[48];
    char adjective[48];
    char adverb[48];
    char number_str[12];

    puts("=== MadLibs ===");
    puts("Fill in the blanks below and I'll tell you a story!\n");

    read_input("Enter a noun: ", noun, sizeof(noun));
    read_input("Enter a verb: ", verb, sizeof(verb));
    read_input("Enter an adjective: ", adjective, sizeof(adjective));
    read_input("Enter an adverb: ", adverb, sizeof(adverb));
    read_input("Enter a number: ", number_str, sizeof(number_str));

    char *endptr;
    long number = strtol(number_str, &endptr, 10);

    // Check if no conversion happened OR if trailing garbage was left behind
    if (endptr == number_str || *endptr != '\0') {
        fprintf(stderr, "Invalid input: expected a whole number without "
                        "trailing characters.\n");
        return 1;
    }

    puts("\n=== Your MadLibs Story ===\n");
    printf("One day, a %s decided to take a walk in the park.\n", noun);
    printf("Suddenly, it spotted a %s squirrel and began to %s %s.\n",
           adjective, verb, adverb);
    printf("After exactly %ld seconds of this, the %s stopped,\n", number,
           noun);
    printf("looked around with a puzzled expression, and walked away.\n");
    printf("The end!\n");

    return 0;
}

static void read_input(char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] =
            '\0'; // Remove newline character if present.
    } else {
        fprintf(stderr, "Error reading input.\n");
        exit(1);
    }
}
