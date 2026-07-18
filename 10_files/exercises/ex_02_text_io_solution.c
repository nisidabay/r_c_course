/*
 * Exercise 02: Text I/O with fgets and fprintf — SOLUTION
 *
 * Concept: Reading with fgets and writing with fprintf.
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[128];
    FILE *fp;

    /* ---- Write three names to names.txt ---- */
    fp = fopen("names.txt", "w");
    if (!fp) {
        puts("[FAIL] Could not open names.txt for writing.");
        return EXIT_FAILURE;
    }

    fprintf(fp, "Alice\n");
    fprintf(fp, "Bob\n");
    fprintf(fp, "Charlie\n");

    fclose(fp);
    puts("[OK] Wrote 3 names to names.txt.");

    /* ---- Read them back ---- */
    fp = fopen("names.txt", "r");
    if (!fp) {
        puts("[FAIL] Could not open names.txt for reading.");
        return EXIT_FAILURE;
    }

    puts("--- Names in file ---");
    int count = 0;
    while (fgets(line, sizeof line, fp)) {
        printf("Name %d: %s", count + 1, line);
        count++;
    }
    puts("---------------------");
    printf("[OK] Read %d names from names.txt.\n", count);

    fclose(fp);
    remove("names.txt");

    return EXIT_SUCCESS;
}
