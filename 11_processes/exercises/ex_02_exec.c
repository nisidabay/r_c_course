/*
 * Exercise 02 — execlp vs execvp
 * Concept reference: 02_execlp_execvp.c
 *
 * Task: The code below uses execlp() with a hard-coded argument list.
 *       Convert it to use execvp() with an argv array instead.
 *
 * Required calls:
 *   - execvp()   (taught in 02_execlp_execvp.c)
 *   - fork()     (taught in 01_fork_exec.c)
 *   - waitpid()  (taught in 01_fork_exec.c)
 *   - perror()
 *
 * What the program should do:
 *   1. Fork a child process.
 *   2. In the child, use execvp() to run "ls" with arguments
 *      "-l", "-a", "/home" — passed via an argv array.
 *   3. If execvp fails, print an error and exit.
 *   4. In the parent, wait for the child.
 *
 * Hints:
 *   - #include <unistd.h> for exec family
 *   - argv must be NULL-terminated
 *   - argv[0] should be the program name ("ls")
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    /* Hard-coded execlp — convert this to execvp with argv[] */
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* ---------- STUDENT TASK ----------
         * Replace this execlp call with execvp() using an argv array.
         *
         * Current (hard-coded):
         *   execlp("ls", "ls", "-l", "-a", "/home", (char *)NULL);
         *
         * New: build char *argv[] = { "ls", "-l", "-a", "/home", NULL };
         *      then call execvp("ls", argv);
         */
        execlp("ls", "ls", "-l", "-a", "/home", (char *)NULL);
        perror("execlp");
        return EXIT_FAILURE;
    }

    /* Parent waits */
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
