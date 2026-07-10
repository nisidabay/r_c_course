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
 * Safe C Standard: use fgets + sscanf (do NOT use scanf).
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

        if (num /*@*/ 0) {
            /*@*/;               /* exit the loop */
        }

        if (num /*@*/ 0) {
            /*@*/;               /* skip negative numbers */
        }

        sum /*@*/ num;
    }

    printf("Sum of positives = %d\n", sum);

    return 0;
}
