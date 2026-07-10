/*
 * 03_fclose_cleanup.c — every fopen needs a matching fclose
 *
 * fclose(fp) flushes buffers, closes the OS file handle, and
 * frees the FILE struct.  Leaking FILE* handles wastes resources
 * and can exhaust the system's per-process file-descriptor limit.
 *
 * This demo shows the correct pattern and then deliberately
 * leaks one handle so you can observe the problem.
 */

#include <stdio.h>

int main(void) {
    FILE *fp = NULL;

    /* ---- Correct: open, work, close ---- */
    fp = fopen("config", "w");
    if (!fp) {
        puts("[FAIL] fopen failed for config.");
        return 1;
    }
    fprintf(fp, "theme=dark\nversion=1\n");
    fclose(fp);
    fp = NULL;               /* defensive: dangling pointer guard */
    puts("[OK] config written and closed.");

    /* ---- Oops: forgot to fclose (resource leak) ---- */
    fp = fopen("leaked.txt", "w");
    if (!fp) {
        puts("[FAIL] fopen failed for leaked.txt.");
        return 1;
    }
    fprintf(fp, "I will never be closed...\n");
    /* fclose(fp) missing — the handle leaks here */
    puts("[WARN] leaked.txt opened but NOT closed — resource leaked.");

    /* ---- Clean up the files at least ---- */
    remove("config");
    remove("leaked.txt");

    return 0;
}
/*
 * Thinking in C:
 * fopen acquires a resource; fclose releases it.
 * Every successful fopen must eventually have a matching fclose.
 * A leaked FILE* may cause data loss (unflushed buffers) and
 * can make subsequent fopen calls fail if the process limit is hit.
 */
