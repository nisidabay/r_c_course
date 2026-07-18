/*
 * Exercise 08 — Time: Date formatter
 *
 * Write a program that:
 *   1. Gets the current time
 *   2. Prints it in these formats:
 *      - "2026-07-18" (ISO date)
 *      - "Saturday, July 18, 2026" (long date)
 *      - "14:30:00" (24-hour time)
 *   3. Asks the user for a year, month, and day, and prints what
 *      day of the week that date falls on.
 *
 * Expected output (example):
 *   Today: 2026-07-18
 *   Long:  Saturday, July 18, 2026
 *   Time:  14:30:00
 *
 *   Enter year:  2026
 *   Enter month: 12
 *   Enter day:   25
 *   That date is a Friday
 *
 * Hints:
 *   - struct tm tm = {0}; then set tm_year, tm_mon, tm_mday
 *   - tm_year = year - 1900, tm_mon = month - 1
 *   - mktime(&tm) normalises the struct AND fills in tm_wday
 *   - strftime with "%A" gives the weekday name
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
