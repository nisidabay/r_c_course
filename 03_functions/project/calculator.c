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
 * (see `06_pointers_101` — strtol's endptr is a pointer to the
 * first unparsed character; you'll master pointers there!)
 */

#include <stdio.h>
#include <stdlib.h>   /* strtol */
#include <string.h>   /* strcspn */

/* Error code for division/modulo by zero */
#define ERROR_DIV_ZERO 2147483647  /* close to INT_MAX, unlikely as valid result */

/* Buffer size for input lines */

/**
 * consume_remaining - Clear stdin of any leftover chars beyond what fgets read.
 * Call when truncation is detected (buf doesn't end with '\n').
 */
static void consume_remaining(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

/* Buffer size for input lines */
#define LINE_BUF 64

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
 * divide - Returns a / b, or ERROR_DIV_ZERO if b is zero.
 */
int divide(int a, int b)
{
    if (b == 0) {
        printf("Error: division by zero is undefined.\n");
        return ERROR_DIV_ZERO;
    }
    return a / b;
}

/**
 * modulo - Returns a % b, or ERROR_DIV_ZERO if b is zero.
 */
int modulo(int a, int b)
{
    if (b == 0) {
        printf("Error: modulo by zero is undefined.\n");
        return ERROR_DIV_ZERO;
    }
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
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] != '\n')
            consume_remaining();

        /* Strip newline so "q\n" becomes "\0" */
        line[strcspn(line, "\n")] = '\0';

        /* Check for quit */
        if (strcmp(line, "q") == 0) {
            break;
        }

        /* Parse first number */
        long tmp = strtol(line, &endptr, 10);
        if (endptr == line || *endptr != '\0') {
            printf("Invalid input. Enter a number or 'q' to quit.\n");
            continue;
        }
        a = (int)tmp;

        /* ---- Read operator ---- */
        printf("Enter operator (+ - * / %%): ");
        if (fgets(line, sizeof line, stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }
        len = strlen(line);
        if (len > 0 && line[len - 1] != '\n')
            consume_remaining();
        op = line[0];

        /* ---- Read second number ---- */
        printf("Enter second number: ");
        if (fgets(line, sizeof line, stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }
        len = strlen(line);
        if (len > 0 && line[len - 1] != '\n')
            consume_remaining();

        tmp = strtol(line, &endptr, 10);
        if (endptr == line || *endptr != '\n') {
            printf("Invalid input. Please enter a valid integer.\n");
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
            result = divide(a, b);
            if (result != ERROR_DIV_ZERO)
                printf("%d / %d = %d\n", a, b, result);
            break;
        case '%':
            result = modulo(a, b);
            if (result != ERROR_DIV_ZERO)
                printf("%d %% %d = %d\n", a, b, result);
            break;
        default:
            printf("Unknown operator '%c'. Use + - * / %% or 'q' to quit.\n", op);
            break;
        }
    }

    printf("Goodbye!\n");
    return 0;
}
