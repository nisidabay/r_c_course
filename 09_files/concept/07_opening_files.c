/*
 * 07_opening_files.c — fopen NULL check + perror
 * Group 09 - Files
 *
 * The simplest possible safe file-open pattern: attempt to open,
 * check for NULL, print the error with perror, and exit cleanly
 * with EXIT_FAILURE.  This is the pattern you will use for every
 * file operation in C.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* Attempt to open a file that doesn't exist */
    FILE *fp = fopen("nonexistent.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    /* We never reach here — but in a real program: */
    fclose(fp);
    return EXIT_SUCCESS;
}

// Thinking in C:
// fopen returns NULL when the file can't be opened (doesn't exist,
// wrong permissions, path error).  perror(\"prefix\") prints
// "prefix: system error message" to stderr, using the errno value
// set by the failed call.  ALWAYS check fopen's return value before
// using the FILE pointer — accessing NULL is undefined behavior.
