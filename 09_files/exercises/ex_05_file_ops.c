/*
 * Exercise 05 — File Operations
 *
 * Copy a file character by character using fgetc and fputc.
 *
 * Expected output:
 *   Copied 26 characters.
 *
 * Hints:
 *   - Create source file with fputs("ABCDEFGHIJKLMNOPQRSTUVWXYZ\n", src);
 *   - Open source for "r", dest for "w"
 *   - int ch; while ((ch = fgetc(src)) != EOF) fputc(ch, dest);
 *   - Count characters as you copy
 *   - fclose both, then remove temp files
 */
