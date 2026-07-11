/*
 * Challenge: Student Grade Record System — SOLUTION
 *
 * Build a small system that manages student records using struct arrays.
 * Uses fgets+sscanf for input, snprintf for string copy, and VLA for
 * the student array.
 */

#include <stdio.h>
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

/* Discard characters remaining in stdin after truncated fgets */
static void consume_remaining(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(void) {
    char buf[64];
    int count = 0;

    printf("How many students? ");
    if (fgets(buf, sizeof buf, stdin) == NULL)
        return 1;
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] != '\n')
        consume_remaining();
    if (sscanf(buf, "%d", &count) != 1 || count < 1 || count > MAX_STUDENTS) {
        printf("Invalid count (1-%d).\n", MAX_STUDENTS);
        return 1;
    }

    Student students[count];

    /* Read data for each student */
    for (int i = 0; i < count; i++) {
        printf("\nStudent %d:\n", i + 1);

        /* Read name */
        printf("Name: ");
        if (fgets(students[i].name, sizeof students[i].name, stdin) == NULL)
            return 1;
        /* Strip trailing newline and check for truncation */
        size_t name_len = strlen(students[i].name);
        if (name_len > 0 && students[i].name[name_len - 1] != '\n') {
            consume_remaining();   /* input was truncated */
        } else if (name_len > 0) {
            students[i].name[name_len - 1] = '\0';  /* remove \n */
        }

        /* Read ID */
        printf("ID: ");
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return 1;
        size_t id_len = strlen(buf);
        if (id_len > 0 && buf[id_len - 1] != '\n')
            consume_remaining();
        if (sscanf(buf, "%d", &students[i].id) != 1) {
            printf("Invalid ID.\n");
            return 1;
        }

        /* Read 3 scores */
        printf("Scores (%d): ", NUM_SCORES);
        if (fgets(buf, sizeof buf, stdin) == NULL)
            return 1;
        size_t scores_len = strlen(buf);
        if (scores_len > 0 && buf[scores_len - 1] != '\n')
            consume_remaining();
        if (sscanf(buf, "%d %d %d",
                   &students[i].scores[0],
                   &students[i].scores[1],
                   &students[i].scores[2]) != 3) {
            printf("Invalid scores.\n");
            return 1;
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

    return 0;
}
