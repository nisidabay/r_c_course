/*
 * Mini-Challenge 07: FizzBuzz (loops + conditionals + comparisons)
 *
 * Concept: Combine everything — for loops, if/else, logical ops, comparisons,
 *          and modulo arithmetic.
 *
 * Write a complete program that reads a positive integer n from the user and
 * prints the numbers from 1 to n with these rules:
 *
 *   - If the number is divisible by 3, print "Fizz"
 *   - If the number is divisible by 5, print "Buzz"
 *   - If divisible by both 3 and 5, print "FizzBuzz"
 *   - Otherwise, print the number itself
 *
 * Example (n = 15):
 *   1
 *   2
 *   Fizz
 *   4
 *   Buzz
 *   Fizz
 *   7
 *   8
 *   Fizz
 *   Buzz
 *   11
 *   Fizz
 *   13
 *   14
 *   FizzBuzz
 *
 * HINT: Use the modulo operator (%) to check divisibility:
 *       if (x % 3 == 0) means x is divisible by 3.
 *
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_07_challenge.c -o ex_07_challenge
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int n;

    /* --- Your code below --- */

    printf("Enter a positive integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    buf[strcspn(buf, "\n")] = '\0';

    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    if (endptr == buf || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Out of int range\n");
        return EXIT_FAILURE;
    }
    n = (int)val;
    if (n < 1) {
        fprintf(stderr, "Must be at least 1\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            printf("FizzBuzz\n");
        } else if (i % 3 == 0) {
            printf("Fizz\n");
        } else if (i % 5 == 0) {
            printf("Buzz\n");
        } else {
            printf("%d\n", i);
        }
    }

    return EXIT_SUCCESS;
}
