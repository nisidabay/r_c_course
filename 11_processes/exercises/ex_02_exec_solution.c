/*
 * Exercise 02 — execlp vs execvp — SOLUTION
 * Concept reference: 02_execlp_execvp.c
 *
 * Runs "/bin/echo hello from execvp" using execvp() with an argv array.
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
        /* Build argv array and call execvp */
        char *argv[] = { "/bin/echo", "hello", "from", "execvp", NULL };
        execvp("/bin/echo", argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
