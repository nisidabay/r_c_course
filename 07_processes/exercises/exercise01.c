/*
 * Exercise 01: Fork a child and print PIDs
 *
 * Modify this example so that the program:
 *   1. Uses waitpid() instead of wait(NULL) to wait for the child
 *   2. Checks if the child exited normally with WIFEXITED/WEXITSTATUS
 *
 * Hint: add a status variable and use waitpid() + macros.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* Child process */
        printf("Child:  PID = %d, Parent PID = %d\n",
               (int)getpid(), (int)getppid());
        _exit(0);
    }

    /* Parent process */
    printf("Parent: PID = %d, Child PID = %d\n",
           (int)getpid(), (int)pid);

    /* ---- REPLACE wait(NULL) WITH waitpid + status check ---- */
    wait(NULL);

    return EXIT_SUCCESS;
}
