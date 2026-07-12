/*
 * Exercise 06: Break and Continue
 *
 * Concept: break  — exits the loop immediately.
 *          continue — skips the rest of the current iteration.
 *
 * Fill in the blanks to complete a program that reads integers one at a time
 * until the user enters 0, then prints the sum of all positive numbers entered.
 * Negative numbers should be skipped (not added to the sum).
 *
 * Safe C Standard: use fgets + strtol (do NOT use scanf).
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

        if (num == 0) {  // FIX ME
            break;               /* exit the loop */  // FIX ME
        }

        if (num < 0) {  // FIX ME
            continue;               /* skip negative numbers */  // FIX ME
        }

        sum += num;  // FIX ME
    }

    printf("Sum of positives = %d\n", sum);

    return EXIT_SUCCESS;
}
