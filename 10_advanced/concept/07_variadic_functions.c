/*
 * File:  07_variadic_functions.c
 * Group: 10 — Paradigm Shift: Variadic Functions (Advanced)
 *
 * Concept: variadic functions — writing functions that accept a variable
 *          number of arguments via <stdarg.h>
 *
 * Shows:
 *   - va_list, va_start, va_arg, va_end
 *   - Variadic sum with explicit count
 *   - Variadic logger with format string + vsnprintf
 *   - va_copy for scanning argument lists multiple times
 *
 * Build:  gcc -std=c11 -Wall -Wextra -pedantic 07_variadic_functions.c -o 07_variadic_functions
 * Run:    ./07_variadic_functions
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* ---------- variadic sum with explicit count ---------- */

int sum(int count, ...) {
    va_list args;
    int total = 0;

    va_start(args, count);
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);

    return total;
}

/* ---------- variadic logger (vlog) with vsnprintf ---------- */

void vlog(const char *tag, const char *fmt, ...) {
    va_list args;
    char buf[256];

    va_start(args, fmt);
    vsnprintf(buf, sizeof buf, fmt, args);
    va_end(args);

    printf("[%s] %s\n", tag, buf);
}

/* ---------- average_positive: va_copy double-scan ---------- */

double average_positive(int count, ...) {
    va_list args, copy;
    int npos = 0;
    int total = 0;

    va_start(args, count);
    va_copy(copy, args);

    /* first scan: count positive values */
    for (int i = 0; i < count; i++) {
        if (va_arg(copy, int) > 0) {
            npos++;
        }
    }
    va_end(copy);

    if (npos == 0) {
        va_end(args);
        return 0.0;
    }

    /* second scan: sum positive values (using original args) */
    for (int i = 0; i < count; i++) {
        int val = va_arg(args, int);
        if (val > 0) {
            total += val;
        }
    }
    va_end(args);

    return (double)total / (double)npos;
}

int main(void) {
    /* ---------- demo 1: variadic sum ---------- */
    printf("1. sum(3, 10, 20, 30)  = %d\n", sum(3, 10, 20, 30));
    printf("   sum(5, 1, 2, 3, 4, 5) = %d\n", sum(5, 1, 2, 3, 4, 5));
    printf("   sum(0)                  = %d  (no args)\n", sum(0));

    /* ---------- demo 2: variadic logger ---------- */
    vlog("INFO", "Temperature: %d°C, Pressure: %d hPa", 22, 1013);
    vlog("WARN", "Sensor reading above threshold: %d", 42);
    vlog("DBUG", "Loop iteration %d / %d", 7, 10);

    /* ---------- demo 3: va_copy double-scan ---------- */
    double avg1 = average_positive(5, 10, -3, 7, 0, 12);
    printf("\n2. average_positive(5, 10, -3, 7, 0, 12) = %.2f  "
           "(3 positives: 10+7+12)\n", avg1);

    double avg2 = average_positive(3, -1, -2, -3);
    printf("   average_positive(3, -1, -2, -3)         = %.2f  "
           "(no positives)\n", avg2);

    double avg3 = average_positive(0);
    printf("   average_positive(0)                       = %.2f  "
           "(zero args)\n", avg3);

    return EXIT_SUCCESS;
}

/*
 * Thinking in C — Group 10
 *
 * Variadic functions trade compile-time type safety for call-site
 * flexibility.  The price: va_arg has no type-checking — if you request
 * an int when the caller passed a double, the result is undefined
 * behavior (silent corruption, not a compiler error).  This is why
 * printf needs format strings to tell it what types to expect.
 *
 * To wrap a variadic function (e.g. a custom logger around printf),
 * you need the "v" variants: vprintf, vfprintf, vsnprintf — these
 * accept a va_list instead of ... so you can forward the arguments.
 *
 * va_copy is required when you need to walk the same arguments more
 * than once.  You cannot simply re-use va_start — va_copy creates an
 * independent copy that can be scanned separately.  Both copies must
 * be cleaned up with va_end.
 *
 * When to use variadics vs arrays:
 *   - Variadic: convenient at call sites with a small, known list of
 *     arguments (printf-style).  No allocation overhead.
 *   - Array: type-safe, can be passed around, resized at runtime.
 *     Requires the caller to build the array explicitly.
 */
