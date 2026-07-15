/******************************************************************************
 * number_guess.c — Number Guessing Game
 *
 * A simple console game where the player guesses a random number between
 * 1 and 100. After each guess, the program tells the player if the guess
 * was too high or too low, and keeps track of the number of attempts.
 *
 * Concepts used:
 *   - stdio: printf, fgets, sscanf
 *   - stdlib: rand, srand
 *   - time: time
 *   - if/else, while, break
 *   - comparison operators, logical operators
 *   - increment (++), compound assignment
 *
 * Compile:
 *   gcc -std=c11 -Wall -Wextra -pedantic number_guess.c -o number_guess
 *
 * Usage:
 *   ./number_guess
 ******************************************************************************/
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {
    int secret;
    int guess;
    int attempts;
    char buffer[64];
    char *endptr;

    /* Seed the random number generator with the current time idiomatically */
    srand(time(NULL));

    /* Generate a random number between 1 and 100 */
    secret = (rand() % 100) + 1;

    attempts = 0;

    printf("========================================\n");
    printf("  Welcome to the Number Guessing Game!\n");
    printf("========================================\n");
    printf("I'm thinking of a number between 1 and 100.\n");
    printf("Can you guess what it is?\n\n");

    /* Main game loop — keep prompting until the player guesses correctly */
    while (1) {
        printf("Enter your guess: ");

        /* Read the player's input as a line of text */
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }

        /* Strip trailing newline */
        buffer[strcspn(buffer, "\n")] = '\0';

        /* Try to parse an integer from the input using strtol */
        errno = 0;
        long tmp = strtol(buffer, &endptr, 10);

        /* Validate: Check if nothing was parsed, or trailing garbage */
        if (endptr == buffer || *endptr != '\0') {
            printf("Please enter a strictly valid number.\n");
            continue;
        }
        if (errno == ERANGE || tmp < INT_MIN || tmp > INT_MAX) {
            printf("Number out of range.\n");
            continue;
        }
        guess = (int)tmp;

        attempts = attempts + 1;

        /* Check the guess against the secret number */
        if (guess < secret) {
            printf("Too low! Try again.\n");
        } else if (guess > secret) {
            printf("Too high! Try again.\n");
        } else {
            /* Correct guess! */
            printf("\n");
            printf("Congratulations! You guessed it!\n");
            printf("The number was %d.\n", secret);
            printf("It took you %d attempt", attempts);
            if (attempts != 1) {
                printf("s");
            }
            printf(".\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}
