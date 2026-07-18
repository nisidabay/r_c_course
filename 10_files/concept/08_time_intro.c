/*
 * 08_time_intro.c — time.h: working with dates and time
 * Group 10 — Files
 *
 * <time.h> provides functions for getting the current time, formatting
 * it, measuring intervals, and converting between time representations.
 *
 * Key types:
 *   time_t     — arithmetic type for calendar time (usually seconds since epoch)
 *   struct tm  — broken-down time (year, month, day, hour, min, sec)
 *
 * Key functions:
 *   time(NULL)       — get current time as time_t
 *   difftime(t1,t2)  — difference in seconds between two time_t values
 *   localtime(&t)    — convert time_t to struct tm (local timezone)
 *   gmtime(&t)       — convert time_t to struct tm (UTC)
 *   strftime(buf,n,fmt,&tm) — format struct tm as a string (like printf for dates)
 *   mktime(&tm)      — convert struct tm back to time_t
 *   clock_gettime()  — high-resolution timer (POSIX, not ISO C)
 */

/* clock_gettime is POSIX, not ISO C alone — must be before any #include */
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    printf("=== time.h — Working with Time ===\n\n");

    /* ---- Current time ---- */
    time_t now = time(NULL);
    printf("1) Current time (time_t): %ld\n", (long)now);
    printf("   That's %ld seconds since 1970-01-01 UTC.\n\n", (long)now);

    /* ---- Formatted date/time ---- */
    struct tm *local = localtime(&now);
    if (local == NULL) {
        fprintf(stderr, "localtime failed\n");
        return EXIT_FAILURE;
    }

    char date_str[64];
    strftime(date_str, sizeof date_str, "%Y-%m-%d %H:%M:%S", local);
    printf("2) Local date/time: %s\n\n", date_str);

    /* ---- Format variations ---- */
    printf("3) Format variations:\n");

    char buf[128];
    strftime(buf, sizeof buf, "%A, %B %d, %Y", local);
    printf("   %s\n", buf);

    strftime(buf, sizeof buf, "%I:%M:%S %p", local);
    printf("   %s\n", buf);

    strftime(buf, sizeof buf, "%Y-%m-%d", local);
    printf("   %s\n\n", buf);

    /* ---- Timing: measure how long something takes ---- */
    printf("4) Measuring elapsed time (busy-wait):\n");

    time_t start = time(NULL);
    volatile double x = 0.0;          /* volatile prevents optimisation */
    for (long i = 0; i < 50000000; i++)
        x += 0.000001;
    time_t end = time(NULL);
    (void)x;                           /* suppress unused warning */

    double elapsed = difftime(end, start);
    printf("   50 million iterations took %.0f second(s)\n\n", elapsed);

    /* ---- High-resolution timing with clock_gettime ---- */
    /* clock_gettime is POSIX, not ISO C, but available on every modern
     * Unix-like system.  We use it here because time() only has 1-second
     * resolution. */
    printf("5) High-resolution timing:\n");

    struct timespec ts_start, ts_end;
    clock_gettime(CLOCK_MONOTONIC, &ts_start);

    x = 0.0;
    for (long i = 0; i < 50000000; i++)
        x += 0.000001;

    clock_gettime(CLOCK_MONOTONIC, &ts_end);
    (void)x;

    double elapsed_ns = (ts_end.tv_sec - ts_start.tv_sec) * 1.0e9
                      + (ts_end.tv_nsec - ts_start.tv_nsec);
    printf("   50 million iterations took %.0f ns (%.3f s)\n",
           elapsed_ns, elapsed_ns / 1.0e9);

    return EXIT_SUCCESS;
}

// Thinking in C:
// time_t is opaque — don't assume it's an integer or that it's
// seconds.  Always use difftime() for subtraction.
//
// struct tm fields:
//   tm_year  — years since 1900 (add 1900!)
//   tm_mon   — month 0-11 (January = 0!)
//   tm_mday  — day of month 1-31
//   tm_hour  — 0-23
//   tm_min   — 0-59
//   tm_sec   — 0-60 (leap seconds allowed)
//   tm_wday  — day of week 0-6 (Sunday = 0)
//   tm_yday  — day of year 0-365
//   tm_isdst — daylight saving time flag
//
// strftime uses the same %-codes as the date command.  See
// 'man strftime' for the full list.
//
// For sub-second timing, time() is useless — use clock_gettime()
// with CLOCK_MONOTONIC (not affected by system clock adjustments).
