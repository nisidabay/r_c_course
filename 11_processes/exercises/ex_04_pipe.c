/*
 * Exercise 04 — Pipe (echo | tr)
 *
 * Create a pipe between a parent and child. Parent writes to pipe,
 * child reads from pipe and transforms the text.
 *
 * Expected output:
 *   Original: hello world
 *   Transformed: HELLO WORLD
 *
 * Hints:
 *   - int pipefd[2]; pipe(pipefd);
 *   - fork(); child reads from pipefd[0], parent writes to pipefd[1]
 *   - Close unused ends in each process
 *   - Child: read(pipefd[0], buf, sizeof(buf)); then toupper each char
 *   - #include <unistd.h>, <sys/wait.h>, <ctype.h>, <stdio.h>, <stdlib.h>
 */
