/*
 * Mini-Challenge 07: Function Composition — SOLUTION
 *
 * Concepts: defining functions, return values, pass-by-value,
 *           scope, prototypes, exit codes.
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
    int fact = factorial(num);

    /* (2) if result is -1, print error and return EXIT_FAILURE */
    if (fact == -1) {
        printf("Error: factorial of %d is out of range.\n", num);
        return EXIT_FAILURE;
    }

    /* (3) print factorial result */
    printf("%d! = %d\n", num, fact);

    /* (4) check if the result is prime, print that info */
    if (is_prime(fact)) {
        printf("%d is prime.\n", fact);
    } else {
        printf("%d is NOT prime.\n", fact);
    }

    /* (5) count divisors and print */
    int divs = count_divisors(fact);
    printf("%d has %d divisor(s).\n", fact, divs);

    /* (6) return EXIT_SUCCESS */
    return EXIT_SUCCESS;
}

/* ---- factorial ---- */
int factorial(int n)
{
    if (n < 0 || n > 12) {
        return -1;
    }
    int result = 1;
    for (int i = 2; i <= n; i = i + 1) {
        result = result * i;
    }
    return result;
}

/* ---- is_prime ---- */
int is_prime(int n)
{
    if (n < 2) {
        return 0;
    }
    for (int i = 2; i <= n / 2; i = i + 1) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/* ---- count_divisors ---- */
int count_divisors(int n)
{
    int count = 0;
    {
        for (int i = 1; i <= n; i = i + 1) {
            if (n % i == 0) {
                count = count + 1;
            }
        }
    }
    return count;
}

/* ---- print_debug ---- */
void print_debug(const char *msg, int val)
{
    if (DEBUG == 1) {
        printf("[DEBUG] %s: %d\n", msg, val);
    }
}
