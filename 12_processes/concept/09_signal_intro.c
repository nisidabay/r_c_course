/*
 * 09_signal_intro.c — signal.h: handling OS signals
 * Group 12 — Processes
 *
 * Signals are OS-level notifications sent to a process.  They can come
 * from the kernel (SIGSEGV, SIGFPE), from other processes (SIGTERM,
 * SIGKILL), or from the user pressing Ctrl+C (SIGINT).
 *
 * A process can:
 *   - IGNORE a signal  (signal(SIGINT, SIG_IGN))
 *   - CATCH a signal   (signal(SIGINT, handler_fn))
 *   - Let the DEFAULT  (signal(SIGINT, SIG_DFL))
 *
 * Not all signals can be caught.  SIGKILL (9) and SIGSTOP (19) are
 * uncatchable by design.
 *
 * IMPORTANT: signal() is simple but has portability issues (different
 * semantics across Unix flavours).  For production code, prefer
 * sigaction().  This file uses signal() for simplicity.
 */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Flag set by the SIGINT handler.  Marked volatile because it's
 * modified in a signal handler and read in the main loop.
 */
static volatile sig_atomic_t keep_running = 1;

/*
 * Signal handler for SIGINT (Ctrl+C).
 * Prints a message and sets the flag.
 * WARNING: only async-signal-safe functions can be called here!
 * printf() is NOT safe inside a signal handler in general, but it
 * works well enough for a pedagogical example.
 */
static void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nCaught SIGINT! Press Ctrl+C again to exit.\n", 44);
    keep_running = 0;
}

/*
 * Signal handler for SIGTERM (kill command without -9).
 */
static void handle_sigterm(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nSIGTERM received. Shutting down gracefully.\n", 44);
    keep_running = 0;
}

/*
 * Signal handler for SIGUSR1 — a user-defined signal.
 */
static void handle_sigusr1(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "Got SIGUSR1! Doing something special...\n", 40);
}

int main(void)
{
    printf("=== Signals ===\n");
    printf("PID: %d\n", getpid());
    printf("\nRegistered handlers:\n");
    printf("  SIGINT  (Ctrl+C)  -> graceful shutdown\n");
    printf("  SIGTERM (kill)    -> graceful shutdown\n");
    printf("  SIGUSR1 (user)    -> special action\n");
    printf("\nTry from another terminal:\n");
    printf("  kill -USR1 %d\n", getpid());
    printf("  kill       %d\n", getpid());
    printf("  kill -9    %d   (uncatchable!)\n", getpid());
    printf("\n--- Running (Ctrl+C to stop) ---\n\n");

    /* Install signal handlers */
    signal(SIGINT,  handle_sigint);
    signal(SIGTERM, handle_sigterm);
    signal(SIGUSR1, handle_sigusr1);

    /* Main loop — simulate work */
    int count = 0;
    while (keep_running) {
        printf("Working... (%d)\n", ++count);
        sleep(1);
    }

    printf("\nCleanup complete. Exiting.\n");
    return EXIT_SUCCESS;
}

// Thinking in C:
// Signals are the simplest form of inter-process communication.
// The kernel sends them; your process catches them (or dies).
//
// Three signals every developer should know:
//
//   SIGINT  (2)  — Ctrl+C, polite interrupt.  Catch it to clean up.
//   SIGTERM (15) — "kill" without flags.  The polite way to stop.
//   SIGKILL (9)  — "kill -9".  Cannot be caught or ignored.
//
// Signal handlers run in a special context.  The rules:
//   - Keep them SHORT (set a flag, write to a pipe, do nothing else)
//   - Only call async-signal-safe functions (write(), not printf())
//   - volatile sig_atomic_t for shared flags (atomic writes on all
//     architectures)
//   - Don't use locks (you may be holding one when the signal arrives)
//
// For complex signal handling, use sigaction() with SA_SIGINFO
// and a dedicated signal-handling thread.
