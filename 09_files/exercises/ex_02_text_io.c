/*
 * Exercise 02: Text I/O with fgets and fprintf
 *
 * Concept: Reading with fgets and writing with fprintf.
 *
 * Fill in the blanks to complete a program that writes a list of names
 * to a file, then reads them back and prints them.
 *
 * Rules:
 *   - fgets(buf, size, fp) reads one line (keeps \\n if room).
 *   - fgets returns NULL on EOF or error.
 *   - fprintf(fp, fmt, ...) writes formatted text.
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>

int main(void) {
    char line[128];
    FILE *fp;

    /* ---- Write three names to names.txt ---- */
    fp = fopen("names.txt", /*@*/);
    if (/*@*/) {
        puts("[FAIL] Could not open names.txt for writing.");
        return 1;
    }

    /*@*/(fp, "Alice\\n");
    /*@*/(fp, "Bob\\n");
    /*@*/(fp, "Charlie\\n");

    /*@*/;
    puts("[OK] Wrote 3 names to names.txt.");

    /* ---- Read them back ---- */
    fp = fopen("names.txt", /*@*/);
    if (/*@*/) {
        puts("[FAIL] Could not open names.txt for reading.");
        return 1;
    }

    puts("--- Names in file ---");
    int count = 0;
    while (/*@*/(line, sizeof line, fp)) {
        printf("Name %d: %s", count + 1, line);
        /*@*/;
    }
    puts("---------------------");
    printf("[OK] Read %d names from names.txt.\\n", count);

    fclose(fp);
    remove("names.txt");

    return 0;
}
