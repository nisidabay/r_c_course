/*
 * Exercise 08 — Validate Integer (is_valid_int)
 *
 * Implement the function is_valid_int() that validates a string as
 * a valid integer using strtol.  It should return 1 if the string
 * is a valid integer, and 0 otherwise.
 *
 *   int is_valid_int(const char *s, long *out);
 *
 * If s is NULL or empty → return 0
 * If strtol reports ERANGE → return 0
 * If there is trailing garbage → return 0
 * If out is not NULL → store the parsed value in *out
 * Otherwise → return 1
 *
 * Expected output with input "42":
 *   Valid: 42
 *
 * Expected output with input "abc":
 *   Invalid input
 *
 * Hints:
 *   - #include <errno.h>, <limits.h>, <string.h>
 *   - Set errno = 0 before calling strtol
 *   - Check endptr == s (no digits) and *endptr != '\0' (trailing garbage)
 *   - Check errno == ERANGE for overflow/underflow
 */
