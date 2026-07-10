/*
 * Exercise 01: Multi-file style with header guards
 *
 * This file simulates a multi-file project in a single .c file.
 * Fill in the blanks to complete the preprocessor guard pattern
 * and the function declaration.
 *
 * Hint: the guard should prevent double-inclusion of the
 * "MathUtil" type, and print_result should be declared before
 * it's used in main().
 */

#include <stdio.h>
#include <stdlib.h>

/* ---- FILL IN THE PREPROCESSOR GUARD PATTERN ---- */
/* Use #ifndef MATHUTIL_H / #define MATHUTIL_H / #endif */

typedef struct {
    int a;
    int b;
} MathUtil;

/* ---- FILL IN THIS FORWARD DECLARATION ---- */
/* Declare: static void print_result(const MathUtil *mu, int result); */
static void print_result(const MathUtil *mu, int result);

int main(void)
{
    MathUtil example = {7, 3};
    int result = example.a + example.b;
    print_result(&example, result);
    return EXIT_SUCCESS;
}

static void print_result(const MathUtil *mu, int result)
{
    printf("%d + %d = %d\n", mu->a, mu->b, result);
}
