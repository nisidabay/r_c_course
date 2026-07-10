/*
 * csv_reader.c — Reads and parses students.csv, displays table + statistics.
 * Uses only concepts from groups 01-09: fopen, fgets, fprintf, fclose, perror,
 * FILE *, struct, sscanf, manual character parsing.
 *
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic csv_reader.c -o csv_reader
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 128
#define NAME_LEN     32

struct Student {
    char name[NAME_LEN];
    int  id;
    int  grade;
};

/* Parse one CSV line (name,id,grade) into a Student struct using manual
 * character parsing. Returns 1 on success, 0 on failure/empty/malformed. */
static int parse_student(const char *line, struct Student *s)
{
    const char *p;
    char        buf[256];
    char       *dst;
    size_t      i, len;

    if (line == NULL || line[0] == '\0')
        return 0;

    len = strlen(line);
    if (len >= sizeof(buf))
        return 0;
    memcpy(buf, line, len + 1);

    /* Strip trailing newline(s) */
    while (len > 0 &&
           (buf[len - 1] == '\n' || buf[len - 1] == '\r'))
        buf[--len] = '\0';

    if (len == 0)
        return 0;

    p = buf;
    i = 0;

    /* --- Field 1 : name (up to ',' or end) --- */
    dst = s->name;
    while (*p != '\0' && *p != ',' && i < NAME_LEN - 1) {
        *dst++ = *p++;
        i++;
    }
    *dst = '\0';
    if (*p == '\0')   /* no more fields — malformed */
        return 0;
    p++;  /* skip ',' */

    /* --- Field 2 : id (digits only) --- */
    i = 0;
    s->id = 0;
    if (*p < '0' || *p > '9')
        return 0;                     /* missing or non-numeric */
    while (*p >= '0' && *p <= '9') {
        s->id = s->id * 10 + (int)(*p - '0');
        p++;
        i++;
    }
    if (i == 0)
        return 0;                     /* no digits at all */
    if (*p == '\0')
        return 0;                     /* missing grade field */
    if (*p != ',')
        return 0;                     /* unexpected character */
    p++;  /* skip ',' */

    /* --- Field 3 : grade (digits only) --- */
    i = 0;
    s->grade = 0;
    if (*p < '0' || *p > '9')
        return 0;                     /* missing or non-numeric */
    while (*p >= '0' && *p <= '9') {
        s->grade = s->grade * 10 + (int)(*p - '0');
        p++;
        i++;
    }
    if (i == 0)
        return 0;                     /* no digits at all */

    /* Reject trailing non-empty content after grade (malformed) */
    if (*p != '\0')
        return 0;

    return 1;   /* success */
}

int main(void)
{
    FILE           *fp;
    char            line[256];
    struct Student  students[MAX_STUDENTS];
    int             count      = 0;
    int             line_no    = 0;
    int             sum        = 0;
    int             max_grade  = -1;
    int             min_grade  = 101;
    double          average    = 0.0;

    /* ── Open CSV ──────────────────────────────────────────── */
    fp = fopen("students.csv", "r");
    if (fp == NULL) {
        perror("fopen(students.csv)");
        return 1;
    }

    /* ── Read & parse ──────────────────────────────────────── */
    while (fgets(line, (int)sizeof(line), fp) != NULL) {
        line_no++;
        if (count >= MAX_STUDENTS) {
            fprintf(stderr, "Warning: too many students, truncating at %d.\n",
                    MAX_STUDENTS);
            break;
        }
        if (!parse_student(line, &students[count])) {
            fprintf(stderr, "Skipping malformed/empty line %d: %s",
                    line_no, line);
            continue;
        }
        count++;
    }

    fclose(fp);

    /* ── No data guard ─────────────────────────────────────── */
    if (count == 0) {
        fprintf(stderr, "No valid student records found.\n");
        return 1;
    }

    /* ── Print table header ────────────────────────────────── */
    printf("\n%-4s  %-20s  %-6s  %-5s\n", "No.", "Name", "ID", "Grade");
    printf("----  --------------------  ------  -----\n");

    /* ── Print rows & aggregate ────────────────────────────── */
    for (int i = 0; i < count; i++) {
        int g = students[i].grade;
        printf("%-4d  %-20s  %-6d  %-5d\n",
               i + 1, students[i].name, students[i].id, g);
        sum += g;
        if (g > max_grade) max_grade = g;
        if (g < min_grade) min_grade = g;
    }

    average = (double)sum / count;

    /* ── Statistics ────────────────────────────────────────── */
    printf("\n--- Statistics ---\n");
    printf("Total students : %d\n", count);
    printf("Average grade  : %.2f\n", average);
    printf("Maximum grade  : %d\n", max_grade);
    printf("Minimum grade  : %d\n", min_grade);
    printf("\n");

    return 0;
}
