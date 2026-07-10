/*
 * Student Database
 * Concepts: structs, typedef, member access, arrays of structs,
 *           structs in functions, string ops, fgets+sscanf
 * Compile: gcc -std=c11 -Wall -Wextra -pedantic student_db.c -o student_db
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* ---------- helper: clear stdin after fgets ---------- */

static void clear_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
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
    int valid;

    /* name */
    printf("Enter name: ");
    if (fgets(buf, sizeof buf, stdin) == NULL) return;
    buf[strcspn(buf, "\n")] = '\0';
    strncpy(s.name, buf, sizeof s.name - 1);
    s.name[sizeof s.name - 1] = '\0';

    /* id */
    do {
        printf("Enter ID: ");
        if (fgets(buf, sizeof buf, stdin) == NULL) return;
        valid = sscanf(buf, "%d", &s.id);
        if (valid != 1) printf("Invalid ID. Try again.\n");
    } while (valid != 1);

    /* scores */
    for (int i = 0; i < 5; i++) {
        do {
            printf("Enter score %d: ", i + 1);
            if (fgets(buf, sizeof buf, stdin) == NULL) return;
            valid = sscanf(buf, "%d", &s.scores[i]);
            if (valid != 1) printf("Invalid score. Try again.\n");
        } while (valid != 1);
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

    char buf[64];
    int search_id, valid;

    do {
        printf("Enter ID to search: ");
        if (fgets(buf, sizeof buf, stdin) == NULL) return;
        valid = sscanf(buf, "%d", &search_id);
        if (valid != 1) printf("Invalid ID. Try again.\n");
    } while (valid != 1);

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

    printf("=== Student Database ===\n");
    printf("a - Add student\n");
    printf("l - List all students\n");
    printf("s - Search by ID\n");
    printf("q - Quit\n");

    for (;;) {
        printf("\nEnter choice: ");
        choice = getchar();
        clear_stdin();

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
            return 0;
        default:
            printf("Unknown option '%c'. Try a/l/s/q.\n", choice);
            break;
        }
    }
}
