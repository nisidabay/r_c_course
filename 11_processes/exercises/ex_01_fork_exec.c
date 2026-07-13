/*
 * Exercise 01 — Fork+exec basics
 * Concept reference: 01_fork_exec.c
 *
 * Task: Write a program that forks, executes /bin/uname -a in the child,
 *       and waits for the child to finish in the parent.
 *
 * Required calls (all taught in 01_fork_exec.c):
 *   - fork()
 *   - execlp() or execvp()
 *   - waitpid()
 *   - perror()
 *   - EXIT_SUCCESS / EXIT_FAILURE
 *
 * Hints:
 *   - #include <unistd.h>   for fork(), exec family
 *   - #include <sys/wait.h> for waitpid()
 *   - #include <stdlib.h>   for EXIT_SUCCESS, EXIT_FAILURE
 *   - #include <stdio.h>    for perror()
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
        /* ---------- CHILD: fill in the exec call ---------- */
        /* Replace the return with execlp("/bin/uname", "uname", "-a", NULL)
         *  or execvp(...) with an argv array.
         *  If execlp fails, call perror("execlp") and exit with EXIT_FAILURE.
         */

        // TODO: call execlp("/bin/uname", "uname", "-a", (char *)NULL);
        // TODO: handle failure with perror and EXIT_FAILURE

        /* Stub placeholder so this compiles */
        return EXIT_FAILURE;
    }

    /* ---------- PARENT: fill in the wait ---------- */
    /* Call waitpid(pid, &status, 0) to wait for the child.
     *  If waitpid fails, call perror("waitpid") and exit with EXIT_FAILURE.
     */

    // TODO: call waitpid(pid, &status, 0);
    // TODO: handle failure with perror and EXIT_FAILURE

    return EXIT_SUCCESS;
}
