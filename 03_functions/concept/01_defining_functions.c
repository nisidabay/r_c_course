/*
 * Concept: Defining Functions
 * Group 03 - Functions
 *
 * Every function needs: a return type, a name, parameter list, and a body.
 * Syntax:  return_type name( param_type param_name, ... ) { body }
 *
 * This file defines three functions and calls them from main.
 */

#include <stdio.h>

/* ---- function definitions ---- */

/* greet: takes no parameters, returns nothing, prints a greeting */
void greet(void)
{
    printf("Hello from greet()!\n");
}

/* add: takes two ints, returns their sum */
int add(int a, int b)
{
    int result = a + b;
    return result;
}

/* max: takes two ints, returns the larger one */
int max(int x, int y)
{
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int main(void)
{
    puts("=== Defining Functions ===");

    /* call greet */
    greet();

    /* call add and print its result */
    int sum = add(10, 25);
    printf("add(10, 25) = %d\n", sum);

    /* call max twice with different arguments */
    int bigger = max(-5, 3);
    printf("max(-5, 3) = %d\n", bigger);

    printf("max(100, 42) = %d\n", max(100, 42));

    return 0;
}

// Thinking in C:
// In C, a function definition is its own declaration if the definition
// appears before any call.  The function's signature (return type, name,
// parameters) tells the compiler exactly how to call it — no overloading,
// no default arguments.  What you write is what you get.
