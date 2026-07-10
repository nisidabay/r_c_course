/*
 * calculator.c - A simple integer calculator
 *
 * Concepts: functions, return values, pass-by-value, exit codes
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic calculator.c -o calculator
 *
 * Operations: +, -, *, /, %
 * Enter 'q' to quit.
 */

#include <stdio.h>

/* Error code for division/modulo by zero */
#define ERROR_DIV_ZERO 2147483647  /* close to INT_MAX, unlikely as valid result */

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
    int a, b, result;
    char op;
    int keep_running = 1;

    printf("=== Integer Calculator ===\n");
    printf("Enter: <number> <operator> <number>\n");
    printf("Operators: + - * / %%\n");
    printf("Enter 'q' to quit.\n\n");

    while (keep_running) {
        printf("> ");

        /* Try to read first number. If user enters 'q', quit. */
        if (scanf("%d", &a) != 1) {
            /* Not a number — check if it's 'q' */
            scanf(" %c", &op);
            if (op == 'q') {
                keep_running = 0;
                continue;
            }
            printf("Invalid input. Enter a number or 'q' to quit.\n");
            /* Clear remaining input up to newline */
            while (getchar() != '\n')
                ;
            continue;
        }

        /* Read operator */
        scanf(" %c", &op);

        /* Read second number */
        if (scanf("%d", &b) != 1) {
            printf("Invalid input. Please enter a valid integer.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        /* Perform the requested operation */
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
