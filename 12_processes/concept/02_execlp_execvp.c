#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Question: When do I use execlp vs execvp?
 *
 * Bash:   ls -la
 * C:      execlp("ls", "ls", "-la", NULL)
 *
 * The shell splits the string for you. In C you separate the program
 * from its arguments. The second argument is argv[0] (what the new
 * program thinks its name is). 99% of the time it matches the program.
 */

/* ── Example 1: execlp — args known at compile time ────────────── */
static void demo_execlp(void)
{
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }

    if (pid == 0) {
        execlp("ls", "ls", "-la", NULL);   /* "p" = PATH search */
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) { perror("waitpid"); exit(EXIT_FAILURE); }
    printf("└─ execlp done (status %d)\n\n", WEXITSTATUS(status));
}

/* ── Example 2: execvp — args built at runtime ────────────────── */
static void demo_execvp(void)
{
    char *argv[] = {"echo", "built", "at", "runtime", NULL};
    /*              ^prog    ^argv[1..n]               ^sentinel */

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }

    if (pid == 0) {
        execvp("echo", argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) { perror("waitpid"); exit(EXIT_FAILURE); }
    printf("└─ execvp done (status %d)\n\n", WEXITSTATUS(status));
}

/* ── Example 3: program not found on PATH ─────────────────────── */
static void demo_not_found(void)
{
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); exit(EXIT_FAILURE); }

    if (pid == 0) {
        execlp("doesnotexist", "doesnotexist", NULL);
        perror("execlp — not found as expected");
        exit(EXIT_FAILURE);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) { perror("waitpid"); exit(EXIT_FAILURE); }
    printf("└─ child exited with status %d\n\n", WEXITSTATUS(status));
}

int main(void)
{
    demo_execlp();
    demo_execvp();
    demo_not_found();
    return EXIT_SUCCESS;
}

/*
 * ── Thinking in C ────────────────────────────────────────────────
 *
 * exec() replaces the running process — it does NOT create one.
 * That's why we always pair it with fork() first.
 *
 * The "p" variants search PATH like your shell does. You write "ls",
 * not "/usr/bin/ls".  There are six exec variants but you only need two:
 *
 *   execlp("prog", "prog", arg1, ..., NULL)   — fixed args at compile time
 *   execvp("prog", argv)                      — dynamic args at runtime
 *
 * The other four (execl, execle, execv, execve, execvpe) either skip
 * PATH search or pass a custom environment. You don't need them yet.
 * ─────────────────────────────────────────────────────────────────
 */
