/*
 * Exercise 03 — system() safety analysis — SOLUTION
 * Concept reference: 03_system.c
 *
 * Demonstrates when system() is safe vs when fork+exec is required.
 * SAFE commands: hard-coded compile-time constant strings.
 * UNSAFE commands: anything involving user input or shell metacharacters.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    /*
     * TASK A: "date"
     *   SAFE — hard-coded compile-time constant string, no user input.
     */
    int ret = system("date");
    if (ret == -1) {
        perror("system");
        return EXIT_FAILURE;
    }

    /*
     * TASK B: user-provided filename
     *   UNSAFE with system() — user could type "; rm -rf /"
     *   Use fork+exec with execlp for safety.
     */
    const char *user_file = "/etc/hostname";

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        execlp("cat", "cat", user_file, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);

    /*
     * TASK C: "echo Done"
     *   SAFE — hard-coded, no user control.
     */
    system("echo Done");

    puts("\nDANGER: system() invokes /bin/sh.  If the string contains");
    puts("user input, shell metacharacters (;, |, &, $) become");
    puts("injection vectors.  Prefer fork+exec when user data is involved.");

    return EXIT_SUCCESS;
}
