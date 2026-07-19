/*
 * Exercise 08 — Time: Date formatter — SOLUTION
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    char buf[128];

    /* ---- Today's date and time ---- */
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    strftime(buf, sizeof buf, "%Y-%m-%d", local);
    printf("Today: %s\n", buf);

    strftime(buf, sizeof buf, "%A, %B %d, %Y", local);
    printf("Long:  %s\n", buf);

    strftime(buf, sizeof buf, "%H:%M:%S", local);
    printf("Time:  %s\n\n", buf);

    /* ---- User-specified date ---- */
    int year, month, day;
    char line[64];

    printf("Enter year:  ");
    if (fgets(line, sizeof line, stdin) == NULL)
        return EXIT_FAILURE;
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        line[len - 1] = '\0';
    }
    char *endptr;
    errno = 0;
    year = (int)strtol(line, &endptr, 10);
    if (errno == ERANGE || endptr == line || *endptr != '\0') {
        fprintf(stderr, "Invalid year\n");
        return EXIT_FAILURE;
    }

    printf("Enter month: ");
    if (fgets(line, sizeof line, stdin) == NULL)
        return EXIT_FAILURE;
    len = strlen(line);
    if (len > 0 && line[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        line[len - 1] = '\0';
    }
    char *endptr_m = NULL;  // separate endptr for month
    errno = 0;
    month = (int)strtol(line, &endptr_m, 10);
    if (errno == ERANGE || endptr_m == line || *endptr_m != '\0') {
        fprintf(stderr, "Invalid month\n");
        return EXIT_FAILURE;
    }

    printf("Enter day:   ");
    if (fgets(line, sizeof line, stdin) == NULL)
        return EXIT_FAILURE;
    len = strlen(line);
    if (len > 0 && line[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else if (len > 0) {
        line[len - 1] = '\0';
    }
    char *endptr_d = NULL;  // separate endptr for day
    errno = 0;
    day = (int)strtol(line, &endptr_d, 10);
    if (errno == ERANGE || endptr_d == line || *endptr_d != '\0') {
        fprintf(stderr, "Invalid day\n");
        return EXIT_FAILURE;
    }

    /* Build a struct tm and let mktime normalise it */
    struct tm target = { 0 };
    target.tm_year = year - 1900;
    target.tm_mon  = month - 1;
    target.tm_mday = day;

    if (mktime(&target) == -1) {
        fprintf(stderr, "Invalid date\n");
        return EXIT_FAILURE;
    }

    strftime(buf, sizeof buf, "%A", &target);
    printf("That date is a %s\n", buf);

    return EXIT_SUCCESS;
}
