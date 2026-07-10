/*
 * Solution 03: For Loops
 *
 * Reads a positive integer n and prints the sum 1 + 2 + ... + n.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int n;
    int sum = 0;

    printf("Enter a positive integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &n) != 1 || n < 1)
        return 1;

    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    printf("Sum = %d\n", sum);

    return 0;
}
