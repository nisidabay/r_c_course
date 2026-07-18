/*
 * 11_errno_intro.c — errno: how C reports what went wrong
 * Group 04 — Functions
 *
 * errno is a global integer (thread-local in modern C) set by library
 * functions when they fail.  It's defined in <errno.h> and starts at
 * 0 at program startup.  Functions SET errno on error — they do NOT
 * clear it before succeeding.
 *
 * THE RULE:
 *   1. Set errno = 0 BEFORE calling a function that may set it.
 *   2. Check the function's return value FIRST (NULL from fopen, -1
 *      from strtol, etc.).
 *   3. Only THEN check errno, and ONLY when the return value indicates
 *      failure.
 *
 * Never check errno without first confirming the function failed.
 * A previous call may have left a stale errno value.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("=== errno — Error Reporting ===\n\n");

    /* ---- Example 1: strtol overflow ---- */
    printf("1) strtol overflow detection:\n");

    errno = 0;
    char *endptr;
    long val = strtol("999999999999999999999", &endptr, 10);

    if (errno == ERANGE) {
        printf("   Overflow detected: value too large for long\n");
    } else {
        printf("   Parsed: %ld\n", val);
    }

    /* ---- Example 2: fopen with a non-existent file ---- */
    printf("\n2) fopen failure:\n");
    errno = 0;
    FILE *fp = fopen("/nonexistent/file.txt", "r");

    if (fp == NULL) {
        /* perror prints the system error message for the current errno */
        perror("   fopen");
        printf("   errno value: %d  (see /usr/include/asm-generic/errno*.h)\n",
               errno);
    }

    /* ---- Example 3: strtol invalid input ---- */
    printf("\n3) strtol with non-numeric input:\n");
    const char *input = "hello";
    errno = 0;
    val = strtol(input, &endptr, 10);

    /* strtol sets errno ONLY on overflow.  Invalid input is detected
     * via endptr, NOT errno. */
    if (endptr == input) {
        printf("   No digits consumed — endptr == input\n");
        printf("   errno is still %d — strtol does NOT set errno for this\n",
               errno);
    }

    /* ---- Example 4: trying to open too many files ---- */
    printf("\n4) Running out of file descriptors:\n");
    errno = 0;
    FILE *many = fopen("/dev/null", "r");
    if (many)
        fclose(many);
    /* We can't easily trigger EMFILE in a short demo, but this shows
     * the pattern: check the return, then check errno. */
    printf("   (This demo doesn't exhaust FDs, but the pattern is the same.)\n");

    printf("\n--- perror is your friend ---\n");
    printf("perror(\"prefix\") prints \"prefix: <system error message>\"\n");
    printf("to stderr using the current value of errno.\n");
    printf("strerror(errno) returns the message string if you need it\n");
    printf("for snprintf or logging.\n");

    return EXIT_SUCCESS;
}

// Thinking in C:
// Every C developer memorises these errno values:
//   ERANGE   — result out of range (strtol, strtod)
//   EINVAL   — invalid argument
//   ENOENT   — file or directory not found
//   ENOMEM   — out of memory
//   EACCES   — permission denied
//
// Rules of thumb:
//   - Always set errno = 0 before the call
//   - Check the RETURN VALUE first, errno second
//   - Use perror() for quick stderr output
//   - Use strerror(errno) if you need the string in a buffer
//   - Never do:  if (some_func() == -1 && errno == EINVAL)
//     ... some_func may set errno on success too on some systems
