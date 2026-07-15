/*
 * Exercise 07 — Challenge: Grade Statistics
 *
 * Read 5 grades from the user, then print min, max, and average.
 *
 * Expected interaction:
 *   Enter grade 1: 85
 *   Enter grade 2: 92
 *   Enter grade 3: 78
 *   Enter grade 4: 95
 *   Enter grade 5: 88
 *   Min: 78
 *   Max: 95
 *   Average: 87.60
 *
 * Hints:
 *   - int grades[5]; and loop to read each with fgets + strtol
 *   - Find min: for loop checking grades[i] < min
 *   - Find max: for loop checking grades[i] > max
 *   - Average: sum / 5.0 (use double for the result)
 *   - #include <errno.h>, <limits.h>, <string.h>
 */
