/*
 * Exercise 09 — Signal: graceful timeout
 *
 * Write a program that sets a 5-second alarm using signal(SIGALRM, ...)
 * and then enters an infinite loop.  When the alarm fires, the program
 * should print "Time's up!" and exit gracefully.
 *
 * Hints:
 *   - alarm(5) sends SIGALRM after 5 seconds
 *   - signal(SIGALRM, handler) to catch it
 *   - In the handler, call _exit(0) for a clean exit
 *   - Or set a volatile sig_atomic_t flag and check it in the loop
 *
 * Expected output:
 *   Waiting for alarm...
 *   (5 second pause)
 *   Time's up!
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
