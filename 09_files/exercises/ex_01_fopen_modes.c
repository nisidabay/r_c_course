/*
 * Exercise 01: fopen Modes
 *
 * Concept: fopen modes "r", "w", "a" and NULL-checking.
 *
 * Fill in the blanks (marked FIX ME) to complete the program.
 * The program opens a file with various modes and prints status messages.
 *
 * Rules:
 *   - Always check if fopen returned NULL.
 *   - "r" — read (file must exist)
 *   - "w" — write (creates or truncates)
 *   - "a" — append (creates or appends)
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>

int main(void) {
    FILE *fp;

    /* ---- Try opening nonexistent file for reading ---- */
    fp = fopen("no_such_file.txt", "r"); // FIX ME
    if (fp == NULL) { // FIX ME
        puts("[OK] fopen with \"r\" returned NULL as expected.");
    } else {
        puts("[FAIL] fopen should have returned NULL!");
        fclose(fp);
    }

    /* ---- Create (or truncate) a file for writing ---- */
    fp = fopen("test_data.txt", "w"); // FIX ME
    if (fp == NULL) { // FIX ME
        puts("[FAIL] Could not open test_data.txt for writing.");
        return 1;
    }
    puts("[OK] Created test_data.txt with mode \"w\".");
    fclose(fp); // FIX ME

    /* ---- Open the same file for appending ---- */
    fp = fopen("test_data.txt", "a"); // FIX ME
    if (!fp) {
        puts("[FAIL] Could not open test_data.txt for appending.");
        return 1;
    }
    puts("[OK] Opened test_data.txt with mode \"a\".");
    fclose(fp);

    /* ---- Re-open existing file for reading ---- */
    fp = fopen("test_data.txt", "r"); // FIX ME
    if (fp == NULL) { // FIX ME
        puts("[FAIL] Could not re-open test_data.txt for reading.");
        return 1;
    }
    puts("[OK] Re-opened test_data.txt with mode \"r\".");
    fclose(fp);

    /* ---- Clean up ---- */
    remove("test_data.txt");
    puts("[OK] Cleaned up test_data.txt.");

    return 0;
}
