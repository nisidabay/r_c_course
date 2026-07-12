/*
 * Challenge: Student Grade Record System
 *
 * Build a small system that manages student records using struct arrays.
 * The program should:
 *   1. Define a Student struct with name, id, and 3 test scores
 *   2. Ask the user how many students to enter (max 10)
 *   3. For each student, read name, id, and 3 test scores
 *   4. Calculate and store the average for each student
 *   5. Display a formatted table of all students with their grades
 *
 * Constraints:
 *   - Use fgets + strtol for ALL input (NO scanf/atoi/atof)
 *   - Use snprintf for string copy (NO strcpy)
 *   - int main(void)
 *   - Compiles with -std=c11
 *   - Student names max 63 chars + null terminator
 *
 * Example output:
 *   How many students? 2
 *
 *   Student 1:
 *   Name: Alice
 *   ID: 101
 *   Scores (3): 85 90 92
 *
 *   Student 2:
 *   Name: Bob
 *   ID: 102
 *   Scores (3): 78 82 88
 *
 *   --- Grade Report ---
 *   #   Name       ID    Score1  Score2  Score3  Average
 *   1   Alice      101   85      90      92      89.0
 *   2   Bob        102   78      82      88      82.7
 */

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10
#define MAX_NAME     64
#define NUM_SCORES   3

/* TODO: Define a Student struct with:
 *   - char name[MAX_NAME]
 *   - int id
 *   - int scores[NUM_SCORES]
 *   - double average
 */
typedef struct {
    char name[MAX_NAME];
    int id;
    int scores[NUM_SCORES];
    double average;
} Student;


int main(void) {
    char buf[64];
    int count = 0;

    printf("How many students? ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return EXIT_FAILURE;
    buf[strcspn(buf, "\n")] = '\0';

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

    /* TODO: Declare an array of Student structs of size 'count' */
    Student students[count];

    /* TODO: Loop to read data for each student */
    for (int i = 0; i < count; i++) {
        printf("\nStudent %d:\n", i + 1);

        /* Name */
        printf("Name: ");
        if (fgets(students[i].name, sizeof students[i].name, stdin) == NULL)
            return EXIT_FAILURE;
        students[i].name[strcspn(students[i].name, "\n")] = '\0';

        /* ID */
        printf("ID: ");
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return EXIT_FAILURE;
        buf[strcspn(buf, "\n")] = '\0';
        errno = 0;
        val = strtol(buf, &endptr, 10);
        if (errno == ERANGE || endptr == buf || *endptr != '\0') {
            printf("Invalid ID.\n");
            return EXIT_FAILURE;
        }
        students[i].id = (int)val;

        /* Scores */
        printf("Scores (%d): ", NUM_SCORES);
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return EXIT_FAILURE;
        buf[strcspn(buf, "\n")] = '\0';

        char *p = buf;
        for (int s = 0; s < NUM_SCORES; s++) {
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
            students[i].scores[s] = (int)val;
            p = endptr;
        }
        /* Check trailing junk */
        while (*p == ' ') p++;
        if (*p != '\0') {
            printf("Invalid scores.\n");
            return EXIT_FAILURE;
        }

        /* Calculate average */
        int sum = students[i].scores[0] + students[i].scores[1] + students[i].scores[2];
        students[i].average = sum / (double)NUM_SCORES;
    }

    /* TODO: Display the grade report table */
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
