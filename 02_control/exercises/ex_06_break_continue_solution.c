/*
 * Solution 06: Break and Continue
 *
 * Reads integers until 0, sums only the positive ones.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 64

int main(void) {
    char buf[BUFSZ];
    int num;
    int sum = 0;

    printf("Enter integers (0 to stop):\n");

    while (1) {
        if (fgets(buf, BUFSZ, stdin) == NULL)
            break;

        buf[strcspn(buf, "\n")] = '\0';

        char *endptr;
        errno = 0;
        long val = strtol(buf, &endptr, 10);

        if (errno == ERANGE) {
            fprintf(stderr, "Number out of range\n");
            continue;
        }
        if (endptr == buf || *endptr != '\0') {
            fprintf(stderr, "Invalid input\n");
            continue;
        }
        if (val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Out of int range\n");
            continue;
        }
        num = (int)val;

        if (num == 0) {
            break;               /* exit the loop */
        }

        if (num < 0) {
            continue;            /* skip negative numbers */
        }

        sum += num;
    }

    printf("Sum of positives = %d\n", sum);

    return EXIT_SUCCESS;
}
