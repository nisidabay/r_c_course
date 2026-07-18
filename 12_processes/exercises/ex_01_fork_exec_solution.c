/*
 * Exercise 01 — Fork+exec basics — SOLUTION
 * Concept reference: 01_fork_exec.c
 *
 * Launches /bin/uname -a via fork+exec+waitpid.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* Child: exec /bin/uname -a */
        execlp("/bin/uname", "uname", "-a", (char *)NULL);
        perror("execlp");
        return EXIT_FAILURE;
    }

    /* Parent: wait for child */
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
