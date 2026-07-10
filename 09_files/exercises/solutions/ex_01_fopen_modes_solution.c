/*
 * Exercise 01: fopen Modes — SOLUTION
 *
 * Concept: fopen modes "r", "w", "a" and NULL-checking.
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>

int main(void) {
    FILE *fp;

    /* ---- Try opening nonexistent file for reading ---- */
    fp = fopen("no_such_file.txt", "r");
    if (!fp) {
        puts("[OK] fopen with \"r\" returned NULL as expected.");
    } else {
        puts("[FAIL] fopen should have returned NULL!");
        fclose(fp);
    }

    /* ---- Create (or truncate) a file for writing ---- */
    fp = fopen("test_data.txt", "w");
    if (!fp) {
        puts("[FAIL] Could not open test_data.txt for writing.");
        return 1;
    }
    puts("[OK] Created test_data.txt with mode \"w\".");
    fclose(fp);

    /* ---- Open the same file for appending ---- */
    fp = fopen("test_data.txt", "a");
    if (!fp) {
        puts("[FAIL] Could not open test_data.txt for appending.");
        return 1;
    }
    puts("[OK] Opened test_data.txt with mode \"a\".");
    fclose(fp);

    /* ---- Re-open existing file for reading ---- */
    fp = fopen("test_data.txt", "r");
    if (!fp) {
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
