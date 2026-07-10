#include <stdio.h>

int main(void)
{
    int age = 25;
    double price = 19.99;
    char grade = 'A';

    printf("Age (int): %d\n", age);
    printf("Price (double): %.2f\n", price);
    printf("Grade (char): %c\n", grade);

    printf("Size of int: %lu bytes\n", sizeof(age));
    printf("Size of double: %lu bytes\n", sizeof(price));
    printf("Size of char: %lu byte\n", sizeof(grade));

    return 0;
}

// Thinking in C:
// C is a statically typed language — every variable's type is fixed at compile time.
// Unlike Python or JavaScript, you cannot change a variable's type after declaration.
// sizeof tells you how much memory a type occupies, measured in bytes.
// Each type has a format specifier: %d for int, %f for double, %c for char.
