/*
 * Exercise 07 — Challenge: Number Guessing
 *
 * Generate a random number between 1 and 100 and let the user guess it.
 * After each guess, tell if it's too high, too low, or correct.
 *
 * Expected interaction (guess 50, then 75, then 63):
 *   Guess a number (1-100): 50
 *   Too low!
 *   Guess a number (1-100): 75
 *   Too high!
 *   Guess a number (1-100): 63
 *   Correct! It took you 3 guesses.
 *
 * Hints:
 *   - srand(time(NULL)); int target = rand() % 100 + 1;
 *   - Loop until correct: while (1) or do-while
 *   - fgets + strtol for each guess
 *   - #include <stdlib.h>, <stdio.h>, <time.h>, <errno.h>, <limits.h>, <string.h>
 */
