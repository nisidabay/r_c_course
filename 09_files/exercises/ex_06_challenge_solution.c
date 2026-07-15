/*
 * Mini-Challenge 06: File Reader — Line Count & Longest Line — SOLUTION
 *
 * Read a text file, count lines, find the longest line.
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 * Uses strlen() from <string.h> for length, manual copy loop for safety.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024

int main(void) {
    char buf[MAX_LINE];
    char longest[MAX_LINE];
    FILE *fp;
    int line_count = 0;
    int max_len = 0;

    fp = fopen("sample.txt", "r");
    if (!fp) {
        perror("fopen sample.txt");
        return EXIT_FAILURE;
    }

    while (fgets(buf, sizeof buf, fp)) {
        line_count++;
        size_t len = strlen(buf);

        if ((int)len > max_len) {
            max_len = (int)len;
            /* Manual copy — no strcpy */
            for (size_t i = 0; i <= len; i++) {
                longest[i] = buf[i];
            }
        }
    }

    fclose(fp);

    printf("Total lines: %d\n", line_count);
    printf("Longest line length: %d\n", max_len);
    printf("Longest line: %s", longest);

    return EXIT_SUCCESS;
}
