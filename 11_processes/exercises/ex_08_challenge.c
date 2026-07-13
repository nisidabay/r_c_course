/*
 * Exercise 08 — Challenge: combine 3+ concepts
 * Concepts referenced: 01_fork_exec.c, 06_getenv.c, 08_getopt_mkdir.c
 *
 * Task: Write a program that:
 *   1. Reads the $EDITOR environment variable (concept 06).
 *   2. Creates the directory ~/.config/notes/ using mkdir (concept 08).
 *      Use the mkdir() syscall with mode 0755.
 *      mkdir() returns 0 on success, -1 on error. If the error is EEXIST
 *      (directory already exists), that's okay — continue. Otherwise fail.
 *   3. Forks and execs the editor (concept 01).
 *      Pass the full path ~/.config/notes/ as an argument to the editor.
 *   4. Waits for the child to finish (concept 01).
 *
 * Required calls:
 *   - getenv()     (taught in 06_getenv.c)
 *   - mkdir()      (taught in 08_getopt_mkdir.c)
 *   - fork()       (taught in 01_fork_exec.c)
 *   - execvp()     (taught in 02_execlp_execvp.c)
 *   - waitpid()    (taught in 01_fork_exec.c)
 *   - snprintf()   (standard C, for constructing the path)
 *   - perror()
 *
 * Required includes:
 *   #include <stdio.h>
 *   #include <stdlib.h>
 *   #include <string.h>
 *   #include <unistd.h>
 *   #include <sys/wait.h>
 *   #include <sys/stat.h>     for mkdir(), mode constants
 *   #include <errno.h>         for EEXIST
 *
 * Hints:
 *   - Use getenv("HOME") to get the home directory path.
 *   - Use snprintf() to construct "~/.config/notes" (actually:
 *     "%s/.config/notes", home_dir). Note: ~ is shell expansion;
 *     in C you must use the full path from getenv("HOME").
 *   - mkdir(path, 0755). Check errno == EEXIST for "already exists".
 *   - The editor argv should be:
 *       argv[0] = editor_name
 *       argv[1] = path_to_notes_dir
 *       argv[2] = NULL
 *
 * Compile with: gcc -std=c11 -Wall -Wextra -pedantic ex_08_challenge.c -o ex_08_challenge
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
    /* TODO: read $EDITOR, get $HOME, build path, mkdir, fork+exec editor */

    /* Stub: placeholder so this compiles */
    fprintf(stderr, "Exercise stub — implement challenge (getenv+mkdir+fork+exec)\n");
    return EXIT_FAILURE;
}
