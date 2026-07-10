/*
 * 04_perror.c — perror() and the errno global variable
 *
 * When a standard library function (fopen, fgets, remove, etc.)
 * fails, it sets the global integer errno to a system-specific
 * error code.  perror("prefix") prints "prefix: <description>".
 *
 * errno is declared in <errno.h>.  Its value is only meaningful
 * immediately after a function reports failure — don't cache it.
 */

#include <stdio.h>
#include <errno.h>

int main(void) {
    char line[256];

    /* ---- fopen failure with perror ---- */
    FILE *fp = fopen("/root/secret_config", "r");
    if (!fp) {
        /* errno tells us WHY — perror prints a human-readable message */
        perror("fopen /root/secret_config");
        printf("   (errno = %d)\n", errno);
    }

    /* ---- Create a file, then demonstrate perror after fgets ---- */
    /* First create the file */
    fp = fopen("data.txt", "w");
    if (!fp) {
        perror("fopen data.txt for writing");
        return 1;
    }
    fprintf(fp, "hello\nworld\n");
    fclose(fp);

    /* Now open for reading */
    fp = fopen("data.txt", "r");
    if (!fp) {
        perror("fopen data.txt for reading");
        return 1;
    }

    /* Read past EOF to trigger fgets returning NULL */
    while (fgets(line, sizeof line, fp)) {
        /* just draining the file */
    }

    if (ferror(fp)) {
        perror("fgets on data.txt");
        printf("   (errno = %d)\n", errno);
    } else {
        puts("[OK] Reached EOF normally (no fgets error).");
    }

    fclose(fp);
    remove("data.txt");

    return 0;
}
/*
 * Thinking in C:
 * errno gives you the numeric reason; perror gives you the English.
 * Always check errno immediately after the failure — another call
 * (even printf) may overwrite it with a different error code.
 * perror's prefix lets you label which operation failed.
 */
