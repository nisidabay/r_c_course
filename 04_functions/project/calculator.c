/*
 * calculator.c - A simple integer calculator
 *
 * Concepts: functions, return values, pass-by-value, exit codes
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic calculator.c -o calculator
 *
 * Operations: +, -, *, /, %
 * Enter 'q' to quit.
 *
 * Safe C Standard: uses fgets + strtol for all number input
 * (see `07_pointers_101` — strtol's endptr is a pointer to the
 * first unparsed character; you'll master pointers there!)
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Buffer size for input lines */
#define LINE_BUF 64

static void consume_remaining(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* Arithmetic function prototypes */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int modulo(int a, int b);

/**
 * add - Returns the sum of a and b.
 */
int add(int a, int b)
{
    return a + b;
}

/**
 * subtract - Returns the difference a - b.
 */
int subtract(int a, int b)
{
    return a - b;
}

/**
 * multiply - Returns the product of a and b.
 */
int multiply(int a, int b)
{
    return a * b;
}

/**
 * divide - Returns a / b.
 */
int divide(int a, int b)
{
    return a / b;
}

/**
 * modulo - Returns a % b.
 */
int modulo(int a, int b)
{
    return a % b;
}

/**
 * main - Interactive calculator loop.
 * Prompts for two integers and an operation, prints the result,
 * and repeats until the user enters 'q'.
 */
int main(void)
{
    char line[LINE_BUF];

    printf("=== Integer Calculator ===\n");
    printf("Enter: <number> <operator> <number>\n");
    printf("Operators: + - * / %%\n");
    printf("Enter 'q' to quit.\n\n");

    while (1) {
        int a, b, result;
        char op;
        char *endptr;

        printf("> ");

        /* ---- Read first number via fgets + strtol ---- */
        if (fgets(line, sizeof line, stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }

        /* Check for truncation, then strip trailing newline */
        {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] != '\n') {
                consume_remaining();
            } else if (len > 0) {
                line[len - 1] = '\0';
            }
        }

        /* Check for quit */
        if (strcmp(line, "q") == 0) {
            break;
        }

        /* Parse first number */
        errno = 0;
        long tmp = strtol(line, &endptr, 10);
        if (errno == ERANGE || endptr == line || *endptr != '\0') {
            printf("Invalid input. Enter a number or 'q' to quit.\n");
            continue;
        }
        if (tmp < INT_MIN || tmp > INT_MAX) {
            printf("Number out of range.\n");
            continue;
        }
        a = (int)tmp;

        /* ---- Read operator ---- */
        printf("Enter operator (+ - * / %%): ");
        if (fgets(line, sizeof line, stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }

        {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] != '\n') {
                consume_remaining();
            } else if (len > 0) {
                line[len - 1] = '\0';
            }
        }
        if (strlen(line) == 0) {
            printf("No operator entered.\n");
            continue;
        }
        op = line[0];

        /* ---- Read second number ---- */
        printf("Enter second number: ");
        if (fgets(line, sizeof line, stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }

        {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] != '\n') {
                consume_remaining();
            } else if (len > 0) {
                line[len - 1] = '\0';
            }
        }

        errno = 0;
        tmp = strtol(line, &endptr, 10);
        if (errno == ERANGE || endptr == line || *endptr != '\0') {
            printf("Invalid input. Please enter a valid integer.\n");
            continue;
        }
        if (tmp < INT_MIN || tmp > INT_MAX) {
            printf("Number out of range.\n");
            continue;
        }
        b = (int)tmp;

        /* ---- Perform the requested operation ---- */
        switch (op) {
        case '+':
            result = add(a, b);
            printf("%d + %d = %d\n", a, b, result);
            break;
        case '-':
            result = subtract(a, b);
            printf("%d - %d = %d\n", a, b, result);
            break;
        case '*':
            result = multiply(a, b);
            printf("%d * %d = %d\n", a, b, result);
            break;
        case '/':
            if (b == 0) {
                printf("Error: division by zero is undefined.\n");
            } else {
                result = divide(a, b);
                printf("%d / %d = %d\n", a, b, result);
            }
            break;
        case '%':
            if (b == 0) {
                printf("Error: modulo by zero is undefined.\n");
            } else {
                result = modulo(a, b);
                printf("%d %% %d = %d\n", a, b, result);
            }
            break;
        default:
            printf("Unknown operator '%c'. Use + - * / %% or 'q' to quit.\n", op);
            break;
        }
    }

    printf("Goodbye!\n");
    return EXIT_SUCCESS;
}
