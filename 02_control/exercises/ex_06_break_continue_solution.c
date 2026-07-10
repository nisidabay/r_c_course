/*
 * Solution 06: Break and Continue
 *
 * Reads integers until 0, sums only the positive ones.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int num;
    int sum = 0;

    printf("Enter integers (0 to stop):\n");

    while (1) {
        if (fgets(buf, BUFSZ, stdin) == NULL)
            break;

        if (sscanf(buf, "%d", &num) != 1)
            continue;

        if (num == 0) {
            break;               /* exit the loop */
        }

        if (num < 0) {
            continue;            /* skip negative numbers */
        }

        sum += num;
    }

    printf("Sum of positives = %d\n", sum);

    return 0;
}
