/*
 * Challenge: Student Grade Record System — SOLUTION
 *
 * Build a small system that manages student records using struct arrays.
 * Uses fgets+strtol for input, snprintf for string copy, and VLA for
 * the student array.
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10
#define MAX_NAME     64
#define NUM_SCORES   3

typedef struct {
    char   name[MAX_NAME];
    int    id;
    int    scores[NUM_SCORES];
    double average;
} Student;

int main(void) {
    char buf[64];
    int count = 0;

    printf("How many students? ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return EXIT_FAILURE;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;   /* input was truncated — drain residue */
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    char *endptr;
    errno = 0;
    long val = strtol(buf, &endptr, 10);
    if (errno == ERANGE || endptr == buf || *endptr != '\0') {
        printf("Invalid count (1-%d).\n", MAX_STUDENTS);
        return EXIT_FAILURE;
    }
    if (val < 1 || val > MAX_STUDENTS) {
        printf("Invalid count (1-%d).\n", MAX_STUDENTS);
        return EXIT_FAILURE;
    }
    count = (int)val;

    Student students[count];

    /* Read data for each student */
    for (int i = 0; i < count; i++) {
        printf("\nStudent %d:\n", i + 1);

        /* Read name */
        printf("Name: ");
        if (fgets(students[i].name, sizeof students[i].name, stdin) == NULL)
            return EXIT_FAILURE;

        {
            size_t ln = strlen(students[i].name);
            if (ln > 0 && students[i].name[ln - 1] != '\n') {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            } else if (ln > 0) {
                students[i].name[ln - 1] = '\0';
            }
        }

        /* Read ID */
        printf("ID: ");
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return EXIT_FAILURE;

        {
            size_t ln = strlen(buf);
            if (ln > 0 && buf[ln - 1] != '\n') {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            } else if (ln > 0) {
                buf[ln - 1] = '\0';
            }
        }

        errno = 0;
        val = strtol(buf, &endptr, 10);
        if (errno == ERANGE || endptr == buf || *endptr != '\0') {
            printf("Invalid ID.\n");
            return EXIT_FAILURE;
        }
        if (val < INT_MIN || val > INT_MAX) {
            printf("Invalid ID.\n");
            return EXIT_FAILURE;
        }
        students[i].id = (int)val;

        /* Read 3 scores */
        printf("Scores (%d): ", NUM_SCORES);
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return EXIT_FAILURE;

        {
            size_t ln = strlen(buf);
            if (ln > 0 && buf[ln - 1] != '\n') {
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
            } else if (ln > 0) {
                buf[ln - 1] = '\0';
            }
        }

        /* Parse three scores */
        char *p = buf;
        for (int s = 0; s < NUM_SCORES; s++) {
            /* skip leading spaces */
            while (*p == ' ') p++;
            if (*p == '\0') {
                printf("Invalid scores.\n");
                return EXIT_FAILURE;
            }
            errno = 0;
            val = strtol(p, &endptr, 10);
            if (errno == ERANGE || endptr == p) {
                printf("Invalid scores.\n");
                return EXIT_FAILURE;
            }
            if (val < INT_MIN || val > INT_MAX) {
                printf("Invalid scores.\n");
                return EXIT_FAILURE;
            }
            students[i].scores[s] = (int)val;
            p = endptr;
        }
        /* Check no trailing junk */
        while (*p == ' ') p++;
        if (*p != '\0') {
            printf("Invalid scores.\n");
            return EXIT_FAILURE;
        }

        /* Calculate average */
        int sum = students[i].scores[0]
                + students[i].scores[1]
                + students[i].scores[2];
        students[i].average = sum / (double)NUM_SCORES;
    }

    /* Display grade report */
    printf("\n--- Grade Report ---\n");
    printf("#   %-12s %-5s  %-6s  %-6s  %-6s  Average\n",
           "Name", "ID", "Score1", "Score2", "Score3");
    for (int i = 0; i < count; i++) {
        printf("%-3d %-12s %-5d  %-6d  %-6d  %-6d  %.1f\n",
               i + 1,
               students[i].name,
               students[i].id,
               students[i].scores[0],
               students[i].scores[1],
               students[i].scores[2],
               students[i].average);
    }

    return EXIT_SUCCESS;
}
