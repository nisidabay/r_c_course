/*
 * Exercise 09 — Signal: graceful timeout — SOLUTION
 */

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static volatile sig_atomic_t alarm_fired = 0;

static void handle_alarm(int sig)
{
    (void)sig;
    alarm_fired = 1;
}

int main(void)
{
    signal(SIGALRM, handle_alarm);

    printf("Waiting for alarm...\n");
    fflush(stdout);

    alarm(5);   /* SIGALRM in 5 seconds */

    /* Busy-wait (in a real program you'd do actual work) */
    while (!alarm_fired)
        ;

    printf("Time's up!\n");
    return EXIT_SUCCESS;
}
