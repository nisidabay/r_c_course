/*
 * Exercise 06 — Challenge: Age Calculator
 *
 * Read a birth year and current year, compute the person's approximate age
 * in years and months, then print both.
 *
 * Expected interaction:
 *   Enter your birth year: 1990
 *   Enter current year: 2026
 *   You are approximately 36 years old.
 *   That is about 432 months!
 *
 * Hints:
 *   - Two fgets + strtol calls (one for each year)
 *   - Validate ranges: birth year 1900-2100, current year 1900-2100
 *   - Validate current_year > birth_year (otherwise age would be negative)
 *   - age = current_year - birth_year
 *   - months = age * 12
 *   - #include <errno.h>, <limits.h>, <string.h>
 */
