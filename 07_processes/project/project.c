/* runit — run a command with timeout and signal handling */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

static volatile sig_atomic_t timed_out = 0;

static void handle_alarm(int sig) {
    (void)sig;
    timed_out = 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <command> [args...]\n", argv[0]);
        fprintf(stderr, "  env TIMEOUT=<seconds> sets a timeout (default: none)\n");
        return EXIT_FAILURE;
    }

    const char *timeout_str = getenv("TIMEOUT");
    int timeout = 0;
    if (timeout_str != NULL) {
        timeout = atoi(timeout_str);
        if (timeout <= 0) {
            fprintf(stderr, "error: TIMEOUT must be a positive integer\n");
            return EXIT_FAILURE;
        }
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        execvp(argv[1], argv + 1);
        perror("execvp");
        _exit(127);
    }

    if (timeout > 0) {
        struct sigaction sa;
        sa.sa_handler = handle_alarm;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGALRM, &sa, NULL);
        alarm(timeout);
    }

    int status;
    waitpid(pid, &status, 0);

    if (timed_out) {
        fprintf(stderr, "error: command timed out after %d seconds\n", timeout);
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return EXIT_FAILURE;
}
