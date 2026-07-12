/*
 * 01_fopen_modes.c — fopen modes and NULL-checking
 *
 * fopen(path, mode) opens a file and returns a FILE* pointer.
 * On failure it returns NULL — you MUST always check this.
 *
 * Modes shown:
 *   "r" — read (file must exist, or NULL)
 *   "w" — write (creates or truncates)
 *   "a" — append (creates or appends)
 *
 * Problem first: trying "r" on a file that doesn't exist → NULL.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* ---- Fail-first: open non-existent file for reading ---- */
    FILE *fp = fopen("nonexistent_data.txt", "r");
    if (!fp) {
        puts("[FAIL] fopen with \"r\" returned NULL — file does not exist.");
        /* perror is introduced in a later concept; we keep it simple here */
    } else {
        fclose(fp);
    }

    /* ---- Create (or truncate) a file for writing ---- */
    fp = fopen("config", "w");
    if (!fp) {
        puts("[FAIL] fopen with \"w\" returned NULL — cannot continue.");
        return EXIT_FAILURE;
    }
    puts("[OK] fopen with \"w\" — created/truncated 'config'.");
    fclose(fp);

    /* ---- Open existing file for appending ---- */
    fp = fopen("config", "a");
    if (!fp) {
        puts("[FAIL] fopen with \"a\" returned NULL.");
        return EXIT_FAILURE;
    }
    puts("[OK] fopen with \"a\" — opened 'config' for appending.");
    fclose(fp);

    /* ---- Re-open existing file for reading ---- */
    fp = fopen("config", "r");
    if (!fp) {
        puts("[FAIL] fopen with \"r\" returned NULL on existing file.");
        return EXIT_FAILURE;
    }
    puts("[OK] fopen with \"r\" — opened existing 'config' for reading.");
    fclose(fp);

    /* Clean up */
    remove("config");

    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * fopen is your gateway to files — but it's a fallible gateway.
 * NULL is its way of saying "I couldn't do that." Check it every time.
 * "r" demands the file exists; "w" and "a" will create it if needed.
 */
