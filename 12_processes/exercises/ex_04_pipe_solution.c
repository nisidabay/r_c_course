/*
 * Exercise 04 — Pipe: connecting two programs — SOLUTION
 * Concept reference: 04_pipe.c
 *
 * Implements: echo "hello" | tr 'a-z' 'A-Z'
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];

    if (pipe(fd) < 0) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    /* Fork first child — echo writer */
    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid1 == 0) {
        /* Child 1: write to pipe, then exec echo */
        close(fd[0]);                     /* close unused read end */
        if (dup2(fd[1], STDOUT_FILENO) < 0) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);                     /* original fd no longer needed */
        execlp("echo", "echo", "hello", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    /* Fork second child — tr reader */
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid2 == 0) {
        /* Child 2: read from pipe, then exec tr */
        close(fd[1]);                     /* close unused write end */
        if (dup2(fd[0], STDIN_FILENO) < 0) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);                     /* original fd no longer needed */
        execlp("tr", "tr", "a-z", "A-Z", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    /* Parent: close both ends, wait for both children */
    close(fd[0]);
    close(fd[1]);

    int status;
    if (waitpid(pid1, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }
    if (waitpid(pid2, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
