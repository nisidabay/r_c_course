/*
 * Exercise 05: File Operations — SOLUTION
 *
 * Concept: remove(), rename(), and checking file existence via fopen + "r".
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>

int main(void) {
    FILE *fp;

    /* ---- Create a file ---- */
    fp = fopen("original.txt", "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    fprintf(fp, "Temporary content\n");
    fclose(fp);
    puts("[OK] Created original.txt.");

    /* ---- Check if it exists ---- */
    fp = fopen("original.txt", "r");
    if (fp) {
        puts("[OK] original.txt exists.");
        fclose(fp);
    } else {
        puts("[FAIL] original.txt should exist!");
        return 1;
    }

    /* ---- Rename it ---- */
    if (rename("original.txt", "renamed.txt") == 0) {
        puts("[OK] Renamed original.txt -> renamed.txt");
    } else {
        perror("rename");
        return 1;
    }

    /* ---- Check old name no longer exists ---- */
    fp = fopen("original.txt", "r");
    if (!fp) {
        puts("[OK] original.txt no longer exists after rename.");
    } else {
        puts("[FAIL] original.txt should not exist!");
        fclose(fp);
    }

    /* ---- Delete the renamed file ---- */
    if (remove("renamed.txt") == 0) {
        puts("[OK] Deleted renamed.txt.");
    } else {
        perror("remove");
        return 1;
    }

    puts("[OK] All file operations completed successfully.");
    return 0;
}
