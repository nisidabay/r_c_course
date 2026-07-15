/*
 * Exercise 06 — Challenge: CSV Reader
 *
 * Read a CSV file with student grades and compute each student's average.
 *
 * Expected input file (grades.csv):
 *   Alice,85,90,92
 *   Bob,78,83,80
 *   Carol,95,91,89
 *
 * Expected output:
 *   Alice: 89.00
 *   Bob: 80.33
 *   Carol: 91.67
 *
 * Hints:
 *   - Create the CSV file first with fprintf
 *   - Read line by line with fgets
 *   - Parse with strtok() to split by commas
 *   - Convert grades with strtol or strtof
 *   - Average = sum / count
 *   - #include <errno.h>, <limits.h>, <string.h>
 */
