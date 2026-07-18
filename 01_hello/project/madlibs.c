/*
 * madlibs.c — A fill-in-the-blank word game
 *
 * Prompts the user for a noun, verb, adjective, adverb, and number,
 * then prints a silly story with the user's words inserted.
 *
 * Safe C Standard: uses fgets for all input with truncation detection,
 * strtol for number parsing (see `07_pointers_101` — you'll master
 * pointers there! For now: strtol uses endptr to detect invalid input).
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic madlibs.c -o madlibs
 * Run:    ./madlibs
 */
#include <errno.h>
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
    errno = 0;
    long number = strtol(number_str, &endptr, 10);

    // Check if no conversion happened OR if trailing garbage was left behind
    if (endptr == number_str || *endptr != '\0') {
        fprintf(stderr, "Invalid input: expected a whole number without "
                        "trailing characters.\n");
        return EXIT_FAILURE;
    }
    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range.\n");
        return EXIT_FAILURE;
    }

    puts("\n=== Your MadLibs Story ===\n");
    printf("One day,  %s decided to take a walk in the park.\n", noun);
    printf("Suddenly, it spotted a %s squirrel and began to %s %s.\n",
           adjective, verb, adverb);
    printf("After exactly %ld seconds of this, %s stopped,\n", number, noun);
    printf("looked around with a puzzled expression, and walked away.\n");
    printf("The end!\n");

    return EXIT_SUCCESS;
}

static void read_input(char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;   /* input was truncated — drain residue */
        } else if (len > 0) {
            buffer[len - 1] = '\0';  /* strip trailing newline */
        }
    } else {
        fprintf(stderr, "Error reading input.\n");
        exit(EXIT_FAILURE);
    }
}
