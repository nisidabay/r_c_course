/*
 * Exercise 05: File Operations — remove, rename, existence check
 *
 * Concept: remove(), rename(), and checking file existence via fopen + "r".
 *
 * Fill in the blanks to complete a program that creates a file, renames it,
 * checks if various files exist, and deletes files.
 *
 * Rules:
 *   - remove(path) returns 0 on success, -1 on failure.
 *   - rename(old, new) returns 0 on success, -1 on failure.
 *   - Check existence: fopen(path, "r") — if non-NULL, file exists.
 *   - Always fclose after a successful fopen, even for existence checks.
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>

int main(void) {
    FILE *fp;

    /* ---- Create a file ---- */
    fp = fopen("original.txt", "w");
    if (/*@*/) {
        perror("fopen");
        return 1;
    }
    fprintf(fp, "Temporary content\\n");
    fclose(fp);
    puts("[OK] Created original.txt.");

    /* ---- Check if it exists ---- */
    fp = fopen("original.txt", /*@*/);
    if (/*@*/) {
        puts("[OK] original.txt exists.");
        fclose(fp);
    } else {
        puts("[FAIL] original.txt should exist!");
        return 1;
    }

    /* ---- Rename it ---- */
    if (rename("original.txt", "renamed.txt") /*@*/ 0) {
        puts("[OK] Renamed original.txt -> renamed.txt");
    } else {
        perror("rename");
        return 1;
    }

    /* ---- Check old name no longer exists ---- */
    fp = fopen("original.txt", "r");
    if (/*@*/) {
        puts("[OK] original.txt no longer exists after rename.");
    } else {
        puts("[FAIL] original.txt should not exist!");
        fclose(fp);
    }

    /* ---- Delete the renamed file ---- */
    if (/*@*/("renamed.txt") == 0) {
        puts("[OK] Deleted renamed.txt.");
    } else {
        perror("remove");
        return 1;
    }

    puts("[OK] All file operations completed successfully.");
    return 0;
}
