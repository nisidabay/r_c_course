/*
 * 03_system.c — How do I "just run a command" without fork+exec?
 *
 * Bash:  ls -la
 *   C:  system("ls -la")
 *
 * system() is the quick way: it calls fork+exec+waitpid for you and
 * returns the command's exit status.  BUT it has two big limitations:
 *   1. It invokes a shell (/bin/sh) behind the scenes — dangerous if
 *      the command string contains user input (shell injection).
 *   2. You can't control stdin/stdout/stderr before the command runs.
 *
 * Use system() for simple, hard-coded commands.  Use fork+exec (concept
 * 01) when you need control or the command involves user input.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    puts("=== system() — the quick way to run a command ===\n");

    /* ---- Simple hard-coded command ---- */
    puts("Running: system(\"ls -la /tmp\")\n");

    int ret = system("ls -la /tmp");

    if (ret == -1) {
        perror("system");
        return EXIT_FAILURE;
    }
    printf("\nCommand exited with status: %d\n\n", ret);

    /* ---- What happens on failure ---- */
    puts("Running: system(\"nonexistent_command_xyz\")\n");

    ret = system("nonexistent_command_xyz");
    if (ret == -1) {
        perror("system");
        return EXIT_FAILURE;
    }
    printf("Exit status: %d  (non-zero = command not found or failed)\n",
           ret);

    /* ---- When NOT to use system() ---- */
    puts("\n--- DANGER: never use system() with user input ---");
    puts("If a user types \"; rm -rf /\" as a filename, system()");
    puts("passes it to /bin/sh which interprets the semicolon.");
    puts("Always use fork+exec when the command contains user data.\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// system() is the sledgehammer.  It works, it's simple, but it invokes
// a full shell behind the scenes.  fork+exec is the scalpel — direct,
// safe, and gives you full control.  Use system() for throwaway scripts
// and hard-coded commands.  Use fork+exec for real programs.

/*
 * Disadvantage: system() vs fork+exec
 * system() is a higher-level wrapper that:
 *   - Spawns /bin/sh -c "command"
 *   - Waits for the command to finish
 *   - Returns the exit status
 * The shell interprets the string — if it contains user input,
 * shell metacharacters (;, |, &, $) become injection vectors.
 *
 * fork+exec:
 *   - No shell involved
 *   - The child's program is an exact argument list
 *   - You control stdin/stdout/stderr (pipe, dup2)
 *   - User input is never interpreted as shell syntax
 *
 * 🚫 NEVER pass user input directly to system().  Use fork+exec instead.
 */
