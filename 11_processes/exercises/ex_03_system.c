/*
 * Exercise 03 — system()
 *
 * Use system() to run a shell command — and understand why it's dangerous.
 *
 * Expected output:
 *   Running: ls -l
 *   [output of ls -l]
 *
 * Hints:
 *   - int ret = system("ls -l");
 *   - system() invokes /bin/sh -c "command"
 *   - It's vulnerable to shell injection — never use with user input
 *   - #include <stdlib.h>, <stdio.h>
 */
