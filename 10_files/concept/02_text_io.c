/*
 * 02_text_io.c — reading and writing text files
 *
 * fgets(buf, size, fp)  — reads one line (including \n if room)
 * fprintf(fp, fmt, ...) — writes formatted text to a file
 *
 * fgets returns NULL on EOF or error — always check.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char line[256];

    /* ---- Write three lines to data.txt ---- */
    FILE *fp = fopen("data.txt", "w");
    if (!fp) {
        puts("[FAIL] Could not open data.txt for writing.");
        return EXIT_FAILURE;
    }

    fprintf(fp, "Line one: apples\n");
    fprintf(fp, "Line two: bananas\n");
    fprintf(fp, "Line three: cherries\n");
    fclose(fp);
    puts("[OK] Wrote 3 lines to data.txt");

    /* ---- Read them back with fgets ---- */
    fp = fopen("data.txt", "r");
    if (!fp) {
        puts("[FAIL] Could not open data.txt for reading.");
        return EXIT_FAILURE;
    }

    puts("--- Contents of data.txt ---");
    int line_no = 1;
    while (fgets(line, sizeof line, fp)) {
        printf("Line %d: %s", line_no, line);
        line_no++;
    }
    puts("---------------------------");

    fclose(fp);
    remove("data.txt");

    return EXIT_SUCCESS;
}
/*
 * Thinking in C:
 * fgets and fprintf are the text I/O workhorses.
 * fgets reads until \n, EOF, or the buffer fills — it keeps the \n.
 * fprintf writes to a file the same way printf writes to stdout.
 * Always match every read/write with an fopen → fclose pair.
 */
