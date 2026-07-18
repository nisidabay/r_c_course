/*
 * Exercise 07 — Challenge: Dynamic List
 *
 * Read numbers from the user (one per line) until they enter 0.
 * Store them in a dynamically growing array, then print them all.
 *
 * Expected interaction:
 *   Enter number (0 to stop): 10
 *   Enter number (0 to stop): 20
 *   Enter number (0 to stop): 30
 *   Enter number (0 to stop): 0
 *   You entered: 10 20 30
 *
 * Hints:
 *   - Start with capacity = 4, malloc, count = 0
 *   - Loop: fgets + strtol, if val == 0 break
 *   - If count == capacity, double with realloc
 *   - Store each value: arr[count++] = val;
 *   - Print all, then free
 *   - #include <errno.h>, <limits.h>, <string.h>
 */
