/*
 * Exercise 07: Opening Files — SOLUTION
 *
 * Concept: fopen, NULL check, perror error reporting.
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Attempt to open a file that does not exist */
    FILE *fp = fopen("test.txt", "r");

    if (fp == NULL) {
        perror("fopen test.txt");
        return EXIT_FAILURE;
    }

    /* We never reach here since test.txt doesn't exist */
    fclose(fp);
    return EXIT_SUCCESS;
}
