/*
 * Exercise 03: fclose and Cleanup
 *
 * Concept: Every successful fopen must have a matching fclose.
 *
 * Fill in the blanks to complete a program that opens files, uses them,
 * and properly closes them. One deliberate leak is shown — fix it.
 *
 * Rules:
 *   - fclose(fp) flushes buffers and releases the file handle.
 *   - Set fp = NULL after fclose (defensive programming).
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>

int main(void) {
    FILE *fp = NULL;

    /* ---- Open, write, and close ---- */
    fp = fopen("log.txt", "w");
    if (fp == NULL) { // FIX ME
        puts("[FAIL] Could not open log.txt.");
        return 1;
    }

    fprintf(fp, "Session started\n");
    fclose(fp); // FIX ME
    fp = NULL; // FIX ME
    puts("[OK] log.txt written and closed.");

    /* ---- Open for reading ---- */
    fp = fopen("log.txt", "r");
    if (fp == NULL) { // FIX ME
        puts("[FAIL] Could not open log.txt for reading.");
        return 1;
    }
    puts("[OK] log.txt opened for reading.");

    /* BUG: We forgot to close! Add the missing fclose + NULL. */
    fclose(fp); // FIX ME
    fp = NULL; // FIX ME

    /* ---- Clean up files ---- */
    remove("log.txt");
    puts("[OK] Cleaned up.");

    return 0;
}
