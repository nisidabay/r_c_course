/*
 * Exercise 05 — dup2: redirecting stdout to a file — SOLUTION
 * Concept reference: 05_dup2.c
 *
 * Runs "ls -la" with stdout redirected to listing.txt.
 * Uses fopen + fileno (same pattern as concept 05), NOT open().
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* Child: open file, dup2, exec ls */
        FILE *fp = fopen("listing.txt", "w");
        if (!fp) {
            perror("fopen listing.txt");
            exit(EXIT_FAILURE);
        }

        int fd = fileno(fp);
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        fclose(fp);

        execlp("ls", "ls", "-la", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    puts("[OK] ls output redirected to listing.txt");
    return EXIT_SUCCESS;
}
