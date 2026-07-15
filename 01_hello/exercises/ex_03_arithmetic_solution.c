#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a = 20;
    int b = 6;

    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    int quot = a / b;
    int rem = a % b;

    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", sum);
    printf("a - b = %d\n", diff);
    printf("a * b = %d\n", prod);
    printf("a / b = %d\n", quot);
    printf("a %% b = %d\n", rem);

    return EXIT_SUCCESS;
}
