/*
 * Exercise 04 — strtok_r (Reentrant)
 *
 * Use the reentrant strtok_r to split a sentence into words.
 *
 * Expected output:
 *   Word: The
 *   Word: quick
 *   Word: brown
 *   Word: fox
 *
 * Hints:
 *   - char str[] = "The quick brown fox";
 *   - char *saveptr;
 *   - char *token = strtok_r(str, " ", &saveptr);
 *   - while (token != NULL) { printf("Word: %s\n", token); token = strtok_r(NULL, " ", &saveptr); }
 *   - #include <string.h>, <stdio.h>, <stdlib.h>
 */
