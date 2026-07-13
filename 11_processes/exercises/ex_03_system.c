/*
 * Exercise 03 — system() safety analysis
 * Concept reference: 03_system.c
 *
 * Task: For each of the commands below, decide whether it is SAFE to call
 *       with system() or whether it MUST use fork+exec instead.
 *
 *   system() is safe when:
 *     - The command string is a compile-time constant (hard-coded literal).
 *     - You trust the command and its arguments completely.
 *
 *   system() is UNSAFE when:
 *     - The command or its arguments contain user-controlled / variable input.
 *       (e.g., a filename typed by the user, an environment variable value)
 *       because shell metacharacters in the input can inject arbitrary commands.
 *
 * What to do:
 *   1. Read each of the three commented commands below.
 *   2. For each, decide: system() or fork+exec?
 *   3. Replace the comment with the correct implementation.
 *
 * Calls you may use:
 *   - system()   (taught in 03_system.c)
 *   - fork(), execvp(), waitpid()   (taught in 01-02)
 *   - perror()
 *
 * Required includes (already present):
 *   #include <stdio.h>      for system() declaration, perror()
 *   #include <stdlib.h>     for system() return value, EXIT_*
 *   #include <unistd.h>     for fork(), exec family
 *   #include <sys/wait.h>   for waitpid()
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    /*
     * TASK A: Run "ls -la /home"
     *   String is a compile-time constant.
     *   Is system() safe here? (YES / NO)
     *   If YES, write: system("ls -la /home");
     *   If NO,  write fork+exec code.
     */

    /* TODO: implement command A here */


    /*
     * TASK B: Run "cat" on a file whose name comes from $HOME environment variable
     *   e.g. system("ls -la $HOME")
     *   $HOME is an environment variable containing a user-chosen path.
     *   Could $HOME contain shell metacharacters?
     *   Is system() safe here? (YES / NO)
     *   If YES, write: system("ls -la $HOME");
     *   If NO,  write fork+exec code (getenv() first, then execvp).
     */

    /* TODO: implement command B here */


    /*
     * TASK C: Run "date" with no arguments.
     *   String is a compile-time constant.
     *   Is system() safe here? (YES / NO)
     *   If YES, write: system("date");
     *   If NO,  write fork+exec code.
     */

    /* TODO: implement command C here */


    return EXIT_SUCCESS;
}
