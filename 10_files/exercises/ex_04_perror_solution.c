/*
 * Exercise 04: perror and errno — SOLUTION
 *
 * Concept: perror() and the errno global variable.
 *
 * Safe C Standard: no scanf, no strcpy/strcat/sprintf/atoi/atof.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(void) {
    char line[128];
    FILE *fp;

    /* ---- Try opening a restricted file ---- */
    fp = fopen("/root/secret.txt", "r");
    if (!fp) {
        perror("fopen /root/secret.txt");
        printf("   (errno = %d)\n", errno);
    } else {
        fclose(fp);
    }

    /* ---- Create a file, then simulate a read error ---- */
    fp = fopen("data.txt", "w");
    if (!fp) {
        perror("fopen data.txt");
        return EXIT_FAILURE;
    }
    fprintf(fp, "Hello\nWorld\n");
    fclose(fp);

    fp = fopen("data.txt", "r");
    if (!fp) {
        perror("fopen data.txt for reading");
        return EXIT_FAILURE;
    }

    /* Read the file until EOF */
    while (fgets(line, sizeof line, fp)) {
        /* just reading */
    }

    /* Check if an error occurred during reading */
    if (ferror(fp)) {
        perror("fgets error");
    } else {
        puts("[OK] Reached EOF with no errors.");
    }

    fclose(fp);
    remove("data.txt");

    return EXIT_SUCCESS;
}
