/*
 * Solution 05: Comparisons (==, !=, <, >, <=, >=)
 *
 * Reads two integers and prints which is greater or if they're equal.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int a, b;

    printf("Enter two integers (space-separated): ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d %d", &a, &b) != 2)
        return 1;

    if (a > b) {
        printf("a is greater\n");
    } else if (a < b) {
        printf("b is greater\n");
    } else {
        printf("equal\n");
    }

    return 0;
}
