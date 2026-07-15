/*
 * Exercise 05 — Simple Input
 *
 * Read the user's name and favorite number, then print a greeting.
 *
 * Expected interaction:
 *   Enter your name: Alice
 *   Enter your favorite number: 42
 *   Hello, Alice! Your favorite number is 42.
 *
 * Hints:
 *   - fgets(name, sizeof(name), stdin) to read a string
 *   - fgets(favorite_str, sizeof(favorite_str), stdin) to read the number as text
 *   - strcspn(name, "\n") to strip the trailing newline
 *   - strtol(favorite_str, &endptr, 10) to parse the number
 *   - Check errno == ERANGE and *endptr != '\0' for validation
 *   - #include <errno.h>, <limits.h>, <string.h>
 */
