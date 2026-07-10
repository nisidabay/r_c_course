/*
 * How do I handle signals?
 *
 * signal() installs a handler for a specific signal.
 * SIGINT (Ctrl+C) is caught and handled gracefully instead of
 * terminating the process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t caught_sigint = 0;

static void handle_sigint(int sig) {
    (void)sig;
    caught_sigint = 1;
}

int main(void) {
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }

    printf("Press Ctrl+C within 3 seconds...\n");
    sleep(3);

    if (caught_sigint) {
        printf("SIGINT was caught. Exiting gracefully.\n");
    } else {
        printf("No SIGINT received. Exiting normally.\n");
    }

    return EXIT_SUCCESS;
}


// 💡 Thinking in C:
// sigaction sets up a signal handler. Keep handlers simple — set a flag and return.
