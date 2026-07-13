/*
 * Exercise 04 — Pipe: connecting two programs
 * Concept reference: 04_pipe.c
 *
 * Task: Implement the shell pipeline:
 *        echo "hello" | tr 'a-z' 'A-Z'
 *
 *   You will need:
 *     1. Create a pipe with pipe(fd).
 *     2. Fork the first child (echo writer).
 *     3. Fork the second child (tr reader).
 *     4. In child 1: dup2(write_end, STDOUT_FILENO), close(read_end),
 *        then execlp("echo", "echo", "hello", NULL).
 *     5. In child 2: dup2(read_end, STDIN_FILENO), close(write_end),
 *        then execlp("tr", "tr", "a-z", "A-Z", NULL).
 *     6. In parent: close BOTH ends of the pipe, wait for both children.
 *
 * Required calls:
 *   - pipe()     (taught in 04_pipe.c)
 *   - fork()     (taught in 01_fork_exec.c)
 *   - dup2()     (taught in 04_pipe.c — also covered in 05_dup2.c)
 *   - close()    (taught in 04_pipe.c)
 *   - execlp()   (taught in 01-02)
 *   - waitpid()  (taught in 01_fork_exec.c)
 *   - perror()
 *
 * Hints:
 *   - pipe() creates two file descriptors: fd[0] for reading, fd[1] for writing.
 *   - STDOUT_FILENO and STDIN_FILENO are defined in <unistd.h>.
 *   - After dup2, close the original pipe fd to prevent resource leaks.
 *   - The parent must close BOTH ends before waiting, otherwise
 *     the reading child may block waiting for more input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];

    /* TODO: create pipe */
    // if (pipe(fd) < 0) { perror("pipe"); return EXIT_FAILURE; }

    /* TODO: fork first child (echo writer) */
    // if (pid1 < 0) { perror("fork"); return EXIT_FAILURE; }

    /* TODO: fork second child (tr reader) */

    /* TODO: in first child, dup2 write end to STDOUT_FILENO, close read end, exec echo */

    /* TODO: in second child, dup2 read end to STDIN_FILENO, close write end, exec tr */

    /* TODO: in parent, close both ends of pipe, wait for both children */

    /* Stub: placeholder so this compiles */
    fprintf(stderr, "Exercise stub — replace with pipe-based implementation\n");
    return EXIT_FAILURE;
}
