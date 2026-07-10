/*
 * Solution 04: Logical Operators (&&, ||, !)
 *
 * Reads an integer and checks if it's in range [10, 50] inclusive.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int num;
    bool in_range;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &num) != 1)
        return 1;

    in_range = (num >= 10) && (num <= 50);

    if (in_range) {
        printf("In range\n");
    } else {
        printf("Out of range\n");
    }

    return 0;
}
