/*
 * Exercise 04 — perror
 *
 * Try to open a file that doesn't exist and use perror to print the error.
 *
 * Expected output:
 *   fopen: No such file or directory
 *
 * Hints:
 *   - FILE *fp = fopen("nonexistent.txt", "r");
 *   - if (fp == NULL) { perror("fopen"); return EXIT_FAILURE; }
 *   - perror() prints the error message based on errno
 */
