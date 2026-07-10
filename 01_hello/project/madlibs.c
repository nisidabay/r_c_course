/*
 * madlibs.c — A fill-in-the-blank word game
 *
 * Prompts the user for a noun, verb, adjective, adverb, and number,
 * then prints a silly story with the user's words inserted.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic madlibs.c -o madlibs
 * Run:    ./madlibs
 */

#include <stdio.h>

int main(void) {
    char noun[64];
    char verb[64];
    char adjective[64];
    char adverb[64];
    char number_str[32];
    int number;
    int ret;

    puts("=== MadLibs ===");
    puts("Fill in the blanks below and I'll tell you a story!\n");

    /* Prompt for a noun */
    printf("Enter a noun: ");
    if (fgets(noun, sizeof(noun), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    ret = sscanf(noun, "%63s", noun);
    if (ret != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    /* Prompt for a verb */
    printf("Enter a verb: ");
    if (fgets(verb, sizeof(verb), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    ret = sscanf(verb, "%63s", verb);
    if (ret != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    /* Prompt for an adjective */
    printf("Enter an adjective: ");
    if (fgets(adjective, sizeof(adjective), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    ret = sscanf(adjective, "%63s", adjective);
    if (ret != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    /* Prompt for an adverb */
    printf("Enter an adverb: ");
    if (fgets(adverb, sizeof(adverb), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    ret = sscanf(adverb, "%63s", adverb);
    if (ret != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    /* Prompt for a number */
    printf("Enter a number: ");
    if (fgets(number_str, sizeof(number_str), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    ret = sscanf(number_str, "%d", &number);
    if (ret != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    /* Print the completed story */
    puts("\n=== Your MadLibs Story ===\n");

    printf("One day, a %s decided to take a walk in the park.\n", noun);
    printf("Suddenly, it spotted a %s squirrel and began to %s %s.\n",
           adjective, verb, adverb);
    printf("After exactly %d seconds of this, the %s stopped,\n", number, noun);
    printf("looked around with a puzzled expression, and walked away.\n");
    printf("The end!\n");

    return 0;
}
