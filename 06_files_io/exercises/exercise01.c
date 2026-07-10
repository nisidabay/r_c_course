/*
 * Exercise 01: Read a file line by line and count lines
 *
 * Modify this example so that the program:
 *   1. Checks if fopen() returned NULL and prints an error
 *   2. Closes the file with fclose() before returning
 *
 * Hint: add perror/fclose calls where indicated.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "example.txt";
    FILE *fp = fopen(filename, "r");

    /* ---- ADD OPEN CHECK HERE ---- */
    /* if (!fp) { perror("fopen"); return EXIT_FAILURE; } */

    char buf[256];
    size_t line_count = 0;

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        line_count++;
    }

    printf("File '%s' has %zu lines.\n", filename, line_count);

    /* ---- ADD FCLOSE HERE ---- */
    /* fclose(fp); */

    return EXIT_SUCCESS;
}
