/*
 * 06_getenv.c — How do I read environment variables like $EDITOR, $HOME?
 *
 * Bash:  echo $EDITOR
 * Bash:  echo $HOME
 * Bash:  EDITOR=nvim ./myprog
 *
 * getenv("NAME") returns the value of the environment variable NAME,
 * or NULL if it's not set.  Environment variables are the standard way
 * to configure programs without command-line arguments.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    puts("=== getenv: read environment variables ===\n");

    /* ---- Read common environment variables ---- */
    const char *editor = getenv("EDITOR");
    const char *home   = getenv("HOME");
    const char *shell  = getenv("SHELL");
    const char *path   = getenv("PATH");

    printf("EDITOR = %s\n", editor ? editor : "(not set)");
    printf("HOME   = %s\n", home   ? home   : "(not set)");
    printf("SHELL  = %s\n", shell  ? shell  : "(not set)");
    printf("PATH   = %s\n\n", path  ? path   : "(not set)");

    /* ---- Use getenv to run a program from the user's PATH ---- */
    if (!path) {
        fprintf(stderr, "PATH is not set — can't find programs\n");
        return EXIT_FAILURE;
    }

    const char *prog = getenv("TEST_PROG");
    if (!prog) {
        prog = "/bin/echo";   /* safe default, not affected by aliases */
    }

    fflush(stdout);  /* flush parent output before fork */

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* CHILD: run the program found via getenv */
        execlp(prog, prog, "Hello from getenv!", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    waitpid(pid, NULL, 0);

    /* ---- Build a path using $HOME ---- */
    puts("\n--- Building paths with $HOME ---");

    if (home) {
        char config_dir[512];
        int n = snprintf(config_dir, sizeof config_dir,
                        "%s/.config/myapp", home);
        if (n < 0 || (size_t)n >= sizeof config_dir) {
            fprintf(stderr, "Path too long\n");
            return EXIT_FAILURE;
        }
        printf("Config directory: %s\n", config_dir);
    }

    /* ---- Useful variables reference ---- */
    puts("\n--- Useful environment variables for real programs ---");
    puts("  USER      — your login name");
    puts("  HOME      — your home directory");
    puts("  EDITOR    — your preferred text editor");
    puts("  SHELL     — your login shell");
    puts("  PWD       — current working directory");
    puts("  PATH      — directories searched by execlp/execvp");
    puts("  LANG      — your locale/language setting");

    return EXIT_SUCCESS;
}

// Thinking in C:
// getenv() is the C equivalent of $VARIABLE in Bash.  Use it to
// read the user's preferences — which editor, where their home is,
// what language they speak.  Always check for NULL: not every
// variable is set on every system.

/*
 * 🚫 setenv() in this course — why we don't teach it yet
 * setenv("VAR", "value", 1) changes the environment of the CURRENT
 * process.  Child processes inherit it.  But parent processes (like
 * the shell you ran your program from) are NOT affected.  This
 * confuses beginners who expect setenv to work like "export VAR".
 * We teach getenv (read) in this group.  setenv is for later.
 */
