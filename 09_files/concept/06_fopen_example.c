/*
 * 06_fopen_example.c — fopen + fprintf + perror + fclose
 * Group 09 - Files
 *
 * Complete open-write-close cycle for file output.
 * fopen returns NULL on failure — always check it.
 * fprintf writes formatted output to a file stream.
 * fclose flushes and closes — always pair with fopen.
 * perror prints a human-readable error message on failure.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *filename = "user_id.txt";
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fprintf(fp, "account: %s - password: %s\n", "user123", "pass123");

    if (fclose(fp) == EOF) {
        perror("fclose");
        return EXIT_FAILURE;
    }

    printf("Successfully wrote to %s\n", filename);

    /* Clean up the test file */
    if (remove(filename) != 0) {
        perror("remove");
        return EXIT_FAILURE;
    }

    printf("Cleaned up: removed %s\n", filename);

    return EXIT_SUCCESS;
}

// Thinking in C:
// The file I/O cycle is always the same: fopen → check NULL →
// read/write → fclose.  Every fopen must have a matching fclose.
// Use fprintf for formatted output (like printf to a file) and
// perror to report why a system call failed.  remove() deletes
// the file when you're done.
