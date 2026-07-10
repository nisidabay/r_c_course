/*
 * Concept: Function Prototypes (Forward Declarations)
 * Group 03 - Functions
 *
 * A prototype tells the compiler about a function BEFORE its definition
 * or use:  return_type name( param_types );
 *
 * Without a prototype, C assumes the function returns 'int' and accepts
 * anything — which is dangerous.  Prototypes give the compiler the
 * information it needs to check calls for correctness.
 */

#include <stdio.h>

/* ---- function prototypes (declarations) ---- */

int factorial(int n);        /* prototype: takes int, returns int */
void print_positive(int n);  /* prototype: takes int, returns nothing */
double average(double a, double b);  /* prototype: two doubles, returns double */

/* ---- main can call these before their definitions appear ---- */

int main(void)
{
    puts("=== Function Prototypes ===");

    int n = 5;
    int fact = factorial(n);
    printf("factorial(%d) = %d\n", n, fact);

    print_positive(fact);
    print_positive(-3);

    double avg = average(10.5, 20.5);
    printf("average(10.5, 20.5) = %.1f\n", avg);

    return 0;
}

/* ---- function definitions (can be anywhere after the prototype) ---- */

int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i = i + 1) {
        result = result * i;
    }
    return result;
}

void print_positive(int n)
{
    if (n > 0) {
        printf("  %d is positive.\n", n);
    } else {
        printf("  %d is NOT positive.\n", n);
    }
}

double average(double a, double b)
{
    return (a + b) / 2.0;
}

// Thinking in C:
// A prototype is just the function's signature followed by a semicolon.
// It tells the compiler: "this function exists, here's how to call it."
// Without prototypes (or putting definitions before all uses), the
// compiler might infer wrong types — prototypes catch mismatches early.
