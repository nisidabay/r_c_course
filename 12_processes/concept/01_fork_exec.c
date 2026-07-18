/* 01_fork_exec.c — How do I launch any program from C and wait for it to finish? */

/*
 * You already know how to run ls -la from Bash:
 *     $ ls -la
 *
 * In C you do the same thing: fork a child process, exec ls inside it,
 * and wait for the child to finish. Same idea, same three steps.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/*
 * Example 1 — Launch /bin/ls -la with the standard fork+exec+waitpid pattern.
 */
static void run_ls(void)
{
    printf("Launching: ls -la\n");
    fflush(stdout);                 /* flush before fork to avoid duped buffers */

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        /* CHILD — replace this process with ls */
        execlp("ls", "ls", "-la", NULL);
        /* Only reached if exec fails */
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    /* PARENT — wait for the child to finish */
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        printf("ls exited with status %d\n\n", WEXITSTATUS(status));
}

/*
 * Example 2 — Launch a program the user types in.
 * Demonstrates input handling and exec integration.
 */
static void run_user_program(void)
{
    char program[256];

    printf("Enter a program to launch (e.g. /bin/date): ");
    fflush(stdout);

    if (fgets(program, sizeof program, stdin) == NULL)
        return;

    size_t len = strlen(program);
    if (len > 0 && program[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;   /* input was truncated — drain residue */
    } else if (len > 0) {
        program[len - 1] = '\0';
    }
    if (program[0] == '\0')
        return;                      /* empty input — nothing to do */

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        execlp(program, program, NULL);
        perror(program);             /* prints "date: No such file or directory" */
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        printf("'%s' exited with status %d\n\n", program, WEXITSTATUS(status));
}

/*
 * Example 3 — Launch a program that doesn't exist.
 * Shows exec failing gracefully instead of crashing.
 */
static void run_nonexistent(void)
{
    printf("Trying to launch: this-program-does-not-exist\n");
    fflush(stdout);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        execlp("this-program-does-not-exist", "this-program-does-not-exist", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        printf("Child exited with status %d\n\n", WEXITSTATUS(status));
}

int main(void)
{
    printf("=== Example 1: ls -la ===\n");
    run_ls();

    printf("=== Example 2: user-chosen program (try: /bin/date) ===\n");
    run_user_program();

    printf("=== Example 3: nonexistent program ===\n");
    run_nonexistent();

    return EXIT_SUCCESS;
}

/*
 * ─── Thinking in C ──────────────────────────────────────────────────────
 *
 * fork+exec+waitpid is how Bash runs every single command you type.
 * Bash calls fork(), the child calls exec(), and the parent calls waitpid().
 * That's it. Three functions. Every shell, every build tool, every launcher.
 *
 * The mental model:
 *   fork()   — "make an identical copy of me"
 *   exec()   — "replace THIS copy with a different program"
 *   waitpid()— "don't move on until that other program finishes"
 *
 * Without waitpid, the child becomes a zombie — it exits but sticks around
 * in the process table until someone collects its status. Always wait.
 *
 * Without error checking, a bad program name silently does nothing.
 * Always check fork and exec. perror tells you exactly what went wrong.
 */
