#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int age = 25;
    double price = 19.99;
    char grade = 'A';

    printf("Age (int): %d\n", age);
    printf("Price (double): %.2f\n", price);
    printf("Grade (char): %c\n", grade);

    printf("Size of int: %zu bytes\n", sizeof(age));
    printf("Size of double: %zu bytes\n", sizeof(price));
    printf("Size of char: %zu byte\n", sizeof(grade));

    return EXIT_SUCCESS;
}

// Thinking in C:
// C is a statically typed language — every variable's type is fixed at compile
// time. Unlike Python or JavaScript, you cannot change a variable's type after
// declaration. sizeof tells you how much memory a type occupies, measured in
// bytes. Each type has a format specifier: %d for int, %f for double, %c for
// char and %zu for sizeof(variable_type), number of bytes it occupies in
// memory.
