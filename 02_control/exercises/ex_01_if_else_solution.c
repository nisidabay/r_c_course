/*
 * Solution 01: If / Else
 *
 * Reads an integer and prints "positive", "negative", or "zero".
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int num;

    printf("Enter an integer: ");
    if (fgets(buf, BUFSZ, stdin) == NULL)
        return 1;

    if (sscanf(buf, "%d", &num) != 1)
        return 1;

    if (num > 0) {
        printf("positive\n");
    } else if (num < 0) {
        printf("negative\n");
    } else {
        printf("zero\n");
    }

    return 0;
}
