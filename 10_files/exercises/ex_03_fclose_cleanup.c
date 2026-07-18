/*
 * Exercise 03 — fclose and Cleanup
 *
 * Show proper cleanup: always close files and check for errors.
 *
 * Expected output:
 *   File written and closed successfully.
 *
 * Hints:
 *   - FILE *fp = fopen("test.txt", "w");
 *   - if (fp == NULL) { perror("fopen"); return EXIT_FAILURE; }
 *   - fprintf(fp, "data\n");
 *   - if (fclose(fp) == EOF) { perror("fclose"); return EXIT_FAILURE; }
 *   - printf("File written and closed successfully.\n");
 *   - remove("test.txt");
 *   - #include <stdio.h>, <stdlib.h>, <errno.h>
 */
