/*
 * 05_file_ops.c — remove(), rename(), and checking file existence
 *
 * remove(path)  — deletes a file; returns 0 on success, -1 on error.
 * rename(old, new) — renames (moves) a file; returns 0 or -1.
 *
 * There is no standard "file exists" function in C11. The idiomatic
 * approach is to try fopen with "r" — if it returns non-NULL the file
 * exists; if NULL it doesn't (or isn't readable).
 */

#include <stdio.h>

int main(void) {
    FILE *fp = NULL;

    /* ---- Create a file to work with ---- */
    fp = fopen("original.txt", "w");
    if (!fp) {
        perror("fopen original.txt");
        return 1;
    }
    fprintf(fp, "Temporary data\n");
    fclose(fp);
    puts("[OK] Created original.txt");

    /* ---- Check if a file exists (fopen + fclose pattern) ---- */
    fp = fopen("original.txt", "r");
    if (fp) {
        puts("[OK] original.txt exists.");
        fclose(fp);
    } else {
        puts("[FAIL] original.txt should exist but doesn't.");
        return 1;
    }

    fp = fopen("ghost.txt", "r");
    if (fp) {
        puts("[UNEXPECTED] ghost.txt exists when it shouldn't.");
        fclose(fp);
    } else {
        puts("[OK] ghost.txt does not exist (fopen returned NULL).");
    }

    /* ---- Rename ---- */
    if (rename("original.txt", "renamed.txt") == 0) {
        puts("[OK] Renamed original.txt → renamed.txt");
    } else {
        perror("rename");
        return 1;
    }

    /* ---- Remove (delete) ---- */
    if (remove("renamed.txt") == 0) {
        puts("[OK] Deleted renamed.txt");
    } else {
        perror("remove");
        return 1;
    }

    /* Verify it's gone */
    fp = fopen("renamed.txt", "r");
    if (!fp) {
        puts("[OK] Confirmed: renamed.txt no longer exists.");
    } else {
        puts("[WARN] renamed.txt still exists after remove.");
        fclose(fp);
    }

    return 0;
}
/*
 * Thinking in C:
 * remove and rename are simple — 0 means success, -1 means failure.
 * There's no built-in "exists" function; fopen+"r" is the C way.
 * rename can also move files across directories on the same filesystem.
 * Always check return values — file operations are surprisingly fallible.
 */
