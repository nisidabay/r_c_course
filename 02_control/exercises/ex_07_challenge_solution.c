/*
 * Solution 07: FizzBuzz Challenge
 *
 * Prints numbers 1 to n with Fizz/Buzz/FizzBuzz substitutions.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int n;

    printf("Enter a positive integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &n) != 1 || n < 1)
        return 1;

    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            printf("FizzBuzz\n");
        } else if (i % 3 == 0) {
            printf("Fizz\n");
        } else if (i % 5 == 0) {
            printf("Buzz\n");
        } else {
            printf("%d\n", i);
        }
    }

    return 0;
}
