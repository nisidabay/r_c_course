#include <stdio.h>

int main(void)
{
    int a = 15;
    int b = 4;

    int sum = a + b;
    int difference = a - b;
    int product = a * b;
    int quotient = a / b;
    int remainder = a % b;

    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", sum);
    printf("a - b = %d\n", difference);
    printf("a * b = %d\n", product);
    printf("a / b = %d  (integer division truncates)\n", quotient);
    printf("a %% b = %d  (modulus, the remainder)\n", remainder);

    int result = a + b * 2;
    printf("a + b * 2 = %d  (multiplication before addition)\n", result);

    result = (a + b) * 2;
    printf("(a + b) * 2 = %d  (parentheses override precedence)\n", result);

    return 0;
}

// Thinking in C:
// C's arithmetic operators work like standard math — but / on two ints truncates.
// Unlike Python, C's / with integers drops the fractional part (no floor division).
// Operator precedence follows PEMDAS; use parentheses to be explicit.
// The modulo operator % works only with integers, not floating-point types.
