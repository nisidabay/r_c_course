/*
 * Student Database
 * Concepts: structs, typedef, member access, arrays of structs,
 *           structs in functions, string ops, fgets+strtol
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic student_db.c -o student_db
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- helper: drain stdin residue ---------- */

static void consume_remaining(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ---------- struct definition ---------- */

typedef struct {
    char name[64];
    int  id;
    int  scores[5];
    double avg;
} Student;

/* ---------- globals ---------- */

static Student db[100];
static size_t  count = 0;

/* ---------- helper: read an integer from stdin with full validation ---------- */

static int read_int(const char *prompt, int *out)
{
    char buf[64];
    int valid;

    do {
        printf("%s", prompt);
        if (fgets(buf, sizeof buf, stdin) == NULL) return 0;

        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] != '\n') {
            consume_remaining();
        } else if (len > 0) {
            buf[len - 1] = '\0';
        }

        char *endptr;
        errno = 0;
        long val = strtol(buf, &endptr, 10);
        if (errno == ERANGE || endptr == buf || *endptr != '\0') {
            printf("Invalid input. Try again.\n");
            valid = 0;
        } else if (val < INT_MIN || val > INT_MAX) {
            printf("Out of range. Try again.\n");
            valid = 0;
        } else {
            *out = (int)val;
            valid = 1;
        }
    } while (!valid);
    return 1;
}

/* ---------- menu actions ---------- */

static void add_student(void)
{
    if (count >= 100) {
        printf("Database is full.\n");
        return;
    }

    Student s;
    char buf[128];

    /* name */
    printf("Enter name: ");
    if (fgets(buf, sizeof buf, stdin) == NULL) return;

    {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] != '\n') {
            consume_remaining();
        } else if (len > 0) {
            buf[len - 1] = '\0';
        }
    }
    strncpy(s.name, buf, sizeof s.name - 1);
    s.name[sizeof s.name - 1] = '\0';

    /* id */
    if (!read_int("Enter ID: ", &s.id)) return;

    /* scores */
    for (int i = 0; i < 5; i++) {
        char prompt[32];
        snprintf(prompt, sizeof prompt, "Enter score %d: ", i + 1);
        if (!read_int(prompt, &s.scores[i])) return;
    }

    /* calculate average */
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += s.scores[i];
    }
    s.avg = sum / 5.0;

    db[count] = s;
    count++;
    printf("Student added.\n");
}

static void list_all(void)
{
    if (count == 0) {
        printf("No students in database.\n");
        return;
    }

    printf("\n%-4s  %-20s  %s\n", "ID", "Name", "Avg");
    printf("----  --------------------  ------\n");
    for (size_t i = 0; i < count; i++) {
        printf("%-4d  %-20s  %.2f\n", db[i].id, db[i].name, db[i].avg);
    }
    printf("\n");
}

static void search_by_id(void)
{
    if (count == 0) {
        printf("No students in database.\n");
        return;
    }

    int search_id;
    if (!read_int("Enter ID to search: ", &search_id)) return;

    for (size_t i = 0; i < count; i++) {
        if (db[i].id == search_id) {
            printf("\nName:   %s\n", db[i].name);
            printf("ID:     %d\n", db[i].id);
            printf("Scores:");
            for (int j = 0; j < 5; j++) {
                printf(" %d", db[i].scores[j]);
            }
            printf("\n");
            printf("Avg:    %.2f\n", db[i].avg);
            return;
        }
    }

    printf("Student with ID %d not found.\n", search_id);
}

/* ---------- main ---------- */

int main(void)
{
    char choice;
    char buf[64];

    printf("=== Student Database ===\n");
    printf("a - Add student\n");
    printf("l - List all students\n");
    printf("s - Search by ID\n");
    printf("q - Quit\n");

    for (;;) {
        printf("\nEnter choice: ");
        if (fgets(buf, sizeof buf, stdin) == NULL) break;
        choice = buf[0];

        switch (choice) {
        case 'a':
            add_student();
            break;
        case 'l':
            list_all();
            break;
        case 's':
            search_by_id();
            break;
        case 'q':
            printf("Goodbye.\n");
            return EXIT_SUCCESS;
        default:
            printf("Unknown option '%c'. Try a/l/s/q.\n", choice);
            break;
        }
    }
    return EXIT_SUCCESS;
}
