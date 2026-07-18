/*
 * Exercise 08 — Challenge: combine 3+ concepts — SOLUTION
 * Concepts referenced: 01_fork_exec.c, 06_getenv.c, 08_getopt_mkdir.c
 *
 * Reads $EDITOR, creates ~/.config/notes/, and opens the editor there.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

int main(void)
{
    /* Read environment variables */
    char *editor = getenv("EDITOR");
    char *home   = getenv("HOME");

    if (editor == NULL) {
        fprintf(stderr, "EDITOR environment variable is not set\n");
        return EXIT_FAILURE;
    }
    if (home == NULL) {
        fprintf(stderr, "HOME environment variable is not set\n");
        return EXIT_FAILURE;
    }

    /* Build path: ~/.config/notes/ */
    char notes_path[1024];
    int len = snprintf(notes_path, sizeof(notes_path), "%s/.config/notes", home);
    if (len < 0 || (size_t)len >= sizeof(notes_path)) {
        fprintf(stderr, "Path too long\n");
        return EXIT_FAILURE;
    }

    /* Create the directory (ok if it already exists) */
    if (mkdir(notes_path, 0755) < 0) {
        if (errno != EEXIST) {
            perror("mkdir");
            return EXIT_FAILURE;
        }
    }

    /* Fork and exec the editor with the notes directory as argument */
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* Child: exec the editor */
        char *argv[] = { editor, notes_path, NULL };
        execvp(editor, argv);
        perror("execvp");
        return EXIT_FAILURE;
    }

    /* Parent: wait for editor to finish */
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
