/*
 * Exercise 11 — errno — SOLUTION
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * safe_strtol — parse a string into a long with errno validation.
 * Returns 0 on success, -1 on error.  Stores result in *out on success.
 */
int safe_strtol(const char *str, long *out)
{
    if (str == NULL || *str == '\0')
        return -1;

    errno = 0;
    char *endptr;
    long val = strtol(str, &endptr, 10);

    if (errno == ERANGE)
        return -1;                    /* overflow / underflow */
    if (endptr == str || *endptr != '\0')
        return -1;                    /* no digits or trailing garbage */

    if (out != NULL)
        *out = val;
    return 0;
}

/*
 * open_config — open "config.txt" with proper error reporting.
 */
FILE *open_config(void)
{
    errno = 0;
    FILE *fp = fopen("config.txt", "r");
    if (fp == NULL) {
        perror("open_config");
        return NULL;
    }
    return fp;
}

int main(void)
{
    printf("=== errno Exercise ===\n\n");

    /* Test safe_strtol */
    const char *tests[] = {"42", "-1", "999999999999999999999", "abc", "12xyz", NULL};
    for (int i = 0; tests[i] != NULL; i++) {
        long result;
        int rc = safe_strtol(tests[i], &result);
        printf("safe_strtol(\"%s\") => ", tests[i]);
        if (rc == 0)
            printf("%ld\n", result);
        else
            printf("ERROR\n");
    }

    /* Test open_config */
    printf("\nOpening 'config.txt' (probably doesn't exist):\n");
    FILE *fp = open_config();
    if (fp)
        fclose(fp);

    return EXIT_SUCCESS;
}
