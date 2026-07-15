/*
 * Exercise 02 — exec Variants
 *
 * Use execlp to run "echo" with command-line arguments.
 *
 * Expected output:
 *   Hello from exec!
 *
 * Hints:
 *   - execlp("echo", "echo", "Hello", "from", "exec!", NULL);
 *   - If exec succeeds, this program is replaced — the printf after it never runs
 *   - If exec fails, perror and _exit
 *   - #include <unistd.h>, <stdio.h>, <stdlib.h>
 */
