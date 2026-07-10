/*
 * Concept: Return Values
 * Group 03 - Functions
 *
 * The return statement sends a value back to the caller and exits the
 * function immediately.  A function declared 'void' returns nothing.
 * Every non-void function must return a value of the declared type.
 */

#include <stdio.h>

/* void function — prints, no return value */
void print_separator(void)
{
    printf("---\n");
    /* reaches end, returns implicitly — OK for void */
}

/* returns an int */
int square(int n)
{
    return n * n;
}

/* returns a double */
double celsius_to_fahrenheit(double c)
{
    return c * 9.0 / 5.0 + 32.0;
}

/* returns a char: the first letter of a word (simplified) */
char first_letter(void)
{
    char word[] = "Celsius";
    return word[0];
}

/* multiple return points — function returns the sign as -1, 0, or 1 */
int sign_of(int value)
{
    if (value > 0) {
        return 1;
    }
    if (value < 0) {
        return -1;
    }
    return 0;
}

int main(void)
{
    puts("=== Return Values ===");

    print_separator();

    /* capture return values in variables */
    int s = square(7);
    printf("square(7) = %d\n", s);

    /* use a return value directly in an expression */
    printf("square(12) = %d\n", square(12));

    print_separator();

    double temp_f = celsius_to_fahrenheit(100.0);
    printf("100.0 C = %.1f F\n", temp_f);

    printf("First letter of 'Celsius': %c\n", first_letter());

    print_separator();

    printf("sign_of(42)  = %d\n", sign_of(42));
    printf("sign_of(0)   = %d\n", sign_of(0));
    printf("sign_of(-17) = %d\n", sign_of(-17));

    print_separator();
    puts("Done.");

    return 0;
}

// Thinking in C:
// Every C function that is not 'void' must return a value on every path.
// A 'void' function can use 'return;' to exit early, or simply fall off
// the end.  Returning the wrong type triggers implicit conversion or a
// compiler warning — C trusts you to get it right.
