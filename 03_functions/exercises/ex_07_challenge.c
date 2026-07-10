/*
 * Mini-Challenge 07: Function Composition
 *
 * Concepts tested: defining functions, return values, pass-by-value,
 *                  scope, prototypes, exit codes — all in one program.
 *
 * Write the complete program below. Do NOT modify the provided structure —
 * fill in the missing pieces marked /*@*//*@*/.
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
 *   - fgets + sscanf for input (no scanf)
 *   - int main(void)
 *   - No strcpy/strcat/sprintf/scanf/atoi/atof
 *   - Must compile with -std=c11 -Wall -Wextra -pedantic
 *
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
 */

#include <stdio.h>
#include <stdlib.h>

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

    if (sscanf(buf, "%d", &num) != 1)
        return EXIT_FAILURE;

    /* (1) call factorial */
    /*@*/

    /* (2) if result is -1, print error and return EXIT_FAILURE */
    /*@*/

    /* (3) print factorial result */
    /*@*/

    /* (4) check if the result is prime, print that info */
    /*@*/

    /* (5) count divisors and print */
    /*@*/

    /* (6) return EXIT_SUCCESS */
    /*@*/
}

/* ---- factorial ---- */
int factorial(int n)
{
    /* TODO: return -1 if n < 0 or n > 12 */
    /* TODO: 0! = 1 */
    /* TODO: compute n! using a for loop */
    /*@*/
}

/* ---- is_prime ---- */
int is_prime(int n)
{
    /* TODO: return 0 for n < 2 */
    /* TODO: check divisibility from 2 to n/2 */
    /*       if any divides evenly, return 0 */
    /* TODO: return 1 if no divisor found */
    /*@*/
}

/* ---- count_divisors ---- */
int count_divisors(int n)
{
    int count = 0;
    /* TODO: loop i from 1 to n, count if n % i == 0 */
    /* Use a block scope for the loop variable i */
    /*@*/
    return count;
}

/* ---- print_debug ---- */
void print_debug(const char *msg, int val)
{
    /* TODO: if DEBUG is 1, print "[DEBUG] msg: val\n" */
    /* TODO: if DEBUG is 0, do nothing */
    /*@*/
}
