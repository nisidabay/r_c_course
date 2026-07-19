/*
 * 04_pipe.c — How do I connect one program's output to another's input?
 *
 * Bash:  ls -la | wc -l
 *   C:  pipe(fds) + fork × 2 + exec × 2 + dup2
 *
 * pipe() creates two file descriptors: fds[0] (read end) and fds[1]
 * (write end).  Data written to fds[1] can be read from fds[0].
 *
 * The pattern:  fork TWO children — one writes to the pipe, the other
 * reads from it.  The parent closes both pipe ends and waits.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int fds[2];

    puts("=== pipe: connect programs like '|' in Bash ===\n");

    /* --- Create the pipe --- */
    if (pipe(fds) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    /*
     * Now we have:
     *   fds[0] = read end  (ls writes to this)
     *   fds[1] = write end (wc reads from this)
     *
     * Layout:  ls --[fds[1]]--> pipe -->[fds[0]]-- wc
     */

    /* --- Fork first child: ls (writes to pipe) --- */
    pid_t pid_ls = fork();

    if (pid_ls < 0) {
        perror("fork (ls)");
        return EXIT_FAILURE;
    }

    if (pid_ls == 0) {
        /* CHILD 1 (ls): write to pipe, don't read */
        close(fds[0]);               /* close unused read end */

        /* Redirect stdout to pipe's write end */
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);               /* dup2 copied it, close original */

        execlp("ls", "ls", "-la", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    /* --- Fork second child: wc (reads from pipe) --- */
    pid_t pid_wc = fork();

    if (pid_wc < 0) {
        perror("fork (wc)");
        close(fds[0]);
        close(fds[1]);
        waitpid(pid_ls, NULL, WNOHANG);  // don't block if ls already finished
        return EXIT_FAILURE;
    }

    if (pid_wc == 0) {
        /* CHILD 2 (wc): read from pipe, don't write */
        close(fds[1]);               /* close unused write end */

        /* Redirect stdin to pipe's read end */
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);               /* dup2 copied it, close original */

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    /* --- Parent: close both ends, wait for both children --- */
    close(fds[0]);
    close(fds[1]);

    waitpid(pid_ls, NULL, 0);
    waitpid(pid_wc, NULL, 0);

    puts("\nPipe complete.  ls | wc -l counted the lines above.\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// pipe() creates a byte stream between two processes.  One writes,
// the other reads.  Combined with fork+exec, this is the C equivalent
// of Bash's | operator.  The kernel buffers the data — no files, no
// temp storage, just in-memory flow between programs.

/*
 * 🚫 popen() — the higher-level pipe wrapper
 * popen("command", "r") runs a command and gives you a FILE* to read
 * its output.  It's simpler but:
 *   1. Only connects ONE direction (either read OR write)
 *   2. Invokes a shell (like system()), so user input is dangerous
 *   3. You can't control stderr or build complex pipelines
 *
 * Use pipe() when you need real control.  Use popen() only for
 * throwaway scripts where you read a command's output once.
 */
