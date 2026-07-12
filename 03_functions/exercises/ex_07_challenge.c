/*
 * Mini-Challenge 07: Function Composition
 *
 * Concepts tested: defining functions, return values, pass-by-value,
 *                  scope, prototypes, exit codes — all in one program.
 *
 * Write the complete program below. Do NOT modify the provided structure —
 * fill in the missing pieces marked FIX ME.
 *
 * The program should:
 *   1. Have a global int DEBUG initialized to 0.
 *   2. Have prototypes for: factorial, is_prime, count_divisors, print_debug.
 *   3. factorial(n): returns n! for n >= 0 (0! = 1). Returns -1 for n < 0 or n > 12.
 *   4. is_prime(n): returns 1 if n is prime, 0 otherwise. For n < 2, return 0.
 *   5. count_divisors(n): returns how many positive integers divide n evenly.
 *      Uses its own local scope (block inside the function) for the loop counter.
 *   6. print_debug(msg, val): void function. If DEBUG is 1, prints "[DEBUG] msg: val".
 *      If DEBUG is 0, prints nothing.
 *   7. main() reads an integer, calls factorial, then checks if result is prime
 *      using is_prime, and prints results. Uses EXIT_SUCCESS/EXIT_FAILURE.
 *
 * Rules:
 *   - fgets + strtol for input (no scanf)
 *   - int main(void)
 *   - No strcpy/strcat/sprintf/scanf/atoi/atof
 *   - Must compile with -std=c11 -Wall -Wextra -pedantic
 *
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- global ---- */
int DEBUG = 0;

/* ---- prototypes ---- */
int factorial(int n);
int is_prime(int n);
int count_divisors(int n);
void print_debug(const char *msg, int val);

int main(void) {
    char buf[64];
    int num;

    printf("Enter a non-negative integer (0-12): ");
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return EXIT_FAILURE;

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
    num = (int)val;

    /* (1) call factorial */
    int fact = factorial(num);  // FIX ME

    /* (2) if result is -1, print error and return EXIT_FAILURE */
    if (fact == -1) {  // FIX ME
        fprintf(stderr, "Error: factorial input out of range\n");
        return EXIT_FAILURE;
    }

    /* (3) print factorial result */
    printf("factorial(%d) = %d\n", num, fact);  // FIX ME

    /* (4) check if the result is prime, print that info */
    if (is_prime(fact)) {  // FIX ME
        printf("%d is prime!\n", fact);
    } else {
        printf("%d is not prime.\n", fact);
    }

    /* (5) count divisors and print */
    int nd = count_divisors(fact);  // FIX ME
    printf("%d has %d divisors.\n", fact, nd);

    /* (6) return EXIT_SUCCESS */
    return EXIT_SUCCESS;  // FIX ME
}

/* ---- factorial ---- */
int factorial(int n)
{
    if (n < 0 || n > 12)  // FIX ME
        return -1;
    if (n == 0)
        return 1;
    int result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}

/* ---- is_prime ---- */
int is_prime(int n)
{
    if (n < 2)
        return 0;
    for (int i = 2; i <= n / 2; i++)  // FIX ME
        if (n % i == 0)
            return 0;
    return 1;
}

/* ---- count_divisors ---- */
int count_divisors(int n)
{
    int count = 0;
    /* Use a block scope for the loop variable i */
    {  // FIX ME
        for (int i = 1; i <= n; i++)
            if (n % i == 0)
                count++;
    }
    return count;
}

/* ---- print_debug ---- */
void print_debug(const char *msg, int val)
{
    if (DEBUG == 1)  // FIX ME
        printf("[DEBUG] %s: %d\n", msg, val);
    /* if DEBUG is 0, do nothing */
}
