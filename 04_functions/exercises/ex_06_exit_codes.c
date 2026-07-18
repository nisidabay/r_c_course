/*
 * Exercise 06 — Exit Codes
 *
 * Use EXIT_SUCCESS for a valid input, EXIT_FAILURE for an invalid one.
 *
 * Expected output with input "hello":
 *   Invalid input.
 *   (program returns EXIT_FAILURE — check with echo $?)
 *
 * Hints:
 *   - fgets + truncation detection to read a name
 *   - Check if the name is "quit" → EXIT_SUCCESS
 *   - Otherwise → EXIT_FAILURE
 *   - #include <errno.h>, <limits.h>, <string.h>
 */
