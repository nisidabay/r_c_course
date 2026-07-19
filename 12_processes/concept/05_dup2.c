/*
 * 05_dup2.c — How do I redirect a program's stdout/stderr to a file?
 *
 * Bash:  ls -la > output.txt     (stdout → file)
 * Bash:  ls -la 2> error.txt     (stderr → file)
 * Bash:  sort < input.txt        (file → stdin)
 *
 * dup2(old_fd, new_fd) copies old_fd onto new_fd, closing new_fd first.
 * After dup2(fd, STDOUT_FILENO), writing to stdout goes to fd instead.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    puts("=== dup2: redirect stdout/stderr like '>' and '2>' in Bash ===\n");

    /* ---- Redirect: stdout → file (Bash equivalent: ls > out.txt) ---- */
    puts("1) Redirecting ls's output to /tmp/list.txt...\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* CHILD: open file, redirect stdout to it, then exec ls */
        FILE *fp = fopen("/tmp/list.txt", "w");
        if (!fp) {
            perror("fopen /tmp/list.txt");
            exit(EXIT_FAILURE);
        }

        /* Convert FILE* to fd, then dup2 onto stdout */
        int fd = fileno(fp);
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        fclose(fp);          /* dup2 copied it, close original */

        execlp("ls", "ls", "-la", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    waitpid(pid, NULL, 0);

    /* Verify: read the file back */
    FILE *fp = fopen("/tmp/list.txt", "r");
    if (!fp) {
        perror("fopen /tmp/list.txt (read)");
        return EXIT_FAILURE;
    }

    char line[256];
    printf("Contents of /tmp/list.txt (first 3 lines):\n");
    for (int i = 0; i < 3 && fgets(line, sizeof line, fp); i++) {
        line[strcspn(line, "\n")] = '\0';
        printf("  %s\n", line);
    }
    fclose(fp);

    /* ---- Redirect: stdin ← file (Bash equivalent: sort < input) ---- */
    puts("\n2) Redirecting stdin from /tmp/list.txt to head...\n");

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* CHILD: redirect stdin to read from the file */
        fp = fopen("/tmp/list.txt", "r");
        if (!fp) {
            perror("fopen /tmp/list.txt (stdin)");
            exit(EXIT_FAILURE);
        }

        int fd = fileno(fp);
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        fclose(fp);

        execlp("head", "head", "-3", NULL);
        perror("execlp head");
        exit(EXIT_FAILURE);
    }

    waitpid(pid, NULL, 0);

    puts("\n---");
    puts("stdout redirection: ls -la > /tmp/list.txt");
    puts("stdin  redirection: head -3 < /tmp/list.txt");
    puts("Both work without a shell — dup2 redirects the fd before exec.");

    return EXIT_SUCCESS;
}

// Thinking in C:
// dup2 is how shells implement > and <.  Before exec'ing a program,
// you open the file, then dup2 its fd onto STDOUT_FILENO (1) or
// STDIN_FILENO (0).  The launched program never knows its I/O was
// redirected.  This is the kernel's file descriptor table in action.

/*
 * 🚫 freopen() for redirection — why we use dup2 instead
 * freopen("file", "w", stdout) also redirects stdout, but it's a
 * stdio-level hack that messes with the FILE* internals.  dup2 is
 * the system-call level — it works with ANY fd, including pipes,
 * sockets, and file descriptors that aren't FILE* streams.
 */
