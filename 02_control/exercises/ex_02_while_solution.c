/*
 * Solution 02: While Loops
 *
 * Reads a positive integer n and counts down from n to 1.
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

    if (sscanf(buf, "%d", &n) != 1 || n <= 0)
        return 1;

    int i = n;
    while (i > 0) {
        printf("%d\n", i);
        i--;
    }

    return 0;
}
