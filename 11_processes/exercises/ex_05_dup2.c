/*
 * Exercise 05 — dup2: redirecting stdout to a file
 * Concept reference: 05_dup2.c
 *
 * Task: Write a program that runs "ls -la" and redirects its output
 *       to a file named "listing.txt" in the current directory.
 *
 * Steps:
 *   1. Fork a child process.
 *   2. In the child:
 *      a. Open (or create) "listing.txt" for writing with open().
 *         Use flags: O_WRONLY | O_CREAT | O_TRUNC, mode 0644.
 *      b. dup2 the file's fd to STDOUT_FILENO.
 *      c. Close the original file fd.
 *      d. execlp("ls", "ls", "-la", NULL).
 *   3. In the parent, wait for the child.
 *
 * Required calls:
 *   - open()     (taught in 05_dup2.c)
 *   - dup2()     (taught in 05_dup2.c)
 *   - close()    (taught in 04-05)
 *   - fork()     (taught in 01_fork_exec.c)
 *   - execlp()   (taught in 01-02)
 *   - waitpid()  (taught in 01_fork_exec.c)
 *   - perror()
 *
 * Required includes:
 *   #include <unistd.h>      for fork, dup2, close, execlp
 *   #include <sys/wait.h>    for waitpid
 *   #include <sys/stat.h>    for S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH (mode macros)
 *   #include <fcntl.h>       for open, O_WRONLY, O_CREAT, O_TRUNC
 *   #include <stdio.h>       for perror
 *   #include <stdlib.h>      for EXIT_SUCCESS, EXIT_FAILURE
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* ---------- CHILD: redirect stdout to listing.txt ---------- */
        /* TODO:
         * 1. int fd = open("listing.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
         * 2. if (fd < 0) { perror("open"); return EXIT_FAILURE; }
         * 3. dup2(fd, STDOUT_FILENO);
         * 4. close(fd);
         * 5. execlp("ls", "ls", "-la", NULL);
         * 6. if execlp fails, perror and exit
         */

        /* Stub: placeholder so this compiles */
        fprintf(stderr, "Exercise stub — implement dup2 redirection\n");
        return EXIT_FAILURE;
    }

    /* Parent: wait for child */
    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
