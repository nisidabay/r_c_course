/*
 * Exercise 09 — Print Wrapper (my_print)
 *
 * Implement a wrapper around printf that adds error checking and
 * NULL-pointer validation.
 *
 *   int my_print(int val, const char *delim);
 *
 * If delim is NULL → print "Error: NULL pointer provided for delimiter\n"
 *                      and return EXIT_FAILURE
 * If printf returns a negative value → call perror("printf") and
 *    return EXIT_FAILURE
 * Otherwise → return EXIT_SUCCESS
 *
 * Expected output calling my_print(42, "| ") twice:
 *   Value: 42| Value: 99
 *
 * Hints:
 *   - #include <stdio.h>, <stdlib.h>
 *   - printf returns the number of characters printed, or a negative value
 *   - Check delimiter == NULL before calling printf
 *   - Use perror() to report printf errors
 */
