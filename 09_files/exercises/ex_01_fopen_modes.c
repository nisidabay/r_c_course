/*
 * Exercise 01 — fopen Modes
 *
 * Open a file for writing, write a line, close it, then open for reading and print.
 *
 * Expected output:
 *   File written, contents: Hello, file!
 *
 * Hints:
 *   - FILE *fp = fopen("test.txt", "w"); fprintf(fp, "Hello, file!\n"); fclose(fp);
 *   - fp = fopen("test.txt", "r"); char buf[64]; fgets(buf, sizeof(buf), fp);
 *   - printf("File written, contents: %s", buf);
 *   - fclose(fp); remove("test.txt");
 *   - #include <stdio.h>, <stdlib.h>
 */
