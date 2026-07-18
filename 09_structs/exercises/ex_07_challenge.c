/*
 * Exercise 07 — Challenge: Student Database
 *
 * Read student records (name + grade) from the user, store them in
 * a dynamically allocated array of structs, and print the class average.
 *
 * Expected interaction:
 *   Enter student name (or '.' to stop): Alice
 *   Enter grade: 85.5
 *   Enter student name (or '.' to stop): Bob
 *   Enter grade: 92.0
 *   Enter student name (or '.' to stop): .
 *   Class average: 88.75
 *
 * Hints:
 *   - typedef struct { char name[32]; double grade; } Student;
 *   - Dynamic array of Students, growing with realloc
 *   - fgets for name, fgets + strtol/strtof for grade
 *   - Sum grades, divide by count for average
 *   - #include <errno.h>, <limits.h>, <string.h>, <stdlib.h>, <stdio.h>
 */
