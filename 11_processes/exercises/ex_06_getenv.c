/*
 * Exercise 06 — getenv: reading environment variables
 * Concept reference: 06_getenv.c
 *
 * Task: Write a program that reads the $EDITOR environment variable.
 *       If $EDITOR is set, launch that editor with execvp.
 *       If $EDITOR is NOT set, fall back to $HOME and print a message
 *       showing the user's home directory.
 *
 * Steps:
 *   1. Call getenv("EDITOR") to try to get the user's preferred editor.
 *   2. If $EDITOR is set (not NULL):
 *      a. Fork a child.
 *      b. In the child, execvp(editor, argv) where argv[0]=editor, argv[1]=NULL.
 *         Note: editor is a char* from getenv, so use execvp(editor, argv)
 *         where argv = { editor, NULL }.
 *      c. In the parent, wait for the child.
 *   3. If $EDITOR is NOT set:
 *      a. Call getenv("HOME").
 *      b. If $HOME is set, print "Home directory: %s\n".
 *      c. If $HOME is also unset, print an error message.
 *
 * Required calls:
 *   - getenv()   (taught in 06_getenv.c)
 *   - fork()     (taught in 01_fork_exec.c)
 *   - execvp()   (taught in 02_execlp_execvp.c)
 *   - waitpid()  (taught in 01_fork_exec.c)
 *   - perror()
 *   - printf()   (standard I/O)
 *
 * Hints:
 *   - getenv() returns NULL if the variable is not set.
 *   - execvp() expects argv[0] to be the program name.
 *   - Don't forget NULL-checks after getenv.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    /* TODO: read $EDITOR environment variable */
    // char *editor = getenv("EDITOR");

    /* TODO: if editor != NULL, fork and exec the editor */
    /* TODO: else, try reading $HOME and print it */

    /* Stub: placeholder so this compiles */
    fprintf(stderr, "Exercise stub — implement getenv logic\n");
    return EXIT_FAILURE;
}
