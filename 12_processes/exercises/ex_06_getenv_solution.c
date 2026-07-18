/*
 * Exercise 06 — getenv: reading environment variables — SOLUTION
 * Concept reference: 06_getenv.c
 *
 * Reads $EDITOR and $HOME and prints them.
 * Does NOT launch the editor — this exercise is about READING variables.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    const char *editor = getenv("EDITOR");
    const char *home   = getenv("HOME");

    if (editor) {
        printf("EDITOR = %s\n", editor);
    } else {
        puts("EDITOR not set");
    }

    if (home) {
        printf("HOME = %s\n", home);

        /* Build a path using $HOME */
        char path[512];
        int n = snprintf(path, sizeof path, "%s/.config/notes", home);
        if (n < 0 || (size_t)n >= sizeof path) {
            fprintf(stderr, "Path too long\n");
            return EXIT_FAILURE;
        }
        printf("Notes directory: %s\n", path);
    } else {
        puts("HOME not set");
    }

    return EXIT_SUCCESS;
}
