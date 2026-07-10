/*
 * Exercise 04: perror and errno
 *
 * Concept: When a file operation fails, errno gives the error code
 *          and perror("prefix") prints a human-readable message.
 *
 * Fill in the blanks to complete a program that attempts to open a
 * protected file, uses perror to describe the failure, then creates
 * a file and safely reads from it.
 *
 * Rules:
 *   - Include <errno.h> to use errno.
 *   - perror("prefix") prints: "prefix: <error description>"
 *   - Check errno immediately after failure — it may be overwritten.
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>
/*@*/

int main(void) {
    char line[128];
    FILE *fp;

    /* ---- Try opening a restricted file ---- */
    fp = fopen("/root/secret.txt", "r");
    if (/*@*/) {
        /*@*/("fopen /root/secret.txt");
        printf("   (errno = %d)\\n", /*@*/);
    } else {
        fclose(fp);
    }

    /* ---- Create a file, then simulate a read error ---- */
    fp = fopen("data.txt", "w");
    if (!fp) {
        perror("fopen data.txt");
        return 1;
    }
    fprintf(fp, "Hello\\nWorld\\n");
    fclose(fp);

    fp = fopen("data.txt", "r");
    if (!fp) {
        perror("fopen data.txt for reading");
        return 1;
    }

    /* Read the file until EOF */
    while (fgets(line, sizeof line, fp)) {
        /* just reading */
    }

    /* Check if an error occurred during reading */
    if (/*@*/(fp)) {
        perror("fgets error");
    } else {
        puts("[OK] Reached EOF with no errors.");
    }

    fclose(fp);
    remove("data.txt");

    return 0;
}
