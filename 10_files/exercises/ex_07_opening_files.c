/*
 * Exercise 07 — Opening Files
 *
 * Attempt to open a file called "test.txt" for reading.
 * Check if fopen() returns NULL. If so, print an error
 * with perror() and exit with EXIT_FAILURE.
 *
 * If the file opens successfully, close it and return EXIT_SUCCESS.
 *
 * Expected behaviour:
 *   Since "test.txt" does NOT exist, the program should print an
 *   error message via perror() and exit with code 1.
 *
 * Hints:
 *   - FILE *fp = fopen("test.txt", "r");
 *   - if (fp == NULL) { perror("fopen test.txt"); return EXIT_FAILURE; }
 *   - if it's not NULL, fclose(fp) and then return EXIT_SUCCESS
 *   - #include <stdio.h>, <stdlib.h>
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* Your code here — the boilerplate below keeps the stub compilable */

    return EXIT_SUCCESS;
}
